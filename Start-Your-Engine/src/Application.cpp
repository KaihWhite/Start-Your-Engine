

/**
	by kunga ngochetsang
*/
#include<iostream>
#include "WindowComponent/CreateWindowForMe.h"
#include"QuadFactory/QuadComponents/ShaderComponent/Shader.h"
#include"QuadFactory/Quad.h"


#include<GLFW/glfw3.h>
#include "QuadFactory/QuadComponents/TextureComponent/Texture.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glad_glViewport(0, 0, width, height);
}

int main() {
	//float vertices[] = {
	//	// positions          // colors           // texture coords
	//	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	//};
	float vertices[] = {
		// positions          // colors           // texture coords
		 1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 1.0f, -1.0f, 0.0f,   0.0f, 0.3f, 0.0f,   1.0f, 0.0f,   // bottom right
		-1.0, -1.0f, 0.0f,   0.0f, 0.0f, 0.3f,   0.0f, 0.0f,   // bottom left
		-1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	
	CreateWindowForMe windowObject = CreateWindowForMe("game",800,600);
	windowObject.activateWindow();
	GLFWwindow* window = windowObject.giveMeWindow();
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	unsigned int EBO;

	glGenBuffers(1, &EBO);
	unsigned int VAO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	// creates a vertex buffer
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	// 0. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	Texture texture1 = Texture("QuadFactory/QuadComponents/TextureComponent/textureFiles/level2.jpg");
	Shader shaderProgram = Shader("QuadFactory/QuadComponents/ShaderComponent/Shaders/vertex.shader", "QuadFactory/QuadComponents/ShaderComponent/Shaders/fragment.shader");

	// 1. then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);



	while (!glfwWindowShouldClose(window)) {
		windowObject.setWindowColorBackground(0.2f, 0.3f, 0.3f, 1.0f);
		windowObject.activateBasickeyboardInputs();
		
		glBindVertexArray(VAO);
		shaderProgram.use();
		texture1.use();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	windowObject.terminateWindow();
	return 0;
}