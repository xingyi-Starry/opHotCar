/*
 * opHot_crossline.c
 *
 *  Created on: 2024��3��28��
 *      Author: 97329
 */

#include "opHot_crossline.h"

CROSSLINE_STATE_enum CROSSLINE_STATE = CROSSLINE_RUNNING;
uint8 CrossLine_value = 0;
uint8 CrossLine_ChangeCount = 0;
bool isWhite = true;
uint8 current_grey;
/**
 * @brief �����߼��
 * @note  ͨ��ɨ��(64, 50)��(124, 50)һ�����ϵĵ㣬���ڰ׵���Ŀ��Լ1:1ʱ���ж�Ϊ��⵽������
 * @attention ����ֱ��ɨ�裬��ֹ����
 *
 */
void CrossLine_Detect(void)
{
    for (uint8 r = 0; r < 40; r += 10)
    {
        CrossLine_ChangeCount = 0;
        for (uint8 i = 64; i <= 124; i += 2)
        {
            current_grey = IMAGE_AT(mt9v03x_image, i, 50 + r);
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
        {
            OVERALL_STATE = CROSSLINE;
            CROSSLINE_STATE = CROSSLINE_RUNNING;
            Encoder_Begin(ENCODER_MOTOR_1);
            return;
        }
    }
    CrossLine_value = CrossLine_ChangeCount;
}

/**
 * @brief ������
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
        // ͣ��
        Motor1_target = 0;
        Motor2_target = 0;
        break;
    default:
        break;
    }
}
