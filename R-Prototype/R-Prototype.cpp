#include "Core/stdafx.h"
#include "sys.h"
#include "core.h"
#include "GameModeManager.h"
#include "ConfigManager.h"
#include "TextureManager.h"

int Main(void)
{
    
    srand(time(nullptr));

    FONT_Init();
    
    ConfigManager::Instance().Init();
    GameModeManager::Instance().Initialize();
    
    
    // Set up rendering
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Sets up clipping
    glClearColor( 0.0f, 0.1f, 0.3f, 0.0f );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho( 0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    while(!SYS_GottaQuit())
    {
        glClear( GL_COLOR_BUFFER_BIT );

        GameModeManager::Instance().ManageState();
        GameModeManager::Instance().Input();
        GameModeManager::Instance().Run();
        GameModeManager::Instance().Draw();
        
        SYS_Show();
        
        // Keep system running
        SYS_Pump();
    }
    
    FONT_End();
    TextureManager::Instance().ReleaseTextures();
    
    return 0;
}