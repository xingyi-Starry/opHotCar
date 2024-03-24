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
    if (Image_isStraightLeft == false || Image_isStraightRight == false)
        tracing_aim = TRACE_COMMON_AIM; // ���ԶԤ��
    else
        tracing_aim = TRACE_CLOSE_AIM;  // ֱ����Ԥ��

    // ʮ�ּ��
    if (Image_LptLeft_Found == true && Image_LptRight_Found == true && OVERALL_STATE == COMMON_ROAD)
    {
        // �ǵ���μ�飬��ʱ����
        /*code*/
        OVERALL_STATE = CROSS;
        CROSS_STATE = CROSS_ENTER;
    }

    // �������
    /*
    if (Image_LptLeft_Found == true || Image_LptRight_Found == true && OVERALL_STATE == COMMON_ROAD)
    {
        OVERALL_STATE = CIRCLE;
        CIRCLE_STATE = CIRCLE_NONE;
        Circle_Check();
    }*/
}