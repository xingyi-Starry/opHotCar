/*
 * opHot_Steering.c
 *
 *  Created on: 2024年3月8日
 *      Author: 97329
 */
#include <opHot_steer.h>

/**
 * @brief 舵机初始化
 * 
 */
void Steer_Init(void)
{
    pwm_init(SERVO_MOTOR_PWM, SERVO_MOTOR_FREQ, STEER_MIDDLE);
}

/**
 * @brief 设置舵机占空比
 * 
 * @param duty 占空比
 */
void Steer_SetDuty(uint32 duty)
{
    pwm_set_duty(SERVO_MOTOR_PWM, duty);
}

/**
 * @brief 设置舵机角度
 * 
 * @param angle 
 */
void Steer_SetAngle(uint8 angle)
{
    pwm_set_duty(SERVO_MOTOR_PWM, SERVO_MOTOR_DUTY(angle));
}



