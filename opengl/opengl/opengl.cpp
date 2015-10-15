// opengl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "LoboRender.h"
LoboRender* render;

void draw()
{
	render->Draw();
}

void resize(int width, int height)
{
	const float ar = (float)width / (float)height;

	glViewport(0, 0, width, height);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(90.0, (float)width / (float)height, 1, 100);

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

}

int _tmain(int argc, _TCHAR* argv[])
{
	render = new LoboRender();
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Lobo Render");
	glewInit();
	render->Init();
	glutReshapeFunc(resize);
	glutDisplayFunc(draw);
	//glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}

