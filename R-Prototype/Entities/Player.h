#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
public:
    
    enum Direction {
        BACKWARD = -1,
        STOP     = 0,
        FORWARD  = 1
    };
    
    void     Init(int health, vec2 pos, vec2 size, vec2 vel, const char* imageName);
    void     Run();
    void     MoveXAxis(Direction direction);
    void     MoveYAxis(Direction direction);
    void     Shoot();
    void     TakeDamage(int damage);
    void     Die();

    long int GetScore();
    int      GetHealth();
    bool     IsAlive();
    void     AddHealth(int health);
    void     AddScore(int score);
    
protected:
    Player();
    ~Player();

private:
    int      m_health;
    long int m_score;
    float    m_shootDelay;
    
    friend class EntityManager;
};

#endif /* PLAYER_H */
