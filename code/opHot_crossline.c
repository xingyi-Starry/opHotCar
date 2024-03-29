/*
 * opHot_crossline.c
 *
 *  Created on: 2024年3月28日
 *      Author: 97329
 */

#include "opHot_crossline.h"

CROSSLINE_STATE_enum CROSSLINE_STATE = CROSSLINE_RUNNING;
uint8 CrossLine_RowCount = 0;
uint8 CrossLine_ChangeCount = 0;
bool isWhite = true;
uint8 actual_grey;
uint8 current_grey;
uint8 last_grey;
uint8 llast_grey;

/**
 * @brief 斑马线检测
 * @note  通过扫描(64, 50)到(124, 50)一条线上的点，当黑白点数目大约1:1时即判断为检测到斑马线
 * @attention 仅在直道扫描，防止误判
 *
 */
void CrossLine_Detect(void)
{
    CrossLine_RowCount = 0;
    for (uint8 r = 0; r < 5; r++)
    {
        CrossLine_ChangeCount = 0;
        for (uint8 i = 64; i <= 124; i += 2)
        {
            llast_grey = last_grey;
            last_grey = current_grey;
            current_grey = IMAGE_AT(mt9v03x_image[0], i, 50 + i);
            actual_grey = (uint8)((float)current_grey * 0.5 + (float)last_grey * 0.3 + (float)llast_grey * 0.2);
            if (isWhite && current_grey < image_thre)
            {
                isWhite = false;
                CrossLine_ChangeCount++;
            }
            else if (!isWhite && current_grey >= image_thre)
            {
                isWhite = true;
                CrossLine_ChangeCount++;
            }
        }
        if (CrossLine_ChangeCount > CROSSLINE_RUNNING_CHANGE_THRE)
            CrossLine_RowCount++;
    }
    // 当5行中不少于3行检测到斑马线特征即判定为检测到斑马线
    if (CrossLine_RowCount >= 3)
    {
        OVERALL_STATE = CROSSLINE;
        CROSSLINE_STATE = CROSSLINE_RUNNING;
        Encoder_Begin(ENCODER_MOTOR_1);
    }
}

/**
 * @brief 斑马线
 *
 */
void CrossLine_Check(void)
{
    switch (CROSSLINE_STATE)
    {
    case CROSSLINE_RUNNING:
        Tracing_LeftFirst(TRACE_NONE);
        if (Encoder_sum_Motor1 > CROSSLINE_RUNNING_ENCODER_THRE)
        {
            Encoder_Clear(ENCODER_MOTOR_1);
            Encoder_End(ENCODER_MOTOR_1);
            CROSSLINE_STATE = CROSSLINE_END;
        }
        break;

    case CROSSLINE_END:
        // 停车
        Motor1_target = 0;
        Motor2_target = 0;
        break;
    default:
        break;
    }
}
