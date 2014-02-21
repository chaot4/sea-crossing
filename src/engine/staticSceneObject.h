#ifndef staticSceneObject_h
#define staticSceneObject_h

#include "sceneEntity.h"
#include "mesh.h"
#include "material.h"
#include <memory>

class StaticSceneObject : public SceneEntity
{
private:
	bool m_is_rendered;

	std::shared_ptr<Mesh> m_geometry;
	std::shared_ptr<Material> m_material;
public:
	StaticSceneObject(const int id, const glm::vec3& inPosition, const glm::quat& inOrientation, const glm::vec3 inScaling,
						std::shared_ptr<Mesh> inGeom, std::shared_ptr<Material> inMtl) : 
						SceneEntity(id, inPosition, inOrientation, inScaling), m_geometry(inGeom), m_material(inMtl) {}
	~StaticSceneObject() {}

	const std::shared_ptr<Mesh> getGeometry();
	const std::shared_ptr<Material> getMaterial();

	void changeGeometry(std::shared_ptr<Mesh> new_geometry);
	void changeMaterial(std::shared_ptr<Material> new_material);

	glm::mat4 computeModelMatrix();
};

#endif
