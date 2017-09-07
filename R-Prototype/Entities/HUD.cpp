#include "stdafx.h"
#include "sys.h"
#include "HUD.h"
#include "Game.h"
#include "World.h"
#include "Player.h"
#include "progressbar.h"
#include "font.h"
#include "LocalizationManager.h"
#include "PlayerConstants.h"
#include "ConfigManager.h"

HUD::HUD()
{

}


void HUD::Draw()
{
    Player* player = Game::Instance()->GetWorld()->GetPlayer();
    
    if(player){
        DrawLifeIndicator(player);
        DrawScoreIndicator(player);
    }
}


void HUD::DrawLifeIndicator(Player* player)
{
    FONT_DrawString(HUD_LIFE_TEXT_POS, LocalizationManager::Instance().LocalizedString(HUD_LIFE_TEXT, ConfigManager::Instance().GetLanguage()));
    PROGRESSBAR_Draw(player->GetHealth(), 0, PLAYER_MAX_HEALTH, HUD_LIFE_POSITION, HUD_LIFE_SIZE, HUD_LIFE_MIN_COLOR, HUD_LIFE_MAX_COLOR, HUD_LIFE_BACK_COLOR);
}


void HUD::DrawScoreIndicator(Player* player)
{
    FONT_DrawString(HUD_SCORE_TEXT_POS, LocalizationManager::Instance().LocalizedString(HUD_SCORE_TEXT, ConfigManager::Instance().GetLanguage()));
    char* score = (char*) malloc(7);
    sprintf(score, "%06ld", player->GetScore());
    FONT_DrawString(HUD_SCORE_POS, score);
    free(score);
}
