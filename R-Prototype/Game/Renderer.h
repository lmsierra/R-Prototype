#ifndef RENDERER_H
#define RENDERER_H

class Sprite;
class HUD;

class Renderer
{
public:
    Renderer();
    ~Renderer();
    
    void Init();
    void Deinit();
    
    void AddSprite(Sprite *sprite);
    void DeleteSprite(Sprite* sprite);
    void Run();
private:
    std::vector<Sprite*> sprites;
    HUD* hud;
};

#endif /* RENDERER_H */
