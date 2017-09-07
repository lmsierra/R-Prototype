#include "stdafx.h"
#include "EntityManager.h"
#include "Game.h"
#include "World.h"
#include "Renderer.h"
#include "Player.h"
#include "Bullet.h"
#include "Entity.h"
#include "Explosion.h"
#include "Sprite.h"
#include "EnemyT1.h"
#include "EnemyT2.h"
#include "EnemyT4.h"
#include "Background.h"
#include "HealthItem.h"
#include "Asteroid.h"
#include "PlayerConstants.h"
#include "EnemyConstants.h"

Enemy* EntityManager::CreateEnemy(Enemy::EnemyType type, vec2 pos, vec2 vel, bool addWorld)
{
    Enemy* enemy;
    switch(type) {
        case Enemy::ENEMY_1:
            enemy = new EnemyT1();
            enemy->Init(E_T_1_HEALTH, E_T_1_DAMAGE, E_T_1_DELAY, E_T_1_SCORE, pos, vmake(E_T_1_WIDTH, E_T_1_HEIGHT), vel, E_T_1_SPRITE);
            break;
        case Enemy::ENEMY_2:
            enemy = new EnemyT2();
            enemy->Init(E_T_2_HEALTH, E_T_2_DAMAGE, E_T_2_DELAY, E_T_2_SCORE, pos, vmake(E_T_2_WIDTH, E_T_2_HEIGHT), vel, E_T_2_SPRITE);
            break;
        case Enemy::ENEMY_4:
            enemy = new EnemyT4();
            enemy->Init(E_T_4_HEALTH, E_T_4_DAMAGE, E_T_4_DELAY, E_T_4_SCORE, pos, vmake(E_T_4_WIDTH, E_T_4_HEIGHT), vel, E_T_4_SPRITE);
            break;
        default:
            return nullptr;
    }
    
    if(addWorld){
        Game::Instance()->GetWorld()->AddEnemy(enemy);
        RegisterSprite(enemy->GetSprite());
    }
    return enemy;
}


Player* EntityManager::CreatePlayer(int health, vec2 pos, vec2 size, vec2 vel, bool addWorld)
{
    Player* player = new Player();
    player->Init(health, pos, size, vel, PLAYER_SPRITE);
    if(addWorld)
    {
        Game::Instance()->GetWorld()->SetPlayer(player);
        RegisterSprite(player->GetSprite());
    }
    return player;
}


Bullet* EntityManager::CreateBullet(int damage, bool isPlayerOwner, vec2 pos, bool addWorld)
{
    Bullet* bullet = new Bullet();
    bullet->Init(damage, isPlayerOwner, pos);
    if(addWorld)
    {
        Game::Instance()->GetWorld()->AddBullet(bullet);
        RegisterSprite(bullet->GetSprite());
    }
    return bullet;
}


Explosion* EntityManager::CreateExplosion(vec2 pos, vec2 size, bool addWorld)
{

    Explosion* explosion = new Explosion();
    explosion->Init(pos, size);
    if(addWorld)
    {
        Game::Instance()->GetWorld()->AddExplosion(explosion);
        RegisterSprite(explosion->GetSprite());
    }

    return explosion;
}


HealthItem* EntityManager::CreateHealthItem(int health, vec2 pos, bool addWorld)
{
    HealthItem* item = new HealthItem();
    item->Init(health, pos, vmake(32.f, 32.f), vmake(-3.f, 0.f), "health.png");
    
    if(addWorld)
    {
        Game::Instance()->GetWorld()->AddHealthItem(item);
        RegisterSprite(item->GetSprite());
    }
    
    return item;
}


Asteroid* EntityManager::CreateAsteroid(vec2 pos, vec2 size, vec2 vel, bool addWorld)
{
    Asteroid* asteroid = new Asteroid();
    asteroid->Init(pos, size, vel, "asteroid.png");
    
    if(addWorld)
    {
        Game::Instance()->GetWorld()->AddAsteroid(asteroid);
        RegisterSprite(asteroid->GetSprite());
    }
    
    return asteroid;
}


Background* EntityManager::CreateBackground(vec2 size, vec2 vel, const char* image)
{
    Background* back  = new Background();
    Background* back2 = new Background();
    back->Init(vmake(size.x/2, size.y/2), size, vel, image);
    back2->Init(vadd(back->GetPos(), vmake(size.x, 0)), size, vel, image);
    
    Game::Instance()->GetWorld()->AddBackground(back, back2);
    RegisterSprite(back->GetSprite());
    RegisterSprite(back2->GetSprite());
    
    return back;
}


Sprite* EntityManager::CreateSprite(vec2 pos, vec2 size, const char* image)
{
    Sprite* sprite = new Sprite();
    sprite->Init(pos, size, image);
    return sprite;
}


void EntityManager::DeleteEnemy(Enemy* enemy, bool rmWorld)
{
    if(enemy)
    {
        if(rmWorld)
            Game::Instance()->GetWorld()->RemoveEnemy(enemy);
        delete enemy;
    }
}


void EntityManager::DeleteBullet(Bullet* bullet, bool rmWorld)
{
    if(bullet)
    {
        if(rmWorld)
            Game::Instance()->GetWorld()->RemoveBullet(bullet);
        delete bullet;
    }
}


void EntityManager::DeletePlayer(Player* player, bool rmWorld)
{
    if(player)
        delete player;
}


void EntityManager::DeleteExplosion(Explosion *explosion, bool rmWorld)
{
    if(explosion)
    {
        if(rmWorld)
            Game::Instance()->GetWorld()->RemoveExplosion(explosion);
        delete explosion;
    }
}


void EntityManager::DeleteHealthItem(HealthItem *item, bool rmWorld)
{
    if(item)
    {
        if(rmWorld)
            Game::Instance()->GetWorld()->RemoveHealthItem(item);
        delete item;
    }
}


void EntityManager::DeleteAsteroid(Asteroid *asteroid, bool rmWorld)
{
    if(asteroid)
    {
        if(rmWorld)
            Game::Instance()->GetWorld()->RemoveAsteroid(asteroid);
        delete asteroid;
    }
}


void EntityManager::DeleteBackground(Background* background)
{
    if(background)
        delete background;
}


void EntityManager::DeleteSprite(Sprite* sprite)
{
    UnregisterSprite(sprite);
    delete sprite;
}


void EntityManager::RegisterSprite(Sprite* sprite)
{
    Game::Instance()->GetRenderer()->AddSprite(sprite);
}


void EntityManager::UnregisterSprite(Sprite* sprite)
{
    Game::Instance()->GetRenderer()->DeleteSprite(sprite);
}
