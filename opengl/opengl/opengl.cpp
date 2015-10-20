/*The MIT License (MIT)
Copyright (c) [2015] [Ran Luo]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

//

// opengl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "LoboRender.h"
#include "LoboModel.h"

LoboRender* render;

void draw()
{
	render->Draw();
	glutPostRedisplay();
}

void resize(int width, int height)
{
	const float ar = (float)width / (float)height;
	glViewport(0, 0, width, height);
	render->Reshape(width, height);

}

void init()
{
//	render->AddModel("mesh/dragonlite.obj");
	render->AddModel("mesh/dragonlite.obj");
	//render->AddModel("mesh/dragonlite.obj");
	render->Init();
}

int _tmain(int argc, _TCHAR* argv[])
{
	render = new LoboRender();
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Lobo Render");
	glewInit();
	init();
	glutReshapeFunc(resize);
	glutDisplayFunc(draw);
	//glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0; 
}

