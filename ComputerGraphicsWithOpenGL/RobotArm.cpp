#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include ".\usr\include\GL\freeglut.h"
#include <vector>

#define HUMONOID_BASE_HEIGHT 3

int Width = 800, Height = 800;
int ManipulateMode = 0;
int controlMode = 0;

float ControledAngle[19][3] = { 0, };

float ControledAngleLimit[19][6] = { //(-x limit, +x limit, -y limit, +y limit, -z limit, +z limit) (if +limit > 180 && -limit < -180 => no limit);
{-200, 200, -200, 200, -200, 200}, //Spine
{-25, 25, -60, 60, -45, 45}, //Hip
{-30, 110, -30, 30, -45, 45}, //Chest
{-90, 45, -60, 30, -60, 30}, //RightUpperLeg
{0, 135, 0, 0, 0, 0}, //RightLowerLeg
{-10, 80, -10, 10, 0, 0}, //RightFoot
{-90, 45, -30, 60, -30, 60}, //LeftUpperLeg
{0, 135, 0, 0, 0, 0}, //LeftLowerLeg
{-10, 80, -10, 10, 0, 0}, //LeftFoot
{-45, 45, -85, 85, -30, 30}, //Neck
{-45, 45, 0, 0, -20, 20}, //Head
{-45, 45, -25, 125, -90, 90}, //RightShoulder
{-90, 90, 0, 0, 0, 0}, //RightUpperArm
{-90, 30, 0, 140, 0, 0}, //RightLowerArm
{0, 0, -30, 30, -90, 90}, //RightHand
{-45, 45, -125, 25, -90, 90}, //LeftShoulder
{-90, 90, 0, 0, 0, 0}, //LeftUpperArm
{-90, 30, -140, 0, 0, 0}, //LeftLowerArm
{0, 0, -30, 30, -90, 90}, //LeftHand
};

int StartPt[2];
float Axis[3] = { 1.0, 0.0, 0.0 };
float Angle = 0.0;
float RotMat[16] = { 1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1 };
float Zoom = -30.0;
float Pan[3] = { 0.0, 0.0, 0.0 };

void BodyControlMenu(int id);
void Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void MouseWheel(int button, int dir, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Render();

void InitOpenGL();
void GetSphereCoord(int x, int y, float *px, float *py, float *pz);
void RenderFloor();
void RenderHierarchy();
void drawCube(float sx, float sy, float sz);
void SetupViewVolume();
void SetupViewTransform();
void Sub(double out[3], double a[3], double b[3]);
void Add(double out[3], double a[3], double b[3]);
void Cross(double out[3], double a[3], double b[3]);


void Cross(double out[3], double a[3], double b[3])
{
	out[0] = a[1] * b[2] - a[2] * b[1];
	out[1] = a[2] * b[0] - a[0] * b[2];
	out[2] = a[0] * b[1] - a[1] * b[0];
}

void Sub(double out[3], double a[3], double b[3])
{
	out[0] = a[0] - b[0];
	out[1] = a[1] - b[1];
	out[2] = a[2] - b[2];
}

void Add(double out[3], double a[3], double b[3])
{
	out[0] = a[0] + b[0];
	out[1] = a[1] + b[1];
	out[2] = a[2] + b[2];
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(Width, Height);
	glutCreateWindow("3DPosing Program");

	InitOpenGL();

	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutMotionFunc(Motion);
	glutMouseWheelFunc(MouseWheel);
	glutDisplayFunc(Render);

	
	GLint RightArm = glutCreateMenu(BodyControlMenu);
	glutAddMenuEntry("RightShoulder", 11);
	glutAddMenuEntry("RightUpperArm", 12);
	glutAddMenuEntry("RightLowerArm", 13);
	glutAddMenuEntry("RightHand", 14);

	GLint LeftArm = glutCreateMenu(BodyControlMenu);
	glutAddMenuEntry("LeftShoulder", 15);
	glutAddMenuEntry("LeftUpperArm", 16);
	glutAddMenuEntry("LeftLowerArm", 17);
	glutAddMenuEntry("LeftHand", 18);
	
	GLint Head = glutCreateMenu(BodyControlMenu);
	glutAddMenuEntry("Neck", 9);
	glutAddMenuEntry("Head", 10);

	GLint RightLeg = glutCreateMenu(BodyControlMenu);
	glutAddMenuEntry("RightUpperLeg", 3);
	glutAddMenuEntry("RightLowerLeg", 4);
	glutAddMenuEntry("RightFoot", 5);

	GLint LeftLeg = glutCreateMenu(BodyControlMenu);
	glutAddMenuEntry("LeftUpperLeg", 6);
	glutAddMenuEntry("LeftLowerLeg", 7);
	glutAddMenuEntry("LeftFoot", 8);

	GLint Body = glutCreateMenu(BodyControlMenu);
	glutAddMenuEntry("Chest", 2);
	glutAddSubMenu("RightArm", RightArm);
	glutAddSubMenu("LeftArm", LeftArm);
	glutAddSubMenu("Head", Head);

	GLint Base = glutCreateMenu(BodyControlMenu);
	glutAddMenuEntry("Spine", 0);
	glutAddMenuEntry("Hip", 1);
	glutAddSubMenu("UpperBody", Body);
	glutAddSubMenu("RightLeg", RightLeg);
	glutAddSubMenu("LeftLeg", LeftLeg);

	glutAttachMenu(GLUT_MIDDLE_BUTTON);

	glutMainLoop();
	return 0;
}

void BodyControlMenu(int id) {
	controlMode = id;
}

void InitOpenGL()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);	
}

void Render()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetupViewVolume();

	SetupViewTransform();

	glMatrixMode(GL_MODELVIEW);
	RenderFloor();
	RenderHierarchy();

	glutSwapBuffers();
}

void RenderHierarchy()
{
	//chest
	glTranslatef(0, HUMONOID_BASE_HEIGHT, 0);
	glRotatef(ControledAngle[0][0], 1,0,0);
	glRotatef(ControledAngle[0][1], 0,1,0);
	glRotatef(ControledAngle[0][2], 0,0,1);
	drawCube(2, 1, 1);

	//lowerBody
	glPushMatrix();
	//hip
	glTranslatef(0, -0.9f, 0);
	glRotatef(ControledAngle[1][0], 1, 0, 0);
	glRotatef(ControledAngle[1][1], 0, 1, 0);
	glRotatef(ControledAngle[1][2], 0, 0, 1);
	drawCube(0.1f, 0.1f, 0.1f);
	glTranslatef(0, -0.1f, 0);
	glutSolidSphere(1, 30, 17);

	//RightLeg
	glPushMatrix();
	//RightUpperLeg
	glTranslatef(-0.75f, 0, 0);
	glRotatef(ControledAngle[3][0], 1, 0, 0);
	glRotatef(ControledAngle[3][1], 0, 1, 0);
	glRotatef(ControledAngle[3][2], 0, 0, 1);
	glutSolidSphere(0.1f, 30, 17);
	glTranslatef(0, -4, 0);
	drawCube(1, 4, 1);
	//RightLowerLeg
	glTranslatef(0, -0.5f, 0);
	glRotatef(ControledAngle[4][0], 1, 0, 0);
	glRotatef(ControledAngle[4][1], 0, 1, 0);
	glRotatef(ControledAngle[4][2], 0, 0, 1);
	glutSolidSphere(0.5f, 30, 17);
	glTranslatef(0, -4.5f, 0);
	drawCube(0.7f, 4, 0.7f);
	//RightFoot
	glTranslatef(0, -0.1f, 0);
	glRotatef(ControledAngle[5][0], 1, 0, 0);
	glRotatef(ControledAngle[5][1], 0, 1, 0);
	glRotatef(ControledAngle[5][2], 0, 0, 1);
	glutSolidSphere(0.1f, 30, 17);
	glTranslatef(0, -0.25f, 0.5f);
	drawCube(0.5f, 0.5f, 1.5f);
	glPopMatrix();

	//LeftLeg
	glPushMatrix();
	//LeftUpperLeg
	glTranslatef(0.75f, 0, 0);
	glRotatef(ControledAngle[6][0], 1, 0, 0);
	glRotatef(ControledAngle[6][1], 0, 1, 0);
	glRotatef(ControledAngle[6][2], 0, 0, 1);
	glutSolidSphere(0.1f, 30, 17);
	glTranslatef(0, -4, 0);
	drawCube(1, 4, 1);
	//LeftLowerLeg
	glTranslatef(0, -0.5f, 0);
	glRotatef(ControledAngle[7][0], 1, 0, 0);
	glRotatef(ControledAngle[7][1], 0, 1, 0);
	glRotatef(ControledAngle[7][2], 0, 0, 1);
	glutSolidSphere(0.5f, 30, 17);
	glTranslatef(0, -4.5f, 0);
	drawCube(0.7f, 4, 0.7f);
	//LeftFoot
	glTranslatef(0, -0.1f, 0);
	glRotatef(ControledAngle[8][0], 1, 0, 0);
	glRotatef(ControledAngle[8][1], 0, 1, 0);
	glRotatef(ControledAngle[8][2], 0, 0, 1);
	glutSolidSphere(0.1f, 30, 17);
	glTranslatef(0, -0.25f, 0.5f);
	drawCube(0.5f, 0.5f, 1.5f);
	glPopMatrix();
	glPopMatrix();

	//UpperBody
	glPushMatrix();
	//Chest
	glTranslatef(0, 1, 0);
	glRotatef(ControledAngle[2][0], 1, 0, 0);
	glRotatef(ControledAngle[2][1], 0, 1, 0);
	glRotatef(ControledAngle[2][2], 0, 0, 1);
	glutSolidSphere(0.2f, 30, 17);
	drawCube(2.5f, 3, 1.5f);

	//Neck&Head
	glPushMatrix();
	//Neck
	glTranslatef(0, 3, 0);
	glRotatef(ControledAngle[9][0], 1, 0, 0);
	glRotatef(ControledAngle[9][1], 0, 1, 0);
	glRotatef(ControledAngle[9][2], 0, 0, 1);
	glutSolidSphere(0.2f, 30, 17);

	glTranslatef(0, 1, 0);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(0.5f, 1, 30, 17);
	glPopMatrix();

	//Head
	glTranslatef(0, 0, 0);
	glRotatef(ControledAngle[10][0], 1, 0, 0);
	glRotatef(ControledAngle[10][1], 0, 1, 0);
	glRotatef(ControledAngle[10][2], 0, 0, 1);
	glutSolidSphere(0.2f, 30, 17);

	glTranslatef(0, 1, 0.5f);
	glutSolidSphere(1.5f, 30, 17);
	glutSolidCylinder(1.5f, 1.5f, 30, 17);
	glPopMatrix();

	//RightArm
	glPushMatrix();
	//RightShoulder
	glTranslatef(-1.75f, 2.5f, 0);
	glRotatef(ControledAngle[11][0], 1, 0, 0);
	glRotatef(ControledAngle[11][1], 0, 1, 0);
	glRotatef(ControledAngle[11][2], 0, 0, 1);
	glutSolidSphere(0.75f, 30, 17);
	//RightUpperArm
	glTranslatef(-2.5f, 0, 0);
	glRotatef(ControledAngle[12][0], 1, 0, 0);
	glRotatef(ControledAngle[12][1], 0, 1, 0);
	glRotatef(ControledAngle[12][2], 0, 0, 1);
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glutSolidCylinder(0.5f, 2, 30, 17);
	glPopMatrix();
	//RightLowerArm
	glTranslatef(-0.5f, 0, 0);
	glRotatef(ControledAngle[13][1], 0, 1, 0);
	glRotatef(ControledAngle[13][0], 1, 0, 0);
	glRotatef(ControledAngle[13][2], 0, 0, 1);
	glutSolidSphere(0.5f, 30, 17);
	glTranslatef(-2.5f, 0, 0);
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glutSolidCylinder(0.5f, 2, 30, 17);
	glPopMatrix();
	//RightHand
	glRotatef(ControledAngle[14][0], 1, 0, 0);
	glRotatef(ControledAngle[14][1], 0, 1, 0);
	glRotatef(ControledAngle[14][2], 0, 0, 1);
	glutSolidSphere(0.1f, 30, 17);
	glTranslatef(-0.75f, 0.25f, 0);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(0.75f, 0.5f, 30, 17);
	glPopMatrix();

	glPopMatrix();


	//LeftArm
	glPushMatrix();
	//LeftShoulder
	glTranslatef(1.75f, 2.5f, 0);
	glRotatef(ControledAngle[15][0], 1, 0, 0);
	glRotatef(ControledAngle[15][1], 0, 1, 0);
	glRotatef(ControledAngle[15][2], 0, 0, 1);
	glutSolidSphere(0.75f, 30, 17);
	//LeftUpperArm
	glTranslatef(2.5f, 0, 0);
	glRotatef(ControledAngle[16][0], 1, 0, 0);
	glRotatef(ControledAngle[16][1], 0, 1, 0);
	glRotatef(ControledAngle[16][2], 0, 0, 1);
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glutSolidCylinder(0.5f, 2, 30, 17);
	glPopMatrix();
	//LeftLowerArm
	glTranslatef(0.5f, 0, 0);
	glRotatef(ControledAngle[17][1], 0, 1, 0);
	glRotatef(ControledAngle[17][0], 1, 0, 0);
	glRotatef(ControledAngle[17][2], 0, 0, 1);
	glutSolidSphere(0.5f, 30, 17);
	glTranslatef(2.5f, 0, 0);
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glutSolidCylinder(0.5f, 2, 30, 17);
	glPopMatrix();
	//LeftHand
	glRotatef(ControledAngle[18][0], 1, 0, 0);
	glRotatef(ControledAngle[18][1], 0, 1, 0);
	glRotatef(ControledAngle[18][2], 0, 0, 1);
	glutSolidSphere(0.1f, 30, 17);
	glTranslatef(0.75f, 0.25f, 0);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(0.75f, 0.5f, 30, 17);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		if(ControledAngle[controlMode][0] - 1 > ControledAngleLimit[controlMode][0]) ControledAngle[controlMode][0]--;
		if (ControledAngle[controlMode][0] < -180) ControledAngle[controlMode][0] += 360;
		break;
	case '2':
		if (ControledAngle[controlMode][0] + 1 < ControledAngleLimit[controlMode][1]) ControledAngle[controlMode][0]++;
		if (ControledAngle[controlMode][0] > 180) ControledAngle[controlMode][0] -= 360;
		break;
	case '3':
		if (ControledAngle[controlMode][1] - 1 > ControledAngleLimit[controlMode][2]) ControledAngle[controlMode][1]--;
		if (ControledAngle[controlMode][1] < -180) ControledAngle[controlMode][1] += 360;
		break;
	case '4':
		if (ControledAngle[controlMode][1] + 1 < ControledAngleLimit[controlMode][3]) ControledAngle[controlMode][1]++;
		if (ControledAngle[controlMode][1] > 180) ControledAngle[controlMode][1] -= 360;
		break;
	case '5':
		if (ControledAngle[controlMode][2] - 1 > ControledAngleLimit[controlMode][4]) ControledAngle[controlMode][2]--;
		if (ControledAngle[controlMode][2] < -180) ControledAngle[controlMode][2] += 360;
		break;
	case '6':
		if (ControledAngle[controlMode][2] + 1 < ControledAngleLimit[controlMode][5]) ControledAngle[controlMode][2]++;
		if (ControledAngle[controlMode][2] > 180) ControledAngle[controlMode][2] -= 360;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void drawCube(float sx, float sy, float sz)
{
	glPushMatrix();
	glTranslatef(0.0, sy * 0.5, 0.0);
	glScalef(sx, sy, sz);
	glutSolidCube(1.0);
	glPopMatrix();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	Width = w;
	Height = h;
}

void SetupViewVolume()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (double)Width / (double)Height, 1.0, 10000.0);
}

void SetupViewTransform()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0, 0.0, Zoom);
	glRotatef(Angle, Axis[0], Axis[1], Axis[2]);

	glMultMatrixf(RotMat);

	glGetFloatv(GL_MODELVIEW_MATRIX, RotMat);
	RotMat[12] = RotMat[13] = RotMat[14] = 0.0;

	glTranslatef(Pan[0], Pan[1], Pan[2]);
}

void RenderFloor()
{
	glDisable(GL_LIGHTING);
	glColor3f(0.7f, 0.7f, 0.7f);
	for (int x = -10; x <= 10; x++)
	{
		if (x == 0)
			continue;
		glBegin(GL_LINES);
		glVertex3f((float)x, 0.0, -10.0f);
		glVertex3f((float)x, 0.0, 10.0f);
		glVertex3f(-10.0f, 0.0, (float)x);
		glVertex3f(10.0f, 0.0, (float)x);
		glEnd();
	}

	glLineWidth(2.0f);
	glColor3f(0.3f, 0.3f, 0.3f);
	glBegin(GL_LINES);
	glVertex3f(-10.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 0.0, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, -10.0f);
	glVertex3f(0.0f, 0.0, 10.0f);
	glEnd();
	glLineWidth(1.0f);
	glEnable(GL_LIGHTING);
}

void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		StartPt[0] = x;
		StartPt[1] = y;
		if (button == GLUT_LEFT_BUTTON)
			ManipulateMode = 1;	

		if (button == GLUT_RIGHT_BUTTON)
			ManipulateMode = 2;	
	}
	if (state == GLUT_UP)
	{
		ManipulateMode = 0;	
		StartPt[0] = StartPt[1] = 0;
		Angle = 0.0;
	}
}

void Motion(int x, int y)
{
	if (ManipulateMode == 1)
	{
		float px, py, pz, qx, qy, qz;
		GetSphereCoord(StartPt[0], StartPt[1], &px, &py, &pz);
		GetSphereCoord(x, y, &qx, &qy, &qz);

		Axis[0] = py * qz - pz * qy;
		Axis[1] = pz * qx - px * qz;
		Axis[2] = px * qy - py * qx;
		Angle = 0.0;
		float len = Axis[0] * Axis[0] + Axis[1] * Axis[1] + Axis[2] * Axis[2];
		if (len > 0.0001) 
			Angle = acos(px * qx + py * qy + pz * qz) * 180.0f / 3.141592f;
	}

	if (ManipulateMode == 2)
	{
		float dx = (float)(x - StartPt[0]) * 0.01f;
		float dy = (float)(StartPt[1] - y) * 0.01f;
		Pan[0] += RotMat[0] * dx + RotMat[1] * dy;
		Pan[1] += RotMat[4] * dx + RotMat[5] * dy;
		Pan[2] += RotMat[8] * dx + RotMat[9] * dy;
	}

	StartPt[0] = x;
	StartPt[1] = y;
	glutPostRedisplay();
}

void MouseWheel(int button, int dir, int x, int y)
{
	if (dir > 0)
		Zoom += 1.0;
	else
		Zoom -= 1.0;
	glutPostRedisplay();
}

void GetSphereCoord(int x, int y, float *px, float *py, float *pz)
{
	*px = (2.0f * x - Width) / Width;
	*py = (-2.0f * y + Height) / Height;

	float r = (*px) * (*px) + (*py) * (*py);
	if (r >= 1.0f)
	{
		*px = *px / sqrt(r);
		*py = *py / sqrt(r);
		*pz = 0.0f;
	}
	else
		*pz = sqrt(1.0f - r);
}
