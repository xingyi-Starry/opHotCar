#ifndef CODE_OPHOT_IMAGE_SHOW_H_
#define CODE_OPHOT_IMAGE_SHOW_H_

#include "zf_common_headfile.h"
#include "opHotCar.h"

void Image_ShowLine(uint8 x, uint8 y);
void Image_ShowResampleLine(uint8 x, uint8 y);
void Image_ShowArray(uint8 x, uint8 y, uint8 height, float Array[], uint8 num, rgb565_color_enum Color);

#endif