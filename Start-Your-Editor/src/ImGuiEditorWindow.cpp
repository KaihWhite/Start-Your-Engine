/*
  by kunga ngochetsang
  test

*/


#include "ImGuiEditorWindow.h"


ImGuiEditorWindow::ImGuiEditorWindow(GLFWwindow* wind, Game& engine, unsigned int width, unsigned  int height)
	: window(wind), engine(engine), SCR_WIDTH(width), SCR_HEIGHT(height), context(ImGui::CreateContext()), io(ImGui::GetIO())
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
	engine.State = GAME_MENU;
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
		if (ImGui::BeginMenu("LEVEL")) {
			if (ImGui::MenuItem("create Level")) {
				engine.removeAllGameObject();
				engine.State = GAME_EDITOR;
			}
			// Add items to the Edit menu here
			if (ImGui::MenuItem("Play Level")) {
				if (engine.gameObjects.empty()) {
					// No level loaded, show a popup window
					ImGui::OpenPopup("NoLevelLoaded");
				}
				else {
					engine.State = GAME_ACTIVE;  // Proceed to play the level
				}
			}
			if (ImGui::MenuItem("load Level", "Ctrl+O")) {
				//demo.initLevel(Level::loadFromJSON("test.json", demo.world, demo.cameraMan));
				IGFD::FileDialogConfig config;
				config.path = "./Start-Your-Editor/Levels";
				ImGuiFileDialog::Instance()->OpenDialog("ChooseLevelDlgKey", "Choose Level", ".json", config);
				engine.State = GAME_EDITOR;
			}
			if (ImGui::MenuItem("Save level", "Ctrl+S")) {
				IGFD::FileDialogConfig config;
				config.path = "./Start-Your-Editor/Levels";
				ImGuiFileDialog::Instance()->OpenDialog("SaveLevelDlgKey", "Save Level", ".json", config);

			}
			if (ImGui::MenuItem("Exit Level")) {
				engine.State = GAME_EDITOR;
			}
			// More File menu items...
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("MODE")) {
			// Add items to the Insert menu here
			if (ImGui::MenuItem("EDITOR MODE", "?")) {
				engine.State = GAME_EDITOR;
			}
			if (ImGui::MenuItem("GAME MODE", "?")) {
				engine.State = GAME_ACTIVE;
			}
			if (ImGui::MenuItem("GAME MENU", "?")) {
				engine.State = GAME_MENU;
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
			engine.removeAllGameObject();
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
	if (engine.State == GAME_EDITOR) {
		// Optional: Add a button to add a new object
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 1.0f, 1.0f)); // red color
		if (ImGui::Button("Add Object")) {
			// Code to add a new object to the gameObjects vector
			//addGameObject(std::string name, ObjectType type, RigidBodyType rtype, std::unordered_map<std::string, Animation*> animations, glm::vec3 color, glm::vec2 size, glm::vec2 pos);
			std::string name = "object";
			std::unordered_map<std::string, Animation*> animations;
			animations["idle"] = new Animation("awesomeface", 1);
			glm::vec3 color = glm::vec3(0.5, 0.5, 0.5);
			glm::vec2 size = glm::vec2(5.0, 5.0);
			glm::vec2 position = glm::vec2(0.0, 0.0);

			std::unordered_set<std::string> sounds; // currently empty

			// This will only be able to handle static, non-player/npc objects
			engine.addGameObject(name, ObjectType::OBJECT, RigidBodyType::STATIC, animations, sounds, color, size, position);

		}
		ImGui::PopStyleColor(1);
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
		stream << "total objects: " << " ->" << engine.gameObjects.size();
		std::string lengthText = stream.str();
		ImGui::TextWrapped(lengthText.c_str());
		// End the scrolling region
		ImGui::EndChild();
	}
	ImGui::End();
}

void ImGuiEditorWindow::collisionBoxControls(GameObject* gameObject) {
	if (ImGui::Checkbox("Has Collision Box", &showCollisionBoxControls)) {
		gameObject->hasCustomCollisionBox = showCollisionBoxControls; // Update gameObject property
		if (!showCollisionBoxControls) {
			// If user unchecks the collision box, we remove the fixture from the body
			if (gameObject->body->GetFixtureList()) {
				gameObject->body->DestroyFixture(gameObject->body->GetFixtureList());
			}
		}
	}

	if (showCollisionBoxControls) {
		const char* shapes[] = { "Rectangle", "Circle", "Triangle" };
		ImGui::TextWrapped("Colision Shape: ");
		ImGui::Indent();
		ImGui::Combo("Shape", &collisionBoxShape, shapes, IM_ARRAYSIZE(shapes));
		gameObject->collisionBoxShape = collisionBoxShape; // Update gameObject property

		switch (collisionBoxShape) {
		case 0: // Rectangle
			ImGui::SliderFloat("Width", &collisionBoxWidth, 0.0f, 20.0f);
			ImGui::SliderFloat("Height", &collisionBoxHeight, 0.0f, 20.0f);
			gameObject->collisionBoxWidth = collisionBoxWidth; // Update gameObject property
			gameObject->collisionBoxHeight = collisionBoxHeight; // Update gameObject property
			break;
		case 1: // Circle
			ImGui::SliderFloat("Radius", &collisionBoxWidth, 0.0f, 20.0f); // Use Width as Radius
			gameObject->collisionBoxWidth = collisionBoxWidth; // Update gameObject property
			break;
		case 2: // Triangle
			ImGui::SliderFloat("Base", &collisionBoxWidth, 0.0f, 20.0f);
			ImGui::SliderFloat("Height", &collisionBoxHeight, 0.0f, 20.0f);
			gameObject->collisionBoxWidth = collisionBoxWidth; // Update gameObject property
			gameObject->collisionBoxHeight = collisionBoxHeight; // Update gameObject property
			break;
		}

		// Visualization of the shape
		ImGui::Text("Preview:");
		ImVec2 canvas_pos = ImGui::GetCursorScreenPos(); // ImDrawList API uses screen coordinates!
		ImVec2 canvas_size = ImVec2(200, 200); // Size of the canvas area
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		ImGui::InvisibleButton("canvas", canvas_size);

		draw_list->AddRectFilled(canvas_pos, ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y), IM_COL32(50, 50, 50, 255)); // Background
		const ImVec2 center = ImVec2(canvas_pos.x + canvas_size.x * 0.5f, canvas_pos.y + canvas_size.y * 0.5f);

		switch (collisionBoxShape) {
		case 0: // Rectangle
			draw_list->AddRect(ImVec2(center.x - collisionBoxWidth * 2, center.y - collisionBoxHeight * 2),
				ImVec2(center.x + collisionBoxWidth * 2, center.y + collisionBoxHeight * 2),
				IM_COL32(255, 255, 0, 255));
			break;
		case 1: // Circle
			draw_list->AddCircle(center, collisionBoxWidth * 2, IM_COL32(255, 255, 0, 255));
			break;
		case 2: // Triangle
			draw_list->AddTriangle(ImVec2(center.x, center.y - collisionBoxHeight * 2),
				ImVec2(center.x - collisionBoxWidth * 2, center.y + collisionBoxHeight * 2),
				ImVec2(center.x + collisionBoxWidth * 2, center.y + collisionBoxHeight * 2),
				IM_COL32(255, 255, 0, 255));
			break;
		}

		if (ImGui::Button("Apply Collision Box")) {
			gameObject->applyCollisionBox();
			ImGui::Separator();
			ImGui::Unindent();
		}
		// further colision features here:
		//........
		ImGui::TextWrapped("further other colision features here:");
		
		

	}
	//end of the colision features
	ImGui::Separator();
	ImGui::Unindent();
}

void ImGuiEditorWindow::attributeSection()
{
	ImGui::Begin("Game Object attributes tab ");
	if (engine.State == GAME_EDITOR) {
		if (selectCamera == false && selectObject == false && engine.gameObjects.find(selectedObjectKey) != engine.gameObjects.end()) {

			ImGui::TextWrapped("this is the attributes tab where the object's property is displayed and changed accordingly");
		}
		else if (selectCamera == true && selectObject == false && engine.gameObjects.find(selectedObjectKey) == engine.gameObjects.end()) {
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

		}
		else if (selectCamera == false && selectObject == true && engine.gameObjects.find(selectedObjectKey) != engine.gameObjects.end()) {
			ImGui::TextWrapped("in object setting");
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f)); // red color
			ImGui::Button("delete game object");
			if (ImGui::IsItemActive()) {
				engine.removeGameObject(selectedObjectKey);

			}
			ImGui::PopStyleColor();
			ImGui::Separator();
			/* together with checking if the key is in the gameobject map
				or not and checking if the animation is empty successfully
				gives enough time padding for the game object to be deleted while
				imgui onrender() runs
			*/
			if (engine.gameObjects.count(selectedObjectKey) == 0) {
				/* this is a second and last check if the object is deleted or not
					the reason is that even after the game object button is
					pressed, the imgui widget successfully retrieves the get
					current animation function while the game object is being
					deleted.  */
			}
			else {
				
				// tab bars for showing object  Subsection
				
				if (ImGui::BeginTabBar("object  Subsection")) {
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.0f, 1.0f)); // yellow color
					//  first tab
					if (ImGui::BeginTabItem("Data Subsection")) {
						objectDataSubsectionOfAttributeSection();
						physicsSubsectionOfAttributeSection();

						ImGui::EndTabItem();
					}
					//  second tab
					if (ImGui::BeginTabItem("Animation Subsection")) {
						animationSubsectionOfAttributeSection();
						ImGui::EndTabItem(); 
					}
					if (ImGui::BeginTabItem(" stats Subsection")) {
						ImGui::TextWrapped("this is the section for the object stats");
						ImGui::EndTabItem();
					}
					ImGui::PopStyleColor();
					ImGui::EndTabBar(); // End of the tab bar
				}
			}
		}
	}
	ImGui::End();
}
void ImGuiEditorWindow::sceneSection()
{
	ImGui::Begin("scene tab ");
	ImVec2 wSize = ImGui::GetWindowSize();
	// scene render section
	if (engine.State == GameState::GAME_EDITOR) {
		// Render title screen
			// frame buffer rendering section
		frameBuffer.startBind();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

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
				//shows that update in the scene
				if (engine.player != NULL)
					engine.player->updateCamera();
				else
					engine.updateWorldCamera();
			}
		}
	}
	else if (engine.State == GameState::GAME_ACTIVE) {
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
	}
	else {

		// frame buffer rendering section
		frameBuffer.startBind();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// render default scene


		// unbind the framebuffer that renders the scene
		frameBuffer.endBind();
		// gets the scene window size so it can resize the image per frame
		//ImVec2 wSize = ImGui::GetWindowSize();

		// renders the buffered texture from the frame buffer into the ImGui image scene
		ImGui::Image((void*)(intptr_t)frameBuffer.gettextureID(), ImVec2(wSize.x, wSize.y), ImVec2(0, 1), ImVec2(1, 0));
	}

	ImGui::End();
}

void ImGuiEditorWindow::assetSection()
{
	ImGui::Begin("Assets tab ");

	if (ImGui::BeginTabBar("Assets tab")) {
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.0f, 1.0f)); // yellow color
		// Add the first tab
		if (ImGui::BeginTabItem("texture tab")) {
			

			ImGui::TextWrapped("this is the asset's tab where the user can import and export assets into the level and outside the level");


			if (ImGui::Button("Load New Asset")) {
				// open a file dialog to select a PNG file
				IGFD::FileDialogConfig config;
				config.path = "./Start-Your-Engine/textures";
				ImGuiFileDialog::Instance()->OpenDialog("ChooseAssetDlgKey", "Choose Asset", ".png,.jpg", config);
			}

			// handle file selection
			if (ImGuiFileDialog::Instance()->Display("ChooseAssetDlgKey")) {
				if (ImGuiFileDialog::Instance()->IsOk()) {
					std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
					std::string fileName = ImGuiFileDialog::Instance()->GetCurrentFileName();

					// copy file to the texture folder
					std::string destination = "./Start-Your-Engine/textures/" + fileName;
					try {
						std::filesystem::copy(filePathName, destination, std::filesystem::copy_options::overwrite_existing);
						// load the copied asset into ResourceManager
						ResourceManager::LoadTexture(destination.c_str(), true, fileName);
						ImGui::Text("Loaded: %s", fileName.c_str());
					}
					catch (std::filesystem::filesystem_error& e) {
						ImGui::Text("Failed to load asset: %s", e.what());
					}
				}
				ImGuiFileDialog::Instance()->Close();
			}

			// display loaded assets
			ImGui::Text("Loaded Assets:");
			ImGui::Separator();
			ImGui::BeginChild("AssetsScrolling", ImVec2(0, 200), true, ImGuiWindowFlags_HorizontalScrollbar);

			// update and display loaded assets dynamically
			std::string texturePath = "./Start-Your-Engine/textures";
			for (const auto& entry : std::filesystem::directory_iterator(texturePath)) {
				if (entry.is_regular_file() && (entry.path().extension() == ".png" || entry.path().extension() == ".jpg")) {
					std::string fileName = entry.path().filename().string();
					std::string filePath = entry.path().string();

					ImGui::PushID(filePath.c_str());

					// check if the texture is loaded, if not, load it
					if (ResourceManager::Textures.find(fileName) == ResourceManager::Textures.end()) {
						ResourceManager::LoadTexture(filePath.c_str(), true, fileName);
					}
					auto textureID = ResourceManager::GetTexture(fileName).ID;

					// display asset thumbnail
					if (ImGui::ImageButton((void*)(intptr_t)textureID, ImVec2(80, 80))) {
						selectedAssetForPreview = fileName; // Set the asset for preview
					}

					bool remove_item = false;

					// context menu for asset removal
					if (ImGui::BeginPopupContextItem()) {
						if (ImGui::MenuItem("Remove")) {
							remove_item = true;
						}
						ImGui::EndPopup();
					}

					if (remove_item) {
						glDeleteTextures(1, &textureID); // delete OpenGL texture
						ResourceManager::Textures.erase(fileName); // remove from ResourceManager
						try {
							std::filesystem::remove(filePath); // remove from the filesystem
						}
						catch (std::filesystem::filesystem_error& e) {
							ImGui::Text("Failed to remove asset: %s", e.what());
						}
					}

					ImGui::PopID();
					ImGui::SameLine(); // display assets in the same line (horizontally)
				}
			}
			ImGui::EndChild();

			// asset preview
			if (!selectedAssetForPreview.empty()) {
				showAssetPreviewWindow();
			}



			ImGui::EndTabItem();
		}
		// Add the second tab
		if (ImGui::BeginTabItem("sound tab")) {
			ImGui::TextWrapped("this is the asset's tab where the user can import and export assets into the level and outside the level");


			if (ImGui::Button("Load New Asset")) {
				// open a file dialog to select a PNG file
				IGFD::FileDialogConfig config;
				config.path = "./Start-Your-Engine/textures";
				ImGuiFileDialog::Instance()->OpenDialog("ChooseAssetDlgKey", "Choose Asset", ".png,.jpg", config);
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


			ImGui::EndTabItem(); // End of Tab 2
		}
		ImGui::PopStyleColor();
		ImGui::EndTabBar(); // End of the tab bar
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

void ImGuiEditorWindow::objectDataSubsectionOfAttributeSection()
{
	if (ImGui::TreeNode("object data")) {

		ImGui::Separator();
		// change name
		ImGui::TextWrapped("Name:");
		ImGui::SameLine();
		static char buffer[256];
		buffer[sizeof(buffer) - 1] = '\0';
		strncpy(buffer, engine.gameObjects.find(selectedObjectKey)->second->name.c_str(), sizeof(buffer));
		if (ImGui::InputText("(INPUT TO CHANGE NAME)", buffer, sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
			// Update the std::string with the modified buffer
			engine.gameObjects.find(selectedObjectKey)->second->name = buffer;
		}
		ImGui::Separator();
		//change color
		ImGui::TextWrapped("color:");
		float rgb[3] = { engine.gameObjects.find(selectedObjectKey)->second->color.x,
			engine.gameObjects.find(selectedObjectKey)->second->color.y,
			engine.gameObjects.find(selectedObjectKey)->second->color.z };
		if (ImGui::ColorEdit3("object color", rgb)) {
			engine.gameObjects.find(selectedObjectKey)->second->color.x = rgb[0];
			engine.gameObjects.find(selectedObjectKey)->second->color.y = rgb[1];
			engine.gameObjects.find(selectedObjectKey)->second->color.z = rgb[2];
		}
		ImGui::Separator();
		//change pos
		ImGui::TextWrapped("Object location: ");
		ImGui::Indent();
		ImGui::TextWrapped("x = %f", engine.gameObjects.find(selectedObjectKey)->second->getLocation().x);
		ImGui::SameLine();
		ImGui::Button("move left");
		if (ImGui::IsItemActive()) {
			engine.gameObjects.find(selectedObjectKey)->second->body->SetTransform(
				engine.gameObjects.find(selectedObjectKey)->second->body->GetPosition()
				+ b2Vec2(-0.005, 0), 0);
		}
		ImGui::SameLine();
		ImGui::Button("move right");
		if (ImGui::IsItemActive()) {
			engine.gameObjects.find(selectedObjectKey)->second->body->SetTransform(
				engine.gameObjects.find(selectedObjectKey)->second->body->GetPosition()
				+ b2Vec2(0.005, 0), 0);
		}
		ImGui::TextWrapped("y = %f", engine.gameObjects.find(selectedObjectKey)->second->getLocation().y);
		ImGui::SameLine();
		ImGui::Button("move up");
		if (ImGui::IsItemActive()) {
			engine.gameObjects.find(selectedObjectKey)->second->body->SetTransform(
				engine.gameObjects.find(selectedObjectKey)->second->body->GetPosition()
				+ b2Vec2(0, -0.005), 0);
		}
		ImGui::SameLine();
		ImGui::Button("move down");
		if (ImGui::IsItemActive()) {
			engine.gameObjects.find(selectedObjectKey)->second->body->SetTransform(
				engine.gameObjects.find(selectedObjectKey)->second->body->GetPosition()
				+ b2Vec2(0, 0.005), 0);
		}
		ImGui::Unindent();
		//change size
		ImGui::TextWrapped("Object Size: ");
		ImGui::Indent();
		if (ImGui::InputFloat("Width", &engine.gameObjects.find(selectedObjectKey)->second->size.x, 0.1f, 1.0f, "%.2f", ImGuiInputTextFlags_EnterReturnsTrue)) {
			engine.gameObjects.find(selectedObjectKey)->second->resize();
		}
		if (ImGui::InputFloat("Height", &engine.gameObjects.find(selectedObjectKey)->second->size.y, 0.1f, 1.0f, "%.2f", ImGuiInputTextFlags_EnterReturnsTrue)) {
			engine.gameObjects.find(selectedObjectKey)->second->resize();
		}
		ImGui::Unindent();
		ImGui::Separator();
		//ImGui::TextWrapped(std::string(engine.gameObjects.find(selectedObjectKey)->second->type).c_str() );



		ImGui::TreePop();
	}
}

void ImGuiEditorWindow::physicsSubsectionOfAttributeSection()
{
	if (ImGui::TreeNode("Physics:")) {
		ImGui::TextWrapped("Object gravity: ");
		ImGui::Indent();
		ImGui::TextWrapped(" %f", engine.gameObjects.find(selectedObjectKey)->second->body->GetGravityScale());
		ImGui::SameLine();
		ImGui::Button("-");
		if (ImGui::IsItemActive()) {
			engine.gameObjects.find(selectedObjectKey)->second->body->SetGravityScale(engine.gameObjects.find(selectedObjectKey)->second->body->GetGravityScale() - 0.001);
		}
		ImGui::SameLine();
		ImGui::Button("+");
		if (ImGui::IsItemActive()) {
			engine.gameObjects.find(selectedObjectKey)->second->body->SetGravityScale(engine.gameObjects.find(selectedObjectKey)->second->body->GetGravityScale() + 0.001);
		}
		ImGui::Unindent();
		ImGui::Separator();
		ImGui::TextWrapped("Object Collision: ");
		ImGui::Indent();
		// Call the function to draw collision box controls
		collisionBoxControls(engine.gameObjects[selectedObjectKey]);
		ImGui::Unindent();
		ImGui::Separator();
		// further physics features here:
		//........
		ImGui::TextWrapped("further physics features here:");
		ImGui::Separator();
		ImGui::TreePop();
	}
}

void ImGuiEditorWindow::animationSubsectionOfAttributeSection()
{

	if (ImGui::TreeNode("current animation:")) {
		ImGui::Separator();
		if (engine.gameObjects[selectedObjectKey]->animations.empty()) {
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 0.0f, 1.0f)); // Green color
			ImGui::TextWrapped("it has no animations in the list. Please add an animation to choose.");
			ImGui::PopStyleColor();

		}
		else {
			ImGui::TextWrapped("current animation Total Frames :");
			static int frames = engine.gameObjects[selectedObjectKey]->animations[engine.gameObjects[selectedObjectKey]->getCurrentAnimation()]->getTotalFrames();
			ImGui::InputInt("total Frames ", &frames);
			//if the user inputs negative number then it reset to its default value
			if (frames < 1) {
				frames = 1;
			}
			engine.gameObjects[selectedObjectKey]->animations[engine.gameObjects[selectedObjectKey]->getCurrentAnimation()]->setTotalFrames(frames);

			ImGui::Separator();
			ImGui::TextWrapped("current animation preview:");
			ImGui::Indent();
			Texture2D& texture = engine.gameObjects.find(selectedObjectKey)->second->getCurrentTexture2D();
			ImGui::Image((void*)(intptr_t)texture.ID, ImVec2(80, 80));
			ImGui::Unindent();
			ImGui::Separator();
		}
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("change current animation:")) {
		ImGui::Separator();
		selectCurrentAnimation();
		ImGui::Separator();
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Add animation:")) {
		ImGui::Separator();
		addNewAnimation();
		ImGui::Separator();
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("delete animation:")) {
		ImGui::Separator();
		deleteExistingAnimation();
		ImGui::Separator();
		ImGui::TreePop();
	}
}

void ImGuiEditorWindow::addNewAnimation()
{
	// set the default frames of value 1
	static int frames = 1;
	ImGui::TextWrapped("input total frames [ as 1 or more]: ");
	ImGui::InputInt("total Frames ", &frames);
	ImGui::Separator();
	//if the user inputs negative number then it reset to its default value
	if (frames < 1) {
		frames = 1;
	}
	ImGui::TextWrapped("list of assets: ");
	if (ImGui::BeginCombo("select", nullptr)) {
		for (auto it = ResourceManager::Textures.begin(); it != ResourceManager::Textures.end();) {
			ImGui::PushID(it->second.ID); // use the texture ID to push the ID

			// display asset thumbnail
			if (ImGui::ImageButton((void*)(intptr_t)it->second.ID, ImVec2(80, 80))) {

				engine.gameObjects[selectedObjectKey]->addAnimation(it->first, frames);
				ImGui::PopID();
				break;
			}
			else {
				it++; // only increment the iterator if no item was removed
			}
			ImGui::PopID();
		}
		ImGui::EndCombo();

	}
}

void ImGuiEditorWindow::deleteExistingAnimation()
{
	ImGui::TextWrapped(" animations list : ");
	if (engine.gameObjects[selectedObjectKey]->animations.empty()) {
		/* this disables the dropdown and displays an information
				to the user that there is no animation to delete 
		*/
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 0.0f, 1.0f)); // Green color
		ImGui::TextWrapped("it has no animations in the list. Please add an animation to choose.");
		ImGui::PopStyleColor();
	}
	else
		// this bring out the drop down menu
		if (ImGui::BeginCombo("select",
			engine.gameObjects[selectedObjectKey]->getCurrentAnimation().c_str())) {
			for (auto& it = engine.gameObjects[selectedObjectKey]->animations.begin(); it != engine.gameObjects[selectedObjectKey]->animations.end();) {
				ImGui::PushID(it->second->getSpriteSheetName().c_str()); // use the texture ID to push the ID

				// display asset thumbnail
				if (ImGui::ImageButton((void*)(intptr_t)it->second->getSpriteSheet().ID, ImVec2(80, 80))) {
					//deletes the animation and gets out of the loop
					engine.gameObjects[selectedObjectKey]->deleteAnimation(it->first);
					ImGui::PopID();
					break;

				}
				else {
					it++; // only increment the iterator if no item was removed
				}
				ImGui::PopID();
			}
			ImGui::EndCombo();

		}
}

void ImGuiEditorWindow::selectCurrentAnimation()
{
	ImGui::TextWrapped(" animations list : ");
	if (engine.gameObjects[selectedObjectKey]->animations.empty()) {
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 0.0f, 1.0f)); // Green color
		ImGui::TextWrapped("it has no animations in the list. Please add an animation to choose.");
		ImGui::PopStyleColor();

	}
	else
		if (ImGui::BeginCombo("selectCurrent Animation",
			engine.gameObjects[selectedObjectKey]->getCurrentAnimation().c_str()))
		{
			// this is to tell the user to add animation to choose one

			for (auto& it = engine.gameObjects[selectedObjectKey]->animations.begin(); it != engine.gameObjects[selectedObjectKey]->animations.end();) {
				ImGui::PushID(it->second->getSpriteSheetName().c_str()); // use the texture ID to push the ID

				// display asset thumbnail
				if (ImGui::ImageButton((void*)(intptr_t)it->second->getSpriteSheet().ID, ImVec2(80, 80))) {

					engine.gameObjects[selectedObjectKey]->setAsCurrentAnimation(it->first);
				}
				else {
					it++; // only increment the iterator if no item was removed
				}
				ImGui::PopID();
			}
			ImGui::EndCombo();

		}


}
