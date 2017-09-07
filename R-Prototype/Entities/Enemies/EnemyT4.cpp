#include "stdafx.h"
#include "EnemyT4.h"
#include "Enemy.h"
#include "EntityManager.h"

EnemyT4::EnemyT4()
{
    m_healthDropped = 0;
}

void EnemyT4::Init(int health, int damage, uint shootDelay, int score, vec2 pos, vec2 size, vec2 vel, const char* image)
{
    Enemy::Init(health, damage, shootDelay, score, pos, size, vel, image);

    m_healthDropped = 50;
}


void EnemyT4::Run()
{
    Entity::Run();
}


void EnemyT4::Die()
{
    EntityManager::CreateHealthItem(m_healthDropped, m_pos);
    EntityManager::DeleteEnemy(this);
}


void EnemyT4::RunBehaviour()
{
    
}

