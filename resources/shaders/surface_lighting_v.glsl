/*---------------------------------------------------------------------------------------------------
File: surface_lighting_v.glsl
Author: Michael Becher
Date of (presumingly) last edit: 26.08.2013

Description: Standard vertex shader for lighting calculations of opaque surfaces.
---------------------------------------------------------------------------------------------------*/
#version 330

uniform mat3 normal_matrix;
uniform mat4 view_matrix;
uniform mat4 model_view_matrix;
uniform mat4 model_view_projection_matrix;

uniform vec3 light_position;

in vec3 v_position;
in vec3 v_normal;
in vec3 v_tangent;
in vec3 v_bitangent;
in vec4 v_colour;
in vec2 v_uv_coord;

out vec3 position;
out vec4 colour;
out vec2 uv_coord;
out vec3 viewer_direction;
out vec3 light_direction;
out vec3 normal;
out vec3 tangent;
out vec3 bitangent;

void main()
{
	/*	Just to be on the safe side, normalize input vectors again */
	normal = normalize(v_normal);
	tangent = normalize(v_tangent);
	bitangent = normalize(v_bitangent);
	
	/*	Transform input vectors into view space */
	normal = normalize(normal_matrix * normal);
	tangent = normalize(normal_matrix * tangent);
	bitangent = normalize(normal_matrix * bitangent);
	//bitangent = -normalize( cross(normal, tangent) );// * v_tangent.w;

	/*	Compute transformation matrix for tangent space transformation */
	mat3 tangentSpaceMatrix = mat3(
		tangent.x, bitangent.x, normal.x,
		tangent.y, bitangent.y, normal.y,
		tangent.z, bitangent.z, normal.z);
	
	/*	Transform vertex position to view space */
	position = (model_view_matrix * vec4(v_position,1.0)).xyz;
	
	/*	Compute direction to the viewer/camer and light source into tangent space */
	viewer_direction = normalize(tangentSpaceMatrix * normalize( -position ));
	light_direction = normalize(tangentSpaceMatrix * normalize((view_matrix * vec4(light_position,1.0)).xyz - position));
	
	colour = v_colour;
	uv_coord = v_uv_coord;
	
	gl_Position =  model_view_projection_matrix * vec4(v_position, 1);
}