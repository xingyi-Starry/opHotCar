/*
 * opHot_tracing.h
 *
 *  Created on: 2024年3月19日
 *      Author: 97329
 */

#ifndef CODE_OPHOT_TRACING_H_
#define CODE_OPHOT_TRACING_H_

#include "zf_common_headfile.h"
#include "opHotCar.h"

#define TRACE_CENTRAL       (94)

typedef enum
{
    LEFT_MIDLINE,
    RIGHT_MIDLINE
}TRACE_TYPE_enum;

extern uint8 tracing_aim;                     // 预瞄点在中线的位置


void Tracing_GetTarget(void);

#endif /* CODE_OPHOT_TRACING_H_ */
