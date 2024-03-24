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
    // 配置预瞄点
    tracing_aim = TRACE_COMMON_AIM;

    switch (CIRCLE_STATE)
    {
    case CIRCLE_RIGHT_BEGIN:
        // 跟踪边线选择
        if (Image_LeftLine_Lost == 0)
            TRACE_TYPE = TRACE_LEFT_MIDLINE;
        else if (Image_RightLine_Lost == 0)
            TRACE_TYPE = TRACE_RIGHT_MIDLINE;
        else
            TRACE_TYPE = TRACE_NONE;
        // 如果检测到第二个角点，切换到十字
        if (Image_LptLeft_Found == true && Image_LptRight_Found == true)
        {
            CIRCLE_STATE = CIRCLE_NONE;
            OVERALL_STATE = CROSS;
            CROSS_STATE = CROSS_ENTER;
        }
        // 如果角点接近或者角点消失，切换到CIRCLE_IN1
        if (Image_rptsRights[Image_LptRight_rptsRights_id][1] >= CIRCLE_BEGIN_CORNER_EDGE_DIST || (Image_LptLeft_Found == false && Image_LptRight_Found == false))
        {
            // 启动编码器积分
            Encoder_Begin(ENCODER_MOTOR_1);

            CIRCLE_STATE = CIRCLE_RIGHT_IN1;
        }
        break;

    case CIRCLE_RIGHT_IN1:
        // 跟踪边线选择 只跟左线
        if (Image_LeftLine_Lost == 0)
            TRACE_TYPE = TRACE_LEFT_MIDLINE;
        else
            TRACE_TYPE = TRACE_NONE;
        // 如果检测到第二个角点，切换到十字
        if (Image_LptLeft_Found == true && Image_LptRight_Found == true)
        {
            CIRCLE_STATE = CIRCLE_NONE;
            OVERALL_STATE = CROSS;
            CROSS_STATE = CROSS_ENTER;
        }
        // 行驶固定距离后进入CIRCLE_IN2
        if (Encoder_sum_Motor1 >= CIRCLE_IN1_ENCODER_THRE)
        {
            // 重置编码器积分
            Encoder_Clear(ENCODER_MOTOR_1);

            CIRCLE_STATE = CIRCLE_RIGHT_IN2;
        }
        break;

    case CIRCLE_RIGHT_IN2:
        // 跟踪边线选择 只跟右线
        if (Image_RightLine_Lost == 0)
            TRACE_TYPE = TRACE_RIGHT_MIDLINE;
        else
            TRACE_TYPE = TRACE_NONE;
        // 行驶固定距离后进入CIRCLE_RUNNING
        if (Encoder_sum_Motor1 >= CIRCLE_IN2_ENCODER_THRE)
        {
            // 结束编码器积分
            Encoder_End(ENCODER_MOTOR_1);
            Encoder_Clear(ENCODER_MOTOR_1);

            CIRCLE_STATE = CIRCLE_RIGHT_RUNNING;
        }
        break;

    case CIRCLE_RIGHT_RUNNING:
        // 跟踪边线选择
        if (Image_LeftLine_Lost == 0)
            TRACE_TYPE = TRACE_LEFT_MIDLINE;
        else if (Image_RightLine_Lost == 0)
            TRACE_TYPE = TRACE_RIGHT_MIDLINE;
        else
            TRACE_TYPE = TRACE_NONE;
        // 左角点接近时进入CIRCLE_OUT1
        if (Image_LptLeft_Found == true && Image_rptsRights[Image_LptRight_rptsRights_id][1] >= CIRCLE_RUNNING_CORNER_EDGE_DIST)
        {
            CIRCLE_STATE = CIRCLE_RIGHT_OUT1;
        }
        break;

    case CIRCLE_RIGHT_OUT1:
        // 跟踪边线选择 只跟右线
        /*
        if (Image_RightLine_Lost == 0)
            TRACE_TYPE = TRACE_RIGHT_MIDLINE;
        else
            TRACE_TYPE = TRACE_NONE;
            */
        // 先开环控制，闭环暂时丢线
        TRACE_TYPE = TRACE_NONE;
        // 发现左线为直线时进入CIRCLE_OUT2
        if (Image_isStraightLeft == true)
        {
            Encoder_Begin(ENCODER_MOTOR_1);

            CIRCLE_STATE = CIRCLE_RIGHT_OUT2;
        }
        break;
    
    case CIRCLE_RIGHT_OUT2:
        // 跟踪边线选择 只跟左线
        if (Image_LeftLine_Lost == 0)
            TRACE_TYPE = TRACE_LEFT_MIDLINE;
        else
            TRACE_TYPE = TRACE_NONE;
        break;
        // 行驶固定距离后切出环岛状态
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
}