#include "stdafx.h"
#include "InputManager.h"
#include "GameConfig.h"
#include "Player.h"
#include "Game.h"
#include "World.h"
#include "GameModeManager.h"

InputManager::InputManager()
{
    m_player = nullptr;
    m_prevPause = true;
}


InputManager::~InputManager()
{
    m_player = nullptr;
}


void InputManager::Init()
{

}


void InputManager::Run()
{
    if(!m_player) return;
    
    if (SYS_KeyPressed(KEY_MOVE_DOWN) == GLFW_PRESS)
        m_player->MoveYAxis(Player::BACKWARD);
    else if (SYS_KeyPressed(KEY_MOVE_UP) == GLFW_PRESS)
        m_player->MoveYAxis(Player::FORWARD);
    else
        m_player->MoveYAxis(Player::STOP);
    
    if (SYS_KeyPressed(KEY_MOVE_LEFT) == GLFW_PRESS)
        m_player->MoveXAxis(Player::BACKWARD);
    else if (SYS_KeyPressed(KEY_MOVE_RIGHT) == GLFW_PRESS)
        m_player->MoveXAxis(Player::FORWARD);
    else
        m_player->MoveXAxis(Player::STOP);
    
    if (SYS_KeyPressed(KEY_SHOOT)) // spacebar
        m_player->Shoot();
    
    if(SYS_KeyPressed(KEY_PAUSE) == GLFW_PRESS && m_prevPause == GLFW_RELEASE)
        GameModeManager::Instance().RequestMode(GameModeManager::PAUSE);
    
    m_prevPause = SYS_KeyPressed(KEY_PAUSE);
}


void InputManager::SetPlayer(Player* player)
{
    m_player = player;
}
