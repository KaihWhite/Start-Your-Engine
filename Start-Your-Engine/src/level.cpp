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
        
        objValue.AddMember("type", obj.type, allocator);

        //TODO: add the rest of the properties to objValue and check that it works
        for (const auto& anim : obj.animations) {
            rapidjson::Value animValue(rapidjson::kObjectType);

			animValue.AddMember("spriteSheet", anim.getSpriteSheetName(), allocator);
			animValue.AddMember("totalFrames", anim.getTotalFrames(), allocator);

            objValue.AddMember("animations", animValue, allocator);
		}


        // Example: objValue.AddMember("id", obj.getId(), allocator);
        // Repeat for other properties...

        // each objValue is a JSON object representing a GameObject

        objects.PushBack(objValue, allocator);
    }

    doc.AddMember("gameObjects", objects, allocator);

    // Write to file
    FILE* fp = fopen(filename.c_str(), "wb");
    char writeBuffer[65536];
    rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
    rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);
    doc.Accept(writer);
    fclose(fp);
}


std::vector<GameObject*> loadFromJSON(const std::string& filename) {
    std::vector<GameObject*> gameObjects;

    FILE* fp = fopen(filename.c_str(), "rb");
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document doc;
    doc.ParseStream(is);
    fclose(fp);

    if (doc.HasMember("gameObjects") && doc["gameObjects"].IsArray()) {
        for (const auto& objValue : doc["gameObjects"].GetArray()) {
            // Create a new GameObject based on the JSON object data
            // parse each property of objValue and pass them to the GameObject constructor
            // Example: int id = objValue["id"].GetInt();
            // Repeat for other properties...

            // TODO: pass the extracted properties to the GameObject constructor
            GameObject* gameObject = new GameObject(/* parameters extracted from objValue */);
            gameObjects.push_back(gameObject);
        }
    }

    return gameObjects;
}

