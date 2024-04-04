/*
 * opHotCar.h
 *
 *  Created on: 2024Äê1ÔÂ23ÈÕ
 *      Author: 97329
 */

#ifndef CODE_OPHOTCAR_H_
#define CODE_OPHOTCAR_H_

#include "cpu0_main.h"
#include "zf_myFunction.h"
#include "opHot_encoder.h"
#include "opHot_motor.h"
#include "opHot_gyroscope.h"
#include "opHot_pid.h"
#include "opHot_steer.h"
#include "opHot_image_processing.h"
#include "opHot_tracing.h"
#include "opHot_image_show.h"
#include "opHot_overall_state.h"
#include "opHot_circle.h"
#include "opHot_cross.h"
#include "opHot_common_road.h"
#include "opHot_crossline.h"
#include "opHot_osci.h"

#define LED1                    (P20_9)
#define LED2                    (P20_8)

#define KEY1                    (P20_6)
#define KEY2                    (P20_7)
#define KEY3                    (P11_2)
#define KEY4                    (P11_3)

extern uint8 fps;

#endif /* CODE_OPHOTCAR_H_ */
