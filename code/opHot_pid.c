/*
 * xiao_pid.c
 *
 *  Created on: 2023��5��1��
 *      Author: Jayden_NaN
 */

#include "opHot_pid.h"
/**
 * @brief           PID��ʼ��
 * @param p         ����ʼ����ָ��
 * @return          NULL
 */
void PID_Init(PID *p)
{
    p->kP = 0.0;
    p->kI = 0.0;
    p->kD = 0.0;
    p->kPSet = 0.0;
    p->kISet = 0.0;
    p->kDSet = 0.0;
    p->sum = 0.0;
    p->preError = 0.0;
    p->ppreError = 0.0;
    p->ut = 0.0;
    p->sumLimit = 0.0;
    p->utLimit = 0.0;
}

/**
 * @brief               ��������p�ĸ������
 * @param pLimit        �����޷�
 * @param coLimit       �����޷�
 * @return              NULL
 */
void PID_SetParameter(PID *p, float setP, float setI, float setD, float pLimit, float coLimit, float boost)
{
    p->kPSet = boost * setP;
    p->kISet = boost * setI;
    p->kDSet = boost * setD;
    p->sumLimit = pLimit;
    p->utLimit = coLimit;
    p->kP = p->kPSet;
    p->kI = p->kISet;
    p->kD = p->kDSet;
}
/**
 * @brief               λ��ʽPID
 * @param   p           ����������PID����
 * @param   target      Ŀ��ֵ
 * @param   cur         ��ǰֵ
 */
void PID_PostionalPID(PID *p, float target, float cur)
{
    float error = target - cur;
    // ������
    p->sum += error * p->kI;
    // ���л����޷�
    p->sum = p->sum > p->sumLimit ? p->sumLimit : p->sum;
    p->sum = p->sum < -p->sumLimit ? -p->sumLimit : p->sum;
    // ���ݽ��м���
    if (-1 < error - p->preError && error - p->preError < 1)
    {
        p->ut = p->kP * error;
    }
    else
    {
        p->ut = p->kP * error + p->sum + p->kD * (error - p->preError);
    }
    // ���������޷�
    p->ut = p->ut > p->utLimit ? p->utLimit : p->ut;
    p->ut = p->ut < -p->utLimit ? -p->utLimit : p->ut;
    // �������ݸ���
    p->preError = error;
}

/**
 * @brief               ����ʽPID
 * @param p             ����������PID����
 * @param target        Ŀ��ֵ
 * @param cur           ��ǰֵ
 *
 */
void PID_IncrementalPID(PID *p, float target, float cur)
{
    float error = target - cur;
    // ���ݽ�������
    p->ut += p->kP * (error - p->preError) + p->kI * error + p->kD * (error - 2 * p->preError + p->preError);
    // ���������޷�
    p->ut = p->ut > p->utLimit ? p->utLimit : p->ut;
    p->ut = p->ut < -p->utLimit ? -p->utLimit : p->ut;
    // �������ݸ���
    p->ppreError = p->preError;
    p->preError = error;
}
