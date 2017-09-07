#include "stdafx.h"
#include "HealthItem.h"

HealthItem::HealthItem()
{

}


void HealthItem::Init(int health, vec2 pos, vec2 size, vec2 vel, const char* image)
{
    Entity::Init(pos, size, vel, image);
}


int HealthItem::GetHealth()
{
    return m_health;
}


void HealthItem::Run()
{
    Entity::Run();
}
