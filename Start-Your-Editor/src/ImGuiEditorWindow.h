#pragma once

/*
  by kunga ngochetsang
*/

#include <iostream>
#include <sstream>
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "game.h"
#include "ImGuiFileDialog.h"
#include "Framebuffer.h"
#include "level.h"

class ImGuiEditorWindow
{

private:
	GLFWwindow* window;
	ImGuiContext* context;
	ImGuiIO& io;
	unsigned int SCR_WIDTH;
	unsigned int SCR_HEIGHT;
	Game& engine;
	/* setting for the frame buffer for ImGui  */
	FrameBuffer frameBuffer;
	int counter;
	bool selectObject; // Flag to control visibility of attributes tab
	int selectedObjectKey; // Index of the currently selected object
	bool selectCamera;

	std::string selectedAssetForPreview; // Declare the member variable
public:

	// constructor
	ImGuiEditorWindow(GLFWwindow* wind, Game& engine, unsigned int width, unsigned  int height);
	//destructor
	~ImGuiEditorWindow();
	// creates te setup window
	void createWindow();
	void startRender();
	void onRender();
	void endRender();
	void destroyWindow();
	
	// Collision box
	bool showCollisionBoxControls;
	float collisionBoxWidth;
	float collisionBoxHeight;
	int collisionBoxShape; // 0 = Rectangle, 1 = Circle, 2 = Triangle
	void collisionBoxControls(GameObject* gameObject);
private:
	// content funtions for on render
	void toolBarSection();
	void objectSection();
	void attributeSection();
	void sceneSection();
	void assetSection();

	// helper methods for assetSection
	void showAssetPreviewWindow(); 

	// helper methods attributeSection
	void objectDataSubsectionOfAttributeSection();
	void physicsSubsectionOfAttributeSection();
	void animationSubsectionOfAttributeSection();

	//helper methods for animationSubsectionOfAttributeSection
	void addNewAnimation();
	void deleteExistingAnimation();
	void selectCurrentAnimation();
};