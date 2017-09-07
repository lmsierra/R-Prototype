#ifndef ENTITY_H
#define ENTITY_H

class Sprite;

class Entity
{
    
public:
    void         Init(vec2 pos, vec2 size, vec2 vel, const char* spriteName);
    virtual void Run();
    void         UpdateSprite();

    vec2         GetPos()    const;
    vec2         GetSize()   const;
    vec2         GetVel()    const;
    Sprite*      GetSprite() const;
    
    void         SetPos(vec2 pos);
    void         SetSize(vec2 size);
    void         SetVel(vec2 vel);
    
protected:
    Entity();
    virtual ~Entity();
    
    vec2    m_pos;
    vec2    m_size;
    vec2    m_vel;
    Sprite* m_sprite;
};

#endif /* ENTITY_H */
