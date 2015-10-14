#include "stdafx.h"
#include "LoboRender.h"



LoboRender::LoboRender()
{
}


LoboRender::~LoboRender()
{
}

void LoboRender::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glutSwapBuffers();

}

void LoboRender::Init()
{
	//read mesh
	tinyobj::LoadObj(shapes_, materials_, "mesh/dragonlite.obj");

	GLfloat vertices[6][4] = {
		{ -0.9, -0.9 ,-6,1},
		{ 0.85, -0.9, -6, 1 },
		{ -0.9, 0.85, -6, 1 },
		{ 0.90, -0.85, -6, 1 },
		{ 0.90, 0.90, -6, 1 },
		{ -0.85, 0.90, -6, 1 },
	};
	//vao config
	GLfloat color[6][4] = {
		{ 0.1, 0.9, 1, 1 },
		{ 0.1, 0.9, 1, 1 },
		{ 0.9, 0.1, 1, 1 },
		{ 0.90, 0.85, 1, 1 },
		{ 0.90, 0.90, 1, 1 },
		{ 0.85, 0.90, 1, 1 },
	};


	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(1, &buffers);
	glBindBuffer(GL_ARRAY_BUFFER, buffers);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
		vertices,
		GL_STATIC_DRAW
		);

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER,"shader/VertexShader.vert.glsl"},
		{GL_FRAGMENT_SHADER,"shader/FragmentShader.fg.glsl"},
		{GL_NONE,NULL}
	};

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);

	GLuint vPosition = glGetAttribLocation(program, "vPosistion");
	glDisableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void LoboRender::Update()
{

}

