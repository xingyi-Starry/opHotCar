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
    switch (CIRCLE_STATE)
    {
    case CIRCLE_NONE:
        // �������������֣�׼�����μ��
        Encoder_Begin(Encoder_sum_Motor1);
        // ����Ƿ�Ϊ�󻷵�
        if (Image_LptLeft_Found == true && Image_LptRight_Found == false)
        {
            CIRCLE_STATE = CIRCLE_LEFT_BEGIN;
        }
        // ����Ƿ�Ϊ�һ���
        else if (Image_LptLeft_Found == false && Image_LptRight_Found == true)
        {
            CIRCLE_STATE =CIRCLE_RIGHT_BEGIN;
        }
        else // wtf???
        {
            Encoder_End(Encoder_sum_Motor1);
            Encoder_Clear(Encoder_sum_Motor1);
            OVERALL_STATE = COMMON_ROAD;
        }
        break;
    
    default:
        break;
    }
}