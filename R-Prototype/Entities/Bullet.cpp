#include "stdafx.h"
#include "Bullet.h"
#include "BulletConstants.h"

Bullet::Bullet() : Entity()
{
    m_damage      = 0;
    m_playerOwner = false;
}

Bullet::~Bullet()
{
    
}


void Bullet::Init(int damage, bool isPlayerOwner, vec2 pos)
{
    vec2 vel = (isPlayerOwner)? BULLET_VEL_R : BULLET_VEL_L;
    const char* img = (isPlayerOwner)? BULLET_IMG_PLAYER : BULLET_IMG_ENEMY;
    Entity::Init(pos, BULLET_SIZE, vel, img);
    
    m_damage      = damage;
    m_playerOwner = isPlayerOwner;
}


void Bullet::Run()
{
    Entity::Run();
}


int Bullet::GetDamage() const
{
    return m_damage;
}


bool Bullet::IsPlayerOwner() const
{
    return m_playerOwner;
}
