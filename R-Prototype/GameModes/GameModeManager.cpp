#include "stdafx.h"
#include "GameModeManager.h"
#include "SinglePlayerMode.h"
#include "Menus.h"

GameModeManager *GameModeManager::m_instance = 0;

GameModeManager::GameModeManager()
{
    m_requestedMode = nullptr;
}


GameModeManager::~GameModeManager()
{
    for(IGameMode* mode : m_currentModes)
        delete mode;
    
    if(m_requestedMode)
        delete m_requestedMode;
    
    m_currentModes.clear();
}


void GameModeManager::Initialize()
{
    m_requestedMode = nullptr;
    m_currentModes.push_back(new MainMenu());
    m_currentModes[m_currentModes.size() - 1]->Activate();
}


void GameModeManager::RequestMode(MODES mode)
{
    switch(mode)
    {
        case MAIN_MENU:
            m_requestedMode = new MainMenu();
            break;
        case SINGLE_PLAYER:
            m_requestedMode = new SinglePlayerMode();
            break;
        case INSTRUCTIONS:
            m_requestedMode = new InstructionsMenu();
            break;
        case LEVEL_SELECTOR:
            m_requestedMode = new LevelSelectorMenu();
            break;
        case PAUSE:
            m_requestedMode = new PauseMenu();
            break;
        case OPTIONS:
            m_requestedMode = new OptionsMenu();
            break;
        case GAME_OVER:
            m_requestedMode = new GameOverMenu();
            break;
        case LEVEL_COMPLETE:
            m_requestedMode = new LevelCompleteMenu();
            break;
        default:
            m_requestedMode = nullptr;
            break;
    }
}



void GameModeManager::ManageState()
{
    unsigned long size = m_currentModes.size();
    if(m_requestedMode != nullptr && size > 0 && m_currentModes[size - 1] != m_requestedMode)
    {
     
        int prevStateLoaded = -1;
        if(!m_requestedMode->IsInGameMode()) {
            int i = 0;
            
            while(i < m_currentModes.size())
            {
                if(strcmp(m_requestedMode->GetTag(), m_currentModes[i]->GetTag()) == 0 &&
                   ((strcmp(m_requestedMode->GetTag(), "SinglePlayerMode") == 0) &&
                    dynamic_cast<SinglePlayerMode*>(m_requestedMode)->GetLevel() == dynamic_cast<SinglePlayerMode*>(m_currentModes[i])->GetLevel()))
                {
                    
                    prevStateLoaded = i;
                    ++i;
                }
                else
                {
                    m_currentModes[i]->Deactivate();
                    delete m_currentModes[i];
                    m_currentModes.erase(m_currentModes.begin() + i);
                }            
            }
        }
        
        if(prevStateLoaded == -1)
        {
            m_currentModes.push_back(m_requestedMode);
            m_currentModes[m_currentModes.size() - 1]->Activate();
        }
        
        m_requestedMode = nullptr;
    }
}


void GameModeManager::Input()
{
    m_currentModes[m_currentModes.size() - 1]->Input();
}


void GameModeManager::Draw()
{
    for(IGameMode* mode : m_currentModes)
        mode->Draw();
}


void GameModeManager::Run()
{
    m_currentModes[m_currentModes.size() - 1]->Run();
}


GameModeManager& GameModeManager::Instance()
{
    if(!m_instance)
        m_instance = new GameModeManager();
    
    return *m_instance;
}


IGameMode* GameModeManager::GetPreviousMode()
{
    unsigned long size = m_currentModes.size();
    if(size <= 1)
        return nullptr;
    else
        return m_currentModes[size - 2];
}


void GameModeManager::StartLevel(int level)
{
    m_requestedMode = new SinglePlayerMode(level);
}


void GameModeManager::PopMode()
{
    m_currentModes.pop_back();
}
