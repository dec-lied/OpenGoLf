#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <map>
#include <string>
#include <fstream>
#include <iostream>

class Shader
{
public:
	GLuint shaderID;
	std::map<const char*, GLint> uniforms;

	Shader(const char* vertexPath, const char* fragPath, bool verbose);
	~Shader();

	void use();
	void unbind();
	void deleteShader();

	GLint getUniformLocation(const char* uniformName);
	void setBool(const char* uniformName, GLboolean value);
	void setInt(const char* uniformName, GLint value);
	void setFloat(const char* uniformName, GLfloat value);
	void set3fv(const char* uniformName, GLsizei count, const GLfloat* value);
	void set4fv(const char* uniformName, GLsizei count, const GLfloat* value);
	void setMatrix3fv(const char* uniformName, GLsizei count, GLboolean transpose, const GLfloat* value);
	void setMatrix4fv(const char* uniformName, GLsizei count, GLboolean transpose, const GLfloat* value);
};