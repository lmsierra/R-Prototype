#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Sprite;

class Bullet : public Entity
{
public:
    void Init(int damage, bool isPlayerOwner, vec2 pos);
    void Run();
    
    int  GetDamage()     const;
    bool IsPlayerOwner() const;
    
protected:
    Bullet();
    ~Bullet();
    
private:
    int  m_damage;
    bool m_playerOwner;
    
    friend class EntityManager;
};

#endif /* BULLET_H */
