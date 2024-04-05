/*
 * opHot_overall_state.c
 *
 *  Created on: 2024年3月21日
 *      Author: 97329
 */
#include "opHot_overall_state.h"

OVERALL_STATE_enum OVERALL_STATE = COMMON_ROAD;

/**
 * @brief 全局状态机检查
 * @note  用于分情况检查不同状态机
 *
 */
void State_Check(void)
{
    switch (OVERALL_STATE)
    {
    case COMMON_ROAD:
        CommonRoad_Check();
        break;
    case CROSS:
        Cross_Check();
        break;
    case CIRCLE:
        Circle_Check();
        break;
    case CROSSLINE:
        CrossLine_Check();
        break;
    case SLOPE:
        Slope_Check();
        break;
    case TEST:
        Gyroscope_Begin(GYROSCOPE_GYRO_Z);
        TRACE_TYPE = TRACE_GYRO;
        break;

    default:
        break;
    }

    // 斑马线检测
    CrossLine_Detect();
    // 坡道检测
    if (OVERALL_STATE != SLOPE && OVERALL_STATE != CROSSLINE)
        Slope_Detect();
}

void State_AimJudge(void)
{
    if (TRACE_TYPE == TRACE_LEFT_MIDLINE)
    {
        // 左线左转近预瞄
        if (Image_LeftDir == 1)
            tracing_aim = TRACE_CLOSE_AIM;
        else
            tracing_aim = TRACE_COMMON_AIM;
    }
    else if (TRACE_TYPE == TRACE_RIGHT_MIDLINE)
    {
        // 右线右转近预瞄
        if (Image_RightDir == 2)
            tracing_aim = TRACE_CLOSE_AIM;
        else
            tracing_aim = TRACE_COMMON_AIM;
    }
}
