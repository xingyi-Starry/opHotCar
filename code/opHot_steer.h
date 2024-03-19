/*
 * opHot_Steering.h
 *
 *  Created on: 2024��3��8��
 *      Author: 97329
 */

#ifndef CODE_OPHOT_STEER_H_
#define CODE_OPHOT_STEER_H_
#include "zf_common_headfile.h"
#include "opHotCar.h"

#define SERVO_MOTOR_PWM             (ATOM1_CH1_P33_9)           // ���������϶����Ӧ����
#define SERVO_MOTOR_FREQ            (150)                       // ���������϶��Ƶ��  �����ע�ⷶΧ 50-300

//---------���ռ�ձ����-----------
#define STEER_R_LIM     (2040)     //�����ת����ռ�ձ�
#define STEER_MID       (2250)     //����ڽ���ֵռ�ձ�
#define STEER_L_LIM     (2480)     //�����ת����ռ�ձ�

//---------PID����----------------
#define STEER_PID_P             (100)
#define STEER_PID_I             (0)
#define STEER_PID_D             (0)
#define STEER_PID_SL            (5000)
#define STEER_PID_UL            (1500)

extern float Steer_target;
extern float Steer_current;

void Steer_Init(void);
void Steer_SetDuty(uint32 duty);
void Steer_PID_Init(void);
void Steer_PID_Set(float K_p_set, float K_i_set, float K_d_set, float pLimit, float coLimit, float boost);
void Steer_SetPIDP(float setP);
void Steer_SetPIDI(float setI);
void Steer_SetPIDD(float setD);
void Steer_SetPIDLimit(float sumLimit);
void Steer_SetPIDCoLimit(float coLimit);
void Steer_PID_Clear(void);
void Steer_PIDwork(void);

#endif /* CODE_OPHOT_STEER_H_ */
