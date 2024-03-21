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
    switch (CROSS_STATE)
    {
    case CROSS_ENTER:
        Image_LineCut();
        if ((Image_rptsLefts[Image_LptLeft_rptsLefts_id][1] + Image_rptsRights[Image_LptRight_rptsRights_id][1]) / 2 <= CROSS_ENTER_CORNER_EDGE_DIST)
        {
            CROSS_STATE = CROSS_EXIT;
        }
        break;
    case CROSS_EXIT:
        if ((Image_rptsLefts[Image_LptLeft_rptsLefts_id][1] + Image_rptsRights[Image_LptRight_rptsRights_id][1]) / 2 <= CROSS_EXIT_CORNER_EDGE_DIST)
        {
            CROSS_STATE = CROSS_ENTER;      // ״̬����λ
            OVERALL_STATE = COMMON_ROAD;    // �˳�ʮ��״̬��
        }
        break;
    default:
        break;
    }
}




