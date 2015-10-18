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


LoboModel::LoboModel()
{
	tinyobj::LoadObj(shapes_, materials_, "mesh/dragonlite.obj");
}

LoboModel::LoboModel(const char* filename)
{
	LoadModel(filename);
	LoadBuffer();
	UpdateNorm();
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
	return true;
}

void LoboModel::LoadBuffer()
{
	buffer_size_ = 0;
	//compute buffer size;
	for (size_t s = 0; s < shapes_.size(); s++)
	{
		vertics_size_ += (int)shapes_[s].mesh.indices.size();
		buffer_size_ += (int)shapes_[s].mesh.indices.size() * 3;
		if (shapes_[s].mesh.normals.size()!=0)
		buffer_size_ += (int)shapes_[s].mesh.indices.size() * 3;
	}

	gl_vertex_buffer_.resize(buffer_size_);
	//load buffer
	int indice = 0;
	for (size_t s = 0; s < shapes_.size();s++)
	for (size_t i = 0; i < shapes_[s].mesh.indices.size(); i++)
	{
		gl_vertex_buffer_[indice  ] = shapes_[s].mesh.positions[shapes_[s].mesh.indices[i] * 3  ];
		gl_vertex_buffer_[indice+1] = shapes_[s].mesh.positions[shapes_[s].mesh.indices[i] * 3+1];
		gl_vertex_buffer_[indice+2] = shapes_[s].mesh.positions[shapes_[s].mesh.indices[i] * 3+2];
		indice += 3;
	}

	this->norml_offset_ = indice*sizeof(float);
	for (size_t s = 0; s < shapes_.size(); s++)
	if (shapes_[s].mesh.normals.size() != 0)
	for (size_t i = 0; i < shapes_[s].mesh.indices.size(); i++)
	{
		gl_vertex_buffer_[indice] = shapes_[s].mesh.normals[shapes_[s].mesh.indices[i] * 3];
		gl_vertex_buffer_[indice + 1] = shapes_[s].mesh.normals[shapes_[s].mesh.indices[i] * 3 + 1];
		gl_vertex_buffer_[indice + 2] = shapes_[s].mesh.normals[shapes_[s].mesh.indices[i] * 3 + 2];
		indice += 3;
	}

}

float* LoboModel::GetVertexBuffer()
{
	return &this->gl_vertex_buffer_[0];
}

void LoboModel::UpdateNorm()
{
	for (size_t s = 0; s < shapes_.size(); s++)
	{
		if (shapes_[s].mesh.normals.size() == 0)
		{
			shapes_[s].mesh.normals.resize(shapes_[s].mesh.positions.size());
		}
		for (size_t i = 0; i < shapes_[s].mesh.indices.size() / 3; i++)
		{
			vmath::vec3 v0(
				shapes_[s].mesh.positions[shapes_[s].mesh.indices[i * 3]],
				shapes_[s].mesh.positions[shapes_[s].mesh.indices[i * 3] + 1],
				shapes_[s].mesh.positions[shapes_[s].mesh.indices[i * 3] + 2]
				);
			vmath::vec3 v1(
				shapes_[s].mesh.positions[shapes_[s].mesh.indices[i * 3 + 1]],
				shapes_[s].mesh.positions[shapes_[s].mesh.indices[i * 3 + 1] + 1],
				shapes_[s].mesh.positions[shapes_[s].mesh.indices[i * 3 + 1] + 2]
				);
			vmath::vec3 v2(
				shapes_[s].mesh.positions[shapes_[s].mesh.indices[i * 3 + 2]],
				shapes_[s].mesh.positions[shapes_[s].mesh.indices[i * 3 + 2] + 1],
				shapes_[s].mesh.positions[shapes_[s].mesh.indices[i * 3 + 2] + 2]
				);

			vmath::vec3 eg1 = v1 - v0;
			vmath::vec3 eg2 = v2 - v0;
			vmath::vec3 normal = vmath::cross(eg1, eg2);
			if (length(normal) == 0)
			{
				std::cout << (v1)[0] << " " << v1[1] << " " << v1[2] << std::endl;
				std::cout << (v2)[0] << " " << v2[1] << " " << v2[2] << std::endl;
				std::cout << (v0)[0] << " " << v0[1] << " " << v0[2] << std::endl;
			}
			normal = vmath::normalize(normal);

			shapes_[s].mesh.normals[shapes_[s].mesh.indices[i * 3]] = normal[0];
			shapes_[s].mesh.normals[shapes_[s].mesh.indices[i * 3] + 1] = normal[1];
			shapes_[s].mesh.normals[shapes_[s].mesh.indices[i * 3] + 2] = normal[2];
			shapes_[s].mesh.normals[shapes_[s].mesh.indices[i * 3 + 1]] = normal[0];
			shapes_[s].mesh.normals[shapes_[s].mesh.indices[i * 3 + 1] + 1] = normal[1];
			shapes_[s].mesh.normals[shapes_[s].mesh.indices[i * 3 + 1] + 2] = normal[2];
			shapes_[s].mesh.normals[shapes_[s].mesh.indices[i * 3 + 2]] = normal[0];
			shapes_[s].mesh.normals[shapes_[s].mesh.indices[i * 3 + 2] + 1] = normal[1];
			shapes_[s].mesh.normals[shapes_[s].mesh.indices[i * 3 + 2] + 2] = normal[2];
		}
	}
}