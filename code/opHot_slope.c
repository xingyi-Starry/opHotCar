/*
 * opHot_slope.c
 *
 *  Created on: 2024��4��4��
 *      Author: 97329
 */
#include "opHot_slope.h"

SLOPE_STATE_enum SLOPE_STATE = SLOPE_RUNNING;

/**
 * @brief �µ����
 * @note  ��Ҫͨ�������ǣ�����ͷ������תʱ�ж�Ϊ�µ�
 * 
 */
void Slope_Detect(void)
{
    if (fabs(Gyro_corrY) >= 35)
    {
        Encoder_End(ENCODER_MOTOR_1);
        Encoder_End(ENCODER_MOTOR_2);
        Encoder_Clear(ENCODER_MOTOR_1);
        Encoder_Clear(ENCODER_MOTOR_2);
        Gyroscope_End(GYROSCOPE_GYRO_Z);
        Gyroscope_Clear(GYROSCOPE_GYRO_Z);

        Encoder_Begin(ENCODER_MOTOR_1);
        OVERALL_STATE = SLOPE;
        SLOPE_STATE = SLOPE_RUNNING;
    }
}

void Slope_Check(void)
{
    // ����Ԥ���
    State_AimJudge();
    // ���ø���ģʽ
    Tracing_LeftFirst(TRACE_NONE);

    // ��ʻһ��������˳��µ�״̬
    if (Encoder_sum_Motor1 >= SLOPE_RUNNING_ENCODER_THRE)
    {
        Encoder_End(ENCODER_MOTOR_1);
        Encoder_Clear(ENCODER_MOTOR_1);
        OVERALL_STATE = COMMON_ROAD;
    }
}


