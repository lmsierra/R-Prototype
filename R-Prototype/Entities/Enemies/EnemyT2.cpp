#include "stdafx.h"
#include "sys.h"
#include "EnemyT2.h"
#include "EntityManager.h"

EnemyT2::EnemyT2()
{
    
}


void EnemyT2::Run()
{
    m_vel = vmake(m_vel.x, 0);
    Enemy::Run();
}


void EnemyT2::RunBehaviour()
{
    m_currentDelay -= 1.f/SCR_FPS;

    if(m_pos.x < SCR_WIDTH && m_pos.x > 0)
    {
        if(m_currentDelay <= 0)
        {
            EntityManager::CreateBullet(m_damage, false, m_pos);
            float offset = (rand() % 2 == 0)? rand() % 30 : -(rand() % 30);
            m_currentDelay = m_shootDelay + offset;
        }
    }
}


void EnemyT2::Init(int health, int damage, uint shootDelay, int score, vec2 pos, vec2 size, vec2 vel, const char* image)
{
    Enemy::Init(health, damage, shootDelay, score, pos, size, vel, image);
}
