/*
 * opHot_tracing.c
 *
 *  Created on: 2024��3��19��
 *      Author: 97329
 */

#include "opHot_tracing.h"

TRACE_TYPE_enum TRACE_TYPE = LEFT_MIDLINE;
const uint8 tracing_weigh[3] = {5, 3, 2};   // Ŀ�����Ȩ��
uint8 tracing_aim = 20;                     // Ԥ��������ߵ�λ��

void Tracing_GetTarget(void)
{
    if (TRACE_TYPE == LEFT_MIDLINE)
    {
        Steer_target = (float)Image_rptsLeftc[bf_clip(tracing_aim, 0, Image_rptsLeftcNum - 1)][0] * tracing_weigh[0] + Image_rptsLeftc[bf_clip(tracing_aim + 1, 0, Image_rptsLeftcNum - 1)][0] * tracing_weigh[1] + Image_rptsLeftc[bf_clip(tracing_aim + 2, 0, Image_rptsLeftcNum - 1)][0] * tracing_weigh[2];
    }
    else if (TRACE_TYPE == RIGHT_MIDLINE)
    {
        Steer_target = (float)Image_rptsRightc[bf_clip(tracing_aim, 0, Image_rptsLeftcNum - 1)][0] * tracing_weigh[0] + Image_rptsRightc[bf_clip(tracing_aim + 1, 0, Image_rptsLeftcNum - 1)][0] * tracing_weigh[1] + Image_rptsRightc[bf_clip(tracing_aim + 2, 0, Image_rptsLeftcNum - 1)][0] * tracing_weigh[2];
    }
}
