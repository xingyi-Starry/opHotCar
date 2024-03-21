/*
 * opHot_overall_state.c
 *
 *  Created on: 2024��3��21��
 *      Author: 97329
 */
#include "opHot_overall_state.h"

OVERALL_STATE_enum OVERALL_STATE = COMMON_ROAD;

/**
 * @brief ȫ��״̬�����
 * @note  ���ڷ������鲻ͬ״̬��
 * 
 */
void State_Check(void)
{
    switch (OVERALL_STATE)
    {
    case COMMON_ROAD:
        CommonRoad_Check();
        break;
    case CROSS:
        Cross_Check();
        break;
    case CIRCLE:
        Circle_Check();
        break;
    
    default:
        break;
    }
}

