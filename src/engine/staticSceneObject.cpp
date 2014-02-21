#include "staticSceneObject.h"

const std::shared_ptr<Mesh> StaticSceneObject::getGeometry()
{
	return m_geometry;
}

const std::shared_ptr<Material> StaticSceneObject::getMaterial()
{
	return m_material;
}

void StaticSceneObject::changeGeometry(std::shared_ptr<Mesh> new_geometry)
{
	m_geometry = new_geometry;
}

void StaticSceneObject::changeMaterial(std::shared_ptr<Material> new_material)
{
	m_material = new_material;
}

glm::mat4 StaticSceneObject::computeModelMatrix()
{
	return (glm::translate(glm::mat4(1.0), m_position))*
		(glm::mat4_cast(m_orientation))*
		(glm::scale(glm::mat4(1.0), m_scaling));
}