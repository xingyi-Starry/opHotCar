/*
 * opHotCar.h
 *
 *  Created on: 2024��1��23��
 *      Author: 97329
 */

#ifndef CODE_OPHOTCAR_H_
#define CODE_OPHOTCAR_H_

#include "cpu0_main.h"
#include "zf_myFunction.h"
#include "opHot_encoder.h"
#include "opHot_motor.h"
#include "opHot_pid.h"
#include "opHot_steer.h"
#include "opHot_image_processing.h"
#include "opHot_tracing.h"
#include "opHot_image_show.h"

#define LED1                    (P20_9)
#define LED2                    (P20_8)

#define KEY1                    (P20_6)
#define KEY2                    (P20_7)
#define KEY3                    (P11_2)
#define KEY4                    (P11_3)

extern uint8 test_value;

#endif /* CODE_OPHOTCAR_H_ */
