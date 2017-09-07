 #include "stdafx.h"
#include "sys.h"
#include "GameModeManager.h"
#include "EntityManager.h"
#include "CollisionManager.h"
#include "Game.h"
#include "World.h"
#include "Renderer.h"
#include "Loader.h"
#include "Player.h"
#include "Bullet.h"
#include "Explosion.h"
#include "Background.h"
#include "HealthItem.h"
#include "Asteroid.h"
#include "PlayerConstants.h"

World::World()
{
    m_level = 0;
    m_player  = nullptr;
}


World::~World()
{
    EntityManager::DeletePlayer(m_player);
    ClearEnemies();
    ClearBullets();
    ClearExplosions();
    ClearHealthItems();
    ClearBackgrounds();
    ClearAsteroids();
    
    m_player = nullptr;
}


void World::Init(uint level)
{
    m_level = level;
    LoadLevel(level);
    EntityManager::CreatePlayer(PLAYER_MAX_HEALTH,
                                vmake(PLAYER_INITIAL_POS_X, PLAYER_INITIAL_POS_Y),
                                vmake(PLAYER_WIDTH, PLAYER_HEIGHT),
                                vmake(0,0));
}


void World::Run()
{
    
    std::vector<Enemy*>       deletedEnemies;
    std::vector<Bullet*>      deletedBullets;
    std::vector<HealthItem*>  deletedItems;
    std::vector<Asteroid*>    deletedAsteroids;
    
    for(Background* back : m_backgrounds)
    {
        if(back->GetPos().x < LEFT_LIMIT - back->GetSize().x / 2)
        {
            back->SetPos(vadd(back->GetPos(), vmake(2*back->GetSize().x , 0)));
        }
        
        back->Run();
    }
    
    if(m_player)
        m_player->Run();
    
    for(HealthItem* item : m_healthItems)
    {
        if(CollisionManager::CheckCollision(item, m_player))
        {
            m_player->AddHealth(item->GetHealth());
            deletedItems.push_back(item);
        }
        else
        {
            item->Run();
        }
    }
    
    while(deletedItems.size() != 0)
    {
        EntityManager::DeleteHealthItem(deletedItems[0]);
        deletedItems.erase(deletedItems.begin());
    }
    
    for(Explosion* explosion : m_explosions)
        explosion->Run();
    
    for(Enemy* enemy : m_enemies)
    {
        if(!enemy)
            break;
        
        bool collide = false;
        if(enemy->GetPos().x < LEFT_LIMIT)
            collide = true;
        else
        {
            if(CollisionManager::CheckCollision(enemy, m_player))
            {
                collide = true;
                m_player->AddScore(enemy->GetScore());
                 
                // Take damage 999 -> In a future maybe an invulnerability
                // powerup is implemented
                m_player->TakeDamage(999);
            }
            else
            {
                if(!enemy)
                    break;
                enemy->Run();
            }
        }
        
        if(collide)
            deletedEnemies.push_back(enemy);
    }
    
    while(deletedEnemies.size() != 0)
    {
        EntityManager::DeleteEnemy(m_enemies[0]);
        deletedEnemies.erase(deletedEnemies.begin());
    }
    
    
    for(Bullet* bullet : m_bullets)
    {
        vec2 pos = bullet->GetPos();
        if(pos.x < LEFT_LIMIT || pos.x > RIGHT_LIMIT)
            EntityManager::DeleteBullet(bullet);
        else
        {
            bool collide = false;
            if(bullet->IsPlayerOwner())
            {
                for(Enemy* enemy: m_enemies)
                {
                    if(CollisionManager::CheckCollision(bullet, enemy))
                    {
                        enemy->TakeDamage(bullet->GetDamage());
                        collide = true;
                        
                        if(enemy->IsDead())
                        {
                            m_player->AddScore(enemy->GetScore());
                            //enemy->Die();
                            deletedEnemies.push_back(enemy);
                        }
                    }
                }
            }
            else
            {
                if(CollisionManager::CheckCollision(bullet, m_player))
                {
                    m_player->TakeDamage(bullet->GetDamage());
                    collide = true;
                }
            }
            
            for(Asteroid* asteroid : m_asteroids)
            {
                if(CollisionManager::CheckCollision(bullet, asteroid))
                    collide = true;
            }
            
            if(collide)
                deletedBullets.push_back(bullet);
            else
            {
                bullet->Run();
            }
        }
    }
    
    while(deletedBullets.size() != 0)
    {
        EntityManager::DeleteBullet(deletedBullets[0]);
        deletedBullets.erase(deletedBullets.begin());
    }
    
    while(deletedEnemies.size() != 0)
    {
        deletedEnemies[0]->Die();
        deletedEnemies.erase(deletedEnemies.begin());
    }
    
    
    for(Asteroid* asteroid : m_asteroids)
    {        
        if(asteroid->GetPos().x < LEFT_LIMIT)
            deletedAsteroids.push_back(asteroid);
        
        if(CollisionManager::CheckCollision(asteroid, m_player))
        {
            m_player->TakeDamage(999);
        }
        asteroid->Run();
    }
    
    while(deletedAsteroids.size() != 0)
    {
        EntityManager::DeleteAsteroid(deletedAsteroids[0]);
        deletedAsteroids.erase(deletedAsteroids.begin());
    }
    
    
    if(!m_player->IsAlive())
    {
        GameModeManager::Instance().RequestMode(GameModeManager::GAME_OVER);
    }
    else if(m_enemies.size() == 0 && m_asteroids.size() == 0)
    {
        GameModeManager::Instance().RequestMode(GameModeManager::LEVEL_COMPLETE);
    }
}


void World::LoadLevel(int level)
{
    Loader::Instance().LoadLevel(level);
}


void World::AddEnemy(Enemy* enemy)
{
    m_enemies.push_back(enemy);
}


void World::SetPlayer(Player* player)
{
    m_player = player;
}


void World::AddBullet(Bullet* bullet)
{
    m_bullets.push_back(bullet);
}


void World::AddExplosion(Explosion* explosion)
{ 
    m_explosions.push_back(explosion);
}


void World::AddHealthItem(HealthItem *item)
{
    m_healthItems.push_back(item);
}


void World::AddBackground(Background *back, Background *back2)
{
    m_backgrounds.push_back(back);
    m_backgrounds.push_back(back2);
}


void World::AddAsteroid(Asteroid *asteroid)
{
    m_asteroids.push_back(asteroid);
}


Player* World::GetPlayer()
{
    return m_player;
}


void World::RemoveEnemy(Enemy* enemy)
{
    for(int i = 0; i < m_enemies.size(); i++)
    {
        if(m_enemies[i] == enemy){
            m_enemies.erase(m_enemies.begin() + i);
            break;
        }
    }
}


void World::RemoveBullet(Bullet* bullet)
{
    for(int i = 0; i < m_bullets.size(); i++)
    {
        if(m_bullets[i] == bullet){
            m_bullets.erase(m_bullets.begin() + i);
            break;
        }
    }
}


void World::RemoveExplosion(Explosion *explosion)
{
    for(int i = 0; i < m_explosions.size(); i++)
    {
        if(m_explosions[i] == explosion)
        {
            m_explosions.erase(m_explosions.begin() + i);
            break;
        }
    }
}


void World::RemoveHealthItem(HealthItem *item)
{
    for(int i = 0; i < m_healthItems.size(); i++)
    {
        if(m_healthItems[i] == item){
            m_healthItems.erase(m_healthItems.begin() + i);
            break;
        }
    }
}


void World::RemoveAsteroid(Asteroid *asteroid)
{
    for(int i = 0; i < m_asteroids.size(); i++)
    {
        if(m_asteroids[i] == asteroid)
        {
            m_asteroids.erase(m_asteroids.begin() + i);
            break;
        }
    }
}


void World::ClearEnemies()
{
    for (Enemy* enemy : m_enemies)
        EntityManager::DeleteEnemy(enemy, false);
    
    m_enemies.clear();
}


void World::ClearBullets()
{
    for(Bullet* bullet : m_bullets)
        EntityManager::DeleteBullet(bullet, false);
    
    m_bullets.clear();
}


void World::ClearExplosions()
{
    for(Explosion* explosion : m_explosions)
        EntityManager::DeleteExplosion(explosion, false);
    
    m_explosions.clear();
}


void World::ClearHealthItems()
{
    for(HealthItem* item : m_healthItems)
        EntityManager::DeleteHealthItem(item, false);
    
    m_healthItems.clear();
}


void World::ClearAsteroids()
{
    for(Asteroid* asteroid : m_asteroids)
        EntityManager::DeleteAsteroid(asteroid, false);
    
    m_asteroids.clear();
}


void World::ClearBackgrounds()
{
    for(Background* back : m_backgrounds)
    {
        EntityManager::DeleteBackground(back);
    }
}


void World::Reset()
{
    ClearEnemies();
    ClearExplosions();
    ClearBullets();
    ClearHealthItems();
    ClearBackgrounds();
    ClearAsteroids();
    
    EntityManager::DeletePlayer(m_player);
    m_player = nullptr;
    Init(m_level);
}


uint World::GetLevel()
{
    return m_level;
}
