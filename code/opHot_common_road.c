#include "opHot_common_road.h"
/*
 * opHot_common_road.c
 *
 *  Created on: 2024年3月21日
 *      Author: 97329
 */

void CommonRoad_Check(void)
{
    if (Image_LptLeft_Found == true && Image_LptRight_Found == true)
    {
        // 角点二次检查，暂时搁置
        OVERALL_STATE = CROSS;
    }
}