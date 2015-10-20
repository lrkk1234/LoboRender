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
#include "vmath.h"
#include <GL/gl.h>
#include <GL/glu.h>

class LoboCamera
{
public:
	LoboCamera();
	~LoboCamera();

	void rotateX(float angel);
	void rotateY(float angel);
	void rotateZ(float angel);
	void translate(float x, float y, float z);

	void perspective(float fovy, float aspect, float n,float f);
	void lookat(vmath::vec3 eye, vmath::vec3 center, vmath::vec3 up);
	void bindShaderProgram(GLuint shader_program);
private:
	void updateCamera();

	GLuint shader_program_;
	vmath::mat4 MVP;
	vmath::mat4 MV;
	vmath::mat4 P;
	vmath::mat4 V;
	vmath::mat4 M;
};

