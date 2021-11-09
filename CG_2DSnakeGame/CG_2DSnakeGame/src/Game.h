#pragma once

#define MAX_LENGTH 50
#define UP 1
#define RIGHT 2
#define DOWN -1
#define LEFT -2

struct Cell
{
	int x = 0;
	int y = 0;

	inline bool operator==(const Cell& rhs) const
	{
		return (this->x == rhs.x) && (this->y == rhs.y);
	}
	inline bool operator!=(const Cell& rhs) const
	{
		return !(*this == rhs);
	}
};

class Game
{
public:
	Game(int tileCountp);

	void drawSnake();
	void drawGrid();
	void drawFood();
	int genRandom(int min, int max);

	void setSnakeDirection(int x);
	int getSnakeDirection();
	bool isGameOver();

private:
	int tileCount;
	bool gameOver;

	int snakePosX[MAX_LENGTH + 1];
	int snakePosY[MAX_LENGTH + 1];
	int snakeLength;
	int snakeDirection;
	bool snakeLengthInc;

	Cell foodPos;
	bool foodExists;
	bool randSeed;
};