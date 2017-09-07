#include "stdafx.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Sprite.h"

Entity::Entity()
{
    m_pos    = {};
    m_size   = {};
    m_vel    = {};
    m_sprite = nullptr;
}


Entity::~Entity()
{
    m_pos  = {};
    m_size = {};
    m_vel  = {};
    if(m_sprite)
    {
        EntityManager::DeleteSprite(m_sprite);
        m_sprite = nullptr;
    }
}


void Entity::Init(vec2 pos, vec2 size, vec2 vel, const char* spriteName)
{
    m_pos    = pos;
    m_size   = size;
    m_vel    = vel;
    m_sprite = EntityManager::CreateSprite(pos, vel, spriteName);
}


vec2 Entity::GetPos() const
{
    return m_pos;
}


vec2 Entity::GetSize() const
{
    return m_size;
}


vec2 Entity::GetVel() const
{
    return m_vel;
}


Sprite* Entity::GetSprite() const
{
    return m_sprite;
}


void Entity::Run()
{
    m_pos = vadd(m_pos, m_vel);
    UpdateSprite();
}


void Entity::UpdateSprite()
{
    if(!m_sprite) return;
    
    m_sprite->SetPos(m_pos);
    m_sprite->SetSize(m_size);
}


void Entity::SetPos(vec2 pos)
{
    m_pos = pos;
}


void Entity::SetSize(vec2 size)
{
    m_size = size;
}


void Entity::SetVel(vec2 vel)
{
    m_vel = vel;
}
