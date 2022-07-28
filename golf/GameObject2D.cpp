#include "GameObject2D.h"

GameObject2D::GameObject2D(float x, float y, float z, float width, float height, float* deltaTime)
	: deltaTime(deltaTime)
	, x(x)
	, y(y)
	, z(z)
	, width(width)
	, height(height)
	, scaleX(1.0f)
	, scaleY(1.0f)
	, forceX(0.0f)
	, forceY(0.0f)
	, rotation(0.0f)
	, opacity(1.0f)
{
	this->viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(this->x, this->y, this->z));
}

void GameObject2D::translateInd(float deltaX, float deltaY)
{
	this->x += deltaX * *deltaTime;
	this->y += deltaY * *deltaTime;
	this->viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(this->x, this->y, this->z));
}

void GameObject2D::translateDep(float deltaX, float deltaY)
{
	this->x += deltaX * *deltaTime;
	this->y += deltaY * *deltaTime;
	this->viewMatrix = glm::translate(this->viewMatrix, glm::vec3(this->x, this->y, this->z));
}

void GameObject2D::scaleInd(glm::vec3 scalars)
{
	this->viewMatrix = glm::scale(glm::mat4(1.0f), scalars);
	this->scaleX = scalars[0];
	this->scaleY = scalars[1];
}

void GameObject2D::scaleDep(glm::vec3 scalars)
{
	this->viewMatrix = glm::scale(this->viewMatrix, scalars);
	this->scaleX *= scalars[0];
	this->scaleY *= scalars[1];
}

void GameObject2D::scaleHybrid(glm::vec3 scalars)
{
	this->viewMatrix = glm::scale(this->viewMatrix, scalars);
	this->scaleX = scalars[0];
	this->scaleY = scalars[1];
}

void GameObject2D::setPos(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(this->x, this->y, this->z));
}

void GameObject2D::rotateInd(float degrees, glm::vec3 axis)
{
	this->viewMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(degrees), axis);
	this->rotation = degrees;
}

void GameObject2D::rotateDep(float degrees, glm::vec3 axis)
{
	this->viewMatrix = glm::rotate(this->viewMatrix, glm::radians(degrees), axis);
	this->rotation = degrees;
}

void GameObject2D::forceTranslation()
{
	this->x += this->forceX * *this->deltaTime;
	this->y += this->forceY * *this->deltaTime;
	this->viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(this->x, this->y, this->z));
}

void GameObject2D::applyFriction(float fricScalarX, float fricScalarY)
{
	if (abs(this->forceX) <= 0.15f)
		this->forceX *= 1.0f - (2.0f * fricScalarX * *deltaTime);
	else if (abs(this->forceX) <= 0.35f)
		this->forceX *= 1.0f - (1.5f * fricScalarX * *deltaTime);
	else
		this->forceX *= 1.0f - (fricScalarX * *deltaTime);

	if (abs(this->forceY) <= 0.15f)
		this->forceY *= 1.0f - (2.0f * fricScalarY * *deltaTime);
	else if (abs(this->forceY) <= 0.35f)
		this->forceY *= 1.0f - (1.5f * fricScalarY * *deltaTime);
	else
		this->forceY *= 1.0f - (fricScalarY * *deltaTime);

	if (abs(this->forceX) <= 0.0085f)
		this->forceX = 0.0f;
	if (abs(this->forceY) <= 0.0085f)
		this->forceY = 0.0f;
}

void GameObject2D::setForceX(float fX)
{
	this->forceX = fX;
}

void GameObject2D::setForceY(float fY)
{
	this->forceY = fY;
}

bool GameObject2D::centerIsTouching(GameObject2D& other, float tolerance)
{
	if (this->x >= other.x - (tolerance * ((other.width / 2.0f) * other.scaleX)) && this->x <= other.x + tolerance * (((other.width / 2.0f) * other.scaleX)) &&
		this->y >= other.y - (tolerance * ((other.height / 2.0f) * other.scaleY)) && this->y <= other.y + tolerance * (((other.height / 2.0f) * other.scaleY)))
		return true;
	else
		return false;
}

bool GameObject2D::xInside(GameObject2D& other)
{
	return true;
}

bool GameObject2D::yInside(GameObject2D& other)
{
	return true;
}