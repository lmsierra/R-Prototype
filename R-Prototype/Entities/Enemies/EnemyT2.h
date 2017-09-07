#ifndef ENEMY_T_2
#define ENEMY_T_2

#include "Enemy.h"

class EnemyT2 : public Enemy
{
public:
    void Init(int health, int damage, uint shootDelay, int score, vec2 pos, vec2 size, vec2 vel, const char* image);
    void Run();
    void RunBehaviour();
    
protected:
    EnemyT2();
    ~EnemyT2() {}
    
    friend class EntityManager;
};
#endif /* ENEMY_T_2 */
