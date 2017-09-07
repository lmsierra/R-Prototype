#include "stdafx.h"
#include "EnemyT1.h"

EnemyT1::EnemyT1()
{

}


void EnemyT1::Run()
{
    m_vel = vmake(m_vel.x, 0);
    Enemy::Run();
}


void EnemyT1::RunBehaviour()
{

}
