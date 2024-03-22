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
    // 截断边线，防止巡出十字
    Image_LineCut();

    // 跟踪边线选择
    if (Image_LeftLine_Lost == 1)
        TRACE_TYPE = TRACE_RIGHT_MIDLINE;
    else
        TRACE_TYPE = TRACE_LEFT_MIDLINE;

    switch (CROSS_STATE)
    {
    case CROSS_ENTER:
        // 预瞄点配置
        tracing_aim = 20;

        // 前角点接近时切换到CROSS_EXIT
        if ((Image_rptsLefts[Image_LptLeft_rptsLefts_id][1] + Image_rptsRights[Image_LptRight_rptsRights_id][1]) / 2 <= CROSS_ENTER_CORNER_EDGE_DIST)
        {
            CROSS_STATE = CROSS_EXIT;
        }
        break;
    case CROSS_EXIT:
        /**切换到反向巡线模式，见image_process()**/
        // 预瞄点配置
        tracing_aim = 5;

        // 后角点接近时切出CROSS_EXIT
        if ((Image_rptsLefts[Image_LptLeft_rptsLefts_id][1] + Image_rptsRights[Image_LptRight_rptsRights_id][1]) / 2 <= CROSS_EXIT_CORNER_EDGE_DIST)
        {
            CROSS_STATE = CROSS_ENTER;         // 状态机复位
            OVERALL_STATE = COMMON_ROAD;       // 退出十字状态机
        }
        break;
    default:
        break;
    }
}
