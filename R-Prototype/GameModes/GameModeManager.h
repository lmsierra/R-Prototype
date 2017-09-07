#ifndef GAME_MODE_MANAGER_H
#define GAME_MODE_MANAGER_H

#include "IGameMode.h"

class GameModeManager
{
public:
    enum MODES{
        MAIN_MENU,
        INSTRUCTIONS,
        LEVEL_SELECTOR,
        SINGLE_PLAYER,
        PAUSE,
        OPTIONS,
        GAME_OVER,
        LEVEL_COMPLETE
    };
    
    static GameModeManager& Instance();
    
    
    void Initialize();
    void RequestMode(MODES mode);
    void ManageState();
    void Input();
    void Draw();
    void Run();

    void PopMode();
    void StartLevel(int level);
    IGameMode* GetPreviousMode();
private:
    static GameModeManager* m_instance;
    
    GameModeManager();
    virtual ~GameModeManager();

    std::vector<IGameMode*> m_currentModes;
    IGameMode*              m_requestedMode;
};

#endif /* GAME_MODE_MANAGER_H */
