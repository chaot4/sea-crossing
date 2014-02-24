#ifndef controls_h
#define controls_h

#include "sceneCamera.h"
#include <GLFW/glfw3.h>
#include "../messageChannel.h"
#include "../messages.h"

namespace Controls
{
	void updateCamera(GLFWwindow *window, SceneCamera *camera);
	void setControlCallbacks(GLFWwindow *active_window);

	TwoWayChannel& getCommunicationChannel();
}

#endif