/*
  by kunga ngochetsang
*/

#include <iostream>
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "game.h"

unsigned int SCR_WIDTH = 1600;
unsigned int SCR_HEIGHT = 800;
Game demo(SCR_WIDTH, SCR_HEIGHT);
bool In_Game = false;

// Callback function for resizing the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

}

// Callback function for key presses and save key state to an array
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        //glfwSetWindowShouldClose(window, true);
        In_Game = false;
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            demo.Keys[key] = true;
        else if (action == GLFW_RELEASE)
            demo.Keys[key] = false;
    }
}

int main()
{
    std::cout << "welcome page" << std::endl;
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Start Your Editor", NULL, NULL);
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


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 400");

    /* Init game */
    demo.Init(SCR_WIDTH, SCR_HEIGHT);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // Here you can add ImGui widgets
        ImGui::Begin("wellcome tab ");
        ImGui::Text("welcome to the UI/game editor, which uses an awesome 2d game engine called Start-Your-Engine ");
        ImGui::End();
        if (!In_Game) {
            // Render title screen
            ImGui::Begin("Main menu");
            ImGui::Text("Press the \"Play\" to start your game");

            if (ImGui::Button("Play")) {
                In_Game = true; // Change state to start the game
            }
            ImGui::Text("Press the \"Exit Program\" to Close the application");
            if (ImGui::Button("Exit Program")) {
                glfwSetWindowShouldClose(window, true);
            }

            ImGui::End();
        }
        else if (In_Game) {
            ImGui::Begin("controller tab ");
            ImGui::Text(" Press the esc key to go back to the main menu");
            ImGui::Text(" Press the 'A' and 'D' keys respectively to go left and right  ");
            ImGui::Text(" Press the 'W' and 'S' keys respectively to look up and down  ");
            ImGui::Text(" Press the 'SPACE' key respectively to jump ");
            ImGui::End();
            // Update and render game
            demo.Update();
            demo.Render();
        }
        // Rendering imgui elements
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    ResourceManager::Clear();
    glfwTerminate();


    return 0;

}
