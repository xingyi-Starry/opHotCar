/*
 * opHot_Steering.c
 *
 *  Created on: 2024年3月8日
 *      Author: 97329
 */
#include <opHot_steer.h>

PID Steer_PID;
float Steer_target = STEER_MID;     // 舵机PID目标占空比
float Steer_current = STEER_MID;

/**
 * @brief 舵机初始化
 * 
 */
void Steer_Init(void)
{
    pwm_init(SERVO_MOTOR_PWM, SERVO_MOTOR_FREQ, STEER_MID);
}

/**
 * @brief 设置舵机占空比
 * 
 * @param duty 占空比，取值690~820，750为中值，大于750右拐，小于750左拐
 */
void Steer_SetDuty(uint32 duty)
{
    // 限幅，保证安全
    if (duty > STEER_L_LIM)
        duty = STEER_L_LIM;
    else if (duty < STEER_R_LIM)
        duty = STEER_R_LIM;

    Steer_current = (float)duty;
    pwm_set_duty(SERVO_MOTOR_PWM, duty);
}

/**
 * @brief 舵机PID初始化
 * 
 */
void Steer_PID_Init(void)
{
    PID_Init(&Steer_PID);
}

/**
 * @brief 舵机PID设置参数
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

// 设置舵机PID积分限幅
void Steer_SetPIDLimit(float sumLimit)
{
    Steer_PID.sumLimit = sumLimit;
}

void Steer_SetPIDCoLimit(float coLimit)
{
    Steer_PID.utLimit = coLimit;
}

// 清除舵机PID的输出
void Steer_PID_Clear(void)
{
    Steer_PID.ut = 0;
}

void Steer_PIDwork(void)
{
    PID_PostionalPID(&Steer_PID, Steer_target, Steer_current);
    Steer_SetDuty((uint32)Steer_PID.ut);
}
