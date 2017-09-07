#ifndef SINGLE_PLAYER_MODE_H
#define SINGLE_PLAYER_MODE_H

#include "IGameMode.h"

class Game;

class SinglePlayerMode : public IGameMode
{
public:
    SinglePlayerMode(uint level = 0, const char* tag = "SinglePlayerMode");
    ~SinglePlayerMode();
    
    void Activate();
    void Deactivate();
    void Run();
    void Draw();
    void Input();
    bool IsInGameMode();
    uint GetLevel();
private:
    Game *game;
    uint m_level;
};

#endif /* SINGLE_PLAYER_MODE_H */
