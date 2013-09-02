#include "mesh.h"


Mesh::Mesh() : filename("0"), va_handle(0), vbo_handle(0), ibo_handle(0)
{
}

Mesh::~Mesh()
{
	glBindVertexArray(va_handle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &ibo_handle);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glDeleteBuffers(1, &vbo_handle);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &va_handle);
}

Mesh::Mesh(const std::string fn) : filename(fn), va_handle(0), vbo_handle(0), ibo_handle(0)
{
}

bool Mesh::bufferDataFromArray(const Vertex_p *vertex_data, const GLuint *index_data, const GLsizei va_size, const GLsizei vi_size, GLenum mesh_type)
{
	if(va_handle == 0 || vbo_handle == 0 || ibo_handle == 0)
	{
		glGenVertexArrays(1, &va_handle);
		glGenBuffers(1, &vbo_handle);
		glGenBuffers(1, &ibo_handle);
	}

	glBindVertexArray(va_handle);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);
	glBufferData(GL_ARRAY_BUFFER, va_size, vertex_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_handle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vi_size, index_data, GL_STATIC_DRAW);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	num_vertices = (vi_size/sizeof(GLuint));
	type = mesh_type;

	return true;
}

void Mesh::draw()
{
	glBindVertexArray(va_handle);
	/*	If stored correctly in the VAO, there is no need to rebind buffers again */
	glDrawElements(type, num_vertices, GL_UNSIGNED_INT, nullptr);
}

void Mesh::setVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer)
{
	glBindVertexArray(va_handle);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::setVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer)
{
	glBindVertexArray(va_handle);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);
	glEnableVertexAttribArray(index);
	glVertexAttribIPointer(index, size, type, stride, pointer);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::setVertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer)
{
	glBindVertexArray(va_handle);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);
	glEnableVertexAttribArray(index);
	glVertexAttribLPointer(index, size, type, stride, pointer);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
