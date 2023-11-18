#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "game.h"

// Global variables
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
Game demo(SCR_WIDTH, SCR_HEIGHT);



// Callback function for resizing the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

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
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Start Your Engine", NULL, NULL);
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
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);


    /* Init game */
    //demo.Init(SCR_WIDTH, SCR_HEIGHT);


    /* deltaTime variables */
    float deltaTime = 0.0f;
    double lastFrame = 0.0f;


    /* Test */
    ResourceManager::LoadShader("Start-Your-Engine/shaders/sprite.vs", "Start-Your-Engine/shaders/sprite.fs", nullptr, "sprite");
    ResourceManager::GetShader("sprite").Use().SetInteger("image", (int)0);
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), static_cast<float>(SCR_HEIGHT), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    
    // I think the error lies in the paths. Changing the project settings change the default path for the project.
    // the reason nothing was rendering is because the relative paths need to be different.
    ResourceManager::LoadTexture("Start-Your-Engine/textures/Grey_Brick.png", true, "ground");

    Renderer* renderer = new Renderer(ResourceManager::GetShader("sprite"));
    glm::vec2 position = glm::vec2(200.0f, 200.0f);
    glm::vec2 size = glm::vec2(300.0f, 400.0f);
    float rotate = glm::radians(0.0f);
    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
    


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* calculate delta time  */
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();


        /* Update game objects */
        //demo.Update(deltaTime);



        /* Render here */
        //demo.Render();

        renderer->RenderSprite(ResourceManager::GetTexture("ground"), position, size, rotate, color);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    ResourceManager::Clear();
    glfwTerminate();
    return 0;
}
