#pragma once

/*
  by kunga ngochetsang
*/

#include <iostream>
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class ImGuiEditorWindow
{
private:
	GLFWwindow* window;

public:
	
	// constructor
	ImGuiEditorWindow(GLFWwindow* wind) { window = wind; };
	//destructor
	~ImGuiEditorWindow() { delete window; }
	// creates te setup window
	void createWindow();
	void startRender();
	void onRender();
	void endRender();
	void destroyWindow();

};

