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
#include "LoboCamera.h"


LoboCamera::LoboCamera()
{
	MVP = vmath::mat4::identity();
	MV = vmath::mat4::identity();
	P = vmath::mat4::identity();
	V = vmath::mat4::identity();
	M = vmath::mat4::identity();
}


LoboCamera::~LoboCamera()
{

}

void LoboCamera::rotateX(float angel)
{
	M=vmath::rotate(-angel, vmath::vec3(1, 0, 0))*M;
	updateCamera();
}

void LoboCamera::rotateY(float angel)
{
	M = vmath::rotate(-angel, vmath::vec3(0, 1, 0))*M;
	updateCamera();
}

void LoboCamera::rotateZ(float angel)
{
	M = vmath::rotate(-angel, vmath::vec3(0, 0, 1))*M;
	updateCamera();
}

void LoboCamera::translate(float x, float y, float z)
{
	M = vmath::translate(vmath::vec3(-x, -y, -z)) * M;
	updateCamera();
}

void LoboCamera::perspective(float fovy, float aspect, float n, float f)
{
	glUseProgram(shader_program_);
	P = vmath::perspective(fovy, aspect, n, f);
	GLuint render_projection_loc = glGetUniformLocation(shader_program_, "Projection");
	glUniformMatrix4fv(render_projection_loc, 1, GL_FALSE, &P[0][0]);
}

void LoboCamera::lookat(vmath::vec3 eye, vmath::vec3 center, vmath::vec3 up)
{
	V = vmath::lookat(eye, center, up);
	updateCamera();
}

void LoboCamera::updateCamera()
{
	glUseProgram(shader_program_);
	MV = V*M;
	GLuint render_modelview_loc = glGetUniformLocation(shader_program_, "ModelView");
	glUniformMatrix4fv(render_modelview_loc, 1, GL_FALSE, &MV[0][0]);
}

void LoboCamera::bindShaderProgram(GLuint shader_program)
{
	this->shader_program_ = shader_program;
}