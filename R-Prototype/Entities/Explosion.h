#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Entity.h"

#define EXPLOSION_TIME 2

class Explosion : public Entity
{
public:
    void Run();
    void Init(vec2 pos, vec2 size);
    
protected:
    Explosion();
    ~Explosion();
    
private:
    uint                     m_index;
    float                    m_currentTime;
    std::vector<const char*> m_explosionImages;
    
    friend class EntityManager;
};

#endif /* EXPLOSION_H */
