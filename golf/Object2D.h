#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Object2D
{
public:
	GLuint VAO, VBO, EBO;

	Object2D(GLfloat* vertices, unsigned vertSize, GLuint* indices, unsigned indSize);
	~Object2D();

	void vertexAttrib(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei byteStride, const void* byteOffset);

	void bindVAO();
	void bindVBO();
	void bindEBO();

	void unbindVAO();
	void unbindVBO();
	void unbindEBO();
};

