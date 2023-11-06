#include<iostream>
#include "WindowComponent/CreateWindowForMe.h"
#include"ShaderComponent/Shader.h"

#include<GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glad_glViewport(0, 0, width, height);
}

int main() {
	float vertices[] = {
-0.5f, -0.5f, 0.0f,
0.5f, -0.5f, 0.0f,
0.0f, 0.5f, 0.0f
	};

	CreateWindowForMe windowObject = CreateWindowForMe("game",800,600);
	windowObject.activateWindow();
	GLFWwindow* window = windowObject.giveMeWindow();
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	// creates a vertex buffer
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 0. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	Shader shaderProgram = Shader("ShaderComponent/Shaders/vertex.shader", "ShaderComponent/Shaders/fragment.shader");
	// 1. then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
		(void*)0);
	glEnableVertexAttribArray(0);
	while (!glfwWindowShouldClose(window)) {
		windowObject.setWindowColorBackground(0.2f, 0.3f, 0.3f, 1.0f);
		windowObject.pressEscToExit();
		shaderProgram.use();
		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	windowObject.terminateWindow();
	return 0;
}