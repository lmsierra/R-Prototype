#ifndef _FONT_H_
#define _FONT_H_

#include "core.h"

void FONT_Init();
void FONT_End();
void FONT_DrawChar(vec2 p0, vec2 p1, unsigned char ch, vec3 color = v3make(255, 255, 255));
void FONT_DrawString(vec2 p0, const char string[], vec3 color = v3make(255, 255, 255), vec2 size = vmake(16.f, 16.f));

#endif
