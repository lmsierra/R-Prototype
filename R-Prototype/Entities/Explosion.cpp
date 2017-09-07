#include "stdafx.h"
#include "sys.h"
#include "Explosion.h"
#include "EntityManager.h"
#include "Sprite.h"

Explosion::Explosion()
{
    m_index       = 0;
    m_currentTime = 0;
    
    m_explosionImages.push_back("explosion-I.png");
    m_explosionImages.push_back("explosion-II.png");
    m_explosionImages.push_back("explosion-III.png");
    m_explosionImages.push_back("explosion-IV.png");
    m_explosionImages.push_back("explosion-V.png");
    m_explosionImages.push_back("explosion-VI.png");
    m_explosionImages.push_back("explosion-VII.png");
    m_explosionImages.push_back("explosion-VIII.png");
    m_explosionImages.push_back("explosion-IX.png");
    m_explosionImages.push_back("explosion-X.png");
}


Explosion::~Explosion()
{
    m_explosionImages.clear();
}


void Explosion::Init(vec2 pos, vec2 size)
{
    Entity::Init(pos, size, vmake(-3.0f, 0), m_explosionImages[0]);
    m_currentTime = 0;
}


void Explosion::Run()
{
    m_currentTime += 1.f / SCR_FPS;

    if(m_currentTime > EXPLOSION_TIME / (m_explosionImages.size() - m_index + 1.f))
    {
        m_index++;
        if(m_index >= m_explosionImages.size())
            EntityManager::DeleteExplosion(this);
        else
            GetSprite()->SetTextureName(m_explosionImages[m_index]);
    }
}
