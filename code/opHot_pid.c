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

/**
 * @brief               模糊PID
 * @parameter p         用来工作的PID参数
 * @parameter target    目标值
 * @parameter cur       当前值
 * @parameter pidClass  用来工作的PID模式
 * @parameter ERROR_MAX 论域映射ERROR最大值
 * @parameter DERROR_MAX 论域映射DERROR最大值和
 */
//模糊规则
MEMBERSHIP_enum PRULE[7][7]={
    {PB, PB, PM, PM, PS, ZO, ZO},
    {PB, PB, PM, PS, PS, ZO, NS},
    {PM, PM, PM, PS, ZO, NS, NS},
    {PM, PM, PS, ZO, NS, NM, NM},
    {PS, PS, ZO, NS, NS, NM, NM},
    {PS, ZO, NS, NM, NM, NM, NB},
    {ZO, ZO, NM, NM, NM, NB, NB}
};
MEMBERSHIP_enum IRULE[7][7]={
    {NB, NB, NM, NM, NS, ZO, ZO},
    {NB, NB, NM, NS, NS, ZO, ZO},
    {NB, NM, NS, NS, ZO, PS, PS},
    {NM, NM, NS, ZO, PS, PM, PM},
    {NM, NS, ZO, PS, PS, PM, PB},
    {ZO, ZO, PS, PS, PM, PB, PB},
    {ZO, ZO, PS, PM, PM, PB, PB}
};
MEMBERSHIP_enum DRULE[7][7]={
    {PS, NS, NB, NB, NB, NM, PS},
    {PS, NS, NB, NM, NM, NS, ZO},
    {ZO, NS, NM, NM, NS, NS, ZO},
    {ZO, NS, NS, NS, NS, NS, ZO},
    {ZO, ZO, ZO, ZO, ZO, ZO, ZO},
    {PB, PS, PS, PS, PS, PS, PB},
    {PB, PM, PM, PM, PS, PS, PB}
};
//隶属度信息
MEMBERSHIP object;
//PID变动范围
float P_LIMIT =0.3;
float I_LIMIT =0.3;
float D_LIMIT =0.3;
void PID_FuzzyPID(PID* p, float target, float cur, PIDCLASS_enum pidClass,float ERROR_MAX,float DERROR_MAX){
    float error = target - cur;
    float derror = error - p->preError;
    //论域映射
    error = error * 3 / ERROR_MAX;
    derror = derror * 3 / DERROR_MAX;
    if (error > 3) error = 3;
    else if (error < -3) error = -3;
    if (derror > 3) derror = 3;
    else if (derror < -3) derror = -3;
    //隶属度确认
    if (error >= 0) {
        object.membershipErrorLeft = (MEMBERSHIP_enum)error;
        object.membershipErrorRight = (MEMBERSHIP_enum)(object.membershipErrorLeft + 1);
        object.valueErrorLeft = object.membershipErrorRight - error;
        object.valueErrorRight = error - object.membershipErrorLeft;
        if (object.membershipErrorLeft == PB) object.membershipErrorRight = PB;
    }
    else {
        object.membershipErrorRight = (MEMBERSHIP_enum)error;
        object.membershipErrorLeft = (MEMBERSHIP_enum)(object.membershipErrorRight - 1);
        object.valueErrorLeft = object.membershipErrorRight - error;
        object.valueErrorRight = derror - object.membershipErrorLeft;
        if (object.membershipErrorRight == NB) object.membershipErrorLeft = NB;
    }
    if (derror >= 0) {
        object.membershipDerrorLeft = (MEMBERSHIP_enum)derror;
        object.membershipDerrorRight = (MEMBERSHIP_enum)(object.membershipDerrorLeft + 1);
        object.valueDerrorLeft = object.membershipDerrorRight - derror;
        object.valueDerrorRight = derror - object.membershipDerrorLeft;
        if (object.membershipDerrorLeft == PB) object.membershipDerrorRight = PB;
    }
    else {
        object.membershipDerrorRight = (MEMBERSHIP_enum)derror;
        object.membershipDerrorLeft = (MEMBERSHIP_enum)(object.membershipDerrorRight - 1);
        object.valueDerrorLeft = object.membershipDerrorRight - derror;
        object.valueDerrorRight = derror - object.membershipDerrorLeft;
        if (object.membershipDerrorRight == NB) object.membershipDerrorLeft = NB;
    }
    //模糊推理与去模糊
    object.membershipKP = PRULE[3+object.membershipErrorLeft][3+object.membershipDerrorLeft]*object.valueErrorLeft*object.valueDerrorLeft
                         +PRULE[3+object.membershipErrorLeft][3+object.membershipDerrorRight]*object.valueErrorLeft*object.valueDerrorRight
                         +PRULE[3+object.membershipErrorRight][3+object.membershipDerrorLeft]*object.valueErrorRight*object.valueDerrorLeft
                         +PRULE[3+object.membershipErrorRight][3+object.membershipDerrorRight]*object.valueErrorRight*object.valueDerrorRight;
    object.membershipKI = IRULE[3+object.membershipErrorLeft][3+object.membershipDerrorLeft]*object.valueErrorLeft*object.valueDerrorLeft
                         +IRULE[3+object.membershipErrorLeft][3+object.membershipDerrorRight]*object.valueErrorLeft*object.valueDerrorRight
                         +IRULE[3+object.membershipErrorRight][3+object.membershipDerrorLeft]*object.valueErrorRight*object.valueDerrorLeft
                         +IRULE[3+object.membershipErrorRight][3+object.membershipDerrorRight]*object.valueErrorRight*object.valueDerrorRight;
    object.membershipKD = DRULE[3+object.membershipErrorLeft][3+object.membershipDerrorLeft]*object.valueErrorLeft*object.valueDerrorLeft
                         +DRULE[3+object.membershipErrorLeft][3+object.membershipDerrorRight]*object.valueErrorLeft*object.valueDerrorRight
                         +DRULE[3+object.membershipErrorRight][3+object.membershipDerrorLeft]*object.valueErrorRight*object.valueDerrorLeft
                         +DRULE[3+object.membershipErrorRight][3+object.membershipDerrorRight]*object.valueErrorRight*object.valueDerrorRight;
    //输出计算
    if(pidClass == PostionalPID){
        p->kP=p->kPSet+object.membershipKP*P_LIMIT/3;
        p->kD=p->kDSet+object.membershipKD*D_LIMIT/3;
    }
    else if(pidClass == IncrementalPID){
        p->kP=p->kPSet+object.membershipKP*P_LIMIT/3;
        p->kI=p->kISet+object.membershipKI*I_LIMIT/3;
        p->kD=p->kDSet+object.membershipKD*D_LIMIT/3;
    }

    //PID控制
    if(pidClass == PostionalPID){
        PID_PostionalPID(p, target, cur);
    }
    else if(pidClass == IncrementalPID){
        PID_IncrementalPID(p, target, cur);
    }
}
