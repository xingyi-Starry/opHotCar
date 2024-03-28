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
    // ���ٱ���ѡ��
    if (Image_LeftLine_Lost == 0)
        TRACE_TYPE = TRACE_LEFT_MIDLINE;
    else if (Image_RightLine_Lost == 0)
        TRACE_TYPE = TRACE_RIGHT_MIDLINE;
    else
        TRACE_TYPE = TRACE_STATIC;

    switch (CROSS_STATE)
    {
    case CROSS_ENTER:
        // Ԥ�������
        tracing_aim = TRACE_CLOSE_AIM;

        // ��ǵ�ӽ����߸ɴ���ʧʱ�л���CROSS_EXIT
        if (Image_rptsLefts[Image_LptLeft_rptsLefts_id][1] >= CROSS_ENTER_CORNER_EDGE_DIST || Image_rptsRights[Image_LptRight_rptsRights_id][1] >= CROSS_ENTER_CORNER_EDGE_DIST || (Image_LptLeft_Found == false && Image_LptRight_Found == false))
        {
            CROSS_STATE = CROSS_EXIT;
            Encoder_Begin(ENCODER_MOTOR_1); // ��ʼ���������֣���������
        }
        break;
        /*��ʱ��Ч��״̬*/
    case CROSS_RUNNING:
        /**�л���б��Ѳ��ģʽ����image_process()**/
        // Ԥ�������
        tracing_aim = 5;

        // ǰ�ǵ���ʧʱ����CROSS_EXIT
        if (Image_LptLeft_Found == false && Image_LptRight_Found == false)
        {
            // ����б��Ѳ�ߣ������Image_Process()
            CROSS_STATE = CROSS_EXIT;
        }
        break;
    case CROSS_EXIT:
        // Ѳǰ��
        image_begin_y = 30;
        // Ԥ�������
        tracing_aim = TRACE_CROSS_AIM;

        // ��ʻ�̶�������˳�CROSS_EXIT
        if (Encoder_sum_Motor1 >= CROSS_EXIT_ENCODER_THRE)
        {
            // �ָ�Ѳ�����
            image_begin_y = IMAGE_HEIGHT - 20;
            // �������֣������������
            Encoder_End(ENCODER_MOTOR_1);
            Encoder_Clear(ENCODER_MOTOR_1);
            // CROSS״̬����λ���˳�CROSS
            CROSS_STATE = CROSS_ENTER;
            OVERALL_STATE = COMMON_ROAD;
        }
        break;
    default:
        break;
    }
}
