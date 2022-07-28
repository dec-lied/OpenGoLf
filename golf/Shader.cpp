#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragPath, bool verbose)
{
	std::ifstream vertexIF(vertexPath, std::ios::in);
	std::ifstream fragIF(fragPath, std::ios::in);

	std::string vertexSource;
	std::string fragSource;

	if (vertexIF.is_open())
	{
		std::string line;
		while (std::getline(vertexIF, line))
			vertexSource += line + '\n';
	}

	if (fragIF.is_open())
	{
		std::string line;
		while (std::getline(fragIF, line))
			fragSource += line + '\n';
	}

	if (verbose)
	{
		std::cout << vertexPath << ": " << std::endl << vertexSource << std::endl << std::endl;
		std::cout << fragPath << ": " << std::endl << fragSource << std::endl << std::endl;
	}

	const char* vertexCSource = vertexSource.c_str();
	const char* fragCSource = fragSource.c_str();

	GLuint vertexShader, fragShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexCSource, nullptr);
	glCompileShader(vertexShader);

	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragCSource, nullptr);
	glCompileShader(fragShader);

	this->shaderID = glCreateProgram();
	glAttachShader(this->shaderID, vertexShader);
	glAttachShader(this->shaderID, fragShader);
	glLinkProgram(this->shaderID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
}

Shader::~Shader()
{
	glDeleteProgram(this->shaderID);
}

void Shader::use()
{
	glUseProgram(this->shaderID);
}

void Shader::unbind()
{
	glUseProgram(0);
}

void Shader::deleteShader()
{
	glDeleteProgram(this->shaderID);
}

GLint Shader::getUniformLocation(const char* uniformName)
{
	return glGetUniformLocation(this->shaderID, uniformName);
}

void Shader::setBool(const char* uniformName, GLboolean value)
{
	glUniform1i(glGetUniformLocation(this->shaderID, uniformName), (GLint)value);
}

void Shader::setInt(const char* uniformName, GLint value)
{
	glUniform1i(glGetUniformLocation(this->shaderID, uniformName), value);
}

void Shader::setFloat(const char* uniformName, GLfloat value)
{
	glUniform1f(glGetUniformLocation(this->shaderID, uniformName), value);
}

void Shader::set3fv(const char* uniformName, GLsizei count, const GLfloat* value)
{
	glUniform3fv(glGetUniformLocation(this->shaderID, uniformName), count, value);
}

void Shader::set4fv(const char* uniformName, GLsizei count, const GLfloat* value)
{
	glUniform4fv(glGetUniformLocation(this->shaderID, uniformName), count, value);
}

void Shader::setMatrix3fv(const char* uniformName, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	glUniformMatrix3fv(glGetUniformLocation(this->shaderID, uniformName), count, transpose, value);
}

void Shader::setMatrix4fv(const char* uniformName, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	glUniformMatrix4fv(glGetUniformLocation(this->shaderID, uniformName), count, transpose, value);
}