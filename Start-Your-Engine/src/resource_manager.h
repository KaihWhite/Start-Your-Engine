/*
Credit to the author of LearnOpenGL.com Joey de Vries for boilerplate code
*/
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <unordered_map>
#include <string>

#include "glad/glad.h"

#include "texture.h"
#include "shader.h"

#include "soloud.h"
#include "soloud_wav.h"

// A static singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and resources are static and no 
// public constructor is defined.
class ResourceManager
{
public:
    // resource storage
    static std::unordered_map<std::string, Shader>    Shaders;
    static std::unordered_map<std::string, Texture2D> Textures;
    static std::unordered_map<std::string, SoLoud::Wav> Sounds;
    // loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
    static Shader    LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
    // retrieves a stored sader
    static Shader&    GetShader(std::string name);
    // loads (and generates) a texture from file
    static Texture2D LoadTexture(const char* file, bool alpha, std::string name);
    // retrieves a stored texture
    static Texture2D& GetTexture(std::string name);
    // loads a sound
    static void         LoadSound(const char* file, std::string name);
    // retrieves a stored sound
    static SoLoud::Wav& GetSound(std::string name);
    // properly de-allocates all loaded resources
    static void      Clear();
private:
    // private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
    ResourceManager() { };
    // loads and generates a shader from file
    static Shader    loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
    // loads a single texture from file
    static Texture2D loadTextureFromFile(const char* file, bool alpha);
};

#endif
