#include "stdafx.h"
#include "sys.h"
#include "Menus.h"
#include "MenuConstants.h"
#include "GameConfig.h"
#include "GameModeManager.h"
#include "Game.h"
#include "World.h"
#include "LocalizationManager.h"
#include "Loader.h"
#include "ConfigManager.h"
#include "StringConstants.h"
#include "progressbar.h"

// Get text in current language
#define LOCALIZED_TEXT(a) LocalizationManager::Instance().LocalizedString(a, ConfigManager::Instance().GetLanguage())

MainMenu::MainMenu(const char* tag) : MenuScreen(tag)
{
    printf("MENU MODE - CONSTRUCTOR\n");
    std::vector<const char*> options;
        
    options.push_back(LOCALIZED_TEXT(TEXT_NEW_GAME));
    options.push_back(LOCALIZED_TEXT(TEXT_LOAD_LEVEL));
    options.push_back(LOCALIZED_TEXT(TEXT_HELP));
    options.push_back(LOCALIZED_TEXT(TEXT_OPTIONS));
    options.push_back(LOCALIZED_TEXT(TEXT_EXIT));
    Initialize(LOCALIZED_TEXT(TEXT_MAIN_TITLE), options);
}


void MainMenu::Draw()
{
    MenuScreen::Draw();
}


void MainMenu::OnOptionSelected(uint option)
{
    switch(option)
    {
        case 0: // Choose Level
            GameModeManager::Instance().RequestMode(GameModeManager::SINGLE_PLAYER);
            break;
            
        case 1: // Level Selector
            GameModeManager::Instance().RequestMode(GameModeManager::LEVEL_SELECTOR);
            break;
            
        case 2: // Instructions
            GameModeManager::Instance().RequestMode(GameModeManager::INSTRUCTIONS);
            break;
            
        case 3:// Exit
            GameModeManager::Instance().RequestMode(GameModeManager::OPTIONS);
            break;
        case 4:
            exit(0);
            break;
        default:
            break;
    }
}

//------------------------------------------------

InstructionsMenu::InstructionsMenu(const char* tag) : MenuScreen(tag)
{
    std::vector<const char*> vector;

    vector.push_back(LOCALIZED_TEXT(TEXT_INSTR_1));
    vector.push_back(LOCALIZED_TEXT(TEXT_INSTR_2));
    vector.push_back(LOCALIZED_TEXT(TEXT_INSTR_3));
    vector.push_back(LOCALIZED_TEXT(TEXT_BACK));
    Initialize(LOCALIZED_TEXT(TEXT_MAIN_TITLE), vector, true);
    SetNavigableOptions(false);
    SetCurrentOption(NUM_INSTR - 1);
}

void InstructionsMenu::Draw()
{
    MenuScreen::Draw();
}

void InstructionsMenu::OnOptionSelected(uint option)
{
    GameModeManager::Instance().RequestMode(GameModeManager::MAIN_MENU);
}

//------------------------------------------------

LevelSelectorMenu::LevelSelectorMenu(const char* tag) : MenuScreen(tag)
{
    std::vector<const char*> vector;
    
    int levels = Loader::Instance().GetNumLevels();
    for(int i = 0; i < levels; i++)
    {
        const char* lvlStr;
        if(i <= ConfigManager::Instance().GetCurrentLevel() && i != m_options.size() - 1)
        {
            lvlStr = LOCALIZED_TEXT(TEXT_LEVEL);
            char* name = (char*) malloc(sizeof(lvlStr) / sizeof(char) + 5);
            sprintf(name, "%s%i", lvlStr, i + 1);
            vector.push_back(name);
        
        } else
        {
            lvlStr = LOCALIZED_TEXT(TEXT_LOCKED);
            vector.push_back(lvlStr);
        }
    
    }
    
    vector.push_back(LOCALIZED_TEXT(TEXT_BACK));
    Initialize(LOCALIZED_TEXT(TEXT_LOAD_LEVEL), vector);
}

void LevelSelectorMenu::Draw()
{
    MenuScreen::Draw();
}

void LevelSelectorMenu::OnOptionSelected(uint option)
{
    if(option == Loader::Instance().GetNumLevels())
        GameModeManager::Instance().RequestMode(GameModeManager::MAIN_MENU);
    else {
        printf("Option: %u\n", option);
        printf("Current Level: %u\n", ConfigManager::Instance().GetCurrentLevel());
        if(option <= ConfigManager::Instance().GetCurrentLevel())
        {
            GameModeManager::Instance().StartLevel(option);
        }
        // Load Level(option)
    }
}

//------------------------------------------------

PauseMenu::PauseMenu(const char* tag) : MenuScreen(tag)
{
    m_prevAcceptKey = true;
    std::vector<const char*> vector;
    
    vector.push_back(LOCALIZED_TEXT(TEXT_RESUME));
    //vector.push_back(LOCALIZED_TEXT(TEXT_OPTIONS));
    vector.push_back(LOCALIZED_TEXT(TEXT_EXIT));
    Initialize(LOCALIZED_TEXT(TEXT_PAUSE), vector);

    std::vector<const char*> empty;
    SetHints(empty);
    SetDeveloperNotes(empty);
}

void PauseMenu::Draw()
{
    MenuScreen::Draw();
}


void PauseMenu::Input()
{
    MenuScreen::Input();
    
    if(SYS_KeyPressed(KEY_PAUSE) == GLFW_PRESS && m_prevAcceptKey == GLFW_RELEASE)
        GameModeManager::Instance().StartLevel(Game::Instance()->GetCurrentLevel());
    
    m_prevAcceptKey = SYS_KeyPressed(KEY_PAUSE);
}


void PauseMenu::OnOptionSelected(uint option)
{
    switch (option) {
        case 0:
            GameModeManager::Instance().StartLevel(Game::Instance()->GetCurrentLevel());
            break;
        case 1:
        //    break;
        //case 2:
            GameModeManager::Instance().RequestMode(GameModeManager::MAIN_MENU);
            break;
        default:
            break;
    }
}


bool PauseMenu::IsInGameMode()
{
    return true;
}

//------------------------------------------------

OptionsMenu::OptionsMenu(const char* tag) : MenuScreen(tag)
{
    RefreshMenu();
}


void OptionsMenu::Draw()
{
    MenuScreen::Draw();
}


void OptionsMenu::Input()
{
    MenuScreen::Input();
}


void OptionsMenu::RefreshMenu()
{
    std::vector<const char*> vector;
    
    const char* sound    = LOCALIZED_TEXT(TEXT_SOUND);
    const char* language = LOCALIZED_TEXT(TEXT_LANGUAGE);
    const char* active   = (ConfigManager::Instance().IsSoundActive())? LOCALIZED_TEXT(TEXT_ON) : LOCALIZED_TEXT(TEXT_OFF);
    
    const char* lang;
    switch (ConfigManager::Instance().GetLanguage()) {
        case LocalizationManager::SPANISH:
            lang = LOCALIZED_TEXT(TEXT_SPANISH);
            break;
        case LocalizationManager::ENGLISH:
            lang = LOCALIZED_TEXT(TEXT_ENGLISH);
            break;
        default:
            lang = LOCALIZED_TEXT(TEXT_ENGLISH);
            break;
    }
    
    char* soundBuff = (char*) malloc(sizeof(sound) / sizeof(char) + 4 + sizeof(active) / sizeof(char));
    char* langBuff  = (char*) malloc(sizeof(language) / sizeof(char) + 4 + sizeof(lang) / sizeof(char));
    
    sprintf(soundBuff, "%s : %s", sound,    active);
    sprintf(langBuff,  "%s : %s", language, lang);
    
    vector.push_back(soundBuff);
    vector.push_back(langBuff);
    vector.push_back(LOCALIZED_TEXT(TEXT_BACK));

    Initialize(LOCALIZED_TEXT(TEXT_OPTIONS), vector);
}


void OptionsMenu::OnOptionSelected(uint option)
{
    switch (option) {
        case 0:
            ConfigManager::Instance().SetSound(!ConfigManager::Instance().IsSoundActive());
            break;
        case 1:
            ConfigManager::Instance().SetNextLanguage();
            break;
        case 2:
            Loader::Instance().Save();
            GameModeManager::Instance().RequestMode(GameModeManager::MAIN_MENU);
            return;
        default:
            break;
    }
    
    RefreshMenu();
}

//------------------------------------------------

GameOverMenu::GameOverMenu(const char* tag) : MenuScreen(tag)
{
    m_prevAcceptKey = true;
    std::vector<const char*> vector;
    
    vector.push_back(LOCALIZED_TEXT(TEXT_RETRY));
    vector.push_back(LOCALIZED_TEXT(TEXT_EXIT));
    Initialize(LOCALIZED_TEXT(TEXT_GAME_OVER), vector);
    
    std::vector<const char*> empty;
    SetHints(empty);
    SetDeveloperNotes(empty);
}


void GameOverMenu::Input()
{
    MenuScreen::Input();
}


void GameOverMenu::Draw()
{
    MenuScreen::Draw();
}


void GameOverMenu::OnOptionSelected(uint option)
{
    switch (option) {
        case 0:
            Game::Instance()->ResetLevel();
            GameModeManager::Instance().StartLevel(Game::Instance()->GetCurrentLevel());
            break;
        case 1:
            GameModeManager::Instance().RequestMode(GameModeManager::MAIN_MENU);
            break;
        default:
            break;
    }
}


bool GameOverMenu::IsInGameMode()
{
    return true;
}

//------------------------------------------------

LevelCompleteMenu::LevelCompleteMenu(const char* tag) : MenuScreen(tag)
{
    m_prevAcceptKey = true;
    std::vector<const char*> vector;
    
    
    if(Game::Instance()->GetCurrentLevel() < Loader::Instance().GetNumLevels() - 1)
        vector.push_back(LOCALIZED_TEXT(TEXT_CONTINUE));
    
    vector.push_back(LOCALIZED_TEXT(TEXT_EXIT));
    Initialize(LOCALIZED_TEXT(TEXT_COMPLETED), vector);
    
    std::vector<const char*> empty;
    SetHints(empty);
    SetDeveloperNotes(empty);
    
    if(ConfigManager::Instance().GetCurrentLevel() == Game::Instance()->GetCurrentLevel())
    {
        ConfigManager::Instance().SetCurrentLevel(ConfigManager::Instance().GetCurrentLevel() + 1);
        Loader::Instance().Save();
    }
}


void LevelCompleteMenu::Input()
{
    MenuScreen::Input();
}


void LevelCompleteMenu::Draw()
{
    MenuScreen::Draw();
}


void LevelCompleteMenu::OnOptionSelected(uint option)
{
    if(m_options.size() > 1)
    {
        switch (option) {
            case 0:
                // Load level 2
                GameModeManager::Instance().StartLevel(Game::Instance()->GetCurrentLevel() + 1);
                break;
            case 1:
                GameModeManager::Instance().RequestMode(GameModeManager::MAIN_MENU);
                break;
            default:
                break;
        }
    }
    else
    {
        GameModeManager::Instance().RequestMode(GameModeManager::MAIN_MENU);
    }
}


bool LevelCompleteMenu::IsInGameMode()
{
    return true;
}
