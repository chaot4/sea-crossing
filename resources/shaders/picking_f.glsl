/*---------------------------------------------------------------------------------------------------
File: picking_f.glsl
Author: Michael Becher
Date of (presumingly) last edit: 13.09.2013

Description: Fragment shader for picking. Ouput the id of rendered objects into
					an integer (requiring a single channel colour attachment)
---------------------------------------------------------------------------------------------------*/
#version 330

in int id;

out uint frag_colour;

void main()
{
	frag_colour = id;
}