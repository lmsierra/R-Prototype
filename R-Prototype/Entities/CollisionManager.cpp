#include "stdafx.h"
#include "CollisionManager.h"
#include "Entity.h"

bool CollisionManager::CheckCollision(Entity* first, Entity* second)
{
    vec2 firstStart = vsub(first->GetPos(), vscale(first->GetSize(), 0.5f));
    vec2 firstEnd   = vadd(firstStart, first->GetSize());
    vec2 secondStart = vsub(second->GetPos(), vscale(second->GetSize(), 0.5f));
    vec2 secondEnd = vadd(secondStart, second->GetSize());
    
    return firstStart.x < secondEnd.x  &&
           firstEnd.x > secondStart.x &&
           firstStart.y < secondEnd.y &&
           firstEnd.y > secondStart.y;
}
