#ifndef MENUS_H
#define MENUS_H

#include "MenuScreen.h"

class MainMenu : public MenuScreen
{
public:
    MainMenu(const char* tag = "MainMenu");
    ~MainMenu() {}
    
    void Draw();
    void OnOptionSelected(uint option);
};

//---------------------------------------

class InstructionsMenu : public MenuScreen
{
public:
    InstructionsMenu(const char* tag = "InstructionsMenu");
    ~InstructionsMenu() {}
    
    void Draw();
    void OnOptionSelected(uint option);
};

//---------------------------------------

class LevelSelectorMenu : public MenuScreen
{
public:
    LevelSelectorMenu(const char* tag = "LevelSelectorMenu");
    ~LevelSelectorMenu() {}
    
    void Draw();
    void OnOptionSelected(uint option);
};

//---------------------------------------

class PauseMenu : public MenuScreen
{
public:
    PauseMenu(const char* tag = "PauseMenu");
    ~PauseMenu() {}
    
    void Input();
    void Draw();
    void OnOptionSelected(uint option);
    bool IsInGameMode();
    
private:
    bool m_prevAcceptKey;
};

//---------------------------------------

class OptionsMenu : public MenuScreen
{
public:
    OptionsMenu(const char* tag = "OptionsMenu");
    ~OptionsMenu() {}
    
    void Input();
    void Draw();
    void OnOptionSelected(uint option);
    void RefreshMenu();
    
private:
    bool m_prevAcceptKey;
};

//---------------------------------------

class GameOverMenu : public MenuScreen
{
public:
    GameOverMenu(const char* tag = "GameOverMenu");
    ~GameOverMenu() {}
    
    void Input();
    void Draw();
    void OnOptionSelected(uint option);
    bool IsInGameMode();
    
private:
    bool m_prevAcceptKey;
};

//---------------------------------------
class LevelCompleteMenu : public MenuScreen
{
public:
    LevelCompleteMenu(const char* tag = "LevelCompleteMenu");
    ~LevelCompleteMenu() {}
    
    void Input();
    void Draw();
    void OnOptionSelected(uint option);
    bool IsInGameMode();
    
private:
    bool m_prevAcceptKey;
};

#endif /* MENUS_H */
