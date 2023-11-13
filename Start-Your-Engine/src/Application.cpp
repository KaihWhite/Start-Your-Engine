#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "renderer.h"
#include "Player.h"
#include "Camera2D.h"

// Global variables
bool Keys[1024];


// Callback function for resizing the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Callback function for key presses and save key state to an array
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            Keys[key] = true;
        else if (action == GLFW_RELEASE)
            Keys[key] = false;
    }
}

int main(void)
{

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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


    /* set key callback */
    glfwSetKeyCallback(window, key_callback);


    /* set frambuffercallback */
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
    /*
        kunga
    */
    //ResourceManager::LoadShader("shaders/bacground.vs", "shaders/bacground.fs", nullptr, "background");

    /*initialize the camera the camera  */
    Camera2D mainCamera = Camera2D(0.0f, static_cast<float>(800), static_cast<float>(600), 0.0f);
    mainCamera.setCameraSpeed(50.0f);

    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projectionView", mainCamera.getPVMatrix());

    ResourceManager::GetShader("anim").Use().SetInteger("image", 0);
    ResourceManager::GetShader("anim").SetMatrix4("projectionView", mainCamera.getPVMatrix());
    ResourceManager::GetShader("anim").SetInteger("currentFrame", 0);
    ResourceManager::GetShader("anim").SetInteger("totalFrames", 10);


    /* create renderer */
    //Renderer *renderer = new Renderer(ResourceManager::GetShader("sprite"));
    Renderer* animRenderer = new Renderer(ResourceManager::GetShader("anim"));


    /* load textures */
    //ResourceManager::LoadTexture("textures/awesomeface.png", true, "face");
    ResourceManager::LoadTexture("textures/idle.png", true, "idle");


    /* create player game object */
    Player* player = new Player(glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), 0.0f, ResourceManager::GetTexture("idle"));


    /* deltaTime variables */
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* calculate delta time  */
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();


        /* Render here */

        /* the below renders a rotating face */
        /*renderer->RenderSprite(ResourceManager::GetTexture("face"), glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f * currentFrame, glm::vec3(1.0f, 1.0f, 1.0f));
        player->draw(*animRenderer);
        player->update(deltaTime);*/

        //moves the camera to the up and right at a constant speed
        mainCamera.setCameraPosition(glm::vec2(glfwGetTime(), glfwGetTime()));

        /* Set current frame for character animations by texture sampling with the fragment shader. Check shaders/fragAmin.fs */
        ResourceManager::GetShader("anim").SetInteger("currentFrame", (int)(10 * currentFrame) % 10);
        ResourceManager::GetShader("anim").SetMatrix4("projectionView", mainCamera.getPVMatrix());
        /*sets the projection view matrix to the player object shader*/
        player->draw(*animRenderer);

        //player->update(deltaTime);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}