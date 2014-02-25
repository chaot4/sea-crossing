/**
* \class SceneEntity
*
* \brief Base class for scene entities
*
* This class contains the id and spatial information of a scene entity
* and offers basic functionality to manipulate those values, e.g. translate, rotate etc.
* The class is abstract due to the protected constructor.
*
* \author Michael Becher
*
* \date 26th November 2013
*/

#ifndef sceneEntity_h
#define sceneEntity_h

/*	OpenGL Math Lib */
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef unsigned int EntityID;

class SceneEntity
{
protected:
	const EntityID m_id;

	glm::vec3 m_position;
	glm::quat m_orientation;
	glm::vec3 m_scaling;

	/**
	* \brief 'Complete' contructor. Declared protected, as only classes derived from this class are supposed to be instantiated.
	*/
	SceneEntity(const int id, const glm::vec3& position, const glm::quat& orientation, const glm::vec3& scaling)
		: m_id(id), m_position(position), m_orientation(orientation), m_scaling(scaling) {}
public:
	~SceneEntity() {}

	/**
	* \brief Change entity position via translation
	* \param tvec Translation vector
	*/
	void translate(const glm::vec3& tvec) { m_position = m_position + tvec; }

	/**
	* \brief Rotate entity by a given angle around a given vector
	* \param angle Rotation angle given in degrees
	* \param angle Rotation angle given in radian
	* \param axis Local rotation vector, e.g. vec3(1.0,0.0,0.0) is always the right hand vector, not the global x-axis
	*/
	void rotate(const float angle,const glm::vec3& axis) {m_orientation = glm::normalize(glm::rotate(m_orientation,angle,axis));}

	/**
	* \brief Get entity id
	* \return Returns entity id as an integer
	*/
	const int getId() {return m_id;}

	/**
	* \brief Set entity position
	* \param position New position
	*/
	void setPosition(const glm::vec3& position) { m_position = position; }

	/**
	* \brief Get entity position
	* \return Returns position
	*/
	glm::vec3 getPosition() { return m_position; }

	/**
	* \brief Set entity orientation
	* \param orientation New orientation
	*/
	void setOrientation(const glm::quat& orientation) {m_orientation = orientation;}

	/**
	* \brief Set entity orientation to specified angle and rotation vector based on initial orientation of glm::quat
	* \param angle Rotation angle given in degrees
	* \param axis Global rotation vector, e.g. for vec3(0.0,1.0,0.0) the entity will be rotated around the global y-axis 
	*/
	void setOrientation(const float angle, const glm::vec3& axis) {m_orientation = glm::rotate(glm::quat(),angle,axis);}

	/**
	* \brief Get entity orientation
	* \return Returns orientation
	*/
	const glm::quat& getOrientation() {return m_orientation;}

	/**
	* \brief Set entity scaling
	* \param scaling New scaling
	*/
	void setScaling(const glm::vec3& scaling) {m_scaling = scaling;}

	/**
	* \brief Get entity scaling
	* \return Returns scaling
	*/
	glm::vec3 getScaling() {return m_scaling;}
};

#endif
