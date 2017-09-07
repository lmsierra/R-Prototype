#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

class Entity;

class CollisionManager
{
public:
    static bool CheckCollision(Entity* first, Entity* second);
};

#endif /* COLLISION_MANAGER_H */
