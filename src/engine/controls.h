#ifndef controls_h
#define controls_h

#include "scene.h"

class Controls
{
public:
	Controls() : x_axis(1.0,0.0,0.0), y_axis(0.0,1.0,0.0), latest_cursor_position(0.0,0.0),latest_y_rotation(0.0),latest_x_rotation(0.0) {}
	~Controls() {}

	void updateCamera(GLFWwindow *window, Scene *scene);
private:
	const glm::vec3 x_axis;
	const glm::vec3 y_axis;

	glm::vec2 latest_cursor_position;
	GLfloat latest_y_rotation;
	GLfloat latest_x_rotation;
};

#endif
