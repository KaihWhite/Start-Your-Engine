// Made by Kaih White
#include "level.h"

void Level::saveToJSON(const std::string& filename, std::vector<GameObject*> gameObjects) {
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    rapidjson::Value objects(rapidjson::kArrayType);

    for (const auto& obj : gameObjects) {
        rapidjson::Value objValue(rapidjson::kObjectType);
        // Serialize GameObject data into objValue
        
        if (obj->type == ObjectType::PLAYER) {
			objValue.AddMember("type", "Player", allocator);
		}
        else if (obj->type == ObjectType::OBJECT) {
			objValue.AddMember("type", "Object", allocator);
		}
        else {
			objValue.AddMember("type", "NPC", allocator);
		}

        if (obj->rigidBodyType == RigidBodyType::DYNAMIC) {
            objValue.AddMember("rigidBodyType", "Dynamic", allocator);
		}
        else {
            objValue.AddMember("rigidBodyType", "Static", allocator);
		}

        rapidjson::Value animations(rapidjson::kObjectType);
        for (const auto& anim : obj->animations) {

            //std::string name = anim.second->getSpriteSheetName();
            rapidjson::Value key;
            key.SetString(anim.second->getSpriteSheetName().c_str(), allocator);

            // Convert the value (total frames) to a RapidJSON Value
            rapidjson::Value value;
            value.SetInt(anim.second->getTotalFrames());

            animations.AddMember(key, value, allocator);
		}
        objValue.AddMember("animations", animations, allocator);

        rapidjson::Value colorValue(rapidjson::kObjectType);
        colorValue.AddMember("x", obj->color.x, allocator);
        colorValue.AddMember("y", obj->color.y, allocator);
        colorValue.AddMember("z", obj->color.z, allocator);
        objValue.AddMember("color", colorValue, allocator);

        rapidjson::Value sizeValue(rapidjson::kObjectType);
        sizeValue.AddMember("x", obj->size.x, allocator);
        sizeValue.AddMember("y", obj->size.y, allocator);
        objValue.AddMember("size", sizeValue, allocator);

        rapidjson::Value positionValue(rapidjson::kObjectType);
        positionValue.AddMember("x", obj->getPosition().x, allocator);
        positionValue.AddMember("y", obj->getPosition().y, allocator);
        objValue.AddMember("position", positionValue, allocator);

        // each objValue is a JSON object representing a GameObject

        objects.PushBack(objValue, allocator);
    }

    doc.AddMember("gameObjects", objects, allocator);

    std::string path = "Start-Your-Editor/Levels/" + filename;

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


std::vector<GameObject*> Level::loadFromJSON(const std::string& filename, b2World* world, Camera2DSystem* cameraMan) {
    std::vector<GameObject*> gameObjects;

    std::string path = "Start-Your-Editor/Levels/" + filename;

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
                //const std::string spriteSheetName = name + ".png";
                const int totalFrames = anim.value.GetInt();
                const char* nameChar = name.c_str();
                animations[name] = new Animation(name, totalFrames);
            }

            std::string dynamCheck = "Dynamic";
            bool dynam = objValue["rigidBodyType"].GetString() == dynamCheck;

            std::string type = objValue["type"].GetString();

            if (type == "Player") {
                Player* player = new Player(position, size, color, animations, world, cameraMan, type, dynam);
                gameObjects.push_back(player);
            } else {
                GameObject* gameObject = new GameObject(position, size, color, animations, world, type, dynam);
                gameObjects.push_back(gameObject);
            }
        }
    }

    return gameObjects;
}

