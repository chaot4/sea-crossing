#ifndef GLSLProgram_h
#define GLSLProgram_h

#include <GL/glew.h>
//	OpenGL Math Library
#include <glm/glm.hpp>
#include <glm/core/type_vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

enum shaderType	{ SURFACE_LIGHTING,PICKING,FLAT, FXAA, IDLE, VOLUME_RAYCASTING, GAUSSIAN, GRADIENT, STRUCTURE_TENSOR, HESSE };

class GLSLProgram
{
private:
	GLSLProgram(GLSLProgram &cpy) {}

	shaderType type;
	GLuint handle;
	bool linkStatus;
	std::string shaderlog;

	GLuint getUniformLocation(const char *name);
public:
	GLSLProgram();
	GLSLProgram(shaderType shader_type);
	~GLSLProgram();

	shaderType getType() {return type;}

	void init();
	bool compileShaderFromString(const std::string * const source, GLenum shaderType);
	bool link();
	bool use();
	const std::string& getLog();
	GLuint getHandle();
	bool isLinked();
	void bindAttribLocation(GLuint location, const char *name);
	void bindFragDataLocation(GLuint location, const char *name);
	void setUniform(const char *name, const glm::vec2 &v);
	void setUniform(const char *name, const glm::vec3 &v);
	void setUniform(const char *name, const glm::vec4 &v);
	void setUniform(const char *name, const glm::mat4 &m);
	void setUniform(const char *name, const glm::mat3 &m);
	void setUniform(const char *name, int i);
	void setUniform(const char *name, float f);
	void setUniform(const char *name, bool b);
	void printActiveUniforms();
	void printActiveAttributes();
};

#endif
