#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "shader/shader_s.h"


class MyGui
{
public:

	MyGui()
	{

	}

    ~MyGui()
    {

    }

    void display();
    void destory();
    void clickF1();
    void regShader(Shader* _shader) { control_shader = _shader; }

    bool isLightShaderOn() { return isLightShader; }
    bool isFogEffectOn() { return isFogEffect; }
    bool isUIShow() { return ui_show; }

    void init(GLFWwindow* window, const char* glsl_version);

private:
    bool show_demo_window;
    bool show_another_window ;
    ImVec4 clear_color;
    bool isLightShader;
    bool isFogEffect;
    GLFWwindow* t_window;
    bool ui_show;
    Shader* control_shader;
};
