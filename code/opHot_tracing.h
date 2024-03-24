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

#define TRACE_CENTRAL       (92)    // ��������
#define TRACE_KDE           (780)     // ����ϵ������ռ�ձ�/����ʵ����������������Ͽ��Ʒ���ĵ����ص�
#define LENGTH_OF_CAR       (15)    // ������
#define TRACE_COMMON_AIM    (20)    // ��׼Ԥ���
#define TRACE_CLOSE_AIM     (15)     // ��Ԥ���
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


void Tracing_GetTarget(void);
void Tracing_Work(void);

#endif /* CODE_OPHOT_TRACING_H_ */
