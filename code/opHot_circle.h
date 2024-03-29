/*
 * opHot_circle.h
 *
 *  Created on: 2024年3月21日
 *      Author: 97329
 */

#ifndef CODE_OPHOT_CIRCLE_H_
#define CODE_OPHOT_CIRCLE_H_

#include "zf_common_headfile.h"
#include "opHotCar.h"

#define CIRCLE_BEGIN_CORNER_EDGE_DIST (IMAGE_HEIGHT - 15)   // 状态机切换边界角点像素距离
#define CIRCLE_RUNNING_CORNER_EDGE_DIST (IMAGE_HEIGHT - 20) // 状态机切换边界角点像素距离
#define CIRCLE_IN_ENCODER_THRE (26000)                      // 退出CIRCLE_IN编码器阈值
#define CIRCLE_RUNNING_ENCODER_THRE (100000)                // 退出CIRCLE_RUNNING编码器阈值
#define CIRCLE_OUT1_ENCODER_THRE (8500)                     // 退出CIRCLE_OUT1编码器阈值
#define CIRCLE_OUT2_ENCODER_THRE (15000)                    // 退出CIRCLE_OUT2编码器阈值
#define CIRCLE_RUNNING_GYRO_THRE (360)                      // 退出CIRCLE_RUNNING的陀螺仪阈值

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
