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
        // ���߶��߻��߱��������ֳ�����ֵ���л���CIRCLE_RUNNING
        if (Image_RightLine_Lost == 1 || Encoder_sum_Motor2 >= CIRCLE_IN_ENCODER_THRE)
        {
            // ���ñ���������
            Encoder_Clear(ENCODER_MOTOR_2);

            CIRCLE_STATE = CIRCLE_LEFT_RUNNING;
        }
        break;

    case CIRCLE_LEFT_RUNNING:
        // ���ٱ���ѡ�� ��������
        if (Image_RightLine_Lost == 0)
            TRACE_TYPE = TRACE_RIGHT_MIDLINE;
        else if (Image_LeftLine_Lost == 0)
            TRACE_TYPE = TRACE_LEFT_MIDLINE;
        else
            TRACE_TYPE = TRACE_NONE;
        // �ҽǵ�ӽ�����������ֳ�����ֵ���л���CIRCLE_OUT1
        if ((Image_LptRight_Found == true && Image_rptsRights[Image_LptRight_rptsRights_id][1] >= CIRCLE_RUNNING_CORNER_EDGE_DIST) || Encoder_sum_Motor2 >= CIRCLE_RUNNING_ENCODER_THRE)
        {
            Encoder_Clear(ENCODER_MOTOR_2);

            CIRCLE_STATE = CIRCLE_LEFT_OUT1;
        }
        break;

    case CIRCLE_LEFT_OUT1:
        // ���ٱ���ѡ�� ��������
        if (Image_RightLine_Lost == 0)
            TRACE_TYPE = TRACE_RIGHT_MIDLINE;
        else if (Image_LeftLine_Lost == 0)
            TRACE_TYPE = TRACE_LEFT_MIDLINE;
        else
            TRACE_TYPE = TRACE_NONE;
        // ���������ֳ�����ֵ���л���CIRCLE_END
        if (Encoder_sum_Motor2 >= CIRCLE_OUT1_ENCODER_THRE)
        {
            Encoder_Clear(ENCODER_MOTOR_2);

            CIRCLE_STATE = CIRCLE_LEFT_OUT2;
        }
        break;

    case CIRCLE_LEFT_OUT2:
        // ���ٱ���ѡ�� ��������
        if (Image_RightLine_Lost == 0)
            TRACE_TYPE = TRACE_RIGHT_MIDLINE;
        else if (Image_LeftLine_Lost == 0)
            TRACE_TYPE = TRACE_LEFT_MIDLINE;
        else
            TRACE_TYPE = TRACE_NONE;
        break;
        // ���߶�ʧ����������ֳ�����ֵ������CIRCLE״̬
        if (Image_LeftLine_Lost == 1 || Encoder_sum_Motor2 >= CIRCLE_OUT2_ENCODER_THRE)
        {
            Encoder_End(ENCODER_MOTOR_2);
            Encoder_Clear(ENCODER_MOTOR_2);

            CIRCLE_STATE = CIRCLE_NONE;
            OVERALL_STATE = COMMON_ROAD;
        }
        break;

    case CIRCLE_RIGHT_BEGIN:
        // ���ٱ���ѡ�� ��������
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
        // ����ǵ�ӽ����߽ǵ���ʧ���л���CIRCLE_IN
        if (Image_rptsRights[Image_LptRight_rptsRights_id][1] >= CIRCLE_BEGIN_CORNER_EDGE_DIST || (Image_LptLeft_Found == false && Image_LptRight_Found == false))
        {
            // ��������������
            Encoder_Begin(ENCODER_MOTOR_1);

            CIRCLE_STATE = CIRCLE_RIGHT_IN;
        }
        break;

    case CIRCLE_RIGHT_IN:
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
        // ���߶��߻��߱��������ֳ�����ֵ���л���CIRCLE_RUNNING
        if (Image_RightLine_Lost == 1 || Encoder_sum_Motor1 >= CIRCLE_IN_ENCODER_THRE)
        {
            // ���ñ���������
            Encoder_Clear(ENCODER_MOTOR_1);

            CIRCLE_STATE = CIRCLE_RIGHT_RUNNING;
        }
        break;

    case CIRCLE_RIGHT_RUNNING:
        // ���ٱ���ѡ�� ��������
        if (Image_LeftLine_Lost == 0)
            TRACE_TYPE = TRACE_LEFT_MIDLINE;
        else if (Image_RightLine_Lost == 0)
            TRACE_TYPE = TRACE_RIGHT_MIDLINE;
        else
            TRACE_TYPE = TRACE_NONE;
        // ��ǵ�ӽ�����������ֳ�����ֵ���л���CIRCLE_OUT1
        if ((Image_LptLeft_Found == true && Image_rptsRights[Image_LptRight_rptsRights_id][1] >= CIRCLE_RUNNING_CORNER_EDGE_DIST) || Encoder_sum_Motor1 >= CIRCLE_RUNNING_ENCODER_THRE)
        {
            Encoder_Clear(ENCODER_MOTOR_1);

            CIRCLE_STATE = CIRCLE_RIGHT_OUT1;
        }
        break;

    case CIRCLE_RIGHT_OUT1:
        // ���ٱ���ѡ�� ��������
        if (Image_LeftLine_Lost == 0)
            TRACE_TYPE = TRACE_LEFT_MIDLINE;
        else if (Image_RightLine_Lost == 0)
            TRACE_TYPE = TRACE_RIGHT_MIDLINE;
        else
            TRACE_TYPE = TRACE_NONE;
        // ���������ֳ�����ֵ���л���CIRCLE_END
        if (Encoder_sum_Motor1 >= CIRCLE_OUT1_ENCODER_THRE)
        {
            Encoder_Clear(ENCODER_MOTOR_1);

            CIRCLE_STATE = CIRCLE_RIGHT_OUT2;
        }
        break;

    case CIRCLE_RIGHT_OUT2:
        // ���ٱ���ѡ�� ��������
        if (Image_LeftLine_Lost == 0)
            TRACE_TYPE = TRACE_LEFT_MIDLINE;
        else if (Image_RightLine_Lost == 0)
            TRACE_TYPE = TRACE_RIGHT_MIDLINE;
        else
            TRACE_TYPE = TRACE_NONE;
        break;
        // ���߶�ʧ����������ֳ�����ֵ������CIRCLE״̬
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