#ifndef renderHub_h
#define renderHub_h
/*
/	In this class, all parts directly related to the rendering done on a single device come together.
/
/	OpenGL context, window management, scene management, aswell as communication with other engine modules
/	is handled here.
*/

#define TIMER 0

#include <vector>
#include "scene.h"
#include "postProcessor.h"
#include "resourceManager.h"
#include "messageReceiver.h"
#include "controls.h"
#include "framebufferObject.h"
#include "GLFW/glfw3.h"

class RenderHub
{
public:
	RenderHub();
	~RenderHub();

	RenderHub(MessageReceiver *&postbox) {postbox = &messageRcvr;}

	/*	Initialize OpenGL context and create a window */
	bool init();

	/*	Scene handling */
	bool addScene();
	bool deleteScene();
	bool setSceneParameters();
	Scene* getScene(const int index);
	void setActiveScene(const int index);
	Scene* getActiveScene();

	/* Render a frame of the active scene and check event-queue. */
	void run();

	/*	Test volume rendering */
	void runVolumeTest();

private:
	ResourceManager resourceMngr;
	MessageReceiver messageRcvr;
	Controls controlHandler;

	std::list<Scene> sceneList;

	GLFWwindow *activeWindow;
	Scene *activeScene;

	bool running;

	/*	Message handling */
	void processMessage(Message *msg);

	/*	Callback handling */
	static RenderHub *activeInstance;
	static void setActiveInstance(RenderHub *instance);
	static void windowSizeCallback(GLFWwindow* window, int width, int height);
	static void windowCloseCallback(GLFWwindow* window);
};

#endif
