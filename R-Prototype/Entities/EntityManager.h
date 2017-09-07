#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Enemy.h"

class Player;
class Bullet;
class Sprite;
class Explosion;
class HealthItem;
class Asteroid;
class Background;

class EntityManager
{
public:
    static Enemy*       CreateEnemy(Enemy::EnemyType type, vec2 pos, vec2 vel, bool addWorld = true);
    static Player*      CreatePlayer(int health, vec2 pos, vec2 size, vec2 vel, bool addWorld = true);
    static Bullet*      CreateBullet(int damage, bool isPlayerOwner, vec2 pos, bool addWorld = true);
    static Explosion*   CreateExplosion(vec2 pos, vec2 size, bool addWorld = true);
    static HealthItem*  CreateHealthItem(int health, vec2 pos, bool addWorld = true);
    static Asteroid*    CreateAsteroid(vec2 pos, vec2 size, vec2 vel, bool addWorld = true);
    static Background*  CreateBackground(vec2 size, vec2 vel, const char* image);
    static Sprite*      CreateSprite(vec2 pos, vec2 size, const char* image);
    
    static void         DeleteEnemy(Enemy* enemy, bool rmWorld = true);
    static void         DeleteBullet(Bullet* bullet, bool rmWorld = true);
    static void         DeletePlayer(Player* player, bool rmWorld = true);
    static void         DeleteExplosion(Explosion* explosion, bool rmWorld = true);
    static void         DeleteHealthItem(HealthItem* item, bool rmWorld = true);
    static void         DeleteAsteroid(Asteroid* asteroid, bool rmWorld = true);
    static void         DeleteBackground(Background* background);
    
    static void         DeleteSprite(Sprite* sprite);
    static void         RegisterSprite(Sprite* sprite);
    static void         UnregisterSprite(Sprite* sprite);
};

#endif /* ENTITY_MANAGER_H */
