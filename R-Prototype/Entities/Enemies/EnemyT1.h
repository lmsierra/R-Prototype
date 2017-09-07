#ifndef ENEMY_T_1_H
#define ENEMY_T_1_H

#include "Enemy.h"

class EnemyT1 : public Enemy
{
public:
    void Run();
    void RunBehaviour();
    
protected:
    EnemyT1();
    ~EnemyT1() {}

friend class EntityManager;
};

#endif /* ENEMY_T_1_H */
