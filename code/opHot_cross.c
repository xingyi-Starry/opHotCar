/*
 * opHot_cross.c
 *
 *  Created on: 2024��3��21��
 *      Author: 97329
 */
#include "opHot_cross.h"

CROSS_STATE_enum CROSS_STATE = CROSS_ENTER;

void Cross_Check(void)
{
    // �ضϱ��ߣ���ֹѲ��ʮ��
    Image_LineCut();

    // ���ٱ���ѡ��
    if (Image_LeftLine_Lost == 1)
        TRACE_TYPE = TRACE_RIGHT_MIDLINE;
    else
        TRACE_TYPE = TRACE_LEFT_MIDLINE;

    switch (CROSS_STATE)
    {
    case CROSS_ENTER:
        // Ԥ�������
        tracing_aim = 20;

        // ǰ�ǵ�ӽ�ʱ�л���CROSS_EXIT
        if ((Image_rptsLefts[Image_LptLeft_rptsLefts_id][1] + Image_rptsRights[Image_LptRight_rptsRights_id][1]) / 2 <= CROSS_ENTER_CORNER_EDGE_DIST)
        {
            CROSS_STATE = CROSS_EXIT;
        }
        break;
    case CROSS_EXIT:
        /**�л�������Ѳ��ģʽ����image_process()**/
        // Ԥ�������
        tracing_aim = 5;

        // ��ǵ�ӽ�ʱ�г�CROSS_EXIT
        if ((Image_rptsLefts[Image_LptLeft_rptsLefts_id][1] + Image_rptsRights[Image_LptRight_rptsRights_id][1]) / 2 <= CROSS_EXIT_CORNER_EDGE_DIST)
        {
            CROSS_STATE = CROSS_ENTER;         // ״̬����λ
            OVERALL_STATE = COMMON_ROAD;       // �˳�ʮ��״̬��
        }
        break;
    default:
        break;
    }
}
