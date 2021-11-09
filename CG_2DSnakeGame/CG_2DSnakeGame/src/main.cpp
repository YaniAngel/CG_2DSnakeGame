#include <GL/glut.h>
#include <iostream>
#include "Game.h"

const unsigned int tileCount = 30;

Game snake(tileCount);
void renderScene();
void processKeyboard(int, int, int);
void changeSize(int, int);
void refreshScene(int);

int main(int argc, char** argv)
{
	// Init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("2D Snake Game");

	// Register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutSpecialFunc(processKeyboard);

	// Refresh so the snake keeps moving
	glutTimerFunc(1000.0/10.0, refreshScene, 0);

	// enter GLUT event processing cycle
	glutMainLoop();
	return 1;
 }

void renderScene()
{
	// Exits the game if gameOver is set to true
	if (snake.isGameOver())
	{
		exit(0);
	}

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Draw everything
	snake.drawGrid();
	snake.drawFood();
	snake.drawSnake();

	glutSwapBuffers();
}

void changeSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	if (h == 0)
		h = 1;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Reset Matrix
	glLoadIdentity();

	// Set the coordinate system to 40 by 40
	glOrtho(0.0, (float)tileCount, 0.0, (float)tileCount, -1.0, 1.0);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void refreshScene(int)
{
	// Update animation
	glutPostRedisplay();

	// Keep updating
	glutTimerFunc(1000.0/10.0, refreshScene, 0);
}

void processKeyboard(int key, int x, int y)
{
	// Changes direction of the snake
	// Can't change into opposite direction 
	switch (key)
	{
	case GLUT_KEY_UP:
		if (snake.getSnakeDirection() != DOWN)
			snake.setSnakeDirection(UP);
		break;
	case GLUT_KEY_DOWN:
		if (snake.getSnakeDirection() != UP)
			snake.setSnakeDirection(DOWN);
		break;
	case GLUT_KEY_RIGHT:
		if (snake.getSnakeDirection() != LEFT)
			snake.setSnakeDirection(RIGHT);
		break;
	case GLUT_KEY_LEFT:
		if (snake.getSnakeDirection() != RIGHT)
			snake.setSnakeDirection(LEFT);
		break;
	}
}
