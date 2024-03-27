/*
 * opHot_tracing.c
 *
 *  Created on: 2024��3��19��
 *      Author: 97329
 */

#include "opHot_tracing.h"

float Err;
const uint8 tracing_weigh[3] = {5, 3, 2};  // Ŀ�����Ȩ��
TRACE_TYPE_enum TRACE_TYPE = TRACE_LEFT_MIDLINE; // ����������Դ����״̬������
uint8 tracing_aim = 15;                    // Ԥ��������ߵ�λ��
uint8 trace_central = TRACE_CENTRAL;
uint16 trace_kde = TRACE_KDE;
uint8 length_of_car = LENGTH_OF_CAR;

/**
 * @brief   ��ȡ���PIDĿ��ֵ
 * @note    Ŀ��ֵΪԤ����Լ�Ԥ���+1��Ԥ���+2�ļ�Ȩƽ����Ȩ�ؼ�����tracing_weigh
 * @note    ���ݴ������㷨ǰ��ƫ��delta_angle = arctan(2Lsin(theta)/len_ahead)������LΪ������࣬thetaΪĿ������ǰ���нǣ�len_aheadΪĿ�굽�������
 * @note    ���ƿɵ�delta_angle = k * err / (length_of_car + row_of_aim) (��Űɣ��Ҹо���-linnuofan-2024/3/20)
 *
 */
void Tracing_GetTarget(void)
{
    // ͼ���Ȩ���
    Err = (float)(Image_MidLine[bf_clip(tracing_aim, 0, Image_MidLineNum - 1)][0] * tracing_weigh[0] + Image_MidLine[bf_clip(tracing_aim + 1, 0, Image_MidLineNum - 1)][0] * tracing_weigh[1] + Image_MidLine[bf_clip(tracing_aim + 2, 0, Image_MidLineNum - 1)][0] * tracing_weigh[2]) / 10 - trace_central;
    // ����ӦĿ��ռ�ձ�
    Steer_target = STEER_MID - Err * trace_kde / (length_of_car + MT9V03X_H - Image_MidLine[bf_clip(tracing_aim, 0, Image_MidLineNum - 1)][1]);
    if (TRACE_TYPE == TRACE_NONE)
        Steer_target = STEER_MID;
    //    if (TRACE_TYPE == LEFT_MIDLINE)
    //    {
    //        Steer_target = (float)(Image_rptsLeftc[bf_clip(tracing_aim, 0, Image_rptsLeftcNum - 1)][0] * tracing_weigh[0] + Image_rptsLeftc[bf_clip(tracing_aim + 1, //0, Image_rptsLeftcNum - 1)][0] * tracing_weigh[1] + Image_rptsLeftc[bf_clip(tracing_aim + 2, 0, Image_rptsLeftcNum - 1)][0] * tracing_weigh[2]) / 10;
    //    }
    //    else if (TRACE_TYPE == RIGHT_MIDLINE)
    //    {
    //        Steer_target = (float)(Image_rptsRightc[bf_clip(tracing_aim, 0, Image_rptsLeftcNum - 1)][0] * tracing_weigh[0] + Image_rptsRightc[bf_clip(tracing_aim + //1, 0, Image_rptsLeftcNum - 1)][0] * tracing_weigh[1] + Image_rptsRightc[bf_clip(tracing_aim + 2, 0, Image_rptsLeftcNum - 1)][0] * tracing_weigh[2]) / 10;
    //    }
}

/**
 * @brief       �����㷨���к���
 * @attention   Ӧ���ڶ�ʱ�ж��У���ͼ�����ж�֮��
 *
 */
void Tracing_Work(void)
{
    Tracing_GetTarget();
    Steer_PIDwork();
}
