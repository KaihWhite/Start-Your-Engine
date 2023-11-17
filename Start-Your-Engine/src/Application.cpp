<<<<<<< HEAD
#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
=======
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "game.h"

// Global variables
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
Game demo(SCR_WIDTH, SCR_HEIGHT);


>>>>>>> 343654b8ab6d5da33ca300c68253688bfd59598d

// Callback function for resizing the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

<<<<<<< HEAD
// Process input from keyboard
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
=======
// Callback function for key presses and save key state to an array
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            demo.Keys[key] = true;
        else if (action == GLFW_RELEASE)
            demo.Keys[key] = false;
    }
>>>>>>> 343654b8ab6d5da33ca300c68253688bfd59598d
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
<<<<<<< HEAD
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for Mac OS X

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
=======
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Start Your Engine", NULL, NULL);
>>>>>>> 343654b8ab6d5da33ca300c68253688bfd59598d
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

<<<<<<< HEAD
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /*set frambuffer function*/
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // GLAD Loader
=======

    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    /* set key callback */
    glfwSetKeyCallback(window, key_callback);


    /* set frambuffercallback */
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    /* GLAD Loader */
>>>>>>> 343654b8ab6d5da33ca300c68253688bfd59598d
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

<<<<<<< HEAD
    /*Set size of rendering window*/
    glViewport(0, 0, 800, 600);
=======

    /* Set size of rendering window */
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);


    /* Init game */
    demo.Init(SCR_WIDTH, SCR_HEIGHT);


    /* deltaTime variables */
    float deltaTime = 0.0f;
    double lastFrame = 0.0f;

>>>>>>> 343654b8ab6d5da33ca300c68253688bfd59598d

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
<<<<<<< HEAD

        processInput(window);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
=======
        /* calculate delta time  */
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();


        /* Update game objects */
        demo.Update(deltaTime);

        /* Render here */
        demo.Render();
>>>>>>> 343654b8ab6d5da33ca300c68253688bfd59598d


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

<<<<<<< HEAD
    glfwTerminate();
    return 0;
}
=======
    ResourceManager::Clear();
    glfwTerminate();
    return 0;
}
>>>>>>> 343654b8ab6d5da33ca300c68253688bfd59598d
