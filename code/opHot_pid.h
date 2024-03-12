/*
 * xiao_pid.h
 *
 *  Created on: 2023年5月1日
 *      Author: Jayden_NaN
 */

#ifndef CODE_OPHOT_PID_H_
#define CODE_OPHOT_PID_H_
#include "../libraries/zf_common/zf_common_headfile.h"
//隶属度等级
typedef enum{
    NB = -3, NM, NS, ZO, PS, PM, PB,
}MEMBERSHIP_enum;
//PID类型
typedef enum{
    PostionalPID,IncrementalPID
}PIDCLASS_enum;
//PID结构体
struct STRUCT_PID {
        float kP;
        float kI;
        float kD;
        float kPSet;
        float kISet;
        float kDSet;
        float sum;
        float preError;
        float ppreError;
        float ut;
        float sumLimit;
        float utLimit;
};

//隶属度结构体
struct STRUCT_MEMBERSHIP{
        MEMBERSHIP_enum membershipErrorLeft;
        float valueErrorLeft;
        MEMBERSHIP_enum membershipErrorRight;
        float valueErrorRight;
        MEMBERSHIP_enum membershipDerrorLeft;
        float valueDerrorLeft;
        MEMBERSHIP_enum membershipDerrorRight;
        float valueDerrorRight;
        float membershipKP;
        float membershipKI;
        float membershipKD;
};
typedef struct STRUCT_PID PID;
typedef struct STRUCT_MEMBERSHIP MEMBERSHIP;
void PID_Init(PID* p);
void PID_SetParameter(PID* p, float setP, float setI, float setD, float pLimit, float coLimit, float boost);
void PID_PostionalPID(PID* p, float target, float cur);
void PID_IncrementalPID(PID* p, float target, float cur);
void PID_FuzzyPID(PID* p, float target, float cur, PIDCLASS_enum pidClass,float ERROR_MAX,float DERROR_MAX);
#endif /* CODE_XIAO_PID_H_ */
