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

#define CIRCLE_BEGIN_CORNER_EDGE_DIST (IMAGE_HEIGHT - 15)   // ״̬���л��߽�ǵ����ؾ���
#define CIRCLE_RUNNING_CORNER_EDGE_DIST (IMAGE_HEIGHT - 20) // ״̬���л��߽�ǵ����ؾ���
#define CIRCLE_IN_ENCODER_THRE (26000)                      // �˳�CIRCLE_IN��������ֵ
#define CIRCLE_RUNNING_ENCODER_THRE (100000)                // �˳�CIRCLE_RUNNING��������ֵ
#define CIRCLE_OUT1_ENCODER_THRE (8500)                     // �˳�CIRCLE_OUT1��������ֵ
#define CIRCLE_OUT2_ENCODER_THRE (15000)                    // �˳�CIRCLE_OUT2��������ֵ
#define CIRCLE_RUNNING_GYRO_THRE (360)                      // �˳�CIRCLE_RUNNING����������ֵ

typedef enum
{
    CIRCLE_NONE,

    CIRCLE_LEFT_BEGIN,   //
    CIRCLE_LEFT_IN,      //
    CIRCLE_LEFT_RUNNING, //
    CIRCLE_LEFT_OUT,     //
    CIRCLE_LEFT_END,

    CIRCLE_RIGHT_BEGIN,   //
    CIRCLE_RIGHT_IN,      //
    CIRCLE_RIGHT_RUNNING, //
    CIRCLE_RIGHT_OUT,     //
    CIRCLE_RIGHT_END      //
} CIRCLE_STATE_enum;

extern CIRCLE_STATE_enum CIRCLE_STATE;

void Circle_Check(void);

#endif /* CODE_OPHOT_CIRCLE_H_ */
