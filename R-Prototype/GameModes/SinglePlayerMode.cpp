#include "stdafx.h"
#include "SinglePlayerMode.h"
#include "Game.h"

SinglePlayerMode::SinglePlayerMode(uint level, const char* tag) : IGameMode(tag)
{
    game     = nullptr;
    m_level  = level;
}


SinglePlayerMode::~SinglePlayerMode()
{

}


void SinglePlayerMode::Activate()
{
    game = Game::Instance();
    game->Init(m_level);
}


void SinglePlayerMode::Deactivate()
{
    game->DeInit();
    game = nullptr;
}


void SinglePlayerMode::Run()
{
    game->Run();
}


void SinglePlayerMode::Draw()
{
    game->Draw();
}


void SinglePlayerMode::Input()
{
    game->Input();
}


bool SinglePlayerMode::IsInGameMode()
{
    return false;
}


uint SinglePlayerMode::GetLevel()
{
    return m_level;
}
