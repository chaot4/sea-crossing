#include "renderHub.h"

RenderHub* RenderHub::activeInstance;

RenderHub::RenderHub()
{
}

RenderHub::~RenderHub()
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

	//glfwWindowHint(GLFW_VERSION_MAJOR,3);
	//glfwWindowHint(GLFW_VERSION_MINOR,3);
	glfwWindowHint(GLFW_SAMPLES, 4);

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

	/*
	/	The callback function needs a reference to this object,
	/	so just hand it over and quietly weep in the corner.
	*/
	setActiveInstance(this);
	glfwSetWindowSizeCallback(activeWindow,windowSizeCallback);
	glfwSetWindowCloseCallback(activeWindow,windowCloseCallback);
	Controls::setControlCallbacks(activeWindow);

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

TwoWayChannel& RenderHub::getChannelAccesPoint()
{
	return messageRcvr;
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
	/	Create resource needed for additional render passes, e.g. shader programs not related to object materials
	/	and framebuffer objects.
	/	Framebuffers are created and stored locally in the context of this method.
	*/
	//std::shared_ptr<GLSLProgram> picking_prgm;
	//resourceMngr.createShaderProgram(PICKING, picking_prgm);
	//
	//FramebufferObject picking_fbo(800,450,true,false);
	//picking_fbo.createColorAttachment(GL_R32UI, GL_RED_INTEGER, GL_UNSIGNED_INT);
	//
	//PostProcessor post_proc(800,450);
	//post_proc.init(&resourceMngr);


	/*
	/	Support for adding cameras and lights via message system will follow later on
	*/

	/*	TEMPORARY SHADER TESTING */
	//std::shared_ptr<Mesh> geomPtr;
	//std::shared_ptr<Material> matPtr;
	//resourceMngr.createBox(geomPtr);
	//resourceMngr.createMesh("../resources/meshes/board_round.fbx",geomPtr);
	//if(!(resourceMngr.createMaterial("../resources/materials/debugging.slmtl",matPtr)))
	//	std::cout<<"Failed to create material."<<std::endl;
	//if(!(activeScene->createStaticSceneObject(0,glm::vec3(0.0,0.0,0.0),glm::quat(),glm::vec3(1.0),geomPtr,matPtr)))
	//	std::cout<<"Failed to create scene object."<<std::endl;
	//
	//geomPtr.reset();
	//matPtr.reset();
	
	//resourceMngr.createMesh("../resources/meshes/performance_test/terrain.fbx", geomPtr);
	//if (!(resourceMngr.createMaterial("../resources/materials/default.slmtl", matPtr)))
	//	std::cout << "Failed to create material." << std::endl;
	//if (!(activeScene->createStaticSceneObject(1, glm::vec3(0.0,0.0, 0.0), glm::quat(),glm::vec3(5000.0), geomPtr, matPtr)))
	//	std::cout << "Failed to create scene object." << std::endl;
	//
	//geomPtr.reset();
	//matPtr.reset();

	if(!(activeScene->createSceneCamera(0,glm::vec3(25.0,25.0,25.0),glm::vec3(0.0,0.0,0.0),16.0f/9.0f,(9.0f/16.0f)*60.0f)))
		std::cout<<"Failed to create camera"<<"\n";

	if(!(activeScene->createSceneLight(0,glm::vec3(3000.0,5000.0,1500.0),glm::vec3(150000.0))))
		std::cout<<"Failed to create light"<<"\n";

	activeScene->setActiveCamera(0);

	running = true;
	glClearColor(0.2f,0.2f,0.2f,1.0f);
	glEnable (GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable( GL_MULTISAMPLE );

	/*  Test picking pass */
	//GLuint *data = new GLuint[1];

	while(running && !glfwWindowShouldClose(activeWindow))
	{
		std::shared_ptr<Message> msg;
		while (messageRcvr.receive(msg))
		{
			processMessage(msg);
		}

		/*	For now, I avoid using a glfw callback function for this */
		Controls::updateCamera(activeWindow,activeScene->getActiveCamera());

		/*  Test picking pass */
		//picking_fbo.bind();
		//glClearColor(0, 0, 0, 0);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glViewport(0, 0, picking_fbo.getWidth(), picking_fbo.getHeight());
		//activeScene->drawPicking(picking_prgm);
		//glReadBuffer(GL_COLOR_ATTACHMENT0);
		//glReadPixels(400, 225, 1, 1, GL_RED_INTEGER, GL_UNSIGNED_INT, data);
		//std::cout << data[0] << std::endl;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		int width, height;
		glfwGetFramebufferSize(activeWindow, &width, &height);
		glViewport(0, 0, width, height);

		activeScene->drawFroward();

		glfwSwapBuffers(activeWindow);
		glfwPollEvents();
	}

	/*	Make sure to delete all OpenGL resources while the context is still active */
	sceneList.clear();
	resourceMngr.clearLists();

	glfwDestroyWindow(activeWindow);
}

void RenderHub::runVolumeTest()
{
	std::shared_ptr<Mesh> geomPtr;
	std::shared_ptr<Texture3D> volPtr;
	std::shared_ptr<GLSLProgram> prgmPtr;
	resourceMngr.createBox(geomPtr);
	resourceMngr.createTexture3D("../resources/volumeData/f.raw",glm::ivec3(67,67,67),volPtr);
	resourceMngr.createShaderProgram(VOLUME_RAYCASTING,prgmPtr);


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
	if(!(activeScene->createSceneLight(0,glm::vec3(0.0,2.0,0.0),glm::vec3(1.0,1.0,1.0))))
	{
		std::cout<<"Failed to create light"
				<<"\n";
	}

	//	TODO: RESET LOCAL SHARED_PTR

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

void RenderHub::processMessage(std::shared_ptr<Message> msg)
{
	MessageType msgType = (msg->type);
	switch (msgType){
	case ENGINE_CREATE:
	{
		std::shared_ptr<MsgEngineCreate> c_msg = std::static_pointer_cast<MsgEngineCreate>(msg);

		std::shared_ptr<Mesh> geomPtr;
		std::shared_ptr<Material> materialPtr;
		if (!(resourceMngr.createMaterial((c_msg->material_path).c_str(), materialPtr)))
		{
			std::cout << "Failed to create material: " << c_msg->material_path << std::endl;
			break;
		}
		if (!(resourceMngr.createMesh((c_msg->geometry_path).c_str(), geomPtr)))
		{
			std::cout<<"Failed to create mesh."<<std::endl;
			break;
		}

		unsigned int entity_id = activeScene->requestNewEntityId();

		if (!(activeScene->createStaticSceneObject(entity_id, (c_msg->position), (c_msg->orientation), (c_msg->scaling), geomPtr, materialPtr)))
			std::cout<<"Failed to create scene object."<<std::endl;

		std::shared_ptr<Message> new_msg(new MsgEngineCreateFeedback(c_msg->msg_id, entity_id));
		messageRcvr.send(new_msg);

		geomPtr.reset();
		materialPtr.reset();
		break;
	}
	case ENGINE_DELETE:
		break;
	case ENGINE_QUIT:
		running = false;
		break;
	default:
		break;
	}
}

void RenderHub::windowSizeCallback(GLFWwindow *window, int width, int height)
{
	if(activeInstance != NULL)
	{
		activeInstance->activeScene->getActiveCamera()->setAspectRation((float)width/(float)height);
	}
}

void RenderHub::windowCloseCallback(GLFWwindow *window)
{
	
}

void RenderHub::setActiveInstance(RenderHub *instance)
{
	activeInstance = instance;
}