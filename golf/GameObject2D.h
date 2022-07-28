#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum POSR // positional relativity
{
	TL, TM, TR,
	ML, MM, MR,
	BL, BM, BR
};

class GameObject2D
{
public:
	float x, y, z, width, height, scaleX, scaleY, forceX, forceY, rotation, opacity;
	float* deltaTime;
	glm::mat4 viewMatrix;

	GameObject2D(float x, float y, float z, float width, float height, float* deltaTime);

	void translateInd(float deltaX, float deltaY);
	void translateDep(float deltaX, float deltaY);
	void scaleInd(glm::vec3 scalars);
	void scaleDep(glm::vec3 scalars);
	void scaleHybrid(glm::vec3 scalars);
	void setPos(float x, float y, float z);
	void rotateInd(float degrees, glm::vec3 axis);
	void rotateDep(float degrees, glm::vec3 axis);
	void forceTranslation();
	void applyFriction(float fricScalarX, float fricScalarY);
	void setForceX(float fX);
	void setForceY(float fY);
	bool centerIsTouching(GameObject2D& other, float tolerance);
	bool xInside(GameObject2D& other);
	bool yInside(GameObject2D& other);
};

