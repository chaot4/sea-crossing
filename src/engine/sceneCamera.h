#ifndef sceneCamera_h
#define sceneCamera_h

#include "sceneEntity.h"

class SceneCamera : public SceneEntity
{
private:
	float aspect_ratio;
	float field_of_view;

	glm::vec3 look_at;

public:
	SceneCamera() {}
	~SceneCamera() {}

	SceneCamera(int inId, const glm::vec3& inPosition, const glm::quat& inOrientation,
					float inAspect, float inFov, const glm::vec3& inLookAt = glm::vec3(0.0))
		: SceneEntity(inId, inPosition, inOrientation, glm::vec3(1.0)), look_at(inLookAt), aspect_ratio(inAspect), field_of_view(inFov) {}

	void setAspectRation(const float inAspectRation) { aspect_ratio = inAspectRation; }
	float getAspectRatio() { return aspect_ratio; }
	void setFieldOfView(const float inFieldOfView) { field_of_view = inFieldOfView; }
	float getFieldOfView() { return field_of_view; }
	void setLookAt(const glm::vec3 inLookAt) { look_at = inLookAt; }
	glm::vec3 getLookAt() { return look_at; }

	/*	
	/	The initial camera orientation is defined as (0,0,-1).
	/	The current orientation is obtained by applying the orientation quaternion to the respective vectors.
	*/
	glm::vec3 computeFrontVector();
	glm::vec3 computeUpVector();
	glm::vec3 computeRightHandVector();

	glm::mat4 computeViewMatrix(){ return glm::lookAt(position,position+computeFrontVector(),computeUpVector()); }
	glm::mat4 computeProjectionMatrix(float nearClippingPlane, float farClippingPlane) { return glm::perspective(field_of_view, aspect_ratio, nearClippingPlane, farClippingPlane); }
};

#endif
