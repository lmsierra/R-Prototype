#include "stdafx.h"
#include "Game.h"
#include "World.h"
#include "InputManager.h"
#include "Renderer.h"

Game *Game::m_instance;

Game::Game()
{
    m_world        = nullptr;
    m_inputManager = nullptr;
    m_renderer     = nullptr;
}


Game::~Game()
{
    m_world        = nullptr;
    m_inputManager = nullptr;
    m_renderer     = nullptr;
}


Game* Game::Instance()
{
    if(!m_instance)
        m_instance = new Game();
    
    return m_instance;
}


void Game::Init(uint level)
{
    // Cargar nivel por fichero de datos
    m_currentLevel = level;
    
    m_world        = new World();
    m_inputManager = new InputManager();
    m_renderer     = new Renderer();
    
    m_world->Init(level);
    m_inputManager->Init();
    m_inputManager->SetPlayer(m_world->GetPlayer());
    m_renderer->Init();
}


void Game::DeInit()
{
    if(m_world)        delete m_world;
    if(m_inputManager) delete m_inputManager;
    if(m_renderer)     delete m_renderer;
}


void Game::Run()
{
    m_world->Run();
}


void Game::Draw()
{
    m_renderer->Run();
}


void Game::Input()
{
    m_inputManager->Run();
}


World* Game::GetWorld()
{
    return m_world;
}


InputManager* Game::GetInputManager()
{
    return m_inputManager;
}


Renderer* Game::GetRenderer()
{
    return m_renderer;
}


uint Game::GetCurrentLevel()
{
    return m_currentLevel;
}


void Game::ResetLevel()
{
    uint level = m_world->GetLevel();
    if(m_world) delete m_world;
    m_world = new World();
    m_world->Init(level);
    m_inputManager->SetPlayer(m_world->GetPlayer());
}
