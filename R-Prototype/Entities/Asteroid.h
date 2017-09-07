#ifndef ASTEROID_H
#define ASTEROID_H

#include "Entity.h"

class Asteroid : public Entity
{
protected:
    Asteroid();
    ~Asteroid() {}
    
    friend class EntityManager;
};

#endif /* ASTEROID_H */
