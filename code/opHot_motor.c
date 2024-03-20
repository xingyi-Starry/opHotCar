/*
 * opHot_motor.c
 *
 *  Created on: 2024��1��23��
 *      Author: 97329
 */
#include "opHot_motor.h"

PID Motor1_PID;
PID Motor2_PID;
float Motor1_target = 75;   // ���1PIDĿ�꣨������������
float Motor2_target = 75;   // ���2PIDĿ�꣨������������

/**
 * @brief   ������ų�ʼ��
 *
 * @warning ��
 * @note    ��
 */
void Motor_Init(void)
{
    pwm_init(MOTOR_1_PWM, MOTOR_FREQ, 0);
    pwm_init(MOTOR_2_PWM, MOTOR_FREQ, 0);
    gpio_init(MOTOR_1_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);
    gpio_init(MOTOR_2_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);
}

/**
 * @brief ���õ��ת��
 *
 * @param motor_name ��ѡ��ĵ��
 * @param speed ��ѡ����ٶ�
 *
 * @warning speed�ķ�Χ��0-10000
 * @note Motor_SetSpeed(MOTOR_1, 1000)
 */

void Motor_SetSpeed(MOTOR_PWM_enum motor, int16 speed)
{
    if (motor == MOTOR_1)
    {
        if (speed < 0)
        {
            speed = -speed;
            gpio_set_level(MOTOR_1_DIR, 1);
            pwm_set_duty(MOTOR_1_PWM, speed);
        }
        else
        {
            gpio_set_level(MOTOR_1_DIR, 0);
            pwm_set_duty(MOTOR_1_PWM, speed);
        }
    }
    else if (motor == MOTOR_2)
    {
        if (speed < 0)
        {
            speed = -speed;
            gpio_set_level(MOTOR_2_DIR, 1);
            pwm_set_duty(MOTOR_2_PWM, speed);
        }
        else
        {
            gpio_set_level(MOTOR_2_DIR, 0);
            pwm_set_duty(MOTOR_2_PWM, speed);
        }
    }
}

void Motor_PID_Init(void)
{
    PID_Init(&Motor1_PID);
    PID_Init(&Motor2_PID);
}

void Motor1_PID_Set(float K_p_set, float K_i_set, float K_d_set, float pLimit, float coLimit, float boost)
{
    PID_SetParameter(&Motor1_PID, K_p_set, K_i_set, K_d_set, pLimit, coLimit, boost);
}
void Motor2_PID_Set(float K_p_set, float K_i_set, float K_d_set, float pLimit, float coLimit, float boost)
{
    PID_SetParameter(&Motor2_PID, K_p_set, K_i_set, K_d_set, pLimit, coLimit, boost);
}

void Motor1_SetPIDP(float setP)
{
    Motor1_PID.kP = setP;
}

void Motor1_SetPIDI(float setI)
{
    Motor1_PID.kI = setI;
}

void Motor1_SetPIDD(float setD)
{

    Motor1_PID.kD = setD;
}

// ���û�������
void Motor1_SetPIDLimit(float pLimit)
{
    Motor1_PID.sumLimit = pLimit;
}

// ���������޷�
void Motor1_SetPIDCoLimit(float coLimt)
{
    Motor1_PID.utLimit = coLimt;
}

void Motor2_SetPIDP(float setP)
{

    Motor2_PID.kP = setP;
}

void Motor2_SetPIDI(float setI)
{
    Motor2_PID.kI = setI;
}

void Motor2_SetPIDD(float setD)
{
    Motor2_PID.kD = setD;
}
void Motor_pidClear()
{
    Motor1_PID.ut = 0.0;
    Motor2_PID.ut = 0.0;
}

// ���û�������
void Motor2_SetPIDLimit(float pLimit)
{
    Motor2_PID.sumLimit = pLimit;
}

// ���������޷�
void Motor2_SetPIDCoLimit(float coLimt)
{
    Motor2_PID.utLimit = coLimt;
}

void Motor1_PIDwork(void)
{
    PID_PostionalPID(&Motor1_PID, Motor1_target, Encoder_1Data);
    Motor_SetSpeed(MOTOR_1, (int16)Motor1_PID.ut);
}

void Motor2_PIDwork(void)
{
    PID_PostionalPID(&Motor2_PID, Motor2_target, Encoder_2Data);
    Motor_SetSpeed(MOTOR_2, (int16)Motor2_PID.ut);
}
