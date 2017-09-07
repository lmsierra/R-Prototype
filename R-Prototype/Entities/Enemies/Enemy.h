#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "IBehaviour.h"

class Enemy : public Entity, IBehaviour
{
public:
    
    enum EnemyType
    {
        ENEMY_ERROR = -1,
        ENEMY_1     = 0,
        ENEMY_2,
        ENEMY_4
    };
    
;
    virtual void Init(int health, int damage, uint shootDelay, int score, vec2 pos, vec2 size, vec2 vel, const char* image);
    virtual void Die();
    
    virtual void Run();
    virtual void RunBehaviour() = 0;
    
    void         TakeDamage(int damage);
    bool         IsDead();
    
    int          GetHealth();
    int          GetDamage();
    int          GetShootDelay();
    int          GetScore();
    
    void         SetHealth(int health);
    void         SetDamage(int damage);
    void         SetShootDelay(uint delay);
    void         SetScore(int score);
    
protected:
    Enemy();
    virtual ~Enemy();
    
    int  m_health;
    int  m_damage;
    uint m_shootDelay;
    int  m_currentDelay;
    int  m_score;

    friend class EntityManager;
};

#endif /* ENEMY_H */
