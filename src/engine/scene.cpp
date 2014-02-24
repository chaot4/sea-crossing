#include "scene.h"

Scene::Scene() : last_used_entity_id(0)
{
}

Scene::~Scene()
{
}


int Scene::createStaticSceneObject(const glm::vec3 position, const glm::quat orientation, const glm::vec3 scaling,
										std::shared_ptr<Mesh> geomPtr, std::shared_ptr<Material> mtlPtr)
{
	/*	Create the new StaticSceneObject */
	std::shared_ptr<StaticSceneObject> new_entity(new StaticSceneObject(last_used_entity_id, position, orientation, scaling, geomPtr, mtlPtr));
	last_used_entity_id++;

	/*	Insert new entity into the render graph */
	m_render_graph.insert(new_entity);

	/*	Insert the new entity into the list for quick acces based on id */
	static_entity_list.insert( std::pair<int,std::shared_ptr<StaticSceneObject>>(new_entity->getId(),new_entity) );

	return (new_entity->getId());
}

void Scene::setStaticSceneObjectPosition(const int id, const glm::vec3 position)
{
	std::unordered_map<int, std::shared_ptr<StaticSceneObject>>::const_iterator entity = static_entity_list.find(id);
	if (entity == static_entity_list.end())
	{
		//TODO Probably should do something clever in this case.
	}
	else
	{
		entity->second->setPosition(position);
	}
}

void Scene::setStaticSceneObjectOrientation(const int id, const glm::quat orientation)
{
	std::unordered_map<int, std::shared_ptr<StaticSceneObject>>::const_iterator entity = static_entity_list.find(id);
	if (entity == static_entity_list.end())
	{
		//TODO Probably should do something clever in this case.
	}
	else
	{
		entity->second->setOrientation(orientation);
	}
}

void Scene::setStaticSceneObjectScaling(const int id, const glm::vec3 scaling)
{
	std::unordered_map<int, std::shared_ptr<StaticSceneObject>>::const_iterator entity = static_entity_list.find(id);
	if (entity == static_entity_list.end())
	{
		//TODO Probably should do something clever in this case.
	}
	else
	{
		entity->second->setScaling(scaling);
	}
}

void Scene::setStaticSceneObjectGeometry(const int id, std::shared_ptr<Mesh> geomPtr)
{
	std::unordered_map<int, std::shared_ptr<StaticSceneObject>>::const_iterator entity = static_entity_list.find(id);
	if (entity == static_entity_list.end())
	{
		//TODO Probably should do something clever in this case.
	}
	else
	{
		//TODO Change geometry, remove from and reinsert into render graph
	}
}

void Scene::setStaticSceneObjectMaterial(const int id, std::shared_ptr<Material> mtlPtr)
{
	std::unordered_map<int, std::shared_ptr<StaticSceneObject>>::const_iterator entity = static_entity_list.find(id);
	if (entity == static_entity_list.end())
	{
		//TODO Probably should do something clever in this case.
	}
	else
	{
		//TODO Change material, remove from and reinsert into render graph
	}
}

void Scene::setStaticSceneObject(const int id, const glm::vec3 position, const glm::quat orientation, const glm::vec3 scaling)
{
	std::unordered_map<int, std::shared_ptr<StaticSceneObject>>::const_iterator entity = static_entity_list.find(id);
	if (entity == static_entity_list.end())
	{
		//TODO Probably should do something clever in this case.
	}
	else
	{
		entity->second->setPosition(position);
		entity->second->setOrientation(orientation);
		entity->second->setScaling(scaling);
	}
}

void Scene::setStaticSceneObject(const int id, std::shared_ptr<Mesh> geomPtr, std::shared_ptr<Material> mtlPtr)
{
	std::unordered_map<int, std::shared_ptr<StaticSceneObject>>::const_iterator entity = static_entity_list.find(id);
	if (entity == static_entity_list.end())
	{
		//TODO Probably should do something clever in this case.
	}
	else
	{
		//TODO Change geometry and material, remove from and reinsert into render graph
	}
}

bool Scene::createVolumetricSceneObject(const int id, const glm::vec3 position, const glm::quat orientation, const glm::vec3 scaling,
											std::shared_ptr<Mesh> geomPtr, std::shared_ptr<Texture3D> volPtr, std::shared_ptr<GLSLProgram> prgmPtr)
{
	volumetricObjectList.push_back(VolumetricSceneObject(id,position,orientation,scaling,geomPtr,volPtr,prgmPtr));
	return true;
}

bool Scene::createSceneLight(const int id, const glm::vec3 position, glm::vec3 colour)
{
	lightSourceList.push_back(SceneLightSource(id, position, colour));
	return true;
}

bool Scene::createSceneCamera(const int id, const glm::vec3 position, const glm::quat orientation, float aspect, float fov)
{
	cameraList.push_back(SceneCamera(id, position, orientation, aspect, fov));
	return true;
}

bool Scene::createSceneCamera(const int id, const glm::vec3 position, const glm::vec3 lookAt, float aspect, float fov)
{
	cameraList.push_back(SceneCamera(id, position, lookAt, aspect, fov));
	return true;
}

void Scene::setActiveCamera(const int inId)
{
	//	check camera list
	for(std::list<SceneCamera>::iterator i = cameraList.begin(); i != cameraList.end(); ++i)
	{
		if((i->getId())==inId)
		{
			activeCamera = &(*i);
		}
	}
}

SceneCamera* Scene::getActiveCamera()
{
	return activeCamera;
}

void Scene::testing()
{
	//	Ehhh, a few lines for testing
	//activeCamera->rotate(90,glm::vec3(0.0,0.0,1.0));
	activeCamera->rotate(45.0,glm::vec3(0.0,1.0,0.0));
	activeCamera->rotate(-22.5,glm::vec3(1.0,0.0,0.0));
	
	//std::cout<<textureList.size();
	//std::cout<<vboList.size()<<"\n";
	//std::cout<<Scenegraph.size();

	//activeCamera->rotate(45.0,glm::vec3(0.0,1.0,0.0));
	//activeCamera->rotate(-45.0,glm::vec3(1.0,0.0,0.0));
	//glm::quat tVec = activeCamera->getOrientation();
	//std::cout<<"Orientation: "<<tVec.x<<" "<<tVec.y<<" "<<tVec.z<<" "<<tVec.w<<"\n";
	//
	//glm::vec3 fVec = activeCamera->computeFrontVector();
	//std::cout<<"Front: "<<fVec.x<<" "<<fVec.y<<" "<<fVec.z<<"\n";
	//glm::vec3 uVec = activeCamera->computeUpVector();
	//std::cout<<"Up: "<<uVec.x<<" "<<uVec.y<<" "<<uVec.z<<"\n";
	//glm::vec3 rVec = activeCamera->computeRightHandVector();
	//std::cout<<"Righthand: "<<rVec.x<<" "<<rVec.y<<" "<<rVec.z<<"\n";
	//
	//glm::vec3 lookat = ((activeCamera->getPosition())+(activeCamera->computeFrontVector()));
	//std::cout<<"Loookat: "<<lookat.x<<" "<<lookat.y<<" "<<lookat.z<<"\n
}

void Scene::drawFroward()
{
	glm::mat4 modelMx;
	glm::mat4 viewMx;
	glm::mat4 modelViewMx;
	glm::mat4 projectionMx;

	std::shared_ptr<GLSLProgram> shader_ptr;
	std::shared_ptr<Material> material_ptr;
	std::shared_ptr<Mesh> mesh_ptr;
	std::shared_ptr<StaticSceneObject> entity_ptr;
	
	/*	Iterate through all levels of the rendergraph */
	while (m_render_graph.getNextShaderProgam(shader_ptr))
	{
		shader_ptr->use();

		/*	Set "per program" uniforms */
		viewMx = activeCamera->computeViewMatrix();
		projectionMx = activeCamera->computeProjectionMatrix(1.0f,500000.0f);
		shader_ptr->setUniform("view_matrix", viewMx);
		shader_ptr->setUniform("projection_matrix", projectionMx);
	
		int light_counter = 0;
		shader_ptr->setUniform("lights.position", lightSourceList.begin()->getPosition());
		shader_ptr->setUniform("lights.intensity", lightSourceList.begin()->getColour());
		shader_ptr->setUniform("num_lights", light_counter);
	
		while (m_render_graph.getNextMaterial(material_ptr))
		{
			material_ptr->use();
	
			while (m_render_graph.getNextMesh(mesh_ptr))
			{
				/*	Draw all entities instanced */
				int instance_counter = 0;
				std::string uniform_name;
				
				while (m_render_graph.getNextEntity(entity_ptr))
				{
					/*	Set transformation matrix for each instance */
					modelMx = entity_ptr->computeModelMatrix();
					modelViewMx = viewMx*modelMx;
					uniform_name = "model_view_matrix[" + std::to_string(instance_counter) + "]";
					shader_ptr->setUniform(uniform_name.c_str(), modelViewMx);

					instance_counter++;
				}

				mesh_ptr->draw(instance_counter);

				//for (std::list<StaticSceneObject>::iterator entity_itr = mesh_itr->second.begin(); entity_itr != mesh_itr->second.end(); ++entity_itr)
				//{
				//	modelMx = entity_itr->computeModelMatrix();
				//	modelViewMx = viewMx*modelMx;
				//	shader_itr->first->setUniform("model_view_matrix[0]", modelViewMx);
				//	mesh_itr->first->draw();
				//}
			}
		}
	}

	m_render_graph.reset();

	///*	obtain transformation matrices */
	//glm::mat4 modelMx;
	//glm::mat4 modelViewMx;
	//glm::mat4 viewMx(activeCamera->computeViewMatrix());
	//glm::mat4 projectionMx(activeCamera->computeProjectionMatrix(1.0f,500000.0f));
	//glm::mat4 viewProjectionMx = projectionMx * viewMx;
	//
	//std::shared_ptr<GLSLProgram> currentPrgm;
	//std::shared_ptr<Material> currentMtl;
	//
	//for(std::list<StaticSceneObject>::iterator i = scenegraph.begin(); i != scenegraph.end(); ++i)
	//{
	//	modelMx = i->computeModelMatrix();
	//	modelViewMx = viewMx * modelMx;
	//
	//	currentMtl = i->getMaterial();
	//	currentPrgm = currentMtl->getShaderProgram();
	//	
	//	currentPrgm->use();
	//
	//	currentPrgm->setUniform("model_view_matrix[0]", modelViewMx);
	//	currentPrgm->setUniform("view_matrix", viewMx);
	//	currentPrgm->setUniform("projection_matrix", projectionMx);
	//
	//	int light_counter = 0;
	//	std::string uniform_name;
	//	//for(std::list<SceneLightSource>::iterator light_itr = lightSourceList.begin(); light_itr != lightSourceList.end(); ++light_itr)
	//	//{
	//	//	uniform_name = "lights.position["+ std::to_string(light_counter);
	//	//	uniform_name.append("]");
	//	//	currentPrgm->setUniform(uniform_name.c_str(),light_itr->getPosition());
	//	//	
	//	//	uniform_name = "lights.intensity["+ std::to_string(light_counter);
	//	//	uniform_name.append("]");
	//	//	currentPrgm->setUniform(uniform_name.c_str(),light_itr->getColour());
	//	//
	//	//   
	//	//	//currentPrgm->setUniform("lights.position[0]",light_itr->getPosition());
	//	//	//currentPrgm->setUniform("lights.intensity[0]",light_itr->getColour());
	//	//
	//	//	light_counter++;
	//	//	if(light_counter>=20) break;
	//	//}
	//
	//	currentPrgm->setUniform("lights.position", lightSourceList.begin()->getPosition());
	//	currentPrgm->setUniform("lights.intensity", lightSourceList.begin()->getColour());
	//
	//	currentPrgm->setUniform("num_lights",light_counter);
	//
	//	currentMtl->use();
	//
	//	(i->getGeometry())->draw();
	//	//i->rotate(0.1f,glm::vec3(0.0f,1.0f,0.0f));
	//}
}

void Scene::drawPicking(std::shared_ptr<GLSLProgram> prgm)
{
	prgm->use();

	glm::mat4 modelMx;
	glm::mat4 viewMx = activeCamera->computeViewMatrix();
	glm::mat4 modelViewMx;
	glm::mat4 projectionMx = activeCamera->computeProjectionMatrix(1.0f,500000.0f);

	prgm->setUniform("projection_matrix", projectionMx);

	std::shared_ptr<GLSLProgram> shader_ptr;
	std::shared_ptr<Material> material_ptr;
	std::shared_ptr<Mesh> mesh_ptr;
	std::shared_ptr<StaticSceneObject> entity_ptr;
	
	/*	Iterate through all levels of the rendergraph */
	while (m_render_graph.getNextShaderProgam(shader_ptr))
	{
		while (m_render_graph.getNextMaterial(material_ptr))
		{
			while (m_render_graph.getNextMesh(mesh_ptr))
			{
				/*	Draw all entities instanced */
				int instance_counter = 0;
				std::string uniform_name;
				
				while (m_render_graph.getNextEntity(entity_ptr))
				{
					/*	Set transformation matrix for each instance */
					modelMx = entity_ptr->computeModelMatrix();
					modelViewMx = viewMx*modelMx;
					uniform_name = "model_view_matrix[" + std::to_string(instance_counter) + "]";
					prgm->setUniform(uniform_name.c_str(), modelViewMx);

					uniform_name = "entity_id[" + std::to_string(instance_counter) + "]";
					prgm->setUniform(uniform_name.c_str(), entity_ptr->getId());

					instance_counter++;
				}

				mesh_ptr->draw(instance_counter);
			}
		}
	}

	m_render_graph.reset();

	//	prgm->use();
	//	
	//	glm::mat4 model_mx;
	//	glm::mat4 view_mx = activeCamera->computeViewMatrix();
	//	glm::mat4 projection_mx = activeCamera->computeProjectionMatrix(1.0f, 500000.0f);
	//	glm::mat4 model_view_projection_mx;
	//	
	//	/*	Iterate through all levels of the rendergraph */
	//	for (ShaderMap::iterator shader_itr = render_graph.begin(); shader_itr != render_graph.end(); ++shader_itr)
	//	{	
	//		for (MaterialMap::iterator material_itr = shader_itr->second.begin(); material_itr != shader_itr->second.end(); ++material_itr)
	//		{
	//			for (MeshMap::iterator mesh_itr = material_itr->second.begin(); mesh_itr != material_itr->second.end(); ++mesh_itr)
	//			{
	//				/*	Draw all entities instanced */
	//				int instance_counter = 0;
	//				std::string uniform_name;
	//	
	//				for (std::list<std::shared_ptr<StaticSceneObject>>::iterator entity_itr = mesh_itr->second.begin(); entity_itr != mesh_itr->second.end(); ++entity_itr)
	//				{
	//					/*	Set transformation matrix for each instance */
	//					model_mx = (*entity_itr)->computeModelMatrix();
	//					model_view_projection_mx = projection_mx*view_mx*model_mx;
	//					uniform_name = "model_view_projection_matrix[" + std::to_string(instance_counter) + "]";
	//					prgm->setUniform(uniform_name.c_str(), model_view_projection_mx);
	//	
	//					uniform_name = "entity_id[" + std::to_string(instance_counter) + "]";
	//					prgm->setUniform(uniform_name.c_str(), (*entity_itr)->getId());
	//	
	//					instance_counter++;
	//				}
	//	
	//				mesh_itr->first->draw(instance_counter);
	//			}
	//		}
	//	}
}

void Scene::renderVolumetricObjects()
{
	/*	obtain transformation matrices */
	glm::mat4 modelViewMx;
	glm::mat4 modelViewProjectionMx;
	glm::mat4 textureMatrix;

	glm::mat4 modelMx;
	glm::mat4 viewMx(activeCamera->computeViewMatrix());
	glm::mat4 projectionMx(activeCamera->computeProjectionMatrix(0.01f,100.0f));

	std::shared_ptr<GLSLProgram> currentPrgm(volumetricObjectList.begin()->getShaderProgram());
	currentPrgm->use();

	for(std::list<VolumetricSceneObject>::iterator i = volumetricObjectList.begin(); i != volumetricObjectList.end(); ++i)
	{
		modelMx = i->computeModelMatrix();
		modelViewMx = viewMx * modelMx;

		/*	construct the texture matrix */
		textureMatrix = glm::scale(glm::mat4(1.0),glm::vec3(1.0,1.0,-1.0));
		textureMatrix = glm::translate(textureMatrix,glm::vec3(0.5,0.5,-0.5));
		textureMatrix = textureMatrix * glm::inverse(modelMx);

		modelViewProjectionMx = projectionMx * viewMx * modelMx;

		glEnable(GL_TEXTURE_3D);
		glActiveTexture(GL_TEXTURE0);
		currentPrgm->setUniform("volumeTexture",0);
		i->getVolumeTexture()->bindTexture();

		currentPrgm->setUniform("modelViewProjectionMatrix",modelViewProjectionMx);
		currentPrgm->setUniform("modelMatrix",modelMx);
		currentPrgm->setUniform("textureMatrix",textureMatrix);
		currentPrgm->setUniform("cameraPosition",activeCamera->getPosition());

		(i->getGeometry())->draw();
		i->rotate(0.1f,glm::vec3(0.0f,1.0f,0.0f));
	}
}