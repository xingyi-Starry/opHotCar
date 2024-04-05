/*
 * opHot_filter.h
 *
 *  Created on: 2024Äê4ÔÂ5ÈÕ
 *      Author: 97329
 */

#ifndef CODE_OPHOT_FILTER_H_
#define CODE_OPHOT_FILTER_H_

#include "opHotCar.h"
#include "zf_common_headfile.h"

float LowPass_Filter(float data, float last_out, float a);
float Sliding_Filter(float data[], float data_weigh[], uint8 data_num, uint8 *data_pointer, float new_data);

#endif /* CODE_OPHOT_FILTER_H_ */
