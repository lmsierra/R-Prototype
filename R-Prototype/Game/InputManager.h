#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

class Player;

class InputManager
{
public:
    InputManager();
    ~InputManager();
    
    void Init();    
    void Run();
    void SetPlayer(Player* player);

private:
    Player* m_player;
    bool    m_prevPause;
};

#endif /* INPUT_MANAGER_H */
