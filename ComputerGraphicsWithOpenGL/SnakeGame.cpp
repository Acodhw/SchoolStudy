#include "include/GL/freeglut.h"
#include "include/GL/glut.h" 
#include <math.h>
#include <vector>
#include <iostream>
#include <ctime>

using namespace std;

int Width = 500, Height = 500;

typedef struct snakeBody {
	float x;
	float y;
}SnakeBody;

vector<SnakeBody> snake;

void Display();
void Reshape(int w, int h);
void Close();
void Keyboard(unsigned char key, int x, int y);
void Arrow(int key, int x, int y);
void Timer(int id);
void CreateMenu(int id);
void diffMenu(int id);

int direction[] = { 1,0 };
float headpoint[] = { 1.5f, 1.5f };
float applePoint[] = { 1.5f, 1.5f };

bool isGameOver = false;
bool isApple = false;
int score = 0;

int timespeed = 300;

bool PointCheckonSnake(float x, float y) {
	if (snake.size() == 0) return false;
	vector<SnakeBody>::iterator iter;
	for (iter = snake.begin(); iter != snake.end(); iter++) {
		if (iter->x == x && iter->y == y) return true;
	}
	return false;
}

void appleSpawn() {
	if (!isApple) {
		float ax = (rand() % 20) + 1.5f, ay = (rand() % 20) + 1.5f;
		while ((ax == headpoint[0] && ay == headpoint[1]) || PointCheckonSnake(ax, ay)) {
			ax = (rand() % 20) + 1.5f;
			ay = (rand() % 20) + 1.5f;
		}
		applePoint[0] = ax;
		applePoint[1] = ay;
		isApple = true;
	}
}

int main(int argc, char** argv)
{
	cout << "SCORE : 0" << endl;
	srand(time(0));
	appleSpawn();

	glutInit(&argc, argv);

	glutInitWindowSize(Width, Height);
	glutInitWindowPosition(0, 0);

	glutInitDisplayMode(GLUT_RGBA);

	glutCreateWindow("Snake Game");

	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutCloseFunc(Close);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Arrow);
	glutTimerFunc(timespeed, Timer, 0);

	GLint DifferentMenu = glutCreateMenu(diffMenu);
	glutAddMenuEntry("EASY", 0);
	glutAddMenuEntry("NORMAL", 1);
	glutAddMenuEntry("HARD", 2);
	glutAddMenuEntry("HELL", 3);

	GLint CreateMenuId = glutCreateMenu(CreateMenu);
	glutAddMenuEntry("RESTART", 0);
	glutAddSubMenu("CHANGE DIFFERENT", DifferentMenu);
	glutAddMenuEntry("EXIT", 1);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}

void gameReset() {
	system("cls");
	cout << "SCORE : 0" << endl;
	isApple = false;
	snake = vector<SnakeBody>();
	score = 0;
	headpoint[0] = 1.5f;
	headpoint[1] = 1.5f;
	direction[0] = 1;
	direction[1] = 0;
	appleSpawn();
	isGameOver = false;
}

void diffMenu(int id)
{
	if (id == 0)
		timespeed = 300;
	else if (id == 1)
		timespeed = 150;
	else if (id == 2)
		timespeed = 75;
	else if (id == 3)
		timespeed = 25;
	gameReset();
}

void CreateMenu(int id)
{
	if (id == 0)
		gameReset();
	else if (id == 1)
		exit(0);
}

bool gameOverCheck() {
	return (headpoint[0] < 1 || headpoint[0] > 21 || headpoint[1] < 1 || headpoint[1] > 21) || PointCheckonSnake(headpoint[0], headpoint[1]);
}

void snakeMove()
{
	if (score >= 1) {
		float tmpx, tmpy, B_tmpx, B_tmpy;
		vector<SnakeBody>::iterator iter = snake.begin();

		B_tmpx = iter->x;
		B_tmpy = iter->y;

		iter->x = headpoint[0];
		iter->y = headpoint[1];

		for (iter = (snake.begin() + 1); iter != snake.end(); iter++) {
			tmpx = iter->x;
			tmpy = iter->y;

			iter->x = B_tmpx;
			iter->y = B_tmpy;

			B_tmpx = tmpx;
			B_tmpy = tmpy;
		}
	}

	headpoint[0] += direction[0];
	headpoint[1] += direction[1];
}

void Timer(int id)
{
	snakeMove();

	if (gameOverCheck() && !isGameOver) {
		system("cls");
		cout << "GAME OVER! \nYOUR SCORE : " << score << endl;
		isGameOver = true;
	}

	if (headpoint[0] == applePoint[0] && headpoint[1] == applePoint[1]) {
		snakeBody body;
		if (score >= 1) {
			vector<SnakeBody>::iterator iter = snake.begin() + score - 1;
			body.x = iter->x;
			body.y = iter->y;
		}
		else {
			body.x = headpoint[0];
			body.y = headpoint[1];
		}
		snake.push_back(body);
		score += 1;
		system("cls");
		cout << "SCORE : " << score << endl;
		isApple = false;
	}

	appleSpawn();

	glutPostRedisplay();
	glutTimerFunc(timespeed, Timer, 0);
}

void Reshape(int w, int h) {
	if (11 * h > 11 * w) {
		glViewport(0, (h - ((w))) / 2, w, (((w))));
	}
	else {
		glViewport((w - ((h))) / 2, 0, ((h)), h);
	}
	Width = w;
	Height = h;
}

void Display()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 22, 0, 22);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_QUADS);
	{
		glColor3f(0, 0, 0);
		glVertex2i(1, 1);
		glVertex2i(21, 1);
		glVertex2i(21, 21);
		glVertex2i(1, 21);
	}
	glEnd();

	if (!isGameOver) {
		glBegin(GL_QUADS);
		{
			glColor3f(1, 0, 0);
			glVertex2f(applePoint[0] + 0.5f, applePoint[1] + 0.5f);
			glVertex2f(applePoint[0] - 0.5f, applePoint[1] + 0.5f);
			glVertex2f(applePoint[0] - 0.5f, applePoint[1] - 0.5f);
			glVertex2f(applePoint[0] + 0.5f, applePoint[1] - 0.5f);
		}
		glEnd();
		//player
		glBegin(GL_QUADS);
		{
			glColor3f(0, 1, 0);
			glVertex2f(headpoint[0] + 0.5f, headpoint[1] + 0.5f);
			glVertex2f(headpoint[0] - 0.5f, headpoint[1] + 0.5f);
			glVertex2f(headpoint[0] - 0.5f, headpoint[1] - 0.5f);
			glVertex2f(headpoint[0] + 0.5f, headpoint[1] - 0.5f);
		}
		glEnd();
		if (score >= 1) {
			vector<SnakeBody>::iterator iter;
			for (iter = snake.begin(); iter != snake.end(); iter++) {
				glBegin(GL_QUADS);
				{
					glColor3f(0, 1, 0);
					glVertex2f(iter->x + 0.5f, iter->y + 0.5f);
					glVertex2f(iter->x - 0.5f, iter->y + 0.5f);
					glVertex2f(iter->x - 0.5f, iter->y - 0.5f);
					glVertex2f(iter->x + 0.5f, iter->y - 0.5f);
				}
				glEnd();
			}
		}
	}
	else {
		glBegin(GL_QUADS);
		{
			glColor3f(1, 1, 1);
			glVertex2f(9, 14);
			glVertex2f(5, 14);
			glVertex2f(5, 13);
			glVertex2f(9, 13);
		}
		glEnd();
		glBegin(GL_QUADS);
		{
			glColor3f(1, 1, 1);
			glVertex2f(5, 13);
			glVertex2f(5, 9);
			glVertex2f(6, 9);
			glVertex2f(6, 13);
		}
		glEnd();
		glBegin(GL_QUADS);
		{
			glColor3f(1, 1, 1);
			glVertex2f(9, 10);
			glVertex2f(6, 10);
			glVertex2f(6, 9);
			glVertex2f(9, 9);
		}
		glEnd();
		glBegin(GL_QUADS);
		{
			glColor3f(1, 1, 1);
			glVertex2f(9, 12);
			glVertex2f(8, 12);
			glVertex2f(8, 10);
			glVertex2f(9, 10);
		}
		glEnd();
		glBegin(GL_QUADS);
		{
			glColor3f(1, 1, 1);
			glVertex2f(8, 12);
			glVertex2f(7, 12);
			glVertex2f(7, 11);
			glVertex2f(8, 11);
		}
		glEnd();

		glBegin(GL_QUADS);
		{
			glColor3f(1, 1, 1);
			glVertex2f(17, 14);
			glVertex2f(13, 14);
			glVertex2f(13, 13);
			glVertex2f(17, 13);
		}
		glEnd();
		glBegin(GL_QUADS);
		{
			glColor3f(1, 1, 1);
			glVertex2f(13, 13);
			glVertex2f(13, 9);
			glVertex2f(14, 9);
			glVertex2f(14, 13);
		}
		glEnd();
		glBegin(GL_QUADS);
		{
			glColor3f(1, 1, 1);
			glVertex2f(17, 10);
			glVertex2f(14, 10);
			glVertex2f(14, 9);
			glVertex2f(17, 9);
		}
		glEnd();
		glBegin(GL_QUADS);
		{
			glColor3f(1, 1, 1);
			glVertex2f(17, 12);
			glVertex2f(16, 12);
			glVertex2f(16, 10);
			glVertex2f(17, 10);
		}
		glEnd();
		glBegin(GL_QUADS);
		{
			glColor3f(1, 1, 1);
			glVertex2f(16, 12);
			glVertex2f(15, 12);
			glVertex2f(15, 11);
			glVertex2f(16, 11);
		}
		glEnd();

	}

	glutSwapBuffers();
}

void Close()
{
	system("cls");
	cout << "GAME OVER! \nYOUR SCORE : " << score << endl;
	isGameOver = true;
}


void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'w') {
		direction[0] = 0;
		direction[1] = 1;
	}
	if (key == 'd') {
		direction[0] = 1;
		direction[1] = 0;
	}
	if (key == 'a') {
		direction[0] = -1;
		direction[1] = 0;
	}
	if (key == 's') {
		direction[0] = 0;
		direction[1] = -1;
	}

	if (key == 'r') gameReset();

}

void Arrow(int key, int x, int y)
{
	if (key == GLUT_KEY_UP) {
		direction[0] = 0;
		direction[1] = 1;
	}
	if (key == GLUT_KEY_RIGHT) {
		direction[0] = 1;
		direction[1] = 0;
	}
	if (key == GLUT_KEY_LEFT) {
		direction[0] = -1;
		direction[1] = 0;
	}
	if (key == GLUT_KEY_DOWN) {
		direction[0] = 0;
		direction[1] = -1;
	}


}
