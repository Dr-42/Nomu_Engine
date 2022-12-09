#include "utils/resource_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

// Instantiate static variables
std::map<std::string, Nomu::Texture2D>    Nomu::ResourceManager::Textures;
std::map<std::string, Nomu::Shader>       Nomu::ResourceManager::Shaders;
std::map<std::string, std::string>        Nomu::ResourceManager::Fonts;


Nomu::Shader Nomu::ResourceManager::LoadShader(std::string vShaderFile, std::string fShaderFile, std::string gShaderFile, std::string name)
{
    if(gShaderFile != "")
        Shaders[name] = loadShaderFromFile(vShaderFile.c_str(), fShaderFile.c_str(), gShaderFile.c_str());
    else
        Shaders[name] = loadShaderFromFile(vShaderFile.c_str(), fShaderFile.c_str(), nullptr);

    return Shaders[name];
}

Nomu::Shader* Nomu::ResourceManager::GetShader(std::string name)
{
    return &Shaders[name];
}

Nomu::Texture2D Nomu::ResourceManager::LoadTexture(std::string file, bl alpha, std::string name)
{
    Textures[name] = loadTextureFromFile(file.c_str(), alpha);
    return Textures[name];
}

Nomu::Texture2D* Nomu::ResourceManager::GetTexture(std::string name)
{
    return &Textures[name];
}

void Nomu::ResourceManager::LoadFont(std::string name, std::string path)
{
    Fonts[name] = path;
}

std::string Nomu::ResourceManager::GetFont(std::string name)
{
    return Fonts[name];
}

void Nomu::ResourceManager::Clear()
{
    // (properly) delete all shaders	
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
    // (properly) delete all textures
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID);
}

Nomu::Shader Nomu::ResourceManager::loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // if geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception const& e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    const char *gShaderCode = geometryCode.c_str();
    // 2. now create shader object from source code
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

Nomu::Texture2D Nomu::ResourceManager::loadTextureFromFile(const char *file, bl alpha)
{
    // create texture object
    Texture2D texture;
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    // load image
    i32 width, height, nrChannels;
    u8* data = stbi_load(file, &width, &height, &nrChannels, 0);
    // now generate texture
    texture.Generate(width, height, data);
    // and finally free image data
    stbi_image_free(data);
    return texture;
}
