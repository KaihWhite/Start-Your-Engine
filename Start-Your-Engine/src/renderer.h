#pragma once

#include "resource_manager.h"
#include "shader.h"
#include "stb_image.h"

class Renderer
{
public:
	Renderer(Shader& shader);
	~Renderer();

	void RenderSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color);

private:
	// I may not need to tie a shader to the renderer, and rather tie the shader to the animation class
	Shader shader;
	unsigned int quadVAO;

	// Initializes and configures the quad's buffer and vertex attributes
	void initRenderData();

};

