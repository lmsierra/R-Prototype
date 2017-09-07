#include "stdafx.h"
#include "progressbar.h"

void DrawRect(const vec2 pos, const vec2 size, const vec3 color)
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glBegin(GL_QUADS);
    glColor3f(color.x / 255.f, color.y / 255.f, color.z / 255.f);
    glVertex2f(pos.x, pos.y);
    glVertex2f(pos.x, pos.y + size.y);
    glVertex2f(pos.x + size.x, pos.y + size.y);
    glVertex2f(pos.x + size.x, pos.y);
    glEnd();
    
    glColor3f(1.f, 1.f, 1.f);
}


void DrawRectGradient(const vec2 pos, const vec2 size, const vec3 initialColor, const vec3 endColor)
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glBegin(GL_QUADS);
    
    glColor3f(initialColor.x / 255.f, initialColor.y / 255.f, initialColor.z / 255.f);
    glVertex2f(pos.x, pos.y);
    glVertex2f(pos.x, pos.y + size.y);

    glColor3f(endColor.x / 255.f, endColor.y / 255.f, endColor.z / 255.f);
    glVertex2f(pos.x + size.x, pos.y + size.y);
    glVertex2f(pos.x + size.x, pos.y);
    
    glEnd();
    glColor3f(1.f, 1.f, 1.f);
}


void PROGRESSBAR_Draw(const float current, const float min, const float max, const vec2 pos, const vec2 size, const vec3 minColor, const vec3 maxColor, const vec3 backColor)
{
    DrawRect(pos, size, backColor);
    
    if(current > 0)
    {
        float percentage = (current - min) / (max - min);
        float x = (percentage * size.x > size.x)? size.x - 6.f : percentage * size.x - 6;
        float y = size.y - 6;
        vec2 contentSize = vmake(x, y);
        vec2 contentPos  = vadd(pos, vmake(3, 3));
        
        float red   = (1 - percentage) * minColor.x + percentage * maxColor.x;
        float green = (1 - percentage) * minColor.y + percentage * maxColor.y;
        float blue  = (1 - percentage) * minColor.z + percentage * maxColor.z;
        
        vec3 color = v3make(red, green, blue);
        DrawRectGradient(contentPos, contentSize, minColor, color);
    }
}
