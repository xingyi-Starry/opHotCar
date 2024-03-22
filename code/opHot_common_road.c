#include "opHot_common_road.h"
/*
 * opHot_common_road.c
 *
 *  Created on: 2024年3月21日
 *      Author: 97329
 */

void CommonRoad_Check(void)
{
    // 跟踪边线选择
    if (Image_LeftLine_Lost == 1)
        TRACE_TYPE = TRACE_RIGHT_MIDLINE;
    else
        TRACE_TYPE = TRACE_LEFT_MIDLINE;
    // 预瞄点配置
    tracing_aim = 25;

    //
    if (Image_LptLeft_Found == true && Image_LptRight_Found == true)
    {
        // 角点二次检查，暂时搁置
        /*code*/
        OVERALL_STATE = CROSS;
        CROSS_STATE = CROSS_ENTER;
    }
}