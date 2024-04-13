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
    Tracing_LeftFirst(TRACE_NONE);

    // 速度决策
    if (Image_isStraightLeft == true && Image_isStraightRight == true)
        Motor_target = MOTOR_STRAIGHT_SPEED;
    else 
        Motor_target = MOTOR_COMMON_SPEED;

    // 预瞄点配置
    State_AimJudge();

    // 十字检查
    if (Cross_Detect())
        return;

    // 右环岛检查
    if (Image_LptRight_Found == true && Image_LptLeft_Found == false && OVERALL_STATE == COMMON_ROAD)
    {
        OVERALL_STATE = CIRCLE;
        CIRCLE_STATE = CIRCLE_RIGHT_BEGIN;
    }
    // 左环岛检查
    else if (Image_LptRight_Found == false && Image_LptLeft_Found == true && OVERALL_STATE == COMMON_ROAD)
    {
        OVERALL_STATE = CIRCLE;
        CIRCLE_STATE = CIRCLE_LEFT_BEGIN;
    }
}