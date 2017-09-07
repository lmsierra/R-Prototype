#ifndef WORLD_H
#define WORLD_H

#include "Enemy.h"

#define LEFT_LIMIT  -100
#define RIGHT_LIMIT (SCR_WIDTH+100)

class Player;
class Enemy;
class Bullet;
class Sprite;
class Explosion;
class HealthItem;
class Asteroid;
class Background;


class World
{
public:
    World();
    ~World();
    
    void    Init(uint level = 0);
    void    Run();
    void    LoadLevel(int level);
    void    SetLevelData();
    void    SetPlayer(Player* player);
    
    void    AddEnemy(Enemy* enemy);
    void    AddBullet(Bullet* bullet);
    void    AddExplosion(Explosion* explosion);
    void    AddHealthItem(HealthItem* item);
    void    AddBackground(Background* back, Background* back2);
    void    AddAsteroid(Asteroid* asteroid);
    
    void    RemoveBullet(Bullet* bullet);
    void    RemoveEnemy(Enemy* enemy);
    void    RemoveExplosion(Explosion* explosion);
    void    RemoveHealthItem(HealthItem* item);
    void    RemoveAsteroid(Asteroid* asteroid);
    
    void    ClearEnemies();
    void    ClearBullets();
    void    ClearExplosions();
    void    ClearHealthItems();
    void    ClearBackgrounds();
    void    ClearAsteroids();
    
    void    Reset();
    Player* GetPlayer();
    uint    GetLevel();
    
private:
    int                       m_level;
    char*                     m_levelname;
    Player*                   m_player;
    std::vector<Enemy*>       m_enemies;
    std::vector<Bullet*>      m_bullets;
    std::vector<Explosion*>   m_explosions;
    std::vector<HealthItem*>  m_healthItems;
    std::vector<Asteroid*>    m_asteroids;
    std::vector<Background*>  m_backgrounds;
};

#endif /* WORLD_H */
