// Made by Kaih White
#include "level.h"

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void Level::saveToJSON(const std::string& filename, std::unordered_map<int, GameObject*> gameObjects) {
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    rapidjson::Value objects(rapidjson::kArrayType);

    for (const auto& obj : gameObjects) {
        rapidjson::Value objValue(rapidjson::kObjectType);
        // Serialize GameObject data into objValue

        rapidjson::Value name;
        // I could also use obj.first here
        name.SetString(obj.second->name.c_str(), allocator);
        objValue.AddMember("name", name, allocator);
        
        if (obj.second->type == ObjectType::PLAYER) {
			objValue.AddMember("type", "Player", allocator);
		}
        else if (obj.second->type == ObjectType::OBJECT) {
			objValue.AddMember("type", "Object", allocator);
		}
        else {
			objValue.AddMember("type", "NPC", allocator);
		}

        if (obj.second->rigidBodyType == RigidBodyType::DYNAMIC) {
            objValue.AddMember("rigidBodyType", "Dynamic", allocator);
		}
        else {
            objValue.AddMember("rigidBodyType", "Static", allocator);
		}

        rapidjson::Value animations(rapidjson::kObjectType);
        for (const auto& anim : obj.second->animations) {

            //std::string name = anim.second->getSpriteSheetName();
            rapidjson::Value key;
            std::string combinedName = anim.second->getSpriteSheetName() + "," + anim.first;
            key.SetString(combinedName.c_str(), allocator);

            // Convert the value (total frames) to a RapidJSON Value
            rapidjson::Value value;
            value.SetInt(anim.second->getTotalFrames());

            animations.AddMember(key, value, allocator);
		}
        objValue.AddMember("animations", animations, allocator);

        rapidjson::Value colorValue(rapidjson::kObjectType);
        colorValue.AddMember("x", obj.second->color.x, allocator);
        colorValue.AddMember("y", obj.second->color.y, allocator);
        colorValue.AddMember("z", obj.second->color.z, allocator);
        objValue.AddMember("color", colorValue, allocator);

        rapidjson::Value sizeValue(rapidjson::kObjectType);
        sizeValue.AddMember("x", obj.second->size.x, allocator);
        sizeValue.AddMember("y", obj.second->size.y, allocator);
        objValue.AddMember("size", sizeValue, allocator);

        rapidjson::Value positionValue(rapidjson::kObjectType);
        positionValue.AddMember("x", obj.second->getLocation().x, allocator);
        positionValue.AddMember("y", obj.second->getLocation().y, allocator);
        objValue.AddMember("position", positionValue, allocator);

        // Serialize collision box properties
        objValue.AddMember("hasCustomCollisionBox", obj.second->hasCustomCollisionBox, allocator);
        objValue.AddMember("collisionBoxShape", obj.second->collisionBoxShape, allocator);
        objValue.AddMember("collisionBoxWidth", obj.second->collisionBoxWidth, allocator);
        objValue.AddMember("collisionBoxHeight", obj.second->collisionBoxHeight, allocator);

        // each objValue is a JSON object representing a GameObject

        objects.PushBack(objValue, allocator);
    }

    doc.AddMember("gameObjects", objects, allocator);

    std::string path = filename;

    // Write to file
    FILE* fp = fopen(path.c_str(), "w");
    if (fp == nullptr) {
		std::cout << "File failed to open for writing: " << filename << std::endl;
		return;
	}
    char writeBuffer[65536];
    rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
    rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);
    doc.Accept(writer);
    fclose(fp);
}


std::unordered_map<int, GameObject*> Level::loadFromJSON(const std::string& filename, b2World* world, Camera2DSystem* cameraMan) {
    std::unordered_map<int, GameObject*> gameObjects;

    std::string path = filename;

    FILE* fp = fopen(path.c_str(), "rb");
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document doc;
    doc.ParseStream(is);
    fclose(fp);

    if (doc.HasMember("gameObjects") && doc["gameObjects"].IsArray()) {
        for (const auto& objValue : doc["gameObjects"].GetArray()) {
            // Create a new GameObject based on the JSON object data
            // parse each property of objValue and pass them to the GameObject constructor

            glm::vec2 position = glm::vec2(objValue["position"]["x"].GetFloat(), objValue["position"]["y"].GetFloat());
            glm::vec2 size = glm::vec2(objValue["size"]["x"].GetFloat(), objValue["size"]["y"].GetFloat());
            glm::vec3 color = glm::vec3(objValue["color"]["x"].GetFloat(), objValue["color"]["y"].GetFloat(), objValue["color"]["z"].GetFloat());

            std::unordered_map<std::string, Animation*> animations;
            for (const auto& anim : objValue["animations"].GetObject()) {

                const std::string name = anim.name.GetString();
                std::vector<std::string> splitName = split(name, ',');

                const int totalFrames = anim.value.GetInt();

                animations[splitName[1]] = new Animation(splitName[0], totalFrames);
            }

            std::string dynamCheck = "Dynamic";
            bool dynam = objValue["rigidBodyType"].GetString() == dynamCheck;

            std::string type = objValue["type"].GetString();

            std::string name = objValue["name"].GetString();

            // Set up random number generation
            std::random_device rd;

            std::mt19937 gen(rd());

            std::uniform_int_distribution<> distr(1, 100);

            // generate unique key
            int unique_key = distr(gen);

            while (gameObjects.find(unique_key) != gameObjects.end()) {
                unique_key = distr(gen);
			}

            if (type == "Player") {
                Player* player = new Player(position, size, color, animations, world, cameraMan, type, dynam);
                gameObjects[unique_key] = player;
            } else {
                GameObject* gameObject = new GameObject(name, position, size, color, animations, world, type, dynam);
                // Deserialize custom collision box properties
                if (objValue.HasMember("hasCustomCollisionBox")) {
                    gameObject->hasCustomCollisionBox = objValue["hasCustomCollisionBox"].GetBool();
                }
                if (objValue.HasMember("collisionBoxShape")) {
                    gameObject->collisionBoxShape = objValue["collisionBoxShape"].GetInt();
                }
                if (objValue.HasMember("collisionBoxWidth")) {
                    gameObject->collisionBoxWidth = objValue["collisionBoxWidth"].GetFloat();
                }
                if (objValue.HasMember("collisionBoxHeight")) {
                    gameObject->collisionBoxHeight = objValue["collisionBoxHeight"].GetFloat();
                }
                // Apply the custom collision box if it exists
                gameObject->applyCollisionBox();
                gameObjects[unique_key] = gameObject;
            }
            
        }
    }

    return gameObjects;
}
