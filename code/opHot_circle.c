#include "opHot_circle.h"
/*
 * opHot_circle.c
 *
 *  Created on: 2024��3��21��
 *      Author: 97329
 */
#include "opHot_circle.h"

CIRCLE_STATE_enum CIRCLE_STATE = CIRCLE_NONE;

void Circle_Check(void)
{
    // ����Ԥ���
    State_AimJudge();

    switch (CIRCLE_STATE)
    {
    case CIRCLE_LEFT_BEGIN:
        // ���ٱ���ѡ�� ��������
        if (Image_RightLine_Lost == 0)
            TRACE_TYPE = TRACE_RIGHT_MIDLINE;
        else if (Image_LeftLine_Lost == 0)
            TRACE_TYPE = TRACE_LEFT_MIDLINE;
        else
            TRACE_TYPE = TRACE_NONE;
        // �����⵽�ڶ����ǵ㣬�л���ʮ��
        if (Image_LptLeft_Found == true && Image_LptRight_Found == true)
        {
            CIRCLE_STATE = CIRCLE_NONE;
            OVERALL_STATE = CROSS;
            CROSS_STATE = CROSS_ENTER;
        }
        // ����ǵ�ӽ����߽ǵ���ʧ���л���CIRCLE_IN
        if (Image_rptsRights[Image_LptLeft_rptsLefts_id][1] >= CIRCLE_BEGIN_CORNER_EDGE_DIST || (Image_LptLeft_Found == false && Image_LptRight_Found == false))
        {
            // ��������������
            Encoder_Begin(ENCODER_MOTOR_2);

            CIRCLE_STATE = CIRCLE_LEFT_IN;
        }
        break;

    case CIRCLE_LEFT_IN:
        // ���ٱ���ѡ�� ��������
        Tracing_LeftFirst(TRACE_NONE);
        // �����⵽�ڶ����ǵ㣬�л���ʮ��
        if (Image_LptLeft_Found == true && Image_LptRight_Found == true)
        {
            CIRCLE_STATE = CIRCLE_NONE;
            OVERALL_STATE = CROSS;
            CROSS_STATE = CROSS_ENTER;
        }
        // ���������ֳ�����ֵ���л���CIRCLE_RUNNING
        if (Encoder_sum_Motor2 >= CIRCLE_IN_ENCODER_THRE)
        {
            // ���ñ���������
            Encoder_Clear(ENCODER_MOTOR_2);
            // ��ʼ�����ǻ���
            Gyroscope_Begin(GYROSCOPE_GYRO_Z);

            CIRCLE_STATE = CIRCLE_LEFT_RUNNING;
        }
        break;

    case CIRCLE_LEFT_RUNNING:
        // ���ٱ���ѡ�� ��������
        Tracing_LeftFirst(TRACE_NONE);
        // �����ǻ��ֳ�����ֵ����������ֳ�����ֵ���л���CIRCLE_OUT1
        if (Gyro_z >= CIRCLE_RUNNING_GYRO_THRE || Encoder_sum_Motor2 >= CIRCLE_RUNNING_ENCODER_THRE)
        {
            Encoder_Clear(ENCODER_MOTOR_2);
            //��������������
            Gyroscope_Clear(GYROSCOPE_GYRO_Z);
            Gyroscope_End(GYROSCOPE_GYRO_Z);

            CIRCLE_STATE = CIRCLE_LEFT_OUT;
        }
        break;

    case CIRCLE_LEFT_OUT:
        // ���ٱ���ѡ�� ֻѲ����
        Tracing_RightOnly(TRACE_NONE);
        break;
        // ���������ֳ�����ֵ������CIRCLE״̬
        if (Encoder_sum_Motor2 >= CIRCLE_OUT2_ENCODER_THRE)
        {
            Encoder_End(ENCODER_MOTOR_2);
            Encoder_Clear(ENCODER_MOTOR_2);

            CIRCLE_STATE = CIRCLE_NONE;
            OVERALL_STATE = COMMON_ROAD;
        }
        break;

    default:
        break;
    }
}