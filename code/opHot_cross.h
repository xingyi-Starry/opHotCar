/*
 * opHot_cross.h
 *
 *  Created on: 2024��3��21��
 *      Author: 97329
 */

#ifndef CODE_OPHOT_CROSS_H_
#define CODE_OPHOT_CROSS_H_

#include "zf_common_headfile.h"
#include "opHotCar.h"

#define CROSS_ENTER_CORNER_EDGE_DIST    (IMAGE_HEIGHT - 35)      // ״̬���л��߽�ǵ����ؾ���
#define CROSS_EXIT_ENCODER_THRE         (7000)                    // �˳�CROSS_EXIT��������ֵ

typedef enum
{
    CROSS_ENTER,
    CROSS_RUNNING,
    CROSS_EXIT
} CROSS_STATE_enum;

extern CROSS_STATE_enum CROSS_STATE;

void Cross_Check(void);

#endif /* CODE_OPHOT_CROSS_H_ */
