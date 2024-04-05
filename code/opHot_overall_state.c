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
    case CROSSLINE:
        CrossLine_Check();
        break;
    case SLOPE:
        Slope_Check();
        break;
    case TEST:
        Gyroscope_Begin(GYROSCOPE_GYRO_Z);
        TRACE_TYPE = TRACE_GYRO;
        break;

    default:
        break;
    }

    // �����߼��
    CrossLine_Detect();
    // �µ����
    if (OVERALL_STATE != SLOPE && OVERALL_STATE != CROSSLINE)
        Slope_Detect();
}

void State_AimJudge(void)
{
    if (TRACE_TYPE == TRACE_LEFT_MIDLINE)
    {
        // ������ת��Ԥ��
        if (Image_LeftDir == 1)
            tracing_aim = TRACE_CLOSE_AIM;
        else
            tracing_aim = TRACE_COMMON_AIM;
    }
    else if (TRACE_TYPE == TRACE_RIGHT_MIDLINE)
    {
        // ������ת��Ԥ��
        if (Image_RightDir == 2)
            tracing_aim = TRACE_CLOSE_AIM;
        else
            tracing_aim = TRACE_COMMON_AIM;
    }
}
