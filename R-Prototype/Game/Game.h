
#ifndef GAME_H
#define GAME_H

class World;
class InputManager;
class Renderer;

class Game
{
public:
    
    enum Modes {
        LOAD_LEVEL,
        START_LEVEL,
        GAME,
        PAUSE_MENU,
        END_LEVEL
    };
    
    static Game* Instance();
    
    void          Init(uint level);
    void          DeInit();
    void          Run();
    void          Draw();
    void          Input();
    void          ResetLevel();
    
    World*        GetWorld();
    InputManager* GetInputManager();
    Renderer*     GetRenderer();
    uint          GetCurrentLevel();
    
private:
    static Game *m_instance;
    
    Game();
    ~Game();
    
    World        *m_world;
    InputManager *m_inputManager;
    Renderer     *m_renderer;
    uint          m_currentLevel;
};

#endif /* GAME_H */
