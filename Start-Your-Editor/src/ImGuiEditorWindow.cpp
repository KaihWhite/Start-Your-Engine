/*
  by kunga ngochetsang
  test

*/


#include "ImGuiEditorWindow.h"


ImGuiEditorWindow::ImGuiEditorWindow(GLFWwindow* wind,Game& engine, unsigned int width, unsigned  int height)
    : window(wind),engine(engine), SCR_WIDTH(width), SCR_HEIGHT(height), context(ImGui::CreateContext()), io(ImGui::GetIO())
{
    
    // this is for the interativity for the object selection and its attributes section
    counter = 0;
    selectCamera = false;
    selectObject = false;
    selectedObjectKey = NULL;
    // this initialised the setup for the framebuffer for the scene
    frameBuffer = FrameBuffer();
    frameBuffer.setupConfig(SCR_WIDTH, SCR_HEIGHT);
    /* Init game */
    engine.Init(SCR_WIDTH, SCR_HEIGHT);
    IMGUI_CHECKVERSION();
    
    (void)io;
}


ImGuiEditorWindow::~ImGuiEditorWindow()
{
    delete context;
    delete window;
}

void ImGuiEditorWindow::createWindow() {
   

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 400");
}

void ImGuiEditorWindow::startRender() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    // starts the feature of docking the widgets
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()); 
}

void ImGuiEditorWindow::onRender() {
    toolBarSection();
    objectSection();
    attributeSection();
    sceneSection();
    assetSection();
}

void ImGuiEditorWindow::endRender() {
    // Rendering imgui elements
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void ImGuiEditorWindow::destroyWindow() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}



//content functions for the on render funtions
void ImGuiEditorWindow::toolBarSection()
{
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
                if (engine.gameObjects.empty()) {
                    // No level loaded, show a popup window
                    ImGui::OpenPopup("NoLevelLoaded");
                }
                else {
                    engine.State =GAME_ACTIVE;  // Proceed to play the level
                }
            }
            if (ImGui::MenuItem("Exit Level")) {
                engine.State = GAME_EDITOR;
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


    // Dialogs for loading and saving levels
    if (ImGuiFileDialog::Instance()->Display("ChooseLevelDlgKey")) {
        if (ImGuiFileDialog::Instance()->IsOk()) { // action if OK
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            // action
            engine.initLevel(Level::loadFromJSON(filePathName, engine.world, engine.cameraMan));
        }
        // close
        ImGuiFileDialog::Instance()->Close();
    }

    if (ImGuiFileDialog::Instance()->Display("SaveLevelDlgKey")) {
        if (ImGuiFileDialog::Instance()->IsOk()) {
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            // action
            Level::saveToJSON(filePathName, engine.gameObjects);
        }
        ImGuiFileDialog::Instance()->Close();
    }
}


void ImGuiEditorWindow::objectSection()
{
    ImGui::Begin("Game Objects tab ");

    // Optional: Add a button to add a new object
    if (ImGui::Button("Add Object")) {
        // Code to add a new object to the gameObjects vector
        //addGameObject(std::string name, ObjectType type, RigidBodyType rtype, std::unordered_map<std::string, Animation*> animations, glm::vec3 color, glm::vec2 size, glm::vec2 pos);
        std::string name = "object";
        std::unordered_map<std::string, Animation*> animations;
        animations["idle"] = new Animation("awesomeface", 1);
        glm::vec3 color = glm::vec3(0.5, 0.5, 0.5);
        glm::vec2 size = glm::vec2(5.0, 5.0);
        glm::vec2 position = glm::vec2(0.0, 0.0);

        // This will only be able to handle static, non-player/npc objects
        engine.addGameObject(name, ObjectType::OBJECT, RigidBodyType::STATIC, animations, color, size, position);
        // Below not necesary with unique key generation
        /*
        if (engine.gameObjects.find(name) == engine.gameObjects.end()) {
            engine.addGameObject(name, OBJECT, STATIC, animations, color, size, position);
        }
        */

    }
    // Start a scrolling region
    ImGui::BeginChild("ObjectList", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
    if (ImGui::Selectable("Camera", false)) {
        // Handle selection logic here
        selectObject = false;
        selectCamera = true;
        selectedObjectKey = NULL;
    }
    for (const auto& pair : engine.gameObjects) {
        if (ImGui::Selectable(pair.second->name.c_str(), false)) {
            // Handle selection logic here
            selectCamera = false;
            selectObject = true;
            selectedObjectKey = pair.first;
        }
    }

    std::ostringstream stream;
    stream << "total objects: " << selectedObjectKey << " ->" << engine.gameObjects.size();
    std::string lengthText = stream.str();
    ImGui::TextWrapped(lengthText.c_str());
    // End the scrolling region
    ImGui::EndChild();
    ImGui::End();
}

void ImGuiEditorWindow::attributeSection()
{
    // 
    if (selectCamera == false && selectObject == false && engine.gameObjects.find(selectedObjectKey) != engine.gameObjects.end()) {
        ImGui::Begin("Game Object attributes tab ");
        ImGui::TextWrapped("this is the attributes tab where the object's property is displayed and changed accordingly");
        ImGui::End();
    }
    else if (selectCamera == true && selectObject == false && engine.gameObjects.find(selectedObjectKey) == engine.gameObjects.end()) {
        ImGui::Begin("Game Object attributes tab ");
        ImGui::TextWrapped("in camera setting");
        if (ImGui::TreeNode("camera movement:")) {
            ImGui::Button("move left");
            if (ImGui::IsItemActive()) {
                engine.cameraMan->moveCamera(glm::vec2(-1, 0), 0.3);
            }
            ImGui::Button("move right");
            if (ImGui::IsItemActive()) {
                engine.cameraMan->moveCamera(glm::vec2(1, 0), 0.3);
            }
            ImGui::Button("move up");
            if (ImGui::IsItemActive()) {
                engine.cameraMan->moveCamera(glm::vec2(0, -1), 0.3);
            }
            ImGui::Button("move down");
            if (ImGui::IsItemActive()) {
                engine.cameraMan->moveCamera(glm::vec2(0, 1), 0.3);
            }
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("player camera movement:")) {
            ImGui::Checkbox("follow player", &engine.cameraMan->enableFollow);
            ImGui::Checkbox("Look Ahead", &engine.cameraMan->enableLookahead);
            ImGui::TreePop();
        }

        ImGui::End();
    }
    else if (selectCamera == false && selectObject == true && engine.gameObjects.find(selectedObjectKey) != engine.gameObjects.end()) {
        ImGui::Begin("Game Object attributes tab ");

        ImGui::TextWrapped("in object setting");
        if (ImGui::Button("gravity")) {
            //demo.cameraMan->moveCamera(glm::vec2(-100, 0), ImGui::GetIO().DeltaTime);
            engine.gameObjects.find(selectedObjectKey)->second->body->SetGravityScale(0.0);

        }
        ImGui::Button("move left");
        if (ImGui::IsItemActive()) {
            //demo.cameraMan->moveCamera(glm::vec2(-100, 0), ImGui::GetIO().DeltaTime);
            engine.gameObjects.find(selectedObjectKey)->second->body->SetTransform(
                engine.gameObjects.find(selectedObjectKey)->second->body->GetPosition()
                + b2Vec2(-0.005, 0), 0);

        }
        ImGui::Button("move right");
        if (ImGui::IsItemActive()) {
            engine.gameObjects.find(selectedObjectKey)->second->body->SetTransform(
                engine.gameObjects.find(selectedObjectKey)->second->body->GetPosition()
                + b2Vec2(0.005, 0), 0);
        }
        ImGui::Button("move up");
        if (ImGui::IsItemActive()) {
            engine.gameObjects.find(selectedObjectKey)->second->body->SetTransform(
                engine.gameObjects.find(selectedObjectKey)->second->body->GetPosition()
                + b2Vec2(0, -0.005), 0);
        }
        ImGui::Button("move down");
        if (ImGui::IsItemActive()) {
            engine.gameObjects.find(selectedObjectKey)->second->body->SetTransform(
                engine.gameObjects.find(selectedObjectKey)->second->body->GetPosition()
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
void ImGuiEditorWindow::sceneSection()
{
    // scene render section
    if (engine.State == GameState::GAME_EDITOR) {
        // Render title screen
        ImGui::Begin("scene tab ");
        ImGuiIO& io = ImGui::GetIO();

        // frame buffer rendering section
        frameBuffer.startBind();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        engine.Update();
        engine.Render();
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
                engine.cameraMan->moveCamera(glm::vec2(deltaX, deltaY), io.DeltaTime);
            }
        }
        ImGui::End();
    }
    else if (engine.State == GameState::GAME_ACTIVE) {
        
        ImGui::Begin("scene tab ");
        // frame buffer rendering section
        frameBuffer.startBind();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // game is rendered here and updated
        engine.Update();
        engine.Render();

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
    else {
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

}

void ImGuiEditorWindow::assetSection()
{

    ImGui::Begin("Assets tab ");
    ImGui::TextWrapped("this is the asset's tab where the user can import and export assets into the level and outside the level");


    if (ImGui::Button("Load New Asset")) {
        // open a file dialog to select a PNG file
        IGFD::FileDialogConfig config;
        config.path = ".";
        ImGuiFileDialog::Instance()->OpenDialog("ChooseAssetDlgKey", "Choose Asset", ".png", config);
    }

    // handle file selection
    if (ImGuiFileDialog::Instance()->Display("ChooseAssetDlgKey")) {
        if (ImGuiFileDialog::Instance()->IsOk()) {
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            std::string fileName = ImGuiFileDialog::Instance()->GetCurrentFileName();
            // load the selected asset using LoadTexture
            ResourceManager::LoadTexture(filePathName.c_str(), true, fileName);
            ImGui::Text("Loaded: %s", fileName.c_str());
        }
        ImGuiFileDialog::Instance()->Close();
    }

    // display loaded assets
    ImGui::Text("Loaded Assets:");
    ImGui::Separator();
    ImGui::BeginChild("AssetsScrolling", ImVec2(0, 200), true, ImGuiWindowFlags_HorizontalScrollbar);

    for (auto it = ResourceManager::Textures.begin(); it != ResourceManager::Textures.end();) {
        ImGui::PushID(it->second.ID); // use the texture ID to push the ID

        // display asset thumbnail
        if (ImGui::ImageButton((void*)(intptr_t)it->second.ID, ImVec2(80, 80))) {
            selectedAssetForPreview = it->first; // set the asset for preview
        }
        ImGui::PopID();

        bool remove_item = false; // flag to determine if the item should be removed

        // context menu for asset removal
        if (ImGui::BeginPopupContextItem()) {
            if (ImGui::MenuItem("Remove")) {
                remove_item = true;
            }
            ImGui::EndPopup();
        }

        if (remove_item) {
            glDeleteTextures(1, &it->second.ID); // delete OpenGL texture
            it = ResourceManager::Textures.erase(it); // remove from ResourceManager and safely increment the iterator
        }
        else {
            it++; // only increment the iterator if no item was removed
        }

        ImGui::SameLine(); // display assets in the same line (horizontally)
    }
    ImGui::EndChild();

    // asset preview
    if (!selectedAssetForPreview.empty()) {
        showAssetPreviewWindow();
    }

    ImGui::End();
}

void ImGuiEditorWindow::showAssetPreviewWindow() {
    if (selectedAssetForPreview.empty()) return; // check if an asset is selected

    // start a new ImGui window for preview
    bool open = true; // variable to control the open state of the window
    ImGui::Begin(("Preview: " + selectedAssetForPreview).c_str(), &open, ImGuiWindowFlags_AlwaysAutoResize);

    // retrieve the texture for the selected asset
    Texture2D& texture = ResourceManager::GetTexture(selectedAssetForPreview);

    // calculate the window size based on the texture size
    ImVec2 windowSize(static_cast<float>(texture.Width), static_cast<float>(texture.Height));

    // display the texture
    ImGui::Image((void*)(intptr_t)texture.ID, windowSize);
    ImGui::End();

    // if the window is closed clear the selection
    if (!open) {
        selectedAssetForPreview.clear();
    }
}
