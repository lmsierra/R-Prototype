#ifndef HUD_H
#define HUD_H

#include "StringConstants.h"

#define HUD_LIFE_BACK_COLOR v3make(150, 150, 150)
#define HUD_LIFE_MIN_COLOR  v3make(255, 0, 0)
#define HUD_LIFE_MAX_COLOR  v3make(0, 255, 0)
#define HUD_LIFE_POSITION   vmake(80,   8)
#define HUD_LIFE_SIZE       vmake(150, 25)
#define HUD_LIFE_TEXT_POS   vmake(10,  12)
#define HUD_LIFE_TEXT       TEXT_LIFE
#define HUD_SCORE_TEXT_POS  vmake(400, 12)
#define HUD_SCORE_POS       vmake(500, 12)
#define HUD_SCORE_TEXT      TEXT_SCORE

class Player;

class HUD
{
public:
    HUD();
    void Draw();
private:
    void DrawLifeIndicator(Player* player);
    void DrawScoreIndicator(Player* player);
};

#endif /* HUD_H */
