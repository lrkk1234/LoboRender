#version 330 core

in vec4 vPosition;


out vec4 color;

void main()
{
	gl_Position = vPosition;
}
