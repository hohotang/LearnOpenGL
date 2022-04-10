#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{

	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

	vec3 result = ambient * objectColor;
	FragColor = vec4(result, 1.0);
}