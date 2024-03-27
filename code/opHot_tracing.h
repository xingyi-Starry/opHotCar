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

#define TRACE_CENTRAL       (86)    // 跟踪中心
#define TRACE_KDE           (470)     // 跟踪系数——占空比/误差，由实际情况决定，理论上控制方向的调参重点
#define LENGTH_OF_CAR       (30)    // 车身长度
#define TRACE_COMMON_AIM    (9)    // 标准预瞄点
#define TRACE_CLOSE_AIM     (7)     // 近预瞄点
#define TRACE_CROSS_AIM     (3)     // 十字预瞄点

typedef enum
{
    TRACE_LEFT_MIDLINE,
    TRACE_RIGHT_MIDLINE,
    TRACE_NONE
}TRACE_TYPE_enum;

extern float Err;
extern TRACE_TYPE_enum TRACE_TYPE;
extern uint8 tracing_aim;                     // 预瞄点在中线的位置
extern uint8 trace_central;
extern uint16 trace_kde;
extern uint8 length_of_car;


void Tracing_GetTarget(void);
void Tracing_Work(void);

#endif /* CODE_OPHOT_TRACING_H_ */
