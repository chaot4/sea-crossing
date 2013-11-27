#ifndef renderGraph_h
#define renderGraph_h

/*	std includes */
#include <list>
#include <map>
#include <memory>

/*	space-lion includes */
#include "GLSLProgram.h"
#include "material.h"
#include "mesh.h"
#include "staticSceneObject.h"

/**
* \class RenderGraph
*
* \brief Datastructure used to (forward) render a scene
*
* Prototype of a datastructure that offers a more optimal access pattern
* to scene-entities for rendering. Pointers to all relevant resources and to all
* scene-entities are stored in a tree-structure, sorted by GLSLshaderprogram,
* Material and Mesh in order to minimize the amount of needless OpenGL calls.
*
* \author Michael Becher
*
* \date 26th November 2013
*/
class RenderGraph
{
private:
	typedef std::map< std::shared_ptr<Mesh>, std::list<std::shared_ptr<StaticSceneObject>> > MeshMap;
	typedef std::map< std::shared_ptr<Material>, MeshMap > MaterialMap;
	typedef std::map< std::shared_ptr<GLSLProgram>, MaterialMap > ShaderMap;

	ShaderMap m_toplevel;

	ShaderMap::iterator shader_itr;
	MaterialMap::iterator material_itr;
	MeshMap::iterator mesh_itr;
	std::list<std::shared_ptr<StaticSceneObject>>::iterator entity_itr;

public:
	RenderGraph();
	~RenderGraph();

	/**
	* \brief Add an entity to the graph
	* \param entity The shared pointer to the entity that is added to the graph
	*/
	void insert(std::shared_ptr<StaticSceneObject> entity);

	/**
	* \brief Remove an entity from the graph
	* \param id Id of the entity
	*/
	void remove(int id);

	bool getNextShaderProgam(std::shared_ptr<GLSLProgram>& program);

	/**
	* \brief Get a pointer to the next material
	* \note Can only be succesfully called after a succesful call to getNextShaderProgram().
	* Checks internal iterator against end() and increments it by one for the next call to the function
	* before the return. 
	* \param material Pointer set to the next material via call-by-reference if return value is true
	* \return Returns true if there is a next material, otherwise false
	*/
	bool getNextMaterial(std::shared_ptr<Material>& material);
	bool getNextMesh(std::shared_ptr<Mesh>& mesh);
	bool getNextEntity(std::shared_ptr<StaticSceneObject>& entity);
	void reset();
};

#endif