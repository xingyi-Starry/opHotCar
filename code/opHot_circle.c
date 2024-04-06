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
            Gyroscope_End(GYROSCOPE_GYRO_Z);
            Gyroscope_Begin(GYROSCOPE_GYRO_Z);
            Tracing_GetGyroTarget();
            return;
        }
        // ����ǵ�ӽ����߽ǵ���ʧ���л���CIRCLE_IN
        if (Image_rptsLefts[Image_LptLeft_rptsLefts_id][1] >= CIRCLE_BEGIN_CORNER_EDGE_DIST || (Image_LptLeft_Found == false && Image_LptRight_Found == false))
        {
            Motor_target = MOTOR_CIRCLE_IN_SPEED;
            // ��������������
            Encoder_Begin(ENCODER_MOTOR_2);

            CIRCLE_STATE = CIRCLE_LEFT_IN;
        }
        break;

    case CIRCLE_LEFT_IN:
        // ���ٱ���ѡ�� ��������
        Tracing_LeftFirst(TRACE_NONE);
        // �����߶�����Ѳ������������������
        if (Image_LeftLine_Lost == 1)
            trace_central = TRACE_CENTRAL - 4;
        else
            trace_central = TRACE_CENTRAL;
        // �����⵽�ڶ����ǵ㣬�л���ʮ��
        if (Image_LptLeft_Found == true && Image_LptRight_Found == true)
        {
            Motor_target = MOTOR_COMMON_SPEED;
            CIRCLE_STATE = CIRCLE_NONE;
            OVERALL_STATE = CROSS;
            CROSS_STATE = CROSS_ENTER;
            Gyroscope_End(GYROSCOPE_GYRO_Z);
            Gyroscope_Begin(GYROSCOPE_GYRO_Z);
            Tracing_GetGyroTarget();
            return;
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
        Tracing_LeftFirst(TRACE_STATIC);
        // �����߶�����Ѳ������������������
        if (Image_LeftLine_Lost == 1)
            trace_central = TRACE_CENTRAL - 4;
        else
            trace_central = TRACE_CENTRAL;
        // �����⵽�ڶ����ǵ㣬�л���ʮ��
        if (Image_LptLeft_Found == true && Image_LptRight_Found == true)
        {
            trace_central = TRACE_CENTRAL;
            Motor_target = MOTOR_COMMON_SPEED;
            CIRCLE_STATE = CIRCLE_NONE;
            OVERALL_STATE = CROSS;
            CROSS_STATE = CROSS_ENTER;
            Encoder_End(ENCODER_MOTOR_2);
            Encoder_Clear(ENCODER_MOTOR_2);
            Gyroscope_End(GYROSCOPE_GYRO_Z);
            Gyroscope_Begin(GYROSCOPE_GYRO_Z);
            Tracing_GetGyroTarget();
            return;
        }
        // �����ǻ��ֳ�����ֵ����������ֳ�����ֵ���л���CIRCLE_OUT1
        if (Gyro_z >= CIRCLE_RUNNING_GYRO_THRE || Encoder_sum_Motor2 >= CIRCLE_RUNNING_ENCODER_THRE)
        {
            // �ٶȾ���
            Motor_target = MOTOR_COMMON_SPEED;
            Encoder_Clear(ENCODER_MOTOR_2);
            // ��������������
            Gyroscope_Clear(GYROSCOPE_GYRO_Z);
            Gyroscope_End(GYROSCOPE_GYRO_Z);

            CIRCLE_STATE = CIRCLE_LEFT_OUT;
        }
        // ֱ�����ֳ�����ֵ��ֱ������COMMON_ROAD
        if (Encoder_sum_Straight >= CIRCLE_RUNNING_ENCODER_S_THRE)
        {
            // ���������������
            Encoder_Clear(ENCODER_MOTOR_2);
            Encoder_End(ENCODER_MOTOR_2);
            Gyroscope_Clear(GYROSCOPE_GYRO_Z);
            Gyroscope_End(GYROSCOPE_GYRO_Z);

            OVERALL_STATE = COMMON_ROAD;
            CIRCLE_STATE = CIRCLE_NONE;
        }
        break;

    case CIRCLE_LEFT_OUT:
        // ���ٱ���ѡ�� ֻѲ����
        Tracing_RightOnly(TRACE_NONE);
        // ���������ֳ�����ֵ������CIRCLE״̬
        if (Encoder_sum_Motor2 >= CIRCLE_OUT2_ENCODER_THRE)
        {
            Encoder_End(ENCODER_MOTOR_2);
            Encoder_Clear(ENCODER_MOTOR_2);

            CIRCLE_STATE = CIRCLE_NONE;
            OVERALL_STATE = COMMON_ROAD;
        }
        break;

    case CIRCLE_RIGHT_BEGIN:
        // ���ٱ���ѡ�� ��������
        Tracing_RightFirst(TRACE_NONE);
        // �����⵽�ڶ����ǵ㣬�л���ʮ��
        if (Image_LptLeft_Found == true && Image_LptRight_Found == true)
        {
            CIRCLE_STATE = CIRCLE_NONE;
            OVERALL_STATE = CROSS;
            CROSS_STATE = CROSS_ENTER;
            Gyroscope_End(GYROSCOPE_GYRO_Z);
            Gyroscope_Begin(GYROSCOPE_GYRO_Z);
            Tracing_GetGyroTarget();
            return;
        }
        // ����ǵ�ӽ����߽ǵ���ʧ���л���CIRCLE_IN
        if (Image_rptsRights[Image_LptRight_rptsRights_id][1] >= CIRCLE_BEGIN_CORNER_EDGE_DIST || (Image_LptLeft_Found == false && Image_LptRight_Found == false))
        {
            Motor_target = MOTOR_CIRCLE_IN_SPEED;
            // ��������������
            Encoder_Begin(ENCODER_MOTOR_1);

            CIRCLE_STATE = CIRCLE_RIGHT_IN;
        }
        break;

    case CIRCLE_RIGHT_IN:
        // ���ٱ���ѡ�� ��������
        Tracing_RightFirst(TRACE_NONE);
        // �����߶�����Ѳ������������������
        if (Image_RightLine_Lost == 1)
            trace_central = TRACE_CENTRAL + 4;
        else
            trace_central = TRACE_CENTRAL;
        // �����⵽�ڶ����ǵ㣬�л���ʮ��
        if (Image_LptLeft_Found == true && Image_LptRight_Found == true)
        {
            Motor_target = MOTOR_COMMON_SPEED;
            CIRCLE_STATE = CIRCLE_NONE;
            OVERALL_STATE = CROSS;
            CROSS_STATE = CROSS_ENTER;
            Gyroscope_End(GYROSCOPE_GYRO_Z);
            Gyroscope_Begin(GYROSCOPE_GYRO_Z);
            Tracing_GetGyroTarget();
            return;
        }
        // ���������ֳ�����ֵ���л���CIRCLE_RUNNING
        if (Encoder_sum_Motor1 >= CIRCLE_IN_ENCODER_THRE)
        {
            // ���ñ���������
            Encoder_Clear(ENCODER_MOTOR_1);
            // ��ʼ�����ǻ���
            Gyroscope_Begin(GYROSCOPE_GYRO_Z);

            CIRCLE_STATE = CIRCLE_RIGHT_RUNNING;
        }
        break;

    case CIRCLE_RIGHT_RUNNING:
        // ���ٱ���ѡ�� ��������
        Tracing_RightFirst(TRACE_STATIC);
        // �����߶�����Ѳ������������������
        if (Image_RightLine_Lost == 1)
            trace_central = TRACE_CENTRAL + 4;
        else
            trace_central = TRACE_CENTRAL;
        // �����⵽�ڶ����ǵ㣬�л���ʮ��
        if (Image_LptLeft_Found == true && Image_LptRight_Found == true)
        {
            Motor_target = MOTOR_COMMON_SPEED;
            trace_central = TRACE_CENTRAL;
            CIRCLE_STATE = CIRCLE_NONE;
            OVERALL_STATE = CROSS;
            CROSS_STATE = CROSS_ENTER;
            Encoder_End(ENCODER_MOTOR_1);
            Encoder_Clear(ENCODER_MOTOR_1);
            Gyroscope_End(GYROSCOPE_GYRO_Z);
            Gyroscope_Begin(GYROSCOPE_GYRO_Z);
            Tracing_GetGyroTarget();
            return;
        }
        // �����ǻ��ֳ�����ֵ����������ֳ�����ֵ���л���CIRCLE_OUT1
        if (Gyro_z <= -CIRCLE_RUNNING_GYRO_THRE || Encoder_sum_Motor1 >= CIRCLE_RUNNING_ENCODER_THRE)
        {
            // �ٶȾ���
            Motor_target = MOTOR_COMMON_SPEED;
            Encoder_Clear(ENCODER_MOTOR_1);
            // ��������������
            Gyroscope_Clear(GYROSCOPE_GYRO_Z);
            Gyroscope_End(GYROSCOPE_GYRO_Z);

            CIRCLE_STATE = CIRCLE_RIGHT_OUT;
        }
        // ֱ�����ֳ�����ֵ��ֱ������COMMON_ROAD
        if (Encoder_sum_Straight >= CIRCLE_RUNNING_ENCODER_S_THRE)
        {
            // ���������������
            Encoder_Clear(ENCODER_MOTOR_1);
            Encoder_End(ENCODER_MOTOR_1);
            Gyroscope_Clear(GYROSCOPE_GYRO_Z);
            Gyroscope_End(GYROSCOPE_GYRO_Z);

            OVERALL_STATE = COMMON_ROAD;
            CIRCLE_STATE = CIRCLE_NONE;
        }
        break;

    case CIRCLE_RIGHT_OUT:
        // ���ٱ���ѡ�� ֻѲ����
        Tracing_LeftOnly(TRACE_NONE);
        // ���������ֳ�����ֵ������CIRCLE״̬
        if (Encoder_sum_Motor1 >= CIRCLE_OUT2_ENCODER_THRE)
        {
            Encoder_End(ENCODER_MOTOR_1);
            Encoder_Clear(ENCODER_MOTOR_1);

            CIRCLE_STATE = CIRCLE_NONE;
            OVERALL_STATE = COMMON_ROAD;
        }
        break;

    default:
        break;
    }
}