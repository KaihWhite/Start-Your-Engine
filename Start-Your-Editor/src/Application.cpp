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
#include "ImGuiFileDialog.h"

unsigned int SCR_WIDTH = 1600;
unsigned int SCR_HEIGHT = 800;

Game demo(SCR_WIDTH, SCR_HEIGHT);
bool In_Game = false;


static int counter = 0;
bool selectObject = false; // Flag to control visibility of attributes tab
std::string selectedObjectKey = ""; // Index of the currently selected object
bool selectCamera = false;
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

void showObjects() {
    ImGui::Begin("Game Objects tab ");

    // Optional: Add a button to add a new object
    if (ImGui::Button("Add Object")) {
       // Code to add a new object to the gameObjects vector
       //addGameObject(std::string name, ObjectType type, RigidBodyType rtype, std::unordered_map<std::string, Animation*> animations, glm::vec3 color, glm::vec2 size, glm::vec2 pos);
        std::string name = "object";
        std::unordered_map<std::string, Animation*> animations;
        animations["idle"] = new Animation("awesomeface", 1);
        glm::vec3 color = glm::vec3(0.5,0.5,0.5);
        glm::vec2 size = glm::vec2(5.0,5.0);
		glm::vec2 position = glm::vec2(0.0,0.0);
		// if the name key is not created yet
        if (demo.gameObjects.find(name) == demo.gameObjects.end()) {
            demo.addGameObject(name, OBJECT, STATIC, animations, color, size, position);
        }
        
    }
    // Start a scrolling region
    ImGui::BeginChild("ObjectList", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
    if (ImGui::Selectable("Camera", false)) {
        // Handle selection logic here
        selectObject = false;
		selectCamera = true;
        selectedObjectKey = "";
    }
    for (const auto& pair : demo.gameObjects) {
        if (ImGui::Selectable(pair.second->name.c_str(), false)) {
            // Handle selection logic here
            selectCamera = false;
            selectObject = true;
            selectedObjectKey = pair.first;
        }
    }
   
    std::ostringstream stream;
    stream << "total objects: " << selectedObjectKey <<" ->" << demo.gameObjects.size();
    std::string lengthText = stream.str();
    ImGui::TextWrapped( lengthText.c_str());
    // End the scrolling region
    ImGui::EndChild();
    ImGui::End();
}

void showAttributes() {
    // 
    if (selectCamera == false && selectObject == false && demo.gameObjects.find(selectedObjectKey) != demo.gameObjects.end()) {
        ImGui::Begin("Game Object attributes tab ");
        ImGui::TextWrapped("this is the attributes tab where the object's property is displayed and changed accordingly");
        ImGui::End();
    }
    else if (selectCamera == true && selectObject == false && demo.gameObjects.find(selectedObjectKey) == demo.gameObjects.end()) {
        ImGui::Begin("Game Object attributes tab ");
        ImGui::TextWrapped("in camera setting");
        if (ImGui::TreeNode("camera movement:")) {
            ImGui::Button("move left");
            if (ImGui::IsItemActive()) {
                demo.cameraMan->moveCamera(glm::vec2(-1, 0), 0.3);
                }
            ImGui::Button("move right");
            if (ImGui::IsItemActive()) {
                demo.cameraMan->moveCamera(glm::vec2(1, 0), 0.3);
            }
            ImGui::Button("move up");
            if (ImGui::IsItemActive()) {
                demo.cameraMan->moveCamera(glm::vec2(0, -1), 0.3);
             }
             ImGui::Button("move down");
             if (ImGui::IsItemActive()) {
                 demo.cameraMan->moveCamera(glm::vec2(0, 1), 0.3);
             }
             ImGui::TreePop();
         }
         
        if (ImGui::TreeNode("player camera movement:")) {
             ImGui::Checkbox("follow player", &demo.cameraMan->enableFollow);
             ImGui::Checkbox("Look Ahead", &demo.cameraMan->enableLookahead);
             ImGui::TreePop();
        }

        ImGui::End();            
    }
    else if (selectCamera == false && selectObject == true && demo.gameObjects.find(selectedObjectKey) != demo.gameObjects.end()) {
        ImGui::Begin("Game Object attributes tab ");
        
            ImGui::TextWrapped("in object setting");
            if (ImGui::Button("gravity")) {
                //demo.cameraMan->moveCamera(glm::vec2(-100, 0), ImGui::GetIO().DeltaTime);
                demo.gameObjects.find(selectedObjectKey)->second->body->SetGravityScale(0.0);

            }
            ImGui::Button("move left");
            if (ImGui::IsItemActive()) {
                //demo.cameraMan->moveCamera(glm::vec2(-100, 0), ImGui::GetIO().DeltaTime);
                demo.gameObjects.find(selectedObjectKey)->second->body->SetTransform(
                    demo.gameObjects.find(selectedObjectKey)->second->body->GetPosition()
                    + b2Vec2(-0.005, 0), 0);
           
            }
            ImGui::Button("move right");
            if (ImGui::IsItemActive()) {
                demo.gameObjects.find(selectedObjectKey)->second->body->SetTransform(
                    demo.gameObjects.find(selectedObjectKey)->second->body->GetPosition()
                    + b2Vec2(0.005, 0), 0);
            }
            ImGui::Button("move up");
            if (ImGui::IsItemActive()) {
                demo.gameObjects.find(selectedObjectKey)->second->body->SetTransform(
                    demo.gameObjects.find(selectedObjectKey)->second->body->GetPosition()
                    + b2Vec2(0, -0.005), 0);
            }
            ImGui::Button("move down");
            if (ImGui::IsItemActive()) {
                demo.gameObjects.find(selectedObjectKey)->second->body->SetTransform(
                    demo.gameObjects.find(selectedObjectKey)->second->body->GetPosition()
                    + b2Vec2(0, 0.005), 0);
            
            };

        ImGui::End();
    }
    else {
        // nothing
        ImGui::Begin("Game Object attributes tab ");
        ImGui::TextWrapped("this is the attributes tab where the object's property is displayed and changed acco     rdingly");
        ImGui::End();
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

    //demo.initLevel(Level::loadFromJSON("test.json", demo.world, demo.cameraMan));

    

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
                    if (demo.gameObjects.empty()) {
                        // No level loaded, show a popup window
                        ImGui::OpenPopup("NoLevelLoaded");
                    }
                    else {
                        In_Game = true;  // Proceed to play the level
                    }
                }
                if (ImGui::MenuItem("Exit Level")) {
                    In_Game = false;
                }
                if (ImGui::MenuItem("load Level", "Ctrl+O")) {
                    //demo.initLevel(Level::loadFromJSON("test.json", demo.world, demo.cameraMan));
                    IGFD::FileDialogConfig config; config.path = ".";
                    ImGuiFileDialog::Instance()->OpenDialog("ChooseLevelDlgKey", "Choose Level", ".json", config);
                }
                if (ImGui::MenuItem("Save level", "Ctrl+S")) {
                    IGFD::FileDialogConfig config; config.path = ".";
                    ImGuiFileDialog::Instance()->OpenDialog("SaveLevelDlgKey", "Save Level", ".json", config);
                    //Level::saveToJSON("test.json", demo.gameObjects);
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
        showObjects();
        showAttributes();
        

       /* ImGui::Begin("Game Object attributes tab ");
        ImGui::TextWrapped("this is the attributes tab where the object's property is displayed and changed accordingly");
        ImGui::End();*/

        ImGui::Begin("Assets tab ");
        ImGui::TextWrapped("this is the asset's tab where the user can import and export assets into the level and outside the level");
        

        ImGui::End();

        if (!In_Game) {
            demo.State = GameState::GAME_EDITOR;
            // Render title screen
            ImGui::Begin("scene tab ");
            ImGuiIO& io = ImGui::GetIO();
            
            // frame buffer rendering section
            frameBuffer.startBind();
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
           
			demo.Update();
            demo.Render();
            // unbind the framebuffer that renders the scene
            frameBuffer.endBind();
            // gets the scene window size so it can resize the image per frame
            ImVec2 wSize = ImGui::GetWindowSize();

            // renders the buffered texture from the frame buffer into the ImGui image scene
            ImGui::Image((void*)(intptr_t)frameBuffer.gettextureID(), ImVec2(wSize.x, wSize.y), ImVec2(0, 1), ImVec2(1, 0));
            if (ImGui::IsItemHovered())
            {
                if (ImGui::IsMouseDragging(0)) {
                    //std::cout << " h" << std::endl;
                    // Calculate movement based on mouse delta
                    float deltaX = -io.MouseDelta.x / io.DeltaTime;
                    float deltaY = -io.MouseDelta.y / io.DeltaTime;

                    // Update camera position
                    demo.cameraMan->moveCamera(glm::vec2(deltaX, deltaY), io.DeltaTime);
                }
            }
            ImGui::End();
        }
        else if (In_Game) {
            demo.State = GameState::GAME_ACTIVE;
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

        } else {
            ImGui::Begin("scene tab ");
            ImGuiIO& io = ImGui::GetIO();

            // frame buffer rendering section
            frameBuffer.startBind();
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

			// render default scene


            // unbind the framebuffer that renders the scene
            frameBuffer.endBind();
            // gets the scene window size so it can resize the image per frame
            ImVec2 wSize = ImGui::GetWindowSize();

            // renders the buffered texture from the frame buffer into the ImGui image scene
            ImGui::Image((void*)(intptr_t)frameBuffer.gettextureID(), ImVec2(wSize.x, wSize.y), ImVec2(0, 1), ImVec2(1, 0));
            ImGui::End();
        }

        // Modal popup for warning if no level is loaded
        if (ImGui::BeginPopupModal("NoLevelLoaded")) {
            ImGui::Text("No level loaded. Please load a level before playing.");
            if (ImGui::Button("OK")) {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }

        // Dialogs for loading and saving levels
        if (ImGuiFileDialog::Instance()->Display("ChooseLevelDlgKey")) {
            if (ImGuiFileDialog::Instance()->IsOk()) { // action if OK
                std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
                // action
                demo.initLevel(Level::loadFromJSON(filePathName, demo.world, demo.cameraMan));
            }
            // close
            ImGuiFileDialog::Instance()->Close();
        }

        if (ImGuiFileDialog::Instance()->Display("SaveLevelDlgKey")) {
            if (ImGuiFileDialog::Instance()->IsOk()) {
                std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
                // action
                Level::saveToJSON(filePathName, demo.gameObjects);
            }
            ImGuiFileDialog::Instance()->Close();
        }

        // Rendering imgui elements
        imguiWindow->endRender();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    imguiWindow->destroyWindow();

    ResourceManager::Clear();
    glfwTerminate();


    return 0;

}
