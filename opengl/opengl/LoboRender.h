#pragma once

#include "stdafx.h"
#include <iostream>
#include "LoadShaders.h"
#include "tiny_obj_loader.h"


class LoboRender
{
public:
	LoboRender();
	~LoboRender();

	virtual void Init();
	virtual void Draw();
	virtual void Update();
	virtual void Finalize();

private:

	GLuint vao; //vertex array object
	GLuint buffers;

	GLint render_modelviewprojection_loc;
};

