#include "stdafx.h"
#include "Renderer.h"
#include "Sprite.h"
#include "HUD.h"

Renderer::Renderer()
{

}


Renderer::~Renderer()
{

}


void Renderer::Init()
{
    hud = new HUD();
}


void Renderer::Deinit()
{
    sprites.clear();
}


void Renderer::AddSprite(Sprite *sprite)
{
    sprites.push_back(sprite);
}


void Renderer::DeleteSprite(Sprite* sprite)
{
    for(int i = 0; i < sprites.size(); i++)
    {
        if(sprites[i] == sprite)
        {
            sprites.erase(sprites.begin() + i);
        }
    }
}


void Renderer::Run()
{
    for(Sprite* sprite : sprites)
    {
        CORE_RenderCenteredSprite(sprite->GetPos(),
                                  sprite->GetSize(),
                                  sprite->GetTexture());
    }
    
    hud->Draw();
}
