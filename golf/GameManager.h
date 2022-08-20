#pragma once

#include <vector>

#include "Shader.h"
#include "Texture.h"
#include "GameObject2D.h"

enum GameState
{
	MENU, AIMING, MOVING, HOLE
};

struct GameManager
{
	GameObject2D& ball, &hole, &endText;
	std::vector<std::pair<GameObject2D*, Texture*>> obstacles;
	Shader* shaderProgram;
	float* deltaTime;
	bool showEnd;
	GameState GS;
	int level;

	GameManager(Shader* shaderProgram, float* deltaTime, GameObject2D& ball, GameObject2D& hole, GameObject2D& endText);

	void addObstacle(const char* obstacleName, float x, float y, float z, float width, float height, float scaleX, float scaleY);
	void clearObstacles();
	void renderObstacles();
	void loadLevel(int levelNum);
};