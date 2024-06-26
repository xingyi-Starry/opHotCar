#include "opHot_circle.h"
/*
 * opHot_circle.c
 *
 *  Created on: 2024年3月21日
 *      Author: 97329
 */
#include "opHot_circle.h"

CIRCLE_STATE_enum CIRCLE_STATE = CIRCLE_NONE;

void Circle_Check(void)
{
    // 速度决策缺省值
    Motor_target = MOTOR_COMMON_SPEED;

    switch (CIRCLE_STATE)
    {
    case CIRCLE_LEFT_BEGIN:
        // 跟踪边线选择 优先外线
        Tracing_OuterFirst(TRACE_NONE);
        // 速度决策
        Motor_target = MOTOR_COMMON_SPEED;
        // 如果检测到第二个角点，切换到十字
        if (Cross_Detect())
            return;
        // 如果角点接近或者角点消失，切换到CIRCLE_IN
        if (Image_rptsLefts[Image_LptLeft_rptsLefts_id][1] >= CIRCLE_BEGIN_CORNER_EDGE_DIST || (Image_LptLeft_Found == false && Image_LptRight_Found == false))
        {
            // 启动编码器积分
            Encoder_Begin(ENCODER_MOTOR_2);

            CIRCLE_STATE = CIRCLE_LEFT_IN;
        }
        break;

    case CIRCLE_LEFT_IN:
        // 跟踪边线选择 优先左线
        Tracing_LeftFirst(TRACE_NONE);
        // 若左线丢线则巡线中心左移以找左线 暂略
        if (Image_LeftLine_Lost == 1)
            trace_central = TRACE_CENTRAL;
        else
            trace_central = TRACE_CENTRAL;
        // 速度决策
        Motor_target = MOTOR_CIRCLE_IN_SPEED;
        // 如果检测到第二个角点，切换到十字
        if (Cross_Detect())
            return;
        // 编码器积分超过阈值，切换到CIRCLE_RUNNING
        if (Encoder_sum_Motor2 >= CIRCLE_IN_ENCODER_THRE)
        {
            // 重置编码器积分
            Encoder_Clear(ENCODER_MOTOR_2);
            // 开始陀螺仪积分
            Gyroscope_Begin(GYROSCOPE_GYRO_Z);
            // 配置圆环专属跟踪系数
            trace_factor = TRACE_FACTOR_CIRCLE;

            CIRCLE_STATE = CIRCLE_LEFT_RUNNING;
        }
        break;

    case CIRCLE_LEFT_RUNNING:
        // 跟踪边线选择 优先左线
        Tracing_LeftFirst(TRACE_STATIC);
        // 若左线丢线则巡线中心左移以找左线
        if (Image_LeftLine_Lost == 1)
            trace_central = TRACE_CENTRAL;
        else
            trace_central = TRACE_CENTRAL;
        // 速度决策
        Motor_target = MOTOR_CIRCLE_RUNNING_SPEED;
        // 如果检测到第二个角点，切换到十字
        if (Cross_Detect())
        {
            trace_factor = TRACE_FACTOR_COMMON;
            return;
        }
        // 陀螺仪积分超过阈值或编码器积分超过阈值，切换到CIRCLE_OUT1
        if (Gyro_z >= CIRCLE_RUNNING_GYRO_THRE || Encoder_sum_Motor2 >= CIRCLE_RUNNING_ENCODER_THRE)
        {
            Encoder_Clear(ENCODER_MOTOR_2);
            // 结束编码器积分
            Gyroscope_Clear(GYROSCOPE_GYRO_Z);
            Gyroscope_End(GYROSCOPE_GYRO_Z);

            trace_factor = TRACE_FACTOR_COMMON;

            CIRCLE_STATE = CIRCLE_LEFT_OUT;
        }
        // 直道积分超过阈值，直接切至COMMON_ROAD
        if (Encoder_sum_Straight >= CIRCLE_RUNNING_ENCODER_S_THRE)
        {
            // 结束并清零各积分
            Encoder_Clear(ENCODER_MOTOR_2);
            Encoder_End(ENCODER_MOTOR_2);
            Gyroscope_Clear(GYROSCOPE_GYRO_Z);
            Gyroscope_End(GYROSCOPE_GYRO_Z);

            trace_factor = TRACE_FACTOR_COMMON;

            OVERALL_STATE = COMMON_ROAD;
            CIRCLE_STATE = CIRCLE_NONE;
        }
        break;

    case CIRCLE_LEFT_OUT:
        // 跟踪边线选择 只巡右线
        Tracing_RightOnly(TRACE_NONE);
        // 速度决策
        Motor_target = MOTOR_COMMON_SPEED;
        // 编码器积分超过阈值，结束CIRCLE状态
        if (Encoder_sum_Motor2 >= CIRCLE_OUT2_ENCODER_THRE)
        {
            Encoder_End(ENCODER_MOTOR_2);
            Encoder_Clear(ENCODER_MOTOR_2);

            CIRCLE_STATE = CIRCLE_NONE;
            OVERALL_STATE = COMMON_ROAD;
        }
        break;

    case CIRCLE_RIGHT_BEGIN:
        // 跟踪边线选择 优先外线
        Tracing_OuterFirst(TRACE_NONE);
        // 速度决策
        Motor_target = MOTOR_COMMON_SPEED;
        // 如果检测到第二个角点，切换到十字
        if (Cross_Detect())
            return;
        // 如果角点接近或者角点消失，切换到CIRCLE_IN
        if (Image_rptsRights[Image_LptRight_rptsRights_id][1] >= CIRCLE_BEGIN_CORNER_EDGE_DIST || (Image_LptLeft_Found == false && Image_LptRight_Found == false))
        {
            // 启动编码器积分
            Encoder_Begin(ENCODER_MOTOR_1);

            CIRCLE_STATE = CIRCLE_RIGHT_IN;
        }
        break;

    case CIRCLE_RIGHT_IN:
        // 跟踪边线选择 优先右线
        Tracing_RightFirst(TRACE_NONE);
        // 若右线丢线则巡线中心右移以找右线
        if (Image_RightLine_Lost == 1)
            trace_central = TRACE_CENTRAL;
        else
            trace_central = TRACE_CENTRAL;
        // 速度决策
        Motor_target = MOTOR_CIRCLE_IN_SPEED;
        // 如果检测到第二个角点，切换到十字
        if (Cross_Detect())
            return;
        // 编码器积分超过阈值，切换到CIRCLE_RUNNING
        if (Encoder_sum_Motor1 >= CIRCLE_IN_ENCODER_THRE)
        {
            // 重置编码器积分
            Encoder_Clear(ENCODER_MOTOR_1);
            // 开始陀螺仪积分
            Gyroscope_Begin(GYROSCOPE_GYRO_Z);
            // 配置圆环专属跟踪系数
            trace_factor = TRACE_FACTOR_CIRCLE;

            CIRCLE_STATE = CIRCLE_RIGHT_RUNNING;
        }
        break;

    case CIRCLE_RIGHT_RUNNING:
        // 跟踪边线选择 优先右线
        Tracing_RightFirst(TRACE_STATIC);
        // 若右线丢线则巡线中心右移以找右线
        if (Image_RightLine_Lost == 1)
            trace_central = TRACE_CENTRAL;
        else
            trace_central = TRACE_CENTRAL;
        // 速度决策
        Motor_target = MOTOR_CIRCLE_RUNNING_SPEED;
        // 如果检测到第二个角点，切换到十字
        if (Cross_Detect())
        {
            trace_factor = TRACE_FACTOR_COMMON;
            return;
        }
        // 陀螺仪积分超过阈值或编码器积分超过阈值，切换到CIRCLE_OUT1
        if (Gyro_z <= -CIRCLE_RUNNING_GYRO_THRE || Encoder_sum_Motor1 >= CIRCLE_RUNNING_ENCODER_THRE)
        {
            Encoder_Clear(ENCODER_MOTOR_1);
            // 结束编码器积分
            Gyroscope_Clear(GYROSCOPE_GYRO_Z);
            Gyroscope_End(GYROSCOPE_GYRO_Z);

            trace_factor = TRACE_FACTOR_COMMON;

            CIRCLE_STATE = CIRCLE_RIGHT_OUT;
        }
        // 直道积分超过阈值，直接切至COMMON_ROAD
        if (Encoder_sum_Straight >= CIRCLE_RUNNING_ENCODER_S_THRE)
        {
            // 结束并清零各积分
            Encoder_Clear(ENCODER_MOTOR_1);
            Encoder_End(ENCODER_MOTOR_1);
            Gyroscope_Clear(GYROSCOPE_GYRO_Z);
            Gyroscope_End(GYROSCOPE_GYRO_Z);

            trace_factor = TRACE_FACTOR_COMMON;

            OVERALL_STATE = COMMON_ROAD;
            CIRCLE_STATE = CIRCLE_NONE;
        }
        break;

    case CIRCLE_RIGHT_OUT:
        // 跟踪边线选择 只巡右线
        Tracing_LeftOnly(TRACE_NONE);
        // 速度决策
        Motor_target = MOTOR_COMMON_SPEED;
        // 编码器积分超过阈值，结束CIRCLE状态
        if (Encoder_sum_Motor1 >= CIRCLE_OUT2_ENCODER_THRE)
        {
            Encoder_End(ENCODER_MOTOR_1);
            Encoder_Clear(ENCODER_MOTOR_1);

            CIRCLE_STATE = CIRCLE_NONE;
            OVERALL_STATE = COMMON_ROAD;
        }
        break;

    default:
        break;
    }
    // 配置预瞄点
    State_AimJudge();
}