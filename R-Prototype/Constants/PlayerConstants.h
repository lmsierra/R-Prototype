#ifndef PLAYER_CONFIG_H
#define PLAYER_CONFIG_H

#include "sys.h"

// Player config
#define PLAYER_MAX_HEALTH       100
#define PLAYER_WIDTH           64.f
#define PLAYER_HEIGHT          32.f
#define PLAYER_SPEED            5.f
#define PLAYER_SHOOT_DMG       20.f
#define PLAYER_SHOOT_DELAY     0.1f
#define PLAYER_SPRITE          "prototype_2.png"

#define MOVE_LIMIT_LEFT        0
#define MOVE_LIMIT_RIGHT       SCR_WIDTH / 3 * 2
#define MOVE_LIMIT_TOP         SCR_HEIGHT
#define MOVE_LIMIT_BOTTOM      75

#define PLAYER_INITIAL_POS_X   75.f
#define PLAYER_INITIAL_POS_Y   (SCR_HEIGHT / 2)

#endif /* PLAYER_CONFIG_H */
