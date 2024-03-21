/*
 * opHot_overall_state.c
 *
 *  Created on: 2024年3月21日
 *      Author: 97329
 */
#include "opHot_overall_state.h"

OVERALL_STATE_enum OVERALL_STATE = COMMON_ROAD;

/**
 * @brief 全局状态机检查
 * @note  用于分情况检查不同状态机
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

