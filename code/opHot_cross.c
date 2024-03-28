/*
 * opHot_cross.c
 *
 *  Created on: 2024年3月21日
 *      Author: 97329
 */
#include "opHot_cross.h"

CROSS_STATE_enum CROSS_STATE = CROSS_ENTER;

void Cross_Check(void)
{
    // 跟踪边线选择
    if (Image_LeftLine_Lost == 0)
        TRACE_TYPE = TRACE_LEFT_MIDLINE;
    else if (Image_RightLine_Lost == 0)
        TRACE_TYPE = TRACE_RIGHT_MIDLINE;
    else
        TRACE_TYPE = TRACE_STATIC;

    switch (CROSS_STATE)
    {
    case CROSS_ENTER:
        // 预瞄点配置
        tracing_aim = TRACE_CLOSE_AIM;

        // 后角点接近或者干脆消失时切换到CROSS_EXIT
        if (Image_rptsLefts[Image_LptLeft_rptsLefts_id][1] >= CROSS_ENTER_CORNER_EDGE_DIST || Image_rptsRights[Image_LptRight_rptsRights_id][1] >= CROSS_ENTER_CORNER_EDGE_DIST || (Image_LptLeft_Found == false && Image_LptRight_Found == false))
        {
            CROSS_STATE = CROSS_EXIT;
            Encoder_Begin(ENCODER_MOTOR_1); // 开始编码器积分，开环控制
        }
        break;
        /*暂时无效的状态*/
    case CROSS_RUNNING:
        /**切换到斜向巡线模式，见image_process()**/
        // 预瞄点配置
        tracing_aim = 5;

        // 前角点消失时切入CROSS_EXIT
        if (Image_LptLeft_Found == false && Image_LptRight_Found == false)
        {
            // 结束斜向巡线，具体见Image_Process()
            CROSS_STATE = CROSS_EXIT;
        }
        break;
    case CROSS_EXIT:
        // 巡前线
        image_begin_y = 30;
        // 预瞄点配置
        tracing_aim = TRACE_CROSS_AIM;

        // 行驶固定距离后退出CROSS_EXIT
        if (Encoder_sum_Motor1 >= CROSS_EXIT_ENCODER_THRE)
        {
            // 恢复巡线起点
            image_begin_y = IMAGE_HEIGHT - 20;
            // 结束积分，清除积分数据
            Encoder_End(ENCODER_MOTOR_1);
            Encoder_Clear(ENCODER_MOTOR_1);
            // CROSS状态机复位，退出CROSS
            CROSS_STATE = CROSS_ENTER;
            OVERALL_STATE = COMMON_ROAD;
        }
        break;
    default:
        break;
    }
}
