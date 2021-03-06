#version 400 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vnormal;

out vec3 pos;
out vec3 N;
out vec3 L;
out vec3 E;


uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform mat4 ModelView;
uniform mat4 Projection;
uniform vec4 LightPosition;
uniform float Shininess;

void main()
{
	pos = vec3(ModelView*vec4(vertexPosition_modelspace,1));
	L = normalize(LightPosition.xyz - pos);
	E = normalize(-pos);
	N = normalize(vec3(ModelView*vec4(vnormal,0)));
	gl_Position = Projection*vec4(pos,1);
}