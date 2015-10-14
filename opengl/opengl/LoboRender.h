#pragma once

#include "stdafx.h"
#include <iostream>
#include <gl\glew.h>
#include <gl\glut.h>


class LoboRender
{
public:
	LoboRender();
	~LoboRender();

	virtual void Init();
	virtual void Draw();
	virtual void Update();

	void SetUpWindow(int argc, char* argv[]);

};

