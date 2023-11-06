#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "renderer.h"
#include "GameObject.h"


// Callback function for resizing the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Process input from keyboard
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /*set frambuffer function*/
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* GLAD Loader */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    /* Set size of rendering window */
    glViewport(0, 0, 800, 600);

    /* load shaders */
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.fs", nullptr, "sprite");
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/fragAnim.fs", nullptr, "anim");

    /* configure shaders with uniforms */
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(800), static_cast<float>(600), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

    ResourceManager::GetShader("anim").Use().SetInteger("image", 0);
    ResourceManager::GetShader("anim").SetMatrix4("projection", projection);
    ResourceManager::GetShader("anim").SetInteger("currentFrame", 0);
    ResourceManager::GetShader("anim").SetInteger("totalFrames", 10);



    /* create renderer */
    Renderer *renderer = new Renderer(ResourceManager::GetShader("sprite"));
    Renderer *animRenderer = new Renderer(ResourceManager::GetShader("anim"));

    /* load textures */
    ResourceManager::LoadTexture("textures/awesomeface.png", true, "face");
    ResourceManager::LoadTexture("textures/idle.png", true, "idle");

    /* create player game object*/
    GameObject *player = new GameObject(glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), 0.0f, ResourceManager::GetTexture("idle"));

    /* deltaTime variables */
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* calculate delta time  */
        float currentFrame = glfwGetTime();
        std::cout << currentFrame << std::endl;
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();

        processInput(window);

        /* Render here */
        
        //renderer->RenderSprite(ResourceManager::GetTexture("face"), glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f * currentFrame, glm::vec3(1.0f, 1.0f, 1.0f));

        /* Set current frame for character animations by texture sampling with the fragment shader. Check shaders/fragAmin.fs */
        ResourceManager::GetShader("anim").SetInteger("currentFrame", (int)(10 * currentFrame) % 10);
        player->draw(*animRenderer);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}