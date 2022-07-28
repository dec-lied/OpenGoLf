#include "Object2D.h"

Object2D::Object2D(GLfloat* vertices, unsigned vertSize, GLuint* indices, unsigned indSize)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertSize, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indSize, indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Object2D::~Object2D()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
}

void Object2D::vertexAttrib(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei byteStride, const void* byteOffset)
{
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);

	glVertexAttribPointer(index, size, type, normalized, byteStride, byteOffset);
	glEnableVertexAttribArray(index);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Object2D::bindVAO()
{
	glBindVertexArray(this->VAO);
}

void Object2D::bindVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
}

void Object2D::bindEBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
}

void Object2D::unbindVAO()
{
	glBindVertexArray(0);
}

void Object2D::unbindVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Object2D::unbindEBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
