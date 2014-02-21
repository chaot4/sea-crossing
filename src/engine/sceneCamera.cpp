#include "sceneCamera.h"


glm::vec3 SceneCamera::computeFrontVector()
{
	//	Use a pure quaternion containing the initial front vector to compute a pure quaternion
	//	containing the front vector according the the cameras orientation

	glm::quat qFront = glm::cross(glm::cross(m_orientation, glm::quat(0.0, 0.0, 0.0, -1.0)), glm::conjugate(m_orientation));

	return glm::normalize(glm::vec3(qFront.x,qFront.y,qFront.z));
}

glm::vec3 SceneCamera::computeUpVector()
{
	//	Use a pure quaternion containing the initial front vector to compute a pure quaternion
	//	containing the front vector according the the cameras orientation

	glm::quat qUp =	glm::cross(glm::cross(m_orientation,glm::quat(0.0,0.0,1.0,0.0)),glm::conjugate(m_orientation));

	return glm::normalize(glm::vec3(qUp.x,qUp.y,qUp.z));
}

glm::vec3 SceneCamera::computeRightHandVector()
{
	//	Use a pure quaternion containing the initial front vector to compute a pure quaternion
	//	containing the front vector according the the cameras orientation

	glm::quat qRighthand = glm::cross(glm::cross(m_orientation,glm::quat(0.0,1.0,0.0,0.0)),glm::conjugate(m_orientation));

	return glm::normalize(glm::vec3(qRighthand.x,qRighthand.y,qRighthand.z));
}
