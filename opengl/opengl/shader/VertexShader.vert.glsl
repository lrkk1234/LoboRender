#version 400 core

in vec3 vertexPosition_modelspace;
in vec3 vnormal;
out vec4 color;
uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform mat4 ModelView;
uniform mat4 Projection;
uniform vec4 LightPosition;
uniform float Shininess;

void main()
{
	vec3 pos = vec3(ModelView*vec4(vertexPosition_modelspace,1));
	vec3 L = normalize(LightPosition.xyz - pos);
	vec3 E = normalize(-pos);
	vec3 H = normalize(L + E);
	vec3 N = normalize(vec3(ModelView*vec4(vnormal,1)));
	vec4 ambient = AmbientProduct;
	float Kd = max(dot(L, N), 0.0);
	vec4  diffuse = Kd*DiffuseProduct;
	float Ks = pow(max(dot(N, H), 0.0), Shininess);
	vec4  specular = Ks * SpecularProduct;
	if (dot(L, N) < 0.0)
		specular = vec4(0.0, 0.0, 0.0, 1.0);

	gl_Position = Projection*ModelView*vec4(vertexPosition_modelspace, 1);

	color = vec4(vnormal, 1);
	color.a = 1.0;
}