#include "stdafx.h"
#include "LoboRender.h"


LoboRender::LoboRender()
{
}


LoboRender::~LoboRender()
{
}

void LoboRender::Draw()
{

}

void LoboRender::Init()
{

}

void LoboRender::Update()
{

}

void LoboRender::SetUpWindow(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Color Cube");

	glewInit();
	//glutDisplayFunc(display);
	//glutKeyboardFunc(keyboard);
	glutMainLoop();
}