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
    if (Image_LeftLine_Lost == 1)
        TRACE_TYPE = TRACE_RIGHT_MIDLINE;
    else
        TRACE_TYPE = TRACE_LEFT_MIDLINE;
    // Ԥ�������
    tracing_aim = 25;

    //
    if (Image_LptLeft_Found == true && Image_LptRight_Found == true)
    {
        // �ǵ���μ�飬��ʱ����
        /*code*/
        OVERALL_STATE = CROSS;
        CROSS_STATE = CROSS_ENTER;
    }
}