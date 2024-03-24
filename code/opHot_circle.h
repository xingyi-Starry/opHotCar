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

#define CIRCLE_BEGIN_CORNER_EDGE_DIST (IMAGE_HEIGHT - 35)   // 状态机切换边界角点像素距离
#define CIRCLE_IN1_ENCODER_THRE (2000)                      // 退出CIRCLE_IN1编码器阈值
#define CIRCLE_IN2_ENCODER_THRE (2000)                      // 退出CIRCLE_IN2编码器阈值
#define CIRCLE_RUNNING_CORNER_EDGE_DIST (IMAGE_HEIGHT - 35) // 状态机切换边界角点像素距离
#define CIRCLE_OUT2_ENCODER_THRE (2000)                     // 退出CIRCLE_OUT2编码器阈值

typedef enum
{
    CIRCLE_NONE,

    CIRCLE_LEFT_BEGIN,   // 检测到单侧角点
    CIRCLE_LEFT_IN1,     // 右巡线寻找内环 编码器写死
    CIRCLE_LEFT_IN2,     // 左巡线入环 编码器写死
    CIRCLE_LEFT_RUNNING, // 巡外环 检测到角点
    CIRCLE_LEFT_OUT1,    // 巡内环出环 发现左线为直线
    CIRCLE_LEFT_OUT2,    // 巡右线离开环岛 编码器写死

    CIRCLE_RIGHT_BEGIN,   // 检测到单侧角点
    CIRCLE_RIGHT_IN1,     // 左巡线寻找内环 编码器写死
    CIRCLE_RIGHT_IN2,     // 右巡线入环 编码器写死
    CIRCLE_RIGHT_RUNNING, // 巡外环 检测到角点
    CIRCLE_RIGHT_OUT1,    // 巡内环出环 发现左线为直线
    CIRCLE_RIGHT_OUT2     // 巡左线离开环岛 编码器写死
} CIRCLE_STATE_enum;

extern CIRCLE_STATE_enum CIRCLE_STATE;

void Circle_Check(void);

#endif /* CODE_OPHOT_CIRCLE_H_ */
