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
    tracing_aim = TRACE_COMMON_AIM;

    switch (CIRCLE_STATE)
    {
    case CIRCLE_RIGHT_BEGIN:
        // ���ٱ���ѡ��
        if (Image_LeftLine_Lost == 0)
            TRACE_TYPE = TRACE_LEFT_MIDLINE;
        else if (Image_RightLine_Lost == 0)
            TRACE_TYPE = TRACE_RIGHT_MIDLINE;
        else
            TRACE_TYPE = TRACE_NONE;
        // �����⵽�ڶ����ǵ㣬�л���ʮ��
        if (Image_LptLeft_Found == true && Image_LptRight_Found == true)
        {
            CIRCLE_STATE = CIRCLE_NONE;
            OVERALL_STATE = CROSS;
            CROSS_STATE = CROSS_ENTER;
        }
        // ����ǵ�ӽ����߽ǵ���ʧ���л���CIRCLE_IN1
        if (Image_rptsRights[Image_LptRight_rptsRights_id][1] >= CIRCLE_BEGIN_CORNER_EDGE_DIST || (Image_LptLeft_Found == false && Image_LptRight_Found == false))
        {
            // ��������������
            Encoder_Begin(ENCODER_MOTOR_1);

            CIRCLE_STATE = CIRCLE_RIGHT_IN1;
        }
        break;

    case CIRCLE_RIGHT_IN1:
        // ���ٱ���ѡ�� ֻ������
        if (Image_LeftLine_Lost == 0)
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
        // ��ʻ�̶���������CIRCLE_IN2
        if (Encoder_sum_Motor1 >= CIRCLE_IN1_ENCODER_THRE)
        {
            // ���ñ���������
            Encoder_Clear(ENCODER_MOTOR_1);

            CIRCLE_STATE = CIRCLE_RIGHT_IN2;
        }
        break;

    case CIRCLE_RIGHT_IN2:
        // ���ٱ���ѡ�� ֻ������
        if (Image_RightLine_Lost == 0)
            TRACE_TYPE = TRACE_RIGHT_MIDLINE;
        else
            TRACE_TYPE = TRACE_NONE;
        // ��ʻ�̶���������CIRCLE_RUNNING
        if (Encoder_sum_Motor1 >= CIRCLE_IN2_ENCODER_THRE)
        {
            // ��������������
            Encoder_End(ENCODER_MOTOR_1);
            Encoder_Clear(ENCODER_MOTOR_1);

            CIRCLE_STATE = CIRCLE_RIGHT_RUNNING;
        }
        break;

    case CIRCLE_RIGHT_RUNNING:
        // ���ٱ���ѡ��
        if (Image_LeftLine_Lost == 0)
            TRACE_TYPE = TRACE_LEFT_MIDLINE;
        else if (Image_RightLine_Lost == 0)
            TRACE_TYPE = TRACE_RIGHT_MIDLINE;
        else
            TRACE_TYPE = TRACE_NONE;
        // ��ǵ�ӽ�ʱ����CIRCLE_OUT1
        if (Image_LptLeft_Found == true && Image_rptsRights[Image_LptRight_rptsRights_id][1] >= CIRCLE_RUNNING_CORNER_EDGE_DIST)
        {
            CIRCLE_STATE = CIRCLE_RIGHT_OUT1;
        }
        break;

    case CIRCLE_RIGHT_OUT1:
        // ���ٱ���ѡ�� ֻ������
        /*
        if (Image_RightLine_Lost == 0)
            TRACE_TYPE = TRACE_RIGHT_MIDLINE;
        else
            TRACE_TYPE = TRACE_NONE;
            */
        // �ȿ������ƣ��ջ���ʱ����
        TRACE_TYPE = TRACE_NONE;
        // ��������Ϊֱ��ʱ����CIRCLE_OUT2
        if (Image_isStraightLeft == true)
        {
            Encoder_Begin(ENCODER_MOTOR_1);

            CIRCLE_STATE = CIRCLE_RIGHT_OUT2;
        }
        break;
    
    case CIRCLE_RIGHT_OUT2:
        // ���ٱ���ѡ�� ֻ������
        if (Image_LeftLine_Lost == 0)
            TRACE_TYPE = TRACE_LEFT_MIDLINE;
        else
            TRACE_TYPE = TRACE_NONE;
        break;
        // ��ʻ�̶�������г�����״̬
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