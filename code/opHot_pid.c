/*
 * xiao_pid.c
 *
 *  Created on: 2023年5月1日
 *      Author: Jayden_NaN
 */

#include "opHot_pid.h"
/**
 * @brief           PID初始化
 * @parameter p     待初始化的指针
 * @return          NULL
 */
void PID_Init(PID* p) {
    p->kP = 0.0;
    p->kI = 0.0;
    p->kD = 0.0;
    p->kPSet = 0.0;
    p->kISet = 0.0;
    p->kDSet = 0.0;
    p->sum = 0.0;
    p->preError = 0.0;
    p->ppreError = 0.0;
    p->ut = 0.0;
    p->sumLimit = 0.0;
    p->utLimit = 0.0;
}

/**
 * @brief               整体设置p的各项参数
 * @parameter pLimit    积分限幅
 * @parameter coLimit   修正限幅
 * @return              NULL
 */
void PID_SetParameter(PID* p, float setP, float setI, float setD, float pLimit, float coLimit, float boost) {
    p->kPSet = boost * setP;
    p->kISet = boost * setI;
    p->kDSet = boost * setD;
    p->sumLimit = pLimit;
    p->utLimit = coLimit;
    p->kP =p->kPSet;
    p->kI =p->kISet;
    p->kD =p->kDSet;
}
/**
 * @brief               位置式PID
 * @parameter   p       用来工作的PID参数
 * @parameter   target  目标值
 * @parameter   cur     当前值
 */
void PID_PostionalPID(PID* p, float target, float cur) {
    float error = target - cur;
    //误差积分
    p->sum += error * p->kI;
    //进行积分限幅
    p->sum = p->sum > p->sumLimit ? p->sumLimit : p->sum;
    p->sum = p->sum < -p->sumLimit ? -p->sumLimit : p->sum;
    //数据进行计算
    if(-1 < error - p->preError && error - p->preError < 1){
        p->ut = p->kP * error;
    }
    else{
        p->ut = p->kP * error
            + p->sum
            + p->kD * (error - p->preError);
    }
    //进行修正限幅
    p->ut = p->ut > p->utLimit ? p->utLimit : p->ut;
    p->ut = p->ut < -p->utLimit ? -p->utLimit : p->ut;
    //进行数据更新
    p->preError = error;
}

/**
 * @brief               增量式PID
 * @parameter p         用来工作的PID参数
 * @parameter target    目标值
 * @parameter cur      当前值
 *
 */
void PID_IncrementalPID(PID* p, float target, float cur) {
    float error = target - cur;
    //数据进行增加
    p->ut += p->kP * (error - p->preError)
            + p->kI * error
            + p->kD * (error - 2 * p->preError + p->preError);
    //进行修正限幅
    p->ut = p->ut > p->utLimit ? p->utLimit : p->ut;
    p->ut = p->ut < -p->utLimit ? -p->utLimit : p->ut;
    //进行数据更新
    p->ppreError = p->preError;
    p->preError = error;
}
