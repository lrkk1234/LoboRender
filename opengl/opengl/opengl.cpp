// opengl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "LoboRender.h"

int _tmain(int argc, _TCHAR* argv[])
{
	LoboRender render;
	render.SetUpWindow(argc, (char**)argv);
	return 0;
}

