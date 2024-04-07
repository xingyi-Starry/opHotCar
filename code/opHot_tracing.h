/*
 * opHot_tracing.h
 *
 *  Created on: 2024��3��19��
 *      Author: 97329
 */

#ifndef CODE_OPHOT_TRACING_H_
#define CODE_OPHOT_TRACING_H_

#include "zf_common_headfile.h"
#include "opHotCar.h"

#define TRACE_CENTRAL (88)    // ��������
#define TRACE_KDE (520)       // ����ϵ������ռ�ձ�/����ʵ����������������Ͽ��Ʒ���ĵ����ص�
#define LENGTH_OF_CAR (27)    // ������
#define TRACE_COMMON_AIM (27) // ��׼Ԥ���
#define TRACE_CLOSE_AIM (6)   // ��Ԥ���
#define TRACE_CROSS_AIM (3)   // ʮ��Ԥ���

typedef enum
{
    TRACE_LEFT_MIDLINE,  // ��Ѳ��
    TRACE_RIGHT_MIDLINE, // ��Ѳ��
    TRACE_NONE,          // ��Ѳ�ߣ����У�
    TRACE_STATIC,        // ��Ѳ�ߣ����֣�
    TRACE_GYRO           // ��Ѳ�ߣ������ǿ��ƣ�
} TRACE_TYPE_enum;

extern float Err;
extern float gyro_target;
extern TRACE_TYPE_enum TRACE_TYPE;
extern uint8 tracing_aim; // Ԥ��������ߵ�λ��
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
