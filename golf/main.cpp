#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <irrKlang/irrKlang.h>

#include <iostream>

#include "Shader.h"
#include "Texture.h"
#include "Object2D.h"
#include "GameManager.h"
#include "GameObject2D.h"

unsigned WINDOWWIDTH, WINDOWHEIGHT;
float prevTime = 0.0f, currTime, deltaTime;

float rgb2f(int value)
{
	return value / 255.0f;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void gameControls(irrklang::ISoundEngine* soundEngine, GLFWwindow* window, GameObject2D& ball, GameObject2D& line, float& power, Texture& powerTexture)
{
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		power = 0.625f;
		powerTexture.replaceTexture("textures/powerLow.png", true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		power = 0.875f;
		powerTexture.replaceTexture("textures/powerMLow.png", true);
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		power = 1.125f;
		powerTexture.replaceTexture("textures/powerMHigh.png", true);
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		power = 1.375f;
		powerTexture.replaceTexture("textures/powerHigh.png", true);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS || glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{
		soundEngine->play2D("audio/putt.mp3");
		ball.setForceX(power * -sinf(glm::radians(line.rotation)));
		ball.setForceY(power * cosf(glm::radians(line.rotation)));
	}
}

int main()
{
	if (!glfwInit())
	{
		std::cout << "failed to initialize glfw" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int monitorX, monitorY;
	glfwGetMonitorPos(glfwGetPrimaryMonitor(), &monitorX, &monitorY);

	const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	WINDOWWIDTH = (unsigned)(videoMode->height * 0.825f); WINDOWHEIGHT = (unsigned)(videoMode->height * 0.825f);

	std::cout << "window resolution: " << WINDOWWIDTH << "x" << WINDOWHEIGHT << std::endl;

	GLFWwindow* window = glfwCreateWindow(WINDOWWIDTH, WINDOWHEIGHT, "OpenGoLf", nullptr, nullptr);
	if (!window)
	{
		std::cout << "failed to initialize window" << std::endl;
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0); // vsync off
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetWindowPos(window, 
		monitorX + (videoMode->width - WINDOWWIDTH) / 2,
		monitorY + (videoMode->height - WINDOWHEIGHT) / 2);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to initialize glad" << std::endl;
		return -1;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	stbi_set_flip_vertically_on_load(true);

	GLfloat grassVertices[]
	{
		-1.0f,  1.0f, 0.0f,		0.0f, 5.5f, // tl
		 1.0f,  1.0f, 0.0f,		5.5f, 5.5f, // tr
		-1.0f, -1.0f, 0.0f,		0.0f, 0.0f, // bl
		 1.0f, -1.0f, 0.0f,		5.5f, 0.0f  // br
	};

	GLuint grassIndices[]
	{
		0, 1, 2,
		1, 2, 3
	};

	GLfloat centerQuadVertices[]
	{
		-0.03f,  0.03f, 0.0f,		0.0f, 1.0f, // tl
		 0.03f,  0.03f, 0.0f,		1.0f, 1.0f, // tr
		-0.03f, -0.03f, 0.0f,		0.0f, 0.0f, // bl
		 0.03f, -0.03f, 0.0f,		1.0f, 0.0f  // br
	};

	GLuint centerQuadIndices[]
	{
		0, 1, 2,
		1, 2, 3
	};

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 projMatrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);

	Shader grassShader("shaders/grass.vert", "shaders/grass.frag", false);
	Shader quadShader("shaders/ball.vert", "shaders/ball.frag", false);

	Object2D grassO2D(grassVertices, sizeof(grassVertices), grassIndices, sizeof(grassIndices));
	grassO2D.vertexAttrib(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0x00);
	grassO2D.vertexAttrib(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	Object2D centerQuadO2D(centerQuadVertices, sizeof(centerQuadVertices), centerQuadIndices, sizeof(centerQuadIndices));
	centerQuadO2D.vertexAttrib(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0x00);
	centerQuadO2D.vertexAttrib(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	Texture grassTexture("textures/square.png", true);
	Texture ballTexture("textures/ball.png", true);
	Texture lineTexture("textures/line.png", true);
	Texture holeTexture("textures/hole.png", true);
	Texture powerTexture("textures/powerMHigh.png", true);
	Texture controlsTextTexture("textures/controlstext.png", true);
	Texture endTextTexture("textures/endtext.png", true);

	GameObject2D ballGO2D(0.0f, -0.55f, 0.0f, 0.06f, 0.06f, &deltaTime);
	GameObject2D lineGO2D(0.0f, -0.55f, 0.0f, 0.06f, 0.06f, &deltaTime);
	GameObject2D powerGO2D(-0.85f, -0.8f, 0.0f, 0.6f, 0.6f, &deltaTime);
	GameObject2D holeGO2D(0.0f, 0.725f, 0.0f, 0.06f, 0.06f, &deltaTime);
	GameObject2D controlsGO2D(0.0f, 0.0f, 0.0f, 0.06f, 0.06f, &deltaTime);
	GameObject2D endTextGO2D(0.0f, 0.0f, 0.0f, 0.06f, 0.06f, &deltaTime);

	powerGO2D.opacity = 0.5f;

	GameManager GM(&quadShader, &deltaTime, ballGO2D, holeGO2D, endTextGO2D);

	float power = 1.125f;
	bool displayText = false;

	irrklang::ISoundEngine* soundEngine = irrklang::createIrrKlangDevice();
	bool canPlayInHoleSound = true;

	while (!glfwWindowShouldClose(window))
	{
		// timestep update
		currTime = (float)glfwGetTime();
		deltaTime = currTime - prevTime;
		prevTime = currTime;

		glClearColor(.50f, .5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		processInput(window);

		grassShader.use();

		grassO2D.bindVAO();
		grassTexture.bindTexture();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0x00);

		quadShader.use();
		centerQuadO2D.bindVAO();
		quadShader.setMatrix4fv("model", 1, GL_FALSE, glm::value_ptr(modelMatrix));
		quadShader.setMatrix4fv("proj", 1, GL_FALSE, glm::value_ptr(projMatrix));

		if (GM.GS == GameState::MENU)
		{
			controlsTextTexture.bindTexture();

			controlsGO2D.setPos(0.0f, 0.0f, 0.0f);
			controlsGO2D.scaleDep(glm::vec3(32.5f, 32.5f, 1.0f));
			quadShader.setFloat("opacity", controlsGO2D.opacity);
			quadShader.setMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(controlsGO2D.viewMatrix));
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0x00);

			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			{
				GM.loadLevel(GM.level);
			}

			glfwSwapBuffers(window);
			glfwPollEvents();

			continue;
		}
		else
		{
			if (ballGO2D.centerIsTouching(holeGO2D, 0.6f))
				GM.GS = GameState::HOLE;
			else if (abs(ballGO2D.forceX) <= 0.0085f && abs(ballGO2D.forceY) <= 0.0085f)
				GM.GS = GameState::AIMING;
			else
				GM.GS = GameState::MOVING;
		}

		holeTexture.bindTexture();
		holeGO2D.setPos(holeGO2D.x, holeGO2D.y, 0.0f);
		holeGO2D.scaleHybrid(glm::vec3(1.4f, 1.4f, 1.0f));
		quadShader.setFloat("opacity", holeGO2D.opacity);
		quadShader.setMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(holeGO2D.viewMatrix));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0x00);

		ballGO2D.forceTranslation();
		ballGO2D.applyFriction(1.0f, 1.0f);

		GM.renderObstacles();

		switch(GM.GS)
		{
			case GameState::AIMING:
				gameControls(soundEngine, window, ballGO2D, lineGO2D, power, powerTexture);

				lineGO2D.setPos(ballGO2D.x, ballGO2D.y, 0.0f);
				lineGO2D.rotateDep(-4.0f * atan2f(sinf((float)glfwGetTime()), cosf((float)glfwGetTime())) * (180.0f / 3.1415926535897f),
					glm::vec3(0.0f, 0.0f, 1.0f));
				if (power == 0.625f)
					lineGO2D.scaleDep(glm::vec3(7.0f, 5.0f, 1.0f));
				else if (power == 0.875f)
					lineGO2D.scaleDep(glm::vec3(7.0f, 6.0f, 1.0f));
				else if (power == 1.125f)
					lineGO2D.scaleDep(glm::vec3(7.0f, 7.0f, 1.0f));
				else if (power == 1.375f)
					lineGO2D.scaleDep(glm::vec3(7.0f, 8.0f, 1.0f));
				else
					std::cout << "unknown line scale" << std::endl;

				quadShader.setFloat("opacity", lineGO2D.opacity);
				quadShader.setMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(lineGO2D.viewMatrix));

				lineTexture.bindTexture();
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0x00);
				canPlayInHoleSound = true;
				break;

			case GameState::MOVING:
				// wall collision detection
				if (ballGO2D.x + (ballGO2D.width / 2.0f) >= 1.0f || ballGO2D.x - (ballGO2D.width / 2.0f) <= -1.0f)
				{
					ballGO2D.forceX = -ballGO2D.forceX;
					soundEngine->play2D("audio/bound.mp3");
				}
				if (ballGO2D.y + (ballGO2D.height / 2.0f) >= 1.0f || ballGO2D.y - (ballGO2D.height / 2.0f) <= -1.0f)
				{
					ballGO2D.forceY = -ballGO2D.forceY;
					soundEngine->play2D("audio/bound.mp3");
				}

				for (int i = 0; i < GM.obstacles.size(); i++)
				{
					// ball right side encroachment
					if (ballGO2D.x + (ballGO2D.width / 2.0f) >= GM.obstacles[i].first->x - (GM.obstacles[i].first->scaleX * (GM.obstacles[i].first->width / 2.0f)) // bR >= oL
						&& ballGO2D.x - (ballGO2D.width / 2.0f) <= GM.obstacles[i].first->x - (GM.obstacles[i].first->scaleX * (GM.obstacles[i].first->width / 2.0f)) // bL <= oL
						&& ballGO2D.y + (ballGO2D.height / 2.0f) <= GM.obstacles[i].first->y + ((GM.obstacles[i].first->height / 2.0f) * GM.obstacles[i].first->scaleY) // bT <= oT
						&& ballGO2D.y - (ballGO2D.height / 2.0f) >= GM.obstacles[i].first->y - ((GM.obstacles[i].first->height / 2.0f) * GM.obstacles[i].first->scaleY)) // bB >= oB
					{
						ballGO2D.forceX = -ballGO2D.forceX;
						ballGO2D.setPos(ballGO2D.x - (ballGO2D.width / 5.0f), ballGO2D.y, 0.0f);
						soundEngine->play2D("audio/hit.mp3");
					}

					// ball left side encroachment
					if (ballGO2D.x - (ballGO2D.width / 2.0f) <= GM.obstacles[i].first->x + (GM.obstacles[i].first->scaleX * (GM.obstacles[i].first->width / 2.0f)) // bL <= oR
						&& ballGO2D.x + (ballGO2D.width / 2.0f) >= GM.obstacles[i].first->x + (GM.obstacles[i].first->scaleX * (GM.obstacles[i].first->width / 2.0f)) // bR >= oR
						&& ballGO2D.y + (ballGO2D.height / 2.0f) <= GM.obstacles[i].first->y + ((GM.obstacles[i].first->height / 2.0f) * GM.obstacles[i].first->scaleY) // bT <= oT
						&& ballGO2D.y - (ballGO2D.height / 2.0f) >= GM.obstacles[i].first->y - ((GM.obstacles[i].first->height / 2.0f) * GM.obstacles[i].first->scaleY)) // bB >= oB
					{
						ballGO2D.forceX = -ballGO2D.forceX;
						ballGO2D.setPos(ballGO2D.x + (ballGO2D.width / 5.0f), ballGO2D.y, 0.0f);
						soundEngine->play2D("audio/hit.mp3");
					}

					// ball top side encroachment
					if (ballGO2D.y + (ballGO2D.height / 2.0f) >= GM.obstacles[i].first->y - (GM.obstacles[i].first->scaleY * (GM.obstacles[i].first->height / 2.0f)) // bT >= oB
						&& ballGO2D.y - (ballGO2D.height / 2.0f) <= GM.obstacles[i].first->y - (GM.obstacles[i].first->scaleY * (GM.obstacles[i].first->height / 2.0f)) // bB <= oL
						&& ballGO2D.x + (ballGO2D.width / 2.0f) <= GM.obstacles[i].first->x + ((GM.obstacles[i].first->width / 2.0f) * GM.obstacles[i].first->scaleX) // bR <= oR
						&& ballGO2D.x - (ballGO2D.width / 2.0f) >= GM.obstacles[i].first->x - ((GM.obstacles[i].first->width / 2.0f) * GM.obstacles[i].first->scaleX)) // bL >= oL
					{
						ballGO2D.forceY = -ballGO2D.forceY;
						ballGO2D.setPos(ballGO2D.x, ballGO2D.y - (ballGO2D.height / 5.0f), 0.0f);
						soundEngine->play2D("audio/hit.mp3");
					}

					// ball bottom side encroachment
					if (ballGO2D.y - (ballGO2D.height / 2.0f) <= GM.obstacles[i].first->y + (GM.obstacles[i].first->scaleY * (GM.obstacles[i].first->height / 2.0f)) // bB <= oT
						&& ballGO2D.y + (ballGO2D.height / 2.0f) >= GM.obstacles[i].first->y + (GM.obstacles[i].first->scaleY * (GM.obstacles[i].first->height / 2.0f)) // bT >= oT
						&& ballGO2D.x + (ballGO2D.width / 2.0f) <= GM.obstacles[i].first->x + ((GM.obstacles[i].first->width / 2.0f) * GM.obstacles[i].first->scaleX) // bR <= oR
						&& ballGO2D.x - (ballGO2D.width / 2.0f) >= GM.obstacles[i].first->x - ((GM.obstacles[i].first->width / 2.0f) * GM.obstacles[i].first->scaleX)) // bL >= oL
					{
						ballGO2D.forceY = -ballGO2D.forceY;
						ballGO2D.setPos(ballGO2D.x, ballGO2D.y + (ballGO2D.height / 5.0f), 0.0f);
						soundEngine->play2D("audio/hit.mp3");
					}
				}
				canPlayInHoleSound = true;
				break;

			case GameState::HOLE:
				ballGO2D.setPos(holeGO2D.x, holeGO2D.y, 0.0f);
				ballGO2D.opacity -= 1.0f * deltaTime;

				if (canPlayInHoleSound)
				{
					soundEngine->play2D("audio/inhole.mp3");
					std::cout << "playing" << std::endl;
					canPlayInHoleSound = false;
				}

				if (ballGO2D.opacity <= -2.0f)
				{
					ballGO2D.setForceX(0.0f);
					ballGO2D.setForceY(0.0f);
					GM.loadLevel(++GM.level);
				}
				break;
		}

		ballTexture.bindTexture();
		quadShader.setFloat("opacity", ballGO2D.opacity);
		quadShader.setMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(ballGO2D.viewMatrix));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0x00);

		if (GM.showEnd)
		{
			endTextTexture.bindTexture();
			endTextGO2D.setPos(0.0f, 0.5f, 0.0f);
			endTextGO2D.scaleDep(glm::vec3(20.0f, 20.0f, 1.0f));
			quadShader.setFloat("opacity", endTextGO2D.opacity);
			quadShader.setMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(endTextGO2D.viewMatrix));
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0x00);
		}

		powerTexture.bindTexture();
		powerGO2D.setPos(powerGO2D.x, powerGO2D.y, 0.0f);
		powerGO2D.scaleHybrid(glm::vec3(2.5f, 5.0f, 1.0f));
		quadShader.setFloat("opacity", powerGO2D.opacity);
		quadShader.setMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(powerGO2D.viewMatrix));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0x00);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// memory deallocation is handled in class destructors
	glfwDestroyWindow(window);
	glfwTerminate();
}