#pragma once

#include "stdafx.h"

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


private:
	std::vector<tinyobj::shape_t> shapes_;
	std::vector<tinyobj::material_t> materials_;

	GLuint vao; //vertex array object
	GLuint buffers;
};

