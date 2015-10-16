#pragma once
#include "tiny_obj_loader.h"
#define unsigned int GLuint

class LoboModel
{
public:
	LoboModel();
	~LoboModel();
	LoboModel(const char* filename);

	bool LoadModel(const char* filename);


	GLuint vertex_array_object_;
	GLuint vertex_buffer_object_;

private:
	std::vector<tinyobj::shape_t> shapes_;
	std::vector<tinyobj::material_t> materials_;
	std::vector<float> gl_vertex_buffer_;
};

