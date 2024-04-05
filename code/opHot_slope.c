/*
 * opHot_slope.c
 *
 *  Created on: 2024年4月4日
 *      Author: 97329
 */
#include "opHot_slope.h"

SLOPE_STATE_enum SLOPE_STATE = SLOPE_RUNNING;

/**
 * @brief 坡道检测
 * @note  主要通过陀螺仪，当车头向上旋转时判定为坡道
 * 
 */
void Slope_Detect(void)
{
    if (fabs(Gyro_corrY) >= 35)
    {
        Encoder_End(ENCODER_MOTOR_1);
        Encoder_End(ENCODER_MOTOR_2);
        Encoder_Clear(ENCODER_MOTOR_1);
        Encoder_Clear(ENCODER_MOTOR_2);
        Gyroscope_End(GYROSCOPE_GYRO_Z);
        Gyroscope_Clear(GYROSCOPE_GYRO_Z);

        Encoder_Begin(ENCODER_MOTOR_1);
        OVERALL_STATE = SLOPE;
        SLOPE_STATE = SLOPE_RUNNING;
    }
}

void Slope_Check(void)
{
    // 配置预瞄点
    State_AimJudge();
    // 配置跟踪模式
    Tracing_LeftFirst(TRACE_NONE);

    // 行驶一定距离后退出坡道状态
    if (Encoder_sum_Motor1 >= SLOPE_RUNNING_ENCODER_THRE)
    {
        Encoder_End(ENCODER_MOTOR_1);
        Encoder_Clear(ENCODER_MOTOR_1);
        OVERALL_STATE = COMMON_ROAD;
    }
}


