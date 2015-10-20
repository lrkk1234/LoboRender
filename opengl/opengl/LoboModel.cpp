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

#include "stdafx.h"
#include "LoboModel.h"

LoboModel::LoboModel(const char* filename)
{
	LoadModel(filename);
	CreateVAO();
}

LoboModel::~LoboModel()
{

}

bool LoboModel::LoadModel(const char* filename)
{
	std::string err = tinyobj::LoadObj(shapes_, materials_, filename);
	if (!err.empty()) {
		std::cout << err << std::endl;
		return false;
	}

	std::cout << std::endl;
	std::cout << "OBJ LOADED: " << filename << std::endl;
	std::cout << "# of shapes : " << shapes_.size() << std::endl;

	for (size_t i = 0; i < shapes_.size(); i++) {
		printf("shape[%ld].name = %s\n", i, shapes_[i].name.c_str());
		printf("shape[%ld].indices: %ld\n", i, shapes_[i].mesh.indices.size());
		assert((shapes_[i].mesh.indices.size() % 3) == 0);
		printf("shape[%ld].vertices: %ld\n", i, shapes_[i].mesh.positions.size());
		assert((shapes_[i].mesh.positions.size() % 3) == 0);
		printf("shape[%ld].normals: %ld\n", i, shapes_[i].mesh.normals.size());
		assert((shapes_[i].mesh.normals.size() % 3) == 0);
	}
	shapes_list_.resize(shapes_.size());

	return true;
}

void LoboModel::CreateVAO()
{
	for (size_t i = 0; i < shapes_.size(); i++)
	{
		glGenVertexArrays(1, &shapes_list_[i].vao_);
		glBindVertexArray(shapes_list_[i].vao_);
		shapes_list_[i].vbo_.resize(NUM_OBJ_BUFFERS);
		glGenBuffers(NUM_OBJ_BUFFERS, &shapes_list_[i].vbo_[0]);
		//vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, shapes_list_[i].vbo_[OBJ_VERTICES]);
		glBufferData(GL_ARRAY_BUFFER, shapes_[i].mesh.positions.size() * sizeof(float),
			&shapes_[i].mesh.positions[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//normals
		if (shapes_[i].mesh.normals.size() != 0)
		{
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, shapes_list_[i].vbo_[OBJ_NORMALS]);
			glBufferData(GL_ARRAY_BUFFER, shapes_[i].mesh.normals.size() * sizeof(float),
				&shapes_[i].mesh.normals[0], GL_STATIC_DRAW);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		}
		//indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shapes_list_[i].vbo_[OBJ_INDICES]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, shapes_[i].mesh.indices.size() * sizeof(unsigned int),
			&shapes_[i].mesh.indices[0], GL_STATIC_DRAW);

		shapes_list_[i].num_indices_ = (int)shapes_[i].mesh.indices.size();
		glBindVertexArray(0);
	}
}

void LoboModel::Render()
{
	for (size_t i = 0; i < shapes_.size(); i++)
	{
		glBindVertexArray(shapes_list_[i].vao_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shapes_list_[i].vbo_[OBJ_INDICES]);
		glDrawElements(GL_TRIANGLES, shapes_list_[i].num_indices_, GL_UNSIGNED_INT, 0);
	}
}

