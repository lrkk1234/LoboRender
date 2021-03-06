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
#pragma once
#include "tiny_obj_loader.h"
#include <assert.h>
#include <GL/gl.h>
#include <GL/glu.h>

enum OBJ_BUFERS
{
	OBJ_VERTICES = 0,
	OBJ_NORMALS,
	OBJ_INDICES,
	NUM_OBJ_BUFFERS
};

//store vao vbo name for each Shape
typedef struct {
	GLuint              vao_;
	std::vector<GLuint> vbo_;
	int         num_indices_;
} ShapeInfo;


class LoboModel
{
public:
	LoboModel(const char* filename);
	~LoboModel();

	bool LoadModel(const char* filename);
	//create vao
	void CreateVAO();
	//render the result
	void Render();

private:

	std::vector<tinyobj::shape_t> shapes_;
	std::vector<tinyobj::material_t> materials_;
	std::vector<ShapeInfo> shapes_list_;
};

