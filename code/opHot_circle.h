/*
 * opHot_circle.h
 *
 *  Created on: 2024��3��21��
 *      Author: 97329
 */

#ifndef CODE_OPHOT_CIRCLE_H_
#define CODE_OPHOT_CIRCLE_H_

#include "zf_common_headfile.h"
#include "opHotCar.h"

#define CIRCLE_BEGIN_CORNER_EDGE_DIST (IMAGE_HEIGHT - 35)   // ״̬���л��߽�ǵ����ؾ���
#define CIRCLE_IN1_ENCODER_THRE (2000)                      // �˳�CIRCLE_IN1��������ֵ
#define CIRCLE_IN2_ENCODER_THRE (2000)                      // �˳�CIRCLE_IN2��������ֵ
#define CIRCLE_RUNNING_CORNER_EDGE_DIST (IMAGE_HEIGHT - 35) // ״̬���л��߽�ǵ����ؾ���
#define CIRCLE_OUT2_ENCODER_THRE (2000)                     // �˳�CIRCLE_OUT2��������ֵ

typedef enum
{
    CIRCLE_NONE,

    CIRCLE_LEFT_BEGIN,   // ��⵽����ǵ�
    CIRCLE_LEFT_IN1,     // ��Ѳ��Ѱ���ڻ� ������д��
    CIRCLE_LEFT_IN2,     // ��Ѳ���뻷 ������д��
    CIRCLE_LEFT_RUNNING, // Ѳ�⻷ ��⵽�ǵ�
    CIRCLE_LEFT_OUT1,    // Ѳ�ڻ����� ��������Ϊֱ��
    CIRCLE_LEFT_OUT2,    // Ѳ�����뿪���� ������д��

    CIRCLE_RIGHT_BEGIN,   // ��⵽����ǵ�
    CIRCLE_RIGHT_IN1,     // ��Ѳ��Ѱ���ڻ� ������д��
    CIRCLE_RIGHT_IN2,     // ��Ѳ���뻷 ������д��
    CIRCLE_RIGHT_RUNNING, // Ѳ�⻷ ��⵽�ǵ�
    CIRCLE_RIGHT_OUT1,    // Ѳ�ڻ����� ��������Ϊֱ��
    CIRCLE_RIGHT_OUT2     // Ѳ�����뿪���� ������д��
} CIRCLE_STATE_enum;

extern CIRCLE_STATE_enum CIRCLE_STATE;

void Circle_Check(void);

#endif /* CODE_OPHOT_CIRCLE_H_ */
