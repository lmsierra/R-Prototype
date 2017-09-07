#include "stdafx.h"
#include "Sprite.h"
#include "TextureManager.h"

Sprite::Sprite()
{
    m_pos         = {};
    m_size        = {};
    m_textureName = "";
    m_texture     = 0;
}


Sprite::~Sprite()
{
    
}


void Sprite::Init(vec2 pos, vec2 size, const char* textureName)
{
    m_pos         = pos;
    m_size        = size;
    m_textureName = textureName;
    m_texture     = TextureManager::Instance().GetTextureFromFile(textureName);
}


void Sprite::Deinit()
{
    TextureManager::Instance().ReleaseTexture(m_textureName);
    m_pos         = {};
    m_size        = {};
    m_textureName = "";
    m_texture     = 0;
}


vec2 Sprite::GetPos()
{
    return m_pos;
}


vec2 Sprite::GetSize()
{
    return m_size;
}


const char* Sprite::GetTextureName()
{
    return m_textureName;
}


GLuint Sprite::GetTexture()
{
    return m_texture;
}


void Sprite::SetPos(vec2 pos)
{
    m_pos = pos;
}


void Sprite::SetSize(vec2 size)
{
    m_size = size;
}

void Sprite::SetTextureName(const char* texture)
{
    m_textureName = texture;
    m_texture     = TextureManager::Instance().GetTextureFromFile(texture);
}

