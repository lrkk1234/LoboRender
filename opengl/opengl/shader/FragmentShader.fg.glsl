#version 400 core


in vec3 pos;
in vec3 N;
in vec3 L;
in vec3 E;

out vec4 fColor;


uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform mat4 ModelView;
uniform mat4 Projection;
uniform vec4 LightPosition;
uniform float Shininess;

void main()
{
	vec3 tN = normalize(cross(dFdx(pos), dFdy(pos)));
	//tN = N;
	//it depends on your compute,if your result is black may need inverse tN;
	//tN *= -1;
	
	vec3 H = normalize(L + E);
	vec4 ambient = AmbientProduct;
	float Kd = max(dot(L, tN), 0.0);
	vec4  diffuse = Kd*DiffuseProduct;
	float Ks = pow(max(dot(tN, H), 0.0), Shininess);
	vec4  specular = Ks * SpecularProduct;
	if (dot(L, tN) < 0.0)
		specular = vec4(0.0, 0.0, 0.0, 1.0);
	fColor = diffuse+specular+ambient;
}