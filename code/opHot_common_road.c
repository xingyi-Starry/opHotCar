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
    if (Image_LeftLine_Lost == 0)
        TRACE_TYPE = TRACE_LEFT_MIDLINE;
    else if (Image_RightLine_Lost == 0)
        TRACE_TYPE = TRACE_RIGHT_MIDLINE;
    else
        TRACE_TYPE = TRACE_NONE;

    // 预瞄点配置
    if (Image_isStraightLeft == false || Image_isStraightRight == false)
        tracing_aim = TRACE_COMMON_AIM; // 弯道远预瞄
    else
        tracing_aim = TRACE_CLOSE_AIM;  // 直道近预瞄

    // 十字检查
    if (Image_LptLeft_Found == true && Image_LptRight_Found == true && OVERALL_STATE == COMMON_ROAD)
    {
        // 角点二次检查，暂时搁置
        /*code*/
        OVERALL_STATE = CROSS;
        CROSS_STATE = CROSS_ENTER;
    }

    // 环岛检查
    /*
    if (Image_LptLeft_Found == true || Image_LptRight_Found == true && OVERALL_STATE == COMMON_ROAD)
    {
        OVERALL_STATE = CIRCLE;
        CIRCLE_STATE = CIRCLE_NONE;
        Circle_Check();
    }*/
}