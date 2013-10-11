/*---------------------------------------------------------------------------------------------------
File: picking_v.glsl
Author: Michael Becher
Date of (presumingly) last edit: 13.09.2013

Description: Vertex shader for picking. Basically a pass trough shader.
---------------------------------------------------------------------------------------------------*/
#version 330

/*	Support handling for up to 256 instances, and reserve a fixed amount of uniforms for it */
uniform mat4 model_view_projection_matrix[256];

/*	Every instance has a specific id */
uniform int entity_id[256];

in vec3 v_position;

out int id;

void main()
{
	id = entity_id[gl_InstanceID];
	
	gl_Position =  model_view_projection_matrix[gl_InstanceID] * vec4(v_position,1.0);
}