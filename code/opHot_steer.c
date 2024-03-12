/*
 * opHot_Steering.c
 *
 *  Created on: 2024��3��8��
 *      Author: 97329
 */
#include <opHot_steer.h>

/**
 * @brief �����ʼ��
 * 
 */
void Steer_Init(void)
{
    pwm_init(SERVO_MOTOR_PWM, SERVO_MOTOR_FREQ, STEER_MIDDLE);
}

/**
 * @brief ���ö��ռ�ձ�
 * 
 * @param duty ռ�ձ�
 */
void Steer_SetDuty(uint32 duty)
{
    pwm_set_duty(SERVO_MOTOR_PWM, duty);
}

/**
 * @brief ���ö���Ƕ�
 * 
 * @param angle 
 */
void Steer_SetAngle(uint8 angle)
{
    pwm_set_duty(SERVO_MOTOR_PWM, SERVO_MOTOR_DUTY(angle));
}



