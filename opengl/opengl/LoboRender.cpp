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
	/*glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);*/
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera.rotateY(20*rotation);
	//glBindVertexArray(vao);
	for (size_t i = 0; i < model_list_.size(); i++)
	{
		model_list_[i]->Render();
	}
	glutSwapBuffers();

}

void LoboRender::Init()
{
	//gl setting
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);


	rotation = 0.01;

	//light position in modelview
	vmath::vec4 lightposition(0.0f,1.0f,0.0f,1.0f);
	float Shininess = 128;

	//color
	vmath::vec4 AmbientProduct(0.1f, 0.1f, 0.1f, 1.0f);
	vmath::vec4 DiffuseProduct(1.0f, 0.35f, 0.35f, 1.0f);
	vmath::vec4 SpecularProduct(0.5, 0.5, 0.5, 1.0f);

	//Create shader program
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "shader/VertexShader.vert.glsl" },
		{ GL_FRAGMENT_SHADER, "shader/FragmentShader.fg.glsl" },
		{ GL_NONE, NULL }
	};
	shader_program_ = LoadShaders(shaders);
	camera.bindShaderProgram(shader_program_);
	glUseProgram(shader_program_);

	camera.perspective(60.0f, 1.0f, 0.1f, 400.0f);
	camera.lookat(vmath::vec3(5, 3, 5),
		vmath::vec3(0, 2, 0),
		vmath::vec3(0, 1, 0));

	//set 
	GLuint lightposition_loc = glGetUniformLocation(shader_program_, "LightPosition");
	glUniform4fv(lightposition_loc, 1, &lightposition[0]);

	GLuint AmbientProduct_loc = glGetUniformLocation(shader_program_, "AmbientProduct");
	glUniform4fv(AmbientProduct_loc, 1, &AmbientProduct[0]);

	GLuint DiffuseProduct_loc = glGetUniformLocation(shader_program_, "DiffuseProduct");
	glUniform4fv(DiffuseProduct_loc, 1, &DiffuseProduct[0]);

	GLuint SpecularProduct_loc = glGetUniformLocation(shader_program_, "SpecularProduct");
	glUniform4fv(SpecularProduct_loc, 1, &SpecularProduct[0]);

	GLuint Shininess_loc = glGetUniformLocation(shader_program_, "Shininess");
	glUniform1f(Shininess_loc,Shininess);

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

void LoboRender::Reshape(int w, int h)
{
	camera.perspective(60.0f, (float)w / (float)h, 0.1f, 400.0f);

	/*projection = vmath::perspective(60.0f, (float)w/(float)h, 0.1f, 400.0f);
	glUseProgram(shader_program_);
	GLuint render_projection_loc = glGetUniformLocation(shader_program_, "Projection");
	glUniformMatrix4fv(render_projection_loc, 1, GL_FALSE, &projection[0][0]);*/
}

void LoboRender::AddModel(const char* filename)
{
	LoboModel* model = new LoboModel(filename);
	model_list_.push_back(model);
}