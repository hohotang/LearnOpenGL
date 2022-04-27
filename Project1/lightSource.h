#pragma once

#include "shader/shader_s.h"
#include "Camera.h"

#define NR_POINT_LIGHTS 4


/// <summary>
/// store light info
/// when light info change, update to shader
/// </summary>

// dir light


class LightSource
{
public:
	struct dirLight
	{
		glm::vec3 direction;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};

	struct pointLight
	{
		glm::vec3 position;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float constant;
		float linear;
		float quadratic;
	};

	struct spotLight
	{
		glm::vec3 position;
		glm::vec3 direction;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float constant;
		float linear;
		float quadratic;
		float cutOff;
		float outerCutOff;
	};

	LightSource()
	{
		init();
	}

	dirLight getDir() { return Dir; }
	void updateDir(dirLight _dir) { Dir = _dir; }
	void updateShaderAllDir(Shader _shader);

	spotLight getSpot() { return Spot; }
	void updateSpot(spotLight _spot) { Spot = _spot; }
	void updateShaderAllSpot(Shader _shader);

	void addPoint(glm::vec3 _pos, glm::vec3 _colors);
	pointLight getPoint(unsigned short num) { return Point[num]; }
	void updatePointPos(glm::vec3 _pos, unsigned short num);
	void updatePointColors(glm::vec3 _colors, unsigned short num);
	void updatePoint(pointLight _point, unsigned short num) { Point[num] = _point; }
	void updateShaderPointPos(unsigned short num, Shader _shader);
	void updateShaderAllPoint(Shader _shader);

	void updateShaderCamera(Camera _camera, Shader _shader);

	void updateShader(Shader _shader);

private:

	dirLight Dir;
	pointLight Point[NR_POINT_LIGHTS];
	spotLight Spot;
	unsigned short pointCount;

	void init();

	void initDir();
	void initSpot();

};