#include <GL/glut.h>
#include "Game.h"
#include <iostream>



Game::Game(int tileCountp)
	: tileCount(tileCountp), 
	foodExists(false),
	randSeed(false),
	gameOver(false),
	snakeLengthInc(false),
	snakeDirection(RIGHT),
	snakeLength(6),
	snakePosX{ 15, 14, 13, 12, 11, 10 },
	snakePosY{ 15, 15, 15, 15, 15, 15 } {}

void Game::drawSnake()
{
	// Shifts the arrays so the body follows the head
	for (int i = snakeLength - 1; i > 0; i--)
	{
		snakePosX[i] = snakePosX[i - 1];
		snakePosY[i] = snakePosY[i - 1];
	}

	// Loop which draws the whole snake
	for (int i = 0; i < snakeLength; i++)
	{
		// Body color
		glColor3f(0.0, 0.5, 0.0);

		// Moves the head according to the direction it's facing
		if (i == 0)
		{
			// Head color
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

			// Checks for collision with walls
			if (snakePosX[i] == -1 || snakePosX[i] == tileCount ||
				snakePosY[i] == -1 || snakePosY[i] == tileCount)
			{
				gameOver = true;
			}

			// Checks for collision with food
			if (snakePosX[i] == foodPos.x &&
				snakePosY[i] == foodPos.y)
			{
				foodExists = false;
				if (snakeLength <= MAX_LENGTH)
					snakeLengthInc = true;
			}

			// Checks for collision with self
			for (int j = 1; j < snakeLength; j++)
			{
				if (snakePosX[j] == snakePosX[0] &&
					snakePosY[j] == snakePosY[0])
				{
					gameOver = true;
				}
			}
		}

		glBegin(GL_QUADS);
		glVertex2i(snakePosX[i], snakePosY[i]);
		glVertex2i(snakePosX[i] + 1, snakePosY[i]);
		glVertex2i(snakePosX[i] + 1, snakePosY[i] + 1);
		glVertex2i(snakePosX[i], snakePosY[i] + 1);
		glEnd();
	}

	// We increment length at the end so we don't draw 
	// the new cell before the arrays are shifted
	if (snakeLengthInc)
	{
		snakeLength++;
		snakeLengthInc = false;
	}
}

void Game::drawGrid()
{

	// Draws lines in the x and y directions to make a grid
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
	// Draws the food at a randomly generated location
	// If there is no food a new location is generated
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
	// Simple random number generator
	if (!randSeed)
	{
		srand(time(NULL));
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

