#include "lightSource.h"

void LightSource::init()
{
    initDir();
    initSpot();
    pointCount = 0;
}

void LightSource::initDir()
{
    Dir.direction = glm::vec3(-0.2f, -1.0f, -0.3f);
    Dir.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    Dir.diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
    Dir.specular = glm::vec3(0.5f, 0.5f, 0.5f);
}

void LightSource::updateShaderAllDir(Shader _shader)
{
    _shader.use();
    _shader.setVec3("dirLight.direction", Dir.direction);
    _shader.setVec3("dirLight.ambient", Dir.ambient);
    _shader.setVec3("dirLight.diffuse", Dir.diffuse);
    _shader.setVec3("dirLight.specular", Dir.specular);
}

void LightSource::initSpot()
{
    //Spot.position = glm::vec3(0.0f);
    //Spot.direction = glm::vec3(0.0f);
    Spot.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    Spot.diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
    Spot.specular = glm::vec3(0.5f, 0.5f, 0.5f);
    Spot.constant = 1.0f;
    Spot.linear = 0.09f;
    Spot.quadratic = 0.032f;
    Spot.cutOff = glm::cos(glm::radians(12.5f));
    Spot.outerCutOff = glm::cos(glm::radians(15.0f));
}

void LightSource::updateShaderAllSpot(Shader _shader)
{
    _shader.use();
    _shader.setVec3("spotLight.ambient", Spot.ambient);
    _shader.setVec3("spotLight.diffuse", Spot.diffuse);
    _shader.setVec3("spotLight.specular", Spot.specular);
    _shader.setFloat("spotLight.constant", Spot.constant);
    _shader.setFloat("spotLight.linear", Spot.linear);
    _shader.setFloat("spotLight.quadratic", Spot.quadratic);
    _shader.setFloat("spotLight.cutOff", Spot.cutOff);
    _shader.setFloat("spotLight.outerCutOff", Spot.outerCutOff);
}

void LightSource::addPoint(glm::vec3 _pos, glm::vec3 _colors)
{
    if (pointCount >= NR_POINT_LIGHTS)
        return;
    Point[pointCount].position = _pos;
    Point[pointCount].ambient = _colors * 0.05f;
    Point[pointCount].diffuse = _colors * 0.8f;
    Point[pointCount].specular = _colors * 1.0f;
    Point[pointCount].constant = 1.0f;
    Point[pointCount].linear = 0.09f;
    Point[pointCount].quadratic = 0.032f;
    pointCount++;
}

void LightSource::updatePointPos(glm::vec3 _pos, unsigned short num)
{
    if (num >= 4 || num < 0) return;
    Point[num].position = _pos;
}

void LightSource::updatePointColors(glm::vec3 _colors, unsigned short num)
{
    if (num >= 4 || num < 0) return;
    Point[num].ambient = _colors * 0.05f;
    Point[num].diffuse = _colors * 0.8f;
    Point[num].specular = _colors * 1.0f;
}

void LightSource::updateShaderPointPos(unsigned short num, Shader _shader)
{
    _shader.use();
    std::string number = std::to_string(num);
    _shader.setVec3("pointLights[" + number + "].position", Point[num].position);
}

void LightSource::updateShaderAllPoint(Shader _shader)
{
    _shader.use();
    for (int i = 0; i < pointCount; ++i) {
        std::string number = std::to_string(i);
        _shader.setVec3("pointLights[" + number + "].position", Point[i].position);
        _shader.setVec3("pointLights[" + number + "].ambient", Point[i].ambient);
        _shader.setVec3("pointLights[" + number + "].diffuse", Point[i].diffuse);
        _shader.setVec3("pointLights[" + number + "].specular", Point[i].specular);
        _shader.setFloat("pointLights[" + number + "].constant", Point[i].constant);
        _shader.setFloat("pointLights[" + number + "].linear", Point[i].linear);
        _shader.setFloat("pointLights[" + number + "].quadratic", Point[i].quadratic);
    }
}

void LightSource::updateShaderCamera(Camera _camera, Shader _shader)
{
    _shader.use();
    _shader.setVec3("viewPos", _camera.Position);

    // spotLight
    _shader.setVec3("spotLight.position", _camera.Position);
    _shader.setVec3("spotLight.direction", _camera.Front);
}

void LightSource::updateShader(Shader _shader)
{
    updateShaderAllDir(_shader);
    updateShaderAllPoint(_shader);
    updateShaderAllSpot(_shader);
}