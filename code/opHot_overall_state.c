/*
 * opHot_overall_state.c
 *
 *  Created on: 2024年3月21日
 *      Author: 97329
 */
#include "opHot_overall_state.h"

OVERALL_STATE_enum OVERALL_STATE = START;

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
    case START:
        Start_Check();
        break;
    case TEST:
        Gyroscope_Begin(GYROSCOPE_GYRO_Z);
        TRACE_TYPE = TRACE_GYRO;
        break;

    default:
        break;
    }

    // 斑马线检测
    if (OVERALL_STATE != START)
        CrossLine_Detect();
    // 坡道检测
    if (OVERALL_STATE != SLOPE && OVERALL_STATE != CROSSLINE && OVERALL_STATE != START)
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

void Start_Check(void)
{
    // 跟踪边线选择
    if (Image_LeftLine_Lost == 0)
        TRACE_TYPE = TRACE_LEFT_MIDLINE;
    else if (Image_RightLine_Lost == 0)
        TRACE_TYPE = TRACE_RIGHT_MIDLINE;
    else
        TRACE_TYPE = TRACE_NONE;

    // 速度决策
    Motor_target = MOTOR_START_SPEED;

    // 预瞄点配置
    State_AimJudge();
    // 开始编码器积分
    Encoder_Begin(ENCODER_MOTOR_1);
    // 行驶固定距离，越过斑马线后退出
    if (Encoder_sum_Motor1 >= START_ENCODER_THRE)
    {
        // 结束编码器积分并清零
        Encoder_Clear(ENCODER_MOTOR_1);
        Encoder_End(ENCODER_MOTOR_1);
        OVERALL_STATE = COMMON_ROAD;
    }
}
