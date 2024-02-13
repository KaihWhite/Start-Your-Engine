/*
  by kunga ngochetsang
*/

#include <iostream>
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "game.h"
#include "ImGuiEditorWindow.h"
#include "Framebuffer.h"
#include "level.h"

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

int main() {

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

    ImGuiEditorWindow* imguiWindow = new ImGuiEditorWindow(window);
    imguiWindow->createWindow();



    /* setting for the frame buffer for ImGui  */
    FrameBuffer frameBuffer = FrameBuffer();
    frameBuffer.setupConfig(SCR_WIDTH, SCR_HEIGHT);
    /* Init game */
    demo.Init(SCR_WIDTH, SCR_HEIGHT);

    demo.initLevel(Level::loadFromJSON("test.json", demo.world, demo.cameraMan));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        // Start the Dear ImGui frame
        imguiWindow->startRender();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

          // Upper head toolbar
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                // Add items to the File menu here
               
                
                if (ImGui::MenuItem("Exit rogram")) {
                    glfwSetWindowShouldClose(window, true);
                }
                // More File menu items...
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit")) {
                // Add items to the Edit menu here
                if (ImGui::MenuItem("Undo", "Ctrl+Z")) {
                }
                if (ImGui::MenuItem("Redo", "Ctrl+Y")) {
                }
                if (ImGui::MenuItem("Play Level")) {
                    In_Game = true;
                }
                if (ImGui::MenuItem("Exit Level")) {
                    In_Game = false;
                }
                if (ImGui::MenuItem("load Level", "Ctrl+O")) {
                    demo.initLevel(Level::loadFromJSON("test.json", demo.world, demo.cameraMan));
                }
                if (ImGui::MenuItem("Save level", "Ctrl+S")) {
                }
                // More File menu items...
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Insert")) {
                // Add items to the Insert menu here
                if (ImGui::MenuItem("Text", "?")) {
                }
                if (ImGui::MenuItem("Image", "?")) {
                }
                // More File menu items...
                ImGui::EndMenu();
            }
            // More toolbar items
            ImGui::EndMainMenuBar();
        }
        // Here you can add ImGui widgets
       
        ImGui::Begin("Game Objects tab ");
        ImGui::TextWrapped("welcome to the UI/game editor, which uses an awesome 2d game engine called Start-Your-Engine ");
        ImGui::End();


        ImGui::Begin("Game Object attributes tab ");
        ImGui::TextWrapped("this is the attributes tab where the object's property is displayed and changed accordingly");
        ImGui::End();

        ImGui::Begin("Assets tab ");
        ImGui::TextWrapped("this is the asset's tab where the user can import and export assets into the level and outside the level");
        ImGui::End();

        if (!In_Game) {
            // Render title screen
            ImGui::Begin("scene tab ");
            
            // frame buffer rendering section
            frameBuffer.startBind();
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            // unbind the framebuffer that renders the scene
            frameBuffer.endBind();
            // gets the scene window size so it can resize the image per frame
            ImVec2 wSize = ImGui::GetWindowSize();

            // renders the buffered texture from the frame buffer into the ImGui image scene
            ImGui::Image((void*)(intptr_t)frameBuffer.gettextureID(), ImVec2(wSize.x, wSize.y), ImVec2(0, 1), ImVec2(1, 0));

            ImGui::End();
        }
        else if (In_Game) {
            
            ImGui::Begin("scene tab ");
            // frame buffer rendering section
            frameBuffer.startBind();
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            // game is rendered here and updated
            demo.Update();
            demo.Render();
            // unbind the framebuffer that renders the scene
            frameBuffer.endBind();
            // gets the scene window size so it can resize the image per frame
            ImVec2 wSize = ImGui::GetWindowSize();

            // renders the buffered texture from the frame buffer into the ImGui image scene
            ImGui::Image((void*)(intptr_t)frameBuffer.gettextureID(), ImVec2(wSize.x, wSize.y), ImVec2(0, 1), ImVec2(1, 0));

            ImGui::End();

            ImGui::Begin("controller tab ");
            ImGui::TextWrapped(" Press the esc key to go back to the main menu");
            ImGui::TextWrapped(" Press the 'A' and 'D' keys respectively to go left and right  ");
            ImGui::TextWrapped(" Press the 'W' and 'S' keys respectively to look up and down  ");
            ImGui::TextWrapped(" Press the 'SPACE' key respectively to jump ");
            ImGui::End();

        }
        // Rendering imgui elements
        imguiWindow->endRender();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    imguiWindow->destroyWindow();

    Level::saveToJSON("autosave.json", demo.gameObjects);
    ResourceManager::Clear();
    glfwTerminate();


    return 0;

}
