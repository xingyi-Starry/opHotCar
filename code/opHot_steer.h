/*
 * opHot_Steering.h
 *
 *  Created on: 2024年3月8日
 *      Author: 97329
 */

#ifndef CODE_OPHOT_STEER_H_
#define CODE_OPHOT_STEER_H_
#include "zf_common_headfile.h"

#define SERVO_MOTOR_PWM             (ATOM1_CH1_P33_9)                           // 定义主板上舵机对应引脚
#define SERVO_MOTOR_FREQ            (50 )                                       // 定义主板上舵机频率  请务必注意范围 50-300

#define SERVO_MOTOR_L_MAX           (30 )                                       // 定义主板上舵机活动范围 角度
#define SERVO_MOTOR_R_MAX           (150)                                       // 定义主板上舵机活动范围 角度

#define SERVO_MOTOR_DUTY(x)         ((float)PWM_DUTY_MAX/(1000.0/(float)SERVO_MOTOR_FREQ)*(0.5+(float)(x)/90.0))
//#define SERVO_MOTOR_DUTY(x)         ((float)PWM_DUTY_MAX/(1000.0/(float)SERVO_MOTOR_FREQ)*(0.5+(float)(x)/90.0))

#define STEER_LEFT      680    //舵机摆角左极限  这里的值是用于测试的，大家根据自己的舵机更改
#define STEER_MIDDLE    750   //舵机摆角中值
#define STEER_RIGHT     810    //舵机摆角右极限

void Steer_Init(void);
void Steer_SetDuty(uint32 duty);
void Steer_SetAngle(uint8 angle);

#endif /* CODE_OPHOT_STEER_H_ */
