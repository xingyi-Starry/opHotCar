#include "opHot_image_show.h"

void Image_ShowLine(uint8 x, uint8 y)
{
    for (uint8 i = 0; i < Image_iptsLeftNum; i++)
    {
        ips200_draw_point(x + Image_iptsLeft[i][0], y + Image_iptsLeft[i][1], RGB565_GREEN);
    }
    for (uint8 i = 0; i < Image_iptsRightNum; i++)
    {
        ips200_draw_point(x + Image_iptsRight[i][0], y + Image_iptsRight[i][1], RGB565_RED);
    }
}

void Image_ShowResampleLine(uint8 x, uint8 y)
{
    for (uint8 i = 0; i < Image_rptsLeftsNum; i++)
    {
        ips200_draw_point(x + Image_rptsLefts[i][0], y + Image_rptsLefts[i][1], RGB565_GREEN);
    }
    for (uint8 i = 0; i < Image_rptsRightsNum; i++)
    {
        ips200_draw_point(x + Image_rptsRights[i][0], y + Image_rptsRights[i][1], RGB565_RED);
    }
    for (uint8 i = 0; i < Image_MidLineNum; i++)
    {
        ips200_draw_point(x + Image_RsMidLine[i][0], y + Image_RsMidLine[i][1], RGB565_YELLOW);
    }
}

void Image_ShowArray(uint8 x, uint8 y, uint8 height, float Array[], uint8 num, rgb565_color_enum Color)
{
    for (uint8 i = 0; i < num; i++)
    {
        ips200_draw_point(x + i, y + height - (uint8)Array[i], Color);
    }
}
