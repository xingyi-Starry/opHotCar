/*
 * opHot_motor.h
 *
 *  Created on: 2024��1��23��
 *      Author: 97329
 */

#ifndef CODE_OPHOT_MOTOR_H_
#define CODE_OPHOT_MOTOR_H_

#include "zf_common_headfile.h"
#include "opHotCar.h"

//һ����������+һ����������
#define MOTOR_FREQ              (17000)
#define MOTOR_1_DIR             (P21_4)
#define MOTOR_1_PWM             (ATOM0_CH3_P21_5)
#define MOTOR_2_DIR             (P21_2)
#define MOTOR_2_PWM             (ATOM0_CH1_P21_3)

// PID����
#define MOTOR_PID_P             (160)
#define MOTOR_PID_I             (0)
#define MOTOR_PID_D             (-1)
#define MOTOR_PID_SL            (5000)
#define MOTOR_PID_UL            (4000)

// �������
#define MOTOR_DIFSPEED_FACTOR   (0.2)   // ��������ϵ��
#define MOTOR_DIFSPEED_THRE     (80)    // ���ٴ������������ռ�ձ�err��

// �ٶ�Ԥ��
#define MOTOR_START_SPEED       (60)
#define MOTOR_STRAIGHT_SPEED    (150)
#define MOTOR_COMMON_SPEED      (100)
#define MOTOR_CIRCLE_IN_SPEED   (70)


typedef enum
{
    MOTOR_1 = 0x00,
    MOTOR_2 = 0x01
} MOTOR_PWM_enum;

extern float Motor_target;
extern float Motor1_target;
extern float Motor2_target;

void Motor_Init(void);
void Motor_SetSpeed(MOTOR_PWM_enum motor_name, int16 speed);

void Motor_PID_Init(void);
void Motor1_PID_Set(float K_p_set, float K_i_set, float K_d_set, float pLimit, float coLimit, float boost);
void Motor2_PID_Set(float K_p_set, float K_i_set, float K_d_set, float pLimit, float coLimit, float boost);
void Motor1_SetPIDP(float setP);
void Motor1_SetPIDI(float setI);
void Motor1_SetPIDD(float setD);
void Motor1_SetPIDLimit(float pLimit);
void Motor1_SetPIDCoLimit(float coLimt);
void Motor2_SetPIDP(float setP);
void Motor2_SetPIDI(float setI);
void Motor2_SetPIDD(float setD);
void Motor2_SetPIDLimit(float pLimit);
void Motor2_SetPIDCoLimit(float coLimt);
void Motor_pidClear(void);
void Motor_GetTarget(void);
void Motor1_PIDwork(void);
void Motor2_PIDwork(void);


#endif /* CODE_OPHOT_MOTOR_H_ */
