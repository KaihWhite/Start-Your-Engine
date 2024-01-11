/*
Credit to the author of LearnOpenGL.com Joey de Vries for boilerplate code
*/
#pragma once

#include "resource_manager.h"
#include "shader.h"
#include "stb_image.h"
#include <glad/glad.h>
#include "GLFW/glfw3.h"

class Renderer
{
public:
	Renderer(Shader& shader);
	~Renderer();

	void RenderSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color);

private:
	Shader shader;
	unsigned int quadVAO;

	// Initializes and configures the quad's buffer and vertex attributes
	void initRenderData();

};

