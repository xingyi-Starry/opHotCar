/*
 * opHot_crossline.h
 *
 *  Created on: 2024��3��28��
 *      Author: 97329
 */

#ifndef CODE_OPHOT_CROSSLINE_H_
#define CODE_OPHOT_CROSSLINE_H_

#include "opHotCar.h"
#include "zf_common_headfile.h"

#define CROSSLINE_RUNNING_CHANGE_THRE   (8) // �������ж��ڰ����������ֵ
#define CROSSLINE_RUNNING_ENCODER_THRE  (7500) // ��⵽�����ߺ���ʻ������ֵ

typedef enum 
{
    CROSSLINE_RUNNING,
    CROSSLINE_END
} CROSSLINE_STATE_enum;

extern uint8 CrossLine_value;
extern uint8 CrossLine_ChangeCount;

void CrossLine_Detect(void);
void CrossLine_Check(void);



#endif /* CODE_OPHOT_CROSSLINE_H_ */
