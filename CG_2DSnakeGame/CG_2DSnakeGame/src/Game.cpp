#include <GL/glut.h>
#include "Game.h"
#include <iostream>

int snakePosX[MAX_LENGTH + 1] = { 15 };
int snakePosY[MAX_LENGTH + 1] = { 15 };

Game::Game(int tileCountp)
	:snakeLength(5),
	foodExists(false),
	randSeed(false),
	gameOver(false),
	tileCount(tileCountp),
	snakeDirection(RIGHT) {}

void Game::drawSnake()
{
	for (int i = snakeLength - 1; i > 0; i--)
	{
		snakePosX[i] = snakePosX[i - 1];
		snakePosY[i] = snakePosY[i - 1];
	}

	for (int i = 0; i < snakeLength; i++)
	{
		glColor3f(0.0, 0.5, 0.0);
		if (i == 0)
		{
			glColor3f(0.0, 1.0, 0.0);
			switch (snakeDirection)
			{
			case UP:
				snakePosY[i]++;
				break;
			case DOWN:
				snakePosY[i]--;
				break;
			case RIGHT:
				snakePosX[i]++;
				break;
			case LEFT:
				snakePosX[i]--;
				break;
			}

			// checks for collision with walls
			if (snakePosX[i] == -1 || snakePosX[i] == tileCount || snakePosY[i] == -1 || snakePosY[i] == tileCount)
			{
				gameOver = true;
			}

			// checks for collision with food
			if (snakePosX[i] == foodPos.x && snakePosY[i] == foodPos.y)
			{
				foodExists = false;
				if (snakeLength <= MAX_LENGTH)
					snakeLength++;
			}

			// checks for collision with self
			for (int j = 1; j < snakeLength; j++)
			{
				if (snakePosX[j] == snakePosX[0] && snakePosY[j] == snakePosY[0])
					gameOver = true;
			}
		}
		glBegin(GL_QUADS);
		glVertex2i(snakePosX[i], snakePosY[i]);
		glVertex2i(snakePosX[i] + 1, snakePosY[i]);
		glVertex2i(snakePosX[i] + 1, snakePosY[i] + 1);
		glVertex2i(snakePosX[i], snakePosY[i] + 1);
		glEnd();
	}
}

void Game::drawGrid()
{
	glLoadIdentity();
	for (int x = 0; x < tileCount; x++)
	{
		for (int y = 0; y < tileCount; y++)
		{
			glColor3f(0.4, 0.4, 0.4);
			glBegin(GL_LINES);
			glVertex2i(x, y);			glVertex2i(x + 1, y);
			glVertex2i(x + 1, y);		glVertex2i(x + 1, y + 1);
			glVertex2i(x + 1, y + 1);   glVertex2i(x, y + 1);
			glVertex2i(x, y + 1);	    glVertex2i(x, y);
			glEnd();
		}
	}
}

void Game::drawFood()
{
	if (!foodExists)
	{
		foodPos.x = genRandom(0, tileCount - 1);
		foodPos.y = genRandom(0, tileCount - 1);
		foodExists = true;
	}
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2i(foodPos.x, foodPos.y);
	glVertex2i(foodPos.x + 1, foodPos.y);
	glVertex2i(foodPos.x + 1, foodPos.y + 1);
	glVertex2i(foodPos.x, foodPos.y + 1);
	glEnd();
}

int Game::genRandom(int min, int max)
{
	if (!randSeed)
	{
		srand(time(NULL)); //seeding for the first time only!
		randSeed = true;
	}
	return min + rand() % ((max + 1) - min);
}

void Game::setSnakeDirection(int x)
{
	snakeDirection = x;
}

int Game::getSnakeDirection()
{
	return snakeDirection;
}

bool Game::isGameOver()
{
	return gameOver;
}

