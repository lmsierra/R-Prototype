#ifndef HEALTH_ITEM_H
#define HEALTH_ITEM_H

#include "Entity.h"

class HealthItem : public Entity
{
public:
    void Init(int health, vec2 pos, vec2 size, vec2 vel, const char* image);
    void Run();

    int GetHealth();
    
protected:
    HealthItem();
    ~HealthItem() {}

private:
    int m_health;
    
    friend class EntityManager;
};

#endif /* HEALTH_ITEM_H */
