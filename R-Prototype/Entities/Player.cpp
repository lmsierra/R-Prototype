#include "stdafx.h"
#include "sys.h"
#include "Player.h"
#include "PlayerConstants.h"
#include "EntityManager.h"

Player::Player() : Entity()
{
    m_health     = 0;
    m_shootDelay = 0;
    m_score      = 0;
}


Player::~Player()
{
    
}


void Player::Init(int health, vec2 pos, vec2 size, vec2 vel, const char* imageName)
{
    Entity::Init(pos, size, vel, imageName);
    m_health     = health;
    m_shootDelay = 0;
}


void Player::Run()
{
    Entity::Run();
    
    m_shootDelay -= (1.f/SCR_FPS);
    
    if(m_shootDelay < 0)
    {
        m_shootDelay = 0;
    }
}


int Player::GetHealth()
{
    return m_health;
}


void Player::MoveXAxis(Direction direction)
{
    if((direction == FORWARD  && m_pos.x >= MOVE_LIMIT_RIGHT) ||
       (direction == BACKWARD && m_pos.x <= MOVE_LIMIT_LEFT))
        m_vel.x = 0;
    else
        m_vel.x = PLAYER_SPEED * direction;
}


void Player::MoveYAxis(Direction direction)
{
    if((direction == FORWARD  && m_pos.y >= MOVE_LIMIT_TOP) ||
       (direction == BACKWARD && m_pos.y <= MOVE_LIMIT_BOTTOM))
        m_vel.y = 0;
    else
        m_vel.y = PLAYER_SPEED * direction;
}


void Player::Shoot()
{
    if(m_shootDelay == 0)
    {
        EntityManager::CreateBullet(PLAYER_SHOOT_DMG, true, vadd(GetPos(), vmake(GetSize().x / 2, 0)));
        m_shootDelay = PLAYER_SHOOT_DELAY;
    }
}


void Player::TakeDamage(int damage)
{
    m_health -= damage;
}


void Player::Die()
{
    //EntityManager::CreateExplosion(GetPos(), GetSize());
    //EntityManager::DeletePlayer(this);
    EntityManager::DeleteSprite(GetSprite());
}


void Player::AddScore(int score)
{
    m_score += score;
}


long int Player::GetScore()
{
    return m_score;
}


bool Player::IsAlive()
{
    return m_health > 0;
}


void Player::AddHealth(int health)
{
    m_health += health;
    if(m_health > PLAYER_MAX_HEALTH)
        m_health = PLAYER_MAX_HEALTH;
}
