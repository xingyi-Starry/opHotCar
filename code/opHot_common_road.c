#include "opHot_common_road.h"
/*
 * opHot_common_road.c
 *
 *  Created on: 2024��3��21��
 *      Author: 97329
 */

void CommonRoad_Check(void)
{
    // ���ٱ���ѡ��
    Tracing_LeftFirst(TRACE_NONE);

    // �ٶȾ���
    if (Image_isStraightLeft == true && Image_isStraightRight == true)
        Motor_target = MOTOR_STRAIGHT_SPEED;
    else 
        Motor_target = MOTOR_COMMON_SPEED;

    // Ԥ�������
    State_AimJudge();

    // ʮ�ּ��
    if (Cross_Detect())
        return;

    // �һ������
    if (Image_LptRight_Found == true && Image_LptLeft_Found == false && OVERALL_STATE == COMMON_ROAD)
    {
        OVERALL_STATE = CIRCLE;
        CIRCLE_STATE = CIRCLE_RIGHT_BEGIN;
    }
    // �󻷵����
    else if (Image_LptRight_Found == false && Image_LptLeft_Found == true && OVERALL_STATE == COMMON_ROAD)
    {
        OVERALL_STATE = CIRCLE;
        CIRCLE_STATE = CIRCLE_LEFT_BEGIN;
    }
}