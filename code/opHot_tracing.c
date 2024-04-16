/*
 * opHot_tracing.c
 *
 *  Created on: 2024��3��19��
 *      Author: 97329
 */

#include "opHot_tracing.h"

float Err;
float gyro_target = 0;
const uint8 tracing_weigh[3] = {5, 3, 2};        // Ŀ�����Ȩ��
TRACE_TYPE_enum TRACE_TYPE = TRACE_RIGHT_MIDLINE; // ����������Դ����״̬������
uint8 tracing_aim = TRACE_COMMON_AIM;            // Ԥ��������ߵ�λ��
uint8 trace_central = TRACE_CENTRAL;
uint16 trace_factor = TRACE_FACTOR_COMMON;
uint8 length_of_car = LENGTH_OF_CAR;

/**
 * @brief   ��ȡ���PIDĿ��ֵ
 * @note    Ŀ��ֵΪԤ����Լ�Ԥ���+1��Ԥ���+2�ļ�Ȩƽ����Ȩ�ؼ�����tracing_weigh
 * @note    ���ݴ������㷨ǰ��ƫ��delta_angle = arctan(2Lsin(theta)/len_ahead)������LΪ������࣬thetaΪĿ������ǰ���нǣ�len_aheadΪĿ�굽�������
 * @note    ���ƿɵ�delta_angle = k * err / (length_of_car + row_of_aim) (��Űɣ��Ҹо���-linnuofan-2024/3/20)
 *
 */
void Tracing_GetTarget(void)
{
    // ��׼Ѳ��ģʽ
    if (TRACE_TYPE == TRACE_LEFT_MIDLINE || TRACE_TYPE == TRACE_RIGHT_MIDLINE)
    {
        // ͼ���Ȩ���
        Err = (float)(Image_MidLine[bf_clip(tracing_aim, 0, Image_MidLineNum - 1)][0] * tracing_weigh[0] + (float)Image_MidLine[bf_clip(tracing_aim + 1, 0, Image_MidLineNum - 1)][0] * tracing_weigh[1] + (float)Image_MidLine[bf_clip(tracing_aim + 2, 0, Image_MidLineNum - 1)][0] * tracing_weigh[2]) / 10 - trace_central;
        // ����ӦĿ��ռ�ձ�
        Steer_target = STEER_MID - Err * trace_factor / (length_of_car + MT9V03X_H - Image_MidLine[bf_clip(tracing_aim, 0, Image_MidLineNum - 1)][1]);
    }
    else if (TRACE_TYPE == TRACE_NONE)
        Steer_target = STEER_MID;
    else if (TRACE_TYPE == TRACE_STATIC)
        Steer_target = Steer_current;
    //�����ǿ���ģʽ
    else if (TRACE_TYPE == TRACE_GYRO)
    {
        Steer_target = (gyro_target - Gyro_z) * 5 + STEER_MID;
    }
    //    if (TRACE_TYPE == LEFT_MIDLINE)
    //    {
    //        Steer_target = (float)(Image_rptsLeftc[bf_clip(tracing_aim, 0, Image_rptsLeftcNum - 1)][0] * tracing_weigh[0] + Image_rptsLeftc[bf_clip(tracing_aim + 1, //0, Image_rptsLeftcNum - 1)][0] * tracing_weigh[1] + Image_rptsLeftc[bf_clip(tracing_aim + 2, 0, Image_rptsLeftcNum - 1)][0] * tracing_weigh[2]) / 10;
    //    }
    //    else if (TRACE_TYPE == RIGHT_MIDLINE)
    //    {
    //        Steer_target = (float)(Image_rptsRightc[bf_clip(tracing_aim, 0, Image_rptsLeftcNum - 1)][0] * tracing_weigh[0] + Image_rptsRightc[bf_clip(tracing_aim + //1, 0, Image_rptsLeftcNum - 1)][0] * tracing_weigh[1] + Image_rptsRightc[bf_clip(tracing_aim + 2, 0, Image_rptsLeftcNum - 1)][0] * tracing_weigh[2]) / 10;
    //    }
}

void Tracing_GetGyroTarget(void)
{
    if (Image_LeftLine_Lost == 1 && Image_RightLine_Lost == 0)
        gyro_target = 90 - Image_LeftTurnAngle;
    else if (Image_LeftLine_Lost == 0 && Image_RightLine_Lost == 1)
        gyro_target = 90 - Image_RightTurnAngle;
    else if (Image_LeftLine_Lost == 0 && Image_RightLine_Lost == 0)
    {
        if (Image_rptsLeftsNum > Image_rptsRightsNum)
            gyro_target = 90 - Image_LeftTurnAngle;
        else
            gyro_target = 90 - Image_RightTurnAngle;
    }
    else 
        gyro_target = 0;
}

/**
 * @brief       �����㷨���к���
 * @attention   Ӧ���ڶ�ʱ�ж��У���ͼ�����ж�֮��
 *
 */
void Tracing_Work(void)
{
    Tracing_GetTarget();
    Steer_PIDwork();
}

/**
 * @brief ����ѡ�� ��������
 *
 * @param TRACE_OTHER �������ѡ��
 */
void Tracing_RightFirst(TRACE_TYPE_enum TRACE_OTHER)
{
    if (Image_RightLine_Lost == 0)
        TRACE_TYPE = TRACE_RIGHT_MIDLINE;
    else if (Image_LeftLine_Lost == 0)
        TRACE_TYPE = TRACE_LEFT_MIDLINE;
    else
        TRACE_TYPE = TRACE_OTHER;
}

/**
 * @brief ����ѡ�� ��������
 *
 * @param TRACE_OTHER �������ѡ��
 */
void Tracing_LeftFirst(TRACE_TYPE_enum TRACE_OTHER)
{
    if (Image_LeftLine_Lost == 0)
        TRACE_TYPE = TRACE_LEFT_MIDLINE;
    else if (Image_RightLine_Lost == 0)
        TRACE_TYPE = TRACE_RIGHT_MIDLINE;
    else
        TRACE_TYPE = TRACE_OTHER;
}

/**
 * @brief ����ѡ�� ֻѲ����
 *
 * @param TRACE_OTHER �������ѡ��
 */
void Tracing_RightOnly(TRACE_TYPE_enum TRACE_OTHER)
{
    if (Image_RightLine_Lost == 0)
        TRACE_TYPE = TRACE_RIGHT_MIDLINE;
    else
        TRACE_TYPE = TRACE_OTHER;
}

/**
 * @brief ����ѡ�� ֻѲ����
 *
 * @param TRACE_OTHER �������ѡ��
 */
void Tracing_LeftOnly(TRACE_TYPE_enum TRACE_OTHER)
{
    if (Image_LeftLine_Lost == 0)
        TRACE_TYPE = TRACE_LEFT_MIDLINE;
    else
        TRACE_TYPE = TRACE_OTHER;
}

/**
 * @brief ����ѡ�� ��������
 * 
 * @param TRACE_OTHER �������ѡ��
 */
void Tracing_OuterFirst(TRACE_TYPE_enum TRACE_OTHER)
{
    if (Image_LeftDir | Image_RightDir == TURNDIR_LEFT) // ʹ�û����㣬������Ű� --linnuofan-2024/4/12
        Tracing_RightFirst(TRACE_OTHER);

    else if (Image_LeftDir | Image_RightDir == TURNDIR_RIGHT)
        Tracing_LeftFirst(TRACE_OTHER);
    
    else
        Tracing_LeftFirst(TRACE_OTHER); // ���Ϊ0x00(ֱ��)��0x03(?)ʱ��ѡһ�߼��ɣ��˴������ҵ�ϰ��ѡ��
}
