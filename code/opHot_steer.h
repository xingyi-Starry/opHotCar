/*
 * opHot_Steering.h
 *
 *  Created on: 2024��3��8��
 *      Author: 97329
 */

#ifndef CODE_OPHOT_STEER_H_
#define CODE_OPHOT_STEER_H_
#include "zf_common_headfile.h"

#define SERVO_MOTOR_PWM             (ATOM1_CH1_P33_9)                           // ���������϶����Ӧ����
#define SERVO_MOTOR_FREQ            (50 )                                       // ���������϶��Ƶ��  �����ע�ⷶΧ 50-300

#define SERVO_MOTOR_L_MAX           (30 )                                       // ���������϶�����Χ �Ƕ�
#define SERVO_MOTOR_R_MAX           (150)                                       // ���������϶�����Χ �Ƕ�

#define SERVO_MOTOR_DUTY(x)         ((float)PWM_DUTY_MAX/(1000.0/(float)SERVO_MOTOR_FREQ)*(0.5+(float)(x)/90.0))
//#define SERVO_MOTOR_DUTY(x)         ((float)PWM_DUTY_MAX/(1000.0/(float)SERVO_MOTOR_FREQ)*(0.5+(float)(x)/90.0))

#define STEER_LEFT      680    //����ڽ�����  �����ֵ�����ڲ��Եģ���Ҹ����Լ��Ķ������
#define STEER_MIDDLE    750   //����ڽ���ֵ
#define STEER_RIGHT     810    //����ڽ��Ҽ���

void Steer_Init(void);
void Steer_SetDuty(uint32 duty);
void Steer_SetAngle(uint8 angle);

#endif /* CODE_OPHOT_STEER_H_ */
