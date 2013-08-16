#include "renderHub.h"


RenderHub::RenderHub(void)
{
}

RenderHub::~RenderHub(void)
{
}


bool RenderHub::init()
{
	//	Initialize GLFW
	if(!glfwInit())
	{
		return false;
	}
	std::cout<<"Initializing GLFW\n";

	//#ifdef _WIN32
	//	//	Get highest openGL Version (doesn't work on linux right now)
	//	//	The glfwGetGLVersion function seems somewhat broken on windows too. When certain, seemingly random
	//	//	conditions are met.
	//
	//	int maj, min, rev;
	//    glfwGetGLVersion(&maj, &min, &rev);
	//
	//	//	Open a glfw window
	//	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, maj);
	//	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, min);
	//	//glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//	//glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//#else
	//	//	Better be save than sorry and choose a low GL version on linux
	//	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
	//	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 0);
	//#endif

	int maj, min;

	#ifdef _WIN32
		maj = 3;
		min = 3;
	#else
		maj = 2;
		min = 0;
	#endif

	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, maj);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, min);
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES,4);

	if(!glfwOpenWindow(400,400,8,8,8,8,32,0,GLFW_WINDOW))
	{
		std::cout<<"-----\n"
				<<"The time is out of joint - O cursed spite,\n"
				<<"That ever I was born to set it right!\n"
				<<"-----\n"
				<<"Error: Couldn't open glfw window";
		return false;
	}

	/*	This is actually not working like this... */
	//const GLubyte *version = glGetString(GL_VERSION);
	//std::cout<<"Supporting OpenGL Version: "<<version<<"\n";
	std::cout<<"Using OpenGL Version: "<<maj<<"."<<min<<"\n\n";

	/*	Initialize glew */
	//glewExperimental = GL_TRUE;
	GLenum error = glewInit();
	if( GLEW_OK != error)
	{
		std::cout<<"-----\n"
				<<"The time is out of joint - O cursed spite,\n"
				<<"That ever I was born to set it right!\n"
				<<"-----\n"
				<<"Error: "<<glewGetErrorString(error);
		return false;
	}
	/*
	/	Apparently glweInit() causes a GL ERROR 1280, so let's just catch that...
	*/
	glGetError();

	return true;
}

bool RenderHub::addScene()
{
	sceneList.push_back(Scene());

	return true;
}

bool RenderHub::deleteScene()
{
	return false;
}

bool RenderHub::setSceneParameters()
{
	return false;
}

Scene* RenderHub::getScene(const int index)
{
	std::list<Scene>::iterator iter = sceneList.begin();
	for( int i=0; i < index; ++i) {++iter;}
	return &(*iter);
}

void RenderHub::setActiveScene(const int index)
{
	std::list<Scene>::iterator iter = sceneList.begin();
	for( int i=0; i < index; ++i) {++iter;}
	activeScene = &(*iter);
}

void RenderHub::run()
{
	/*
	/	Support for adding cameras and lights via message system will follow later on
	*/

	if(!(activeScene->createSceneCamera(0,glm::vec3(2.5,-2.0,12.0),glm::quat(),16.0f/9.0f,60.0f)))
		std::cout<<"Failed to create camera"<<"\n";

	if(!(activeScene->createSceneLight(0,glm::vec3(0.0,2.0,0.0),glm::vec4(1.0,1.0,1.0,1.0))))
		std::cout<<"Failed to create light"<<"\n";

	activeScene->setActiveCamera(0);
	
	activeScene->testing();

	running = true;
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glEnable (GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable( GL_MULTISAMPLE );

	while(running && glfwGetWindowParam(GLFW_OPENED))
	{
		while(messageRcvr.checkQueue()) processMessage( &(messageRcvr.popMessage()) );

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0,0,1200,675);
		activeScene->render();

		glfwSwapBuffers();
		glfwSleep(0.01);
	}
}

void RenderHub::runVolumeTest()
{
	Mesh* geomPtr;
	Texture3D* volPtr;
	GLSLProgram* prgmPtr;
	resourceMngr.createBox(geomPtr);
	resourceMngr.createTexture3D("../resources/volumeData/f.raw",glm::ivec3(67,67,67),volPtr);
	resourceMngr.createShaderProgram(FTV_VOLUME_RAYCASTING,prgmPtr);


	if(!(activeScene->createVolumetricSceneObject(0,glm::vec3(0.0,0.0,0.0),glm::quat(),glm::vec3(1.0,1.0,1.0),geomPtr,volPtr,prgmPtr)))
	{
		std::cout<<"Failed to create scene object"
				<<"\n";
	}

	if(!(activeScene->createVolumetricSceneObject(1,glm::vec3(0.0,0.0,-2.0),glm::quat(),glm::vec3(1.0,1.0,1.0),geomPtr,volPtr,prgmPtr)))
	{
		std::cout<<"Failed to create scene object"
				<<"\n";
	}
	
	if(!(activeScene->createVolumetricSceneObject(2,glm::vec3(-2.0,0.0,0.0),glm::quat(),glm::vec3(1.0,1.0,1.0),geomPtr,volPtr,prgmPtr)))
	{
		std::cout<<"Failed to create scene object"
				<<"\n";
	}

	if(!(activeScene->createSceneCamera(0,glm::vec3(1.5,1.0,1.5),glm::quat(),16.0f/9.0f,55.0f)))
	{
		std::cout<<"Failed to create camera"
				<<"\n";
	}
	if(!(activeScene->createSceneLight(0,glm::vec3(0.0,2.0,0.0),glm::vec4(1.0,1.0,1.0,1.0))))
	{
		std::cout<<"Failed to create light"
				<<"\n";
	}

	activeScene->setActiveCamera(0);

	activeScene->testing();

	running = true;
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glEnable (GL_DEPTH_TEST);
	//glEnable (GL_BLEND);
	//glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_CULL_FACE);

	while(running && glfwGetWindowParam(GLFW_OPENED))
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0,0,1200,675);
		activeScene->renderVolumetricObjects();

		glfwSwapBuffers();
	}
}

void RenderHub::processMessage(Message *msg)
{
	messageType msgType = (msg->type);
	switch (msgType)
	{
	case CREATE:
		Mesh* geomPtr;
		Material* materialPtr;
		resourceMngr.createMaterial((msg->material_path).c_str(),materialPtr);
		resourceMngr.createMesh((msg->geometry_path).c_str(),geomPtr);

		if(!(activeScene->createStaticSceneObject((msg->id),(msg->position),(msg->orientation),geomPtr,materialPtr)))
			std::cout<<"Failed to create scene object"<<"\n";

		break;
	case DELETE:
		break;
	case EXIT:
		running = false;
		break;
	default:
		break;
	}
}