/*
 * opHot_slope.h
 *
 *  Created on: 2024年4月4日
 *      Author: 97329
 */

#ifndef CODE_OPHOT_SLOPE_H_
#define CODE_OPHOT_SLOPE_H_

#include "opHotCar.h"
#include "zf_common_headfile.h"

#define SLOPE_RUNNING_ENCODER_THRE  (7500) // 退出坡道状态编码器阈值

typedef enum
{
    SLOPE_RUNNING
} SLOPE_STATE_enum;

void Slope_Detect(void);
void Slope_Check(void);

#endif /* CODE_OPHOT_SLOPE_H_ */
