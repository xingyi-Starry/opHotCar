/*
 * opHot_motor.h
 *
 *  Created on: 2024年1月23日
 *      Author: 97329
 */

#ifndef CODE_OPHOT_MOTOR_H_
#define CODE_OPHOT_MOTOR_H_

#include "zf_common_headfile.h"

//一个方向引脚+一个控制引脚
#define MOTOR_FREQ              (17000)

#define MOTOR_1_DIR             (P21_4)
#define MOTOR_1_PWM             (ATOM0_CH3_P21_5)
#define MOTOR_2_DIR             (P21_2)
#define MOTOR_2_PWM             (ATOM0_CH1_P21_3)

typedef enum
{
    MOTOR_1 = 0x00,
    MOTOR_2 = 0x01
} MOTOR_PWM_enum;

void Motor_Init(void);
void Motor_SetSpeed(MOTOR_PWM_enum motor_name, int16 speed);

#endif /* CODE_OPHOT_MOTOR_H_ */
