#ifndef ENEMY_T_4_H
#define ENEMY_T_4_H

#include "Enemy.h"

class EnemyT4 : public Enemy
{
public:
    void Init(int health, int damage, uint shootDelay, int score, vec2 pos, vec2 size, vec2 vel, const char* image);
    void Run();
    void RunBehaviour();
    void Die();
    
protected:
    EnemyT4();
    ~EnemyT4() {}
    
private:
    int m_healthDropped;
    
    friend class EntityManager;
};

#endif /* EnemyT4_h */
