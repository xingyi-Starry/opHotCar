/*
 * opHot_overall_state.h
 *
 *  Created on: 2024Äê3ÔÂ21ÈÕ
 *      Author: 97329
 */

#ifndef CODE_OPHOT_OVERALL_STATE_H_
#define CODE_OPHOT_OVERALL_STATE_H_

#include "zf_common_headfile.h"
#include "opHotCar.h"

#define     START_ENCODER_THRE  (6500)

typedef enum
{
    COMMON_ROAD,
    CROSS,
    CIRCLE,
    CROSSLINE,
    SLOPE,
    START,
    TEST
} OVERALL_STATE_enum;

extern OVERALL_STATE_enum OVERALL_STATE;

void State_Check(void);
void State_AimJudge(void);
void Start_Check(void);

#endif /* CODE_OPHOT_OVERALL_STATE_H_ */
