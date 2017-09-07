#ifndef SPRITE_H
#define SPRITE_H

class Sprite
{
public:
    Sprite();
    ~Sprite();
    
    void         Init(vec2 pos, vec2 size, const char* textureName);
    void         Deinit();
    
    vec2         GetPos();
    vec2         GetSize();
    const char*  GetTextureName();
    GLuint       GetTexture();
   
    void         SetTextureName(const char* texture);
    void         SetPos(vec2 pos);
    void         SetSize(vec2 size);
    
private:
    vec2         m_pos;
    vec2         m_size;
    const char*  m_textureName;
    GLuint       m_texture;
};

#endif /* SPRITE_H */
