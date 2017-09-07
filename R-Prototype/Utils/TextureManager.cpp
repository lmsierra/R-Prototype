#include "stdafx.h"
#include "TextureManager.h"

#define IMAGE_PATH "Data/"

TextureManager* TextureManager::m_instance;


TextureManager::TextureManager()
{

}


TextureManager::~TextureManager()
{
    ReleaseTextures();
    m_textureMap.clear();
}


TextureManager& TextureManager::Instance()
{
    if(!m_instance) m_instance = new TextureManager();
    
    return *m_instance;
}


GLuint TextureManager::GetTextureFromFile(const char* filename)
{
    GLuint texture = LoadTexture(filename);
    return texture;
}


GLuint TextureManager::LoadTexture(const char* filename)
{
    auto iterator = m_textureMap.find(filename);
    
    if(iterator == m_textureMap.end())
    {
        int length = sizeof(IMAGE_PATH) / sizeof(char) + sizeof(filename) / sizeof(*filename);
        
        char* pathBuf = (char*) malloc(length + 1);
        strcpy(pathBuf, IMAGE_PATH);
        strcat(pathBuf, filename);
        
        GLuint texture = CORE_LoadPNG(pathBuf, false);
        
        m_textureMap.insert(std::make_pair(filename, texture));
        
        free(pathBuf);
        
        return texture;
    }
    else
        return iterator->second;
    
}


void TextureManager::ReleaseTexture(const char* filename)
{
    RemoveTexture(filename);
}


GLuint TextureManager::RemoveTexture(const char* filename)
{
    auto iterator = m_textureMap.find(filename);
    
    if(iterator == m_textureMap.end())
        return 0;
    else
    {
        GLuint texture = iterator->second;
        UnloadTexture(texture);
        m_textureMap.erase(filename);
        return texture;
    }
}


void TextureManager::UnloadTexture(GLuint texture)
{
    CORE_UnloadPNG(texture);
}


void TextureManager::ReleaseTextures()
{
    for(auto& pair : m_textureMap)
    {
        UnloadTexture(pair.second);
    }
}
