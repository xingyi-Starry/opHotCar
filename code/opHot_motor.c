/*
 * opHot_motor.c
 *
 *  Created on: 2024年1月23日
 *      Author: 97329
 */
#include "opHot_motor.h"

/**
 * @brief   电机引脚初始化
 *
 * @warning 无
 * @note    无
 */
void Motor_Init(void)
{
    pwm_init(MOTOR_1_PWM, MOTOR_FREQ, 0);
    pwm_init(MOTOR_2_PWM, MOTOR_FREQ, 0);
    gpio_init(MOTOR_1_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);
    gpio_init(MOTOR_2_DIR, GPO, GPIO_HIGH, GPO_PUSH_PULL);
}

/**
 * @brief 设置电机转速
 *
 * @param motor_name 所选择的电机
 * @param speed 所选择的速度
 *
 * @warning speed的范围是0-10000
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
