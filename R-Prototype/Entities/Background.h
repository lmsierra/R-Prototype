#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Entity.h"

class Background : public Entity
{
public:
    void Run();
    
protected:
    Background();
    ~Background() {}

    friend class EntityManager;
};

#endif /* BACKGROUND_H */
