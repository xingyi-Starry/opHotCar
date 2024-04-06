/*
 * opHot_overall_state.c
 *
 *  Created on: 2024��3��21��
 *      Author: 97329
 */
#include "opHot_overall_state.h"

OVERALL_STATE_enum OVERALL_STATE = START;

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
    case START:
        Start_Check();
        break;
    case TEST:
        Gyroscope_Begin(GYROSCOPE_GYRO_Z);
        TRACE_TYPE = TRACE_GYRO;
        break;

    default:
        break;
    }

    // �����߼��
    if (OVERALL_STATE != START)
        CrossLine_Detect();
    // �µ����
    if (OVERALL_STATE != SLOPE && OVERALL_STATE != CROSSLINE && OVERALL_STATE != START)
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

void Start_Check(void)
{
    // ���ٱ���ѡ��
    if (Image_LeftLine_Lost == 0)
        TRACE_TYPE = TRACE_LEFT_MIDLINE;
    else if (Image_RightLine_Lost == 0)
        TRACE_TYPE = TRACE_RIGHT_MIDLINE;
    else
        TRACE_TYPE = TRACE_NONE;

    // �ٶȾ���
    Motor_target = MOTOR_START_SPEED;

    // Ԥ�������
    State_AimJudge();
    // ��ʼ����������
    Encoder_Begin(ENCODER_MOTOR_1);
    // ��ʻ�̶����룬Խ�������ߺ��˳�
    if (Encoder_sum_Motor1 >= START_ENCODER_THRE)
    {
        // �������������ֲ�����
        Encoder_Clear(ENCODER_MOTOR_1);
        Encoder_End(ENCODER_MOTOR_1);
        OVERALL_STATE = COMMON_ROAD;
    }
}
