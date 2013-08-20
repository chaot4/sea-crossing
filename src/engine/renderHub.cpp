#include "renderHub.h"


RenderHub::RenderHub(void)
{
}

RenderHub::~RenderHub(void)
{
}


bool RenderHub::init()
{
	//std::cout<<"----------------------------\n"
	//		<<"SPACE LION - Early Prototype\n"
	//		<<"----------------------------\n";
	//	Initialize GLFW
	if(!glfwInit())
	{
		std::cout<<"-----\n"
				<<"The time is out of joint - O cursed spite,\n"
				<<"That ever I was born to set it right!\n"
				<<"-----\n"
				<<"Error: Couldn't initialize glfw.";

		return false;
	}
	//std::cout<<"Initializing GLFW\n";


	activeWindow = glfwCreateWindow(800,450,"Sea-Crossing",NULL,NULL);

	if(!activeWindow)
	{
		std::cout<<"-----\n"
				<<"The time is out of joint - O cursed spite,\n"
				<<"That ever I was born to set it right!\n"
				<<"-----\n"
				<<"Error: Couldn't open glfw window";

		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(activeWindow);

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

	/*
	/	This is actually not supposed to be done like this!
	*/
	addScene();
	setActiveScene(0);
	run();

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

	if(!(activeScene->createSceneCamera(0,glm::vec3(0.0,0.0,20.0),glm::quat(),16.0f/9.0f,60.0f)))
		std::cout<<"Failed to create camera"<<"\n";

	if(!(activeScene->createSceneLight(0,glm::vec3(-20.0,10.0,-20.0),glm::vec4(1.0,1.0,1.0,1.0))))
		std::cout<<"Failed to create light"<<"\n";

	activeScene->setActiveCamera(0);
	
	//activeScene->testing();

	running = true;
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glEnable (GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable( GL_MULTISAMPLE );

	while(running && !glfwWindowShouldClose(activeWindow))
	{
		while(messageRcvr.checkQueue())
		{
			Message msg(messageRcvr.popMessage());
			processMessage(&msg);
		}

		/*	For now, I avoid using glfw callback functions */
		controlHandler.updateCamera(activeWindow,activeScene);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0,0,800,450);
		activeScene->render();

		glfwSwapBuffers(activeWindow);
		glfwPollEvents();
	}
	//glfwDestroyWindow(activeWindow);
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

	while(running && !glfwWindowShouldClose(activeWindow))
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0,0,1200,675);
		activeScene->renderVolumetricObjects();

		glfwSwapBuffers(activeWindow);
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
		if(!(resourceMngr.createMaterial((msg->material_path).c_str(),materialPtr)))
		{
			std::cout<<"Failed to create material."<<std::endl;
			break;
		}
		if(!(resourceMngr.createMesh((msg->geometry_path).c_str(),geomPtr)))
		{
			std::cout<<"Failed to create mesh."<<std::endl;
			break;
		}

		if(!(activeScene->createStaticSceneObject((msg->id),(msg->position),(msg->orientation),geomPtr,materialPtr)))
			std::cout<<"Failed to create scene object."<<std::endl;

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