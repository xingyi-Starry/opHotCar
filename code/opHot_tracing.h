/*
 * opHot_tracing.h
 *
 *  Created on: 2024年3月19日
 *      Author: 97329
 */

#ifndef CODE_OPHOT_TRACING_H_
#define CODE_OPHOT_TRACING_H_

#include "zf_common_headfile.h"
#include "opHotCar.h"

#define TRACE_CENTRAL (88)    // 跟踪中心
#define TRACE_KDE (520)       // 跟踪系数——占空比/误差，由实际情况决定，理论上控制方向的调参重点
#define LENGTH_OF_CAR (27)    // 车身长度
#define TRACE_COMMON_AIM (27) // 标准预瞄点
#define TRACE_CLOSE_AIM (6)   // 近预瞄点
#define TRACE_CROSS_AIM (3)   // 十字预瞄点

typedef enum
{
    TRACE_LEFT_MIDLINE,  // 左巡线
    TRACE_RIGHT_MIDLINE, // 右巡线
    TRACE_NONE,          // 不巡线（归中）
    TRACE_STATIC,        // 不巡线（保持）
    TRACE_GYRO           // 不巡线（陀螺仪控制）
} TRACE_TYPE_enum;

extern float Err;
extern float gyro_target;
extern TRACE_TYPE_enum TRACE_TYPE;
extern uint8 tracing_aim; // 预瞄点在中线的位置
extern uint8 trace_central;
extern uint16 trace_kde;
extern uint8 length_of_car;

void Tracing_GetTarget(void);
void Tracing_GetGyroTarget(void);
void Tracing_Work(void);
void Tracing_LeftFirst(TRACE_TYPE_enum TRACE_OTHER);
void Tracing_RightFirst(TRACE_TYPE_enum TRACE_OTHER);
void Tracing_LeftOnly(TRACE_TYPE_enum TRACE_OTHER);
void Tracing_RightOnly(TRACE_TYPE_enum TRACE_OTHER);

#endif /* CODE_OPHOT_TRACING_H_ */
