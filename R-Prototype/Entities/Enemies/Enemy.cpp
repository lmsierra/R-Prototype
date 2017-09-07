#include "stdafx.h"
#include "Enemy.h"
#include "EnemyConstants.h"
#include "EntityManager.h"

Enemy::Enemy() : Entity()
{
    m_health               = 0;
    m_damage               = 0;
    m_shootDelay           = 0;
    m_score                = 0;
    m_currentDelay         = 0;
}


Enemy::~Enemy()
{
    
}


void Enemy::Init(int health, int damage, uint shootDelay, int score, vec2 pos, vec2 size, vec2 vel, const char* image)
{
    Entity::Init(pos, size, vel, image);
    m_health               = health;
    m_damage               = damage;
    m_score                = score;
    m_shootDelay           = shootDelay;
    m_currentDelay         = 0;
}

void Enemy::TakeDamage(int damage)
{
    m_health-= damage;
}


void Enemy::Die()
{
    //EntityManager::CreateExplosion(GetPos(), GetSize());
    EntityManager::DeleteEnemy(this);
}


bool Enemy::IsDead()
{
    return m_health <= 0;
}


void Enemy::Run()
{
    Entity::Run();
    RunBehaviour();
}


int Enemy::GetHealth()
{
    return m_health;
}

int Enemy::GetDamage()
{
    return m_damage;
}


int Enemy::GetShootDelay()
{
    return m_shootDelay;
}


int Enemy::GetScore()
{
    return m_score;
}


void Enemy::SetHealth(int health)
{
    m_health = health;
}


void Enemy::SetDamage(int damage)
{
    m_damage = damage;
}


void Enemy::SetShootDelay(uint delay)
{
    m_shootDelay = delay;
}


void Enemy::SetScore(int score)
{
    m_score = score;
}
