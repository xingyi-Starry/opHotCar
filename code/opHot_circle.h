/*
 * opHot_circle.h
 *
 *  Created on: 2024Äê3ÔÂ21ÈÕ
 *      Author: 97329
 */

#ifndef CODE_OPHOT_CIRCLE_H_
#define CODE_OPHOT_CIRCLE_H_

#include "zf_common_headfile.h"
#include "opHotCar.h"

#define CIRCLE_RECHECK_

typedef enum
{
    CIRCLE_NONE,

    CIRCLE_LEFT_BEGIN,
    CIRCLE_LEFT_IN,
    CIRCLE_LEFT_RUNNING,
    CIRCLE_LEFT_OUT,
    CIRCLE_LEFT_END,

    CIRCLE_RIGHT_BEGIN,
    CIRCLE_RIGHT_IN,
    CIRCLE_RIGHT_RUNNING,
    CIRCLE_RIGHT_OUT,
    CIRCLE_RIGHT_END
} CIRCLE_STATE_enum;

extern CIRCLE_STATE_enum CIRCLE_STATE;

void Circle_Check(void);

#endif /* CODE_OPHOT_CIRCLE_H_ */
