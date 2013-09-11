#include "controls.h"

Controls* Controls::activeInstance;

void Controls::updateCamera(GLFWwindow *window, Scene *scene)
{
	// TODO: USE ACTUAL LOOK_AT POINT FOR ORBITAL CAMERA

	/*	Get current cursor position on the screen */
	double pos_x, pos_y;
	glfwGetCursorPos(window,&pos_x,&pos_y);
	glm::vec2 currentCursorPosition(pos_x,pos_y);

	/*	Register cursor movement if the right mouse button is pressed */
	glm::vec2 cursor_movement;
	if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
		cursor_movement = (latest_cursor_position-currentCursorPosition)*0.1f;

	/*	Get pointer to active camera */
	SceneCamera* scene_camera_ptr = scene->getActiveCamera();

	/*	Update camera position */
	glm::vec4 cam_position = glm::vec4(scene_camera_ptr->getPosition(),1.0);
	glm::vec4 new_position = glm::rotate(glm::mat4(1.0), cursor_movement.x, y_axis)
								* glm::rotate(glm::mat4(1.0), cursor_movement.y, scene_camera_ptr->computeRightHandVector()) 
								* cam_position;
	scene_camera_ptr->setPosition(glm::vec3(new_position));

	/*	Update camera oritentation */
	glm::quat cam_orientation = scene_camera_ptr->getOrientation();
	/*	First, global rotation around y-axis */
	glm::quat new_orientation = glm::normalize(glm::rotate(glm::quat(), cursor_movement.x, y_axis)) * cam_orientation;
	scene_camera_ptr->setOrientation(new_orientation);
	/*	Followed by a local rotation around x-axis*/
	scene_camera_ptr->rotate(cursor_movement.y, x_axis);

	/*	Implement "zoom" function */
	float distance_from_center = glm::length(glm::vec3(new_position) - scene_camera_ptr->getLookAt());
	scene_camera_ptr->translate( latest_scroll_input * (distance_from_center/8.0f) * scene_camera_ptr->computeFrontVector());
	latest_scroll_input = 0.0;

	/*	Update latest cursor position */
	latest_cursor_position = currentCursorPosition;
}

void Controls::mouseScrollFeedback(GLFWwindow *window, double x_offset, double y_offset)
{
	activeInstance->latest_scroll_input += 0.5f * (float) y_offset;
}
