/*---------------------------------------------------------------------------------------------------
FFile: surface_lighting_f.glsl
Author: Michael Becher
Date of (presumingly) last edit: 26.08.2013

Description: Standard fragment shader for lighting calculations of opaque surfaces.
			 Based on the Cook-Torrance BRDF.
---------------------------------------------------------------------------------------------------*/
#version 330

#define PI 3.1415926535

uniform sampler2D diffuse_tx2D;
uniform sampler2D specular_tx2D;
uniform sampler2D roughness_tx2D;
uniform sampler2D normal_tx2D;

uniform vec4 light_colour;

in vec3 position;
in vec4 colour;
in vec2 uv_coord;
in vec3 viewer_direction;
in vec3 light_direction;
in vec3 normal;
in vec3 tangent;
in vec3 bitangent;

out vec4 fragColour;

vec3 phongShading(in float specFactor ,in vec3 sColour , in vec3 sNormal, in vec3 lightDir, in vec4 light_colour)
{
	vec3 n = normalize(sNormal);
	vec3 reflection = reflect(-normalize(lightDir), n);

	return light_colour.w *
		( sColour*max( dot(normalize(lightDir), n), 0.0)) +
			(specFactor*light_colour.xyz*pow(max(dot(reflection,normalize(viewer_direction)),0.0),55.0) );
}

vec3 cookTorranceShading(in vec3 surface_albedo, in vec3 surface_specular_color, in float surface_roughness,
							in vec3 surface_normal, in vec3 light_direction, in vec3 viewer_direction, in vec3 light_colour)
{
	vec3 halfway = normalize(light_direction + viewer_direction);
	float n_dot_h = dot(surface_normal,halfway);
	float n_dot_l = dot(surface_normal,light_direction);
	float n_dot_v = dot(surface_normal,viewer_direction);
	float v_dot_h = dot(viewer_direction,halfway);
	float l_dot_h = dot(light_direction,halfway);
	
	/*	Compute Fresnel term using the Schlick approximation */
	vec3 fresnel_term = mix(surface_specular_color, vec3(1.0) , pow(l_dot_h,5.0) );
	
	/*	Compute geometric attenuation */
	float g_1 = 2.0/(1.0 + sqrt(1.0 + (pow(surface_roughness,2.0)*(1.0 - pow(n_dot_v,2.0))/pow(n_dot_v,2.0))));
	float g_2 = 2.0/(1.0 + sqrt(1.0 + (pow(surface_roughness,2.0)*(1.0 - pow(n_dot_l,2.0))/pow(n_dot_l,2.0))));
	float geometry_term = g_1*g_2;
	//	float geometry_term = min( min(1.0, (2.0*n_dot_h*n_dot_v)/v_dot_h) , (2.0*n_dot_h*n_dot_l)/v_dot_h );
	
	/*	Compute microfacet normal distrubution term using GGX distribution by Walter et al (2007) */
	float distribution_term = (surface_roughness)/
								(PI*pow(pow(n_dot_h,2.0)*(pow(surface_roughness,2.0)-1.0)+1.0 , 2.0));
	//	/*	Beckman distribution */
	//	float distribution_term = exp( -(1.0-pow(n_dot_h,2.0))/(pow(surface_roughness,2.0)*pow(n_dot_h,2.0)) )/
	//								(PI*pow(surface_roughness,2.0)*pow(n_dot_h,4.0));
								
	/*	Compute Cook Torrance BRDF */
	vec3 specular_brdf = (fresnel_term*geometry_term*distribution_term)/(4.0*n_dot_l*n_dot_v);
	
	/*	"Compute" diffuse lambertian BRDF and */
	vec3 diffuse_brdf = (vec3(1.0)-specular_brdf)*(surface_albedo/PI);

	vec3 surfance_reflectance = light_colour * (diffuse_brdf+specular_brdf) * max(0.0,n_dot_l);

	return surfance_reflectance;
}

void main()
{
	fragColour = vec4(1.0);
	vec3 tLightDirection;

	/*	Fetch colour from diffuse map and blend it with vertex colour */
	vec3 tColour = texture(diffuse_tx2D, uv_coord).xyz;
	//tColour = mix(tColour,colour.xyz,colour.w);

	/*	Fetch specular color from specular map */
	vec3 tSpecColour = texture(specular_tx2D, uv_coord).xyz;
	
	/*	Fetch roughness from roughness map */
	float tRoughness = texture(roughness_tx2D, uv_coord).x;

	/*	Fetch normal vector from normal map */
	vec3 tNormal = ((texture(normal_tx2D, uv_coord).xyz)*2.0)-1.0;
	//vec3 tNormal = texture2D(normal_tx2D, uv_coord).xyz;

	/*	Calculate Cook Torrance shading */
	fragColour = vec4( cookTorranceShading(tColour,tSpecColour,tRoughness,
											tNormal, light_direction, viewer_direction, light_colour.xyz), 1.0 );

	/*	Let's do some debugging */
	//fragColour = vec4(vec3(tSpecFactor),1.0);
}