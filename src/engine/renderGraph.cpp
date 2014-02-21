#include "renderGraph.h"

RenderGraph::RenderGraph() : shader_itr(), material_itr(), mesh_itr(), entity_itr()
{
}

RenderGraph::~RenderGraph()
{
}


void RenderGraph::insert(std::shared_ptr<StaticSceneObject> entity)
{
	/*	Get the shader program as starting point */
	std::shared_ptr<GLSLProgram> prgmPtr = entity->getMaterial()->getShaderProgram();

	/*
	/	Push the new scene entity into the render graph datastructure.
	/
	/	The used iterators will either point to a newly created list/map or
	/	an already existing one. In both cases the retrieved iterator can be used to insert
	/	a new map (or push the new entity into the list) or find an already existing one
	/	to continue on to the bottom of the datastructure.
	*/
	std::pair<ShaderMap::iterator, bool> itr_firstlevel =
		m_toplevel.insert(std::pair<std::shared_ptr<GLSLProgram>, MaterialMap>(prgmPtr, MaterialMap()));

	std::pair<MaterialMap::iterator, bool> itr_secondlevel =
		itr_firstlevel.first->second.insert(std::pair<std::shared_ptr<Material>, MeshMap>(entity->getMaterial(), MeshMap()));

	std::pair<MeshMap::iterator, bool> itr_thirdlevel =
		itr_secondlevel.first->second.insert(std::pair<std::shared_ptr<Mesh>, std::list<std::shared_ptr<StaticSceneObject>>>(entity->getGeometry(), std::list<std::shared_ptr<StaticSceneObject>>()));

	itr_thirdlevel.first->second.push_back(entity);

	shader_itr = m_toplevel.begin();
}

void RenderGraph::remove(int id)
{
}

bool RenderGraph::getNextShaderProgam(std::shared_ptr<GLSLProgram>& program)
{
	if (shader_itr != m_toplevel.end() && (m_toplevel.size()>0))
	{
		program = shader_itr->first;
		material_itr = shader_itr->second.begin();
		++shader_itr;
		return true;
	}

	return false;
}

bool RenderGraph::getNextMaterial(std::shared_ptr<Material>& material)
{
	if (material_itr != std::prev(shader_itr)->second.end())
	{
		material = material_itr->first;
		mesh_itr = material_itr->second.begin();
		++material_itr;
		return true;
	}

	return false;
}

bool RenderGraph::getNextMesh(std::shared_ptr<Mesh>& mesh)
{
	if (mesh_itr != std::prev(material_itr)->second.end())
	{
		mesh = mesh_itr->first;
		entity_itr = mesh_itr->second.begin();
		++mesh_itr;
		return true;
	}

	return false;
}

bool RenderGraph::getNextEntity(std::shared_ptr<StaticSceneObject>& entity)
{
	if (entity_itr != std::prev(mesh_itr)->second.end() )
	{
		entity = (*entity_itr);
		++entity_itr;
		return true;
	}

	return false;
}

void RenderGraph::reset()
{
	shader_itr = m_toplevel.begin();
}