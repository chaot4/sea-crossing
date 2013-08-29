#ifndef staticSceneObject_h
#define staticSceneObject_h

//openGL Math Lib
#include "sceneEntity.h"
#include <memory>

class StaticSceneObject : public SceneEntity
{
private:
	bool isRendered;

	std::shared_ptr<Mesh> geometry;
	Material *mtl;
public:
	StaticSceneObject() {}
	~StaticSceneObject() {}

	StaticSceneObject(const int inId, const glm::vec3& inPosition, const glm::quat& inOrientation, std::shared_ptr<Mesh> inGeom, Material* inMtl) : SceneEntity(inId, inPosition, inOrientation), geometry(inGeom), mtl(inMtl) {}

	std::shared_ptr<Mesh> getGeometry() {return geometry;}
	Material* getMaterial() {return mtl;}

	glm::mat4 computeModelMatrix() {return (glm::translate(glm::mat4(1.0),position))*(glm::mat4_cast(orientation))*(glm::scale(glm::mat4(1.0),scaling));}
};

#endif
