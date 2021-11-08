#include <GL/glut.h>
#include <iostream>
#include "Game.h"

const unsigned int tileCount = 30;

Game snake(tileCount);
void displayCallback();
void inputCallback(int, int, int);
void reshapeCallback(int, int);
void timerCallback(int);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("2D Snake Game");
	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback);
	glutSpecialFunc(inputCallback);
	glutTimerFunc(100, timerCallback, 0);
	glutMainLoop();
	return 1;
 }

void displayCallback()
{
	if (snake.isGameOver())
	{
		exit(0);
	}
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	snake.drawGrid();
	snake.drawFood();
	snake.drawSnake();
	glutSwapBuffers();
}

void reshapeCallback(int w, int h)
{
	glViewport(0, 0, (GLfloat)w, GLfloat(h));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (float)tileCount, 0.0, (float)tileCount, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void timerCallback(int)
{
	glutPostRedisplay();
	glutTimerFunc(100, timerCallback, 0);
}

void inputCallback(int key, int x, int y)
{
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
