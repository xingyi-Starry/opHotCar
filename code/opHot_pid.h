/*
 * xiao_pid.h
 *
 *  Created on: 2023年5月1日
 *      Author: Jayden_NaN
 */

#ifndef CODE_OPHOT_PID_H_
#define CODE_OPHOT_PID_H_
#include "../libraries/zf_common/zf_common_headfile.h"
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

typedef struct STRUCT_PID PID;
void PID_Init(PID* p);
void PID_SetParameter(PID* p, float setP, float setI, float setD, float pLimit, float coLimit, float boost);
void PID_PostionalPID(PID* p, float target, float cur);
void PID_IncrementalPID(PID* p, float target, float cur);
#endif /* CODE_XIAO_PID_H_ */
