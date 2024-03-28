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
    if (Image_LeftLine_Lost == 0)
        TRACE_TYPE = TRACE_LEFT_MIDLINE;
    else if (Image_RightLine_Lost == 0)
        TRACE_TYPE = TRACE_RIGHT_MIDLINE;
    else
        TRACE_TYPE = TRACE_NONE;

    // Ԥ�������
    State_AimJudge();
    
    // ʮ�ּ��
    if (Image_LptLeft_Found == true && Image_LptRight_Found == true && OVERALL_STATE == COMMON_ROAD)
    {
        // �ǵ���μ�飬��ʱ����

        OVERALL_STATE = CROSS;
        CROSS_STATE = CROSS_ENTER;
    }

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