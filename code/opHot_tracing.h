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

#define TRACE_CENTRAL       (86)    // ��������
#define TRACE_KDE           (490)     // ����ϵ������ռ�ձ�/����ʵ����������������Ͽ��Ʒ���ĵ����ص�
#define LENGTH_OF_CAR       (30)    // ������
#define TRACE_COMMON_AIM    (20)    // ��׼Ԥ���
#define TRACE_CLOSE_AIM     (5)     // ��Ԥ���
#define TRACE_CROSS_AIM     (3)     // ʮ��Ԥ���

typedef enum
{
    TRACE_LEFT_MIDLINE,
    TRACE_RIGHT_MIDLINE,
    TRACE_NONE
}TRACE_TYPE_enum;

extern float Err;
extern TRACE_TYPE_enum TRACE_TYPE;
extern uint8 tracing_aim;                     // Ԥ��������ߵ�λ��
extern uint8 trace_central;
extern uint16 trace_kde;
extern uint8 length_of_car;


void Tracing_GetTarget(void);
void Tracing_Work(void);

#endif /* CODE_OPHOT_TRACING_H_ */
