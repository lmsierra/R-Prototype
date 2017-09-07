#ifndef IGAME_MODE_H
#define IGAME_MODE_H

class IGameMode
{
public:
    
    IGameMode(const char* tag) { m_tag = tag; }
    virtual ~IGameMode() {};

    virtual void Activate()     = 0;
    virtual void Deactivate()   = 0;
    virtual void Run()          = 0;
    virtual void Draw()         = 0;
    virtual void Input()        = 0;
    virtual bool IsInGameMode() = 0;
    
    const char* GetTag() { return m_tag; }
    
    virtual bool operator==(IGameMode* mode) {
        return strcmp(m_tag, mode->GetTag()) == 0;
    }
    
protected:
    const char* m_tag;
};


#endif /* IGAME_MODE_H */
