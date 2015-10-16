#include "stdafx.h"
#include "LoboRender.h"
#include "vmath.h"
//#include "common\shader.hpp"


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
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glutSwapBuffers();

}

void LoboRender::Init()
{
	
	//vao config
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};


	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(1, &buffers);
	glBindBuffer(GL_ARRAY_BUFFER, buffers);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
		&g_vertex_buffer_data[0],
		GL_STATIC_DRAW
		);

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER,"shader/VertexShader.vert.glsl"},
		{GL_FRAGMENT_SHADER,"shader/FragmentShader.fg.glsl"},
		{GL_NONE,NULL}
	};

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);

	GLuint render_modelviewprojection_loc = glGetUniformLocation(program, "MVP");
	vmath::mat4 projection = vmath::perspective(45.0f, 1.0f, 0.1f, 100.0f);
	vmath::mat4 view = vmath::lookat(
		vmath::vec3(0, 0, 2),
		vmath::vec3(0, 0, 0),
		vmath::vec3(0, 1, 0)
		);
	vmath::mat4 model = vmath::mat4().identity();

	vmath::mat4 MVP = projection*view*model;
	glUniformMatrix4fv(render_modelviewprojection_loc, 1, GL_FALSE, &MVP[0][0]);

	GLuint vPosition = glGetAttribLocation(program, "vertexPosition_modelspace");
	glEnableVertexAttribArray(vPosition);
	//glBindBuffer(GL_ARRAY_BUFFER, buffers);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
}

void LoboRender::Update()
{

}

void LoboRender::Finalize()
{
	glUseProgram(0);
}

