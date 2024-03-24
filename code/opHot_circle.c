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
    switch (CIRCLE_STATE)
    {
    case CIRCLE_NONE:
        // 启动编码器积分，准备二次检查
        Encoder_Begin(Encoder_sum_Motor1);
        // 检测是否为左环岛
        if (Image_LptLeft_Found == true && Image_LptRight_Found == false)
        {
            CIRCLE_STATE = CIRCLE_LEFT_BEGIN;
        }
        // 检测是否为右环岛
        else if (Image_LptLeft_Found == false && Image_LptRight_Found == true)
        {
            CIRCLE_STATE =CIRCLE_RIGHT_BEGIN;
        }
        else // wtf???
        {
            Encoder_End(Encoder_sum_Motor1);
            Encoder_Clear(Encoder_sum_Motor1);
            OVERALL_STATE = COMMON_ROAD;
        }
        break;
    
    default:
        break;
    }
}