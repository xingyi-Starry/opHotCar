#include "opHot_image_show.h"
#include "opHotCar.h"

void Image_ShowLine(uint8 x, uint8 y)
{
    for (uint8 i = 0; i < Image_rptsLeftsNum; i++)
    {
        ips200_draw_point(x + Image_rptsLefts[i][0], y + Image_rptsLefts[i][1], RGB565_GREEN);
        ips200_draw_point(x + Image_rptsRights[i][0], y + Image_rptsRights[i][1], RGB565_RED);
    }
}