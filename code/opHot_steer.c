/*
 * opHot_Steering.c
 *
 *  Created on: 2024��3��8��
 *      Author: 97329
 */
#include <opHot_steer.h>

PID Steer_PID;
float Steer_target = STEER_MID;     // ���PIDĿ��ռ�ձ�
float Steer_current = STEER_MID;

/**
 * @brief �����ʼ��
 * 
 */
void Steer_Init(void)
{
    pwm_init(SERVO_MOTOR_PWM, SERVO_MOTOR_FREQ, STEER_MID);
}

/**
 * @brief ���ö��ռ�ձ�
 * 
 * @param duty ռ�ձȣ�ȡֵ690~820��750Ϊ��ֵ������750�ҹգ�С��750���
 */
void Steer_SetDuty(uint32 duty)
{
    // �޷�����֤��ȫ
    if (duty > STEER_L_LIM)
        duty = STEER_L_LIM;
    else if (duty < STEER_R_LIM)
        duty = STEER_R_LIM;

    Steer_current = (float)duty;
    pwm_set_duty(SERVO_MOTOR_PWM, duty);
}

/**
 * @brief ���PID��ʼ��
 * 
 */
void Steer_PID_Init(void)
{
    PID_Init(&Steer_PID);
}

/**
 * @brief ���PID���ò���
 * 
 */
void Steer_PID_Set(float K_p_set, float K_i_set, float K_d_set, float pLimit, float coLimit, float boost)
{
    PID_SetParameter(&Steer_PID, K_p_set, K_i_set, K_d_set, pLimit, coLimit, boost);
}

void Steer_SetPIDP(float setP)
{
    Steer_PID.kP = setP;
}

void Steer_SetPIDI(float setI)
{
    Steer_PID.kI = setI;
}

void Steer_SetPIDD(float setD)
{
    Steer_PID.kD = setD;
}

// ���ö��PID�����޷�
void Steer_SetPIDLimit(float sumLimit)
{
    Steer_PID.sumLimit = sumLimit;
}

void Steer_SetPIDCoLimit(float coLimit)
{
    Steer_PID.utLimit = coLimit;
}

// ������PID�����
void Steer_PID_Clear(void)
{
    Steer_PID.ut = 0;
}

void Steer_PIDwork(void)
{
    PID_PostionalPID(&Steer_PID, Steer_target, Steer_current);
    Steer_SetDuty((uint32)Steer_PID.ut);
}
