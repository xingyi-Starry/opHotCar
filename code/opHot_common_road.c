#include "opHot_common_road.h"
/*
 * opHot_common_road.c
 *
 *  Created on: 2024��3��21��
 *      Author: 97329
 */

void CommonRoad_Check(void)
{
    if (Image_LptLeft_Found == true && Image_LptRight_Found == true)
    {
        // �ǵ���μ�飬��ʱ����
        OVERALL_STATE = CROSS;
    }
}