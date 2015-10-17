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
#include "LoboRender.h"
#include "LoboModel.h"

LoboRender::LoboRender()
{
}


LoboRender::~LoboRender()
{
	
}

void LoboRender::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glBindVertexArray(vao);
	for (size_t i = 0; i < model_list_.size(); i++)
	{
		//gl bind VAO and VBO
		glBindVertexArray(model_list_[i]->vertex_array_object_);
		glBindBuffer(GL_ARRAY_BUFFER, model_list_[i]->vertex_buffer_object_);

		//set MVP
		GLuint render_modelviewprojection_loc = glGetUniformLocation(shader_program_, "MVP");
		glUniformMatrix4fv(render_modelviewprojection_loc, 1, GL_FALSE, &MVP[0][0]);

		//set vertex position buffer
		GLuint vPosition = glGetAttribLocation(shader_program_, "vertexPosition_modelspace");
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

		//render
		glDrawArrays(GL_TRIANGLES, 0, model_list_[i]->vertics_size_);
	}
	glutSwapBuffers();

}

void LoboRender::Init()
{
	//projection
	vmath::mat4 projection = vmath::perspective(60.0f, 1.0f, 0.1f, 400.0f);
	vmath::mat4 view = vmath::lookat(
		vmath::vec3(0, 5, 11),
		vmath::vec3(0, 0, 0),
		vmath::vec3(0, 1, 0)
		);
	vmath::mat4 model = vmath::mat4().identity();

	MVP = projection*view*model;
	//init VAO
	CreateVAO();

	//Create shader program
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "shader/VertexShader.vert.glsl" },
		{ GL_FRAGMENT_SHADER, "shader/FragmentShader.fg.glsl" },
		{ GL_NONE, NULL }
	};
	shader_program_ = LoadShaders(shaders);
	glUseProgram(shader_program_);
	
	//set background color
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
}

void LoboRender::Update()
{

}

void LoboRender::Finalize()
{
	glUseProgram(0);
}

void LoboRender::CreateVAO()
{
	for (size_t i = 0; i < model_list_.size(); i++)
	{
		glGenVertexArrays(1, &model_list_[i]->vertex_array_object_);
		glBindVertexArray(model_list_[i]->vertex_array_object_);

		glGenBuffers(1, &model_list_[i]->vertex_buffer_object_);
		glBindBuffer(GL_ARRAY_BUFFER, model_list_[i]->vertex_buffer_object_);
		glBufferData(GL_ARRAY_BUFFER, model_list_[i]->buffer_size_*sizeof(GLfloat),
			model_list_[i]->GetVertexBuffer(),
			GL_STATIC_DRAW
			);
	}
}

void LoboRender::AddModel(const char* filename)
{
	LoboModel* model = new LoboModel(filename);
	model_list_.push_back(model);
}