/*
 * opHot_tracing.c
 *
 *  Created on: 2024年3月19日
 *      Author: 97329
 */

#include "opHot_tracing.h"

float Err;
float gyro_target = 0;
const uint8 tracing_weigh[3] = {5, 3, 2};        // 目标计算权重
TRACE_TYPE_enum TRACE_TYPE = TRACE_RIGHT_MIDLINE; // 跟踪中线来源，由状态机决定
uint8 tracing_aim = TRACE_COMMON_AIM;            // 预瞄点在中线的位置
uint8 trace_central = TRACE_CENTRAL;
uint16 trace_factor = TRACE_FACTOR_COMMON;
uint8 length_of_car = LENGTH_OF_CAR;

/**
 * @brief   获取舵机PID目标值
 * @note    目标值为预瞄点以及预瞄点+1和预瞄点+2的加权平均，权重见数组tracing_weigh
 * @note    根据纯跟踪算法前轮偏角delta_angle = arctan(2Lsin(theta)/len_ahead)，其中L为车轮轴距，theta为目标与正前方夹角，len_ahead为目标到后轴距离
 * @note    近似可得delta_angle = k * err / (length_of_car + row_of_aim) (大概吧，我感觉的-linnuofan-2024/3/20)
 *
 */
void Tracing_GetTarget(void)
{
    // 标准巡线模式
    if (TRACE_TYPE == TRACE_LEFT_MIDLINE || TRACE_TYPE == TRACE_RIGHT_MIDLINE)
    {
        // 图像加权误差
        Err = (float)(Image_MidLine[bf_clip(tracing_aim, 0, Image_MidLineNum - 1)][0] * tracing_weigh[0] + (float)Image_MidLine[bf_clip(tracing_aim + 1, 0, Image_MidLineNum - 1)][0] * tracing_weigh[1] + (float)Image_MidLine[bf_clip(tracing_aim + 2, 0, Image_MidLineNum - 1)][0] * tracing_weigh[2]) / 10 - trace_central;
        // 误差对应目标占空比
        Steer_target = STEER_MID - Err * trace_factor / (length_of_car + MT9V03X_H - Image_MidLine[bf_clip(tracing_aim, 0, Image_MidLineNum - 1)][1]);
    }
    else if (TRACE_TYPE == TRACE_NONE)
        Steer_target = STEER_MID;
    else if (TRACE_TYPE == TRACE_STATIC)
        Steer_target = Steer_current;
    //陀螺仪控制模式
    else if (TRACE_TYPE == TRACE_GYRO)
    {
        Steer_target = (gyro_target - Gyro_z) * 5 + STEER_MID;
    }
    //    if (TRACE_TYPE == LEFT_MIDLINE)
    //    {
    //        Steer_target = (float)(Image_rptsLeftc[bf_clip(tracing_aim, 0, Image_rptsLeftcNum - 1)][0] * tracing_weigh[0] + Image_rptsLeftc[bf_clip(tracing_aim + 1, //0, Image_rptsLeftcNum - 1)][0] * tracing_weigh[1] + Image_rptsLeftc[bf_clip(tracing_aim + 2, 0, Image_rptsLeftcNum - 1)][0] * tracing_weigh[2]) / 10;
    //    }
    //    else if (TRACE_TYPE == RIGHT_MIDLINE)
    //    {
    //        Steer_target = (float)(Image_rptsRightc[bf_clip(tracing_aim, 0, Image_rptsLeftcNum - 1)][0] * tracing_weigh[0] + Image_rptsRightc[bf_clip(tracing_aim + //1, 0, Image_rptsLeftcNum - 1)][0] * tracing_weigh[1] + Image_rptsRightc[bf_clip(tracing_aim + 2, 0, Image_rptsLeftcNum - 1)][0] * tracing_weigh[2]) / 10;
    //    }
}

void Tracing_GetGyroTarget(void)
{
    if (Image_LeftLine_Lost == 1 && Image_RightLine_Lost == 0)
        gyro_target = 90 - Image_LeftTurnAngle;
    else if (Image_LeftLine_Lost == 0 && Image_RightLine_Lost == 1)
        gyro_target = 90 - Image_RightTurnAngle;
    else if (Image_LeftLine_Lost == 0 && Image_RightLine_Lost == 0)
    {
        if (Image_rptsLeftsNum > Image_rptsRightsNum)
            gyro_target = 90 - Image_LeftTurnAngle;
        else
            gyro_target = 90 - Image_RightTurnAngle;
    }
    else 
        gyro_target = 0;
}

/**
 * @brief       跟踪算法运行函数
 * @attention   应放在定时中断中，如图像处理中断之后
 *
 */
void Tracing_Work(void)
{
    Tracing_GetTarget();
    Steer_PIDwork();
}

/**
 * @brief 边线选择 优先右线
 *
 * @param TRACE_OTHER 丢线情况选择
 */
void Tracing_RightFirst(TRACE_TYPE_enum TRACE_OTHER)
{
    if (Image_RightLine_Lost == 0)
        TRACE_TYPE = TRACE_RIGHT_MIDLINE;
    else if (Image_LeftLine_Lost == 0)
        TRACE_TYPE = TRACE_LEFT_MIDLINE;
    else
        TRACE_TYPE = TRACE_OTHER;
}

/**
 * @brief 边线选择 优先左线
 *
 * @param TRACE_OTHER 丢线情况选择
 */
void Tracing_LeftFirst(TRACE_TYPE_enum TRACE_OTHER)
{
    if (Image_LeftLine_Lost == 0)
        TRACE_TYPE = TRACE_LEFT_MIDLINE;
    else if (Image_RightLine_Lost == 0)
        TRACE_TYPE = TRACE_RIGHT_MIDLINE;
    else
        TRACE_TYPE = TRACE_OTHER;
}

/**
 * @brief 边线选择 只巡右线
 *
 * @param TRACE_OTHER 丢线情况选择
 */
void Tracing_RightOnly(TRACE_TYPE_enum TRACE_OTHER)
{
    if (Image_RightLine_Lost == 0)
        TRACE_TYPE = TRACE_RIGHT_MIDLINE;
    else
        TRACE_TYPE = TRACE_OTHER;
}

/**
 * @brief 边线选择 只巡左线
 *
 * @param TRACE_OTHER 丢线情况选择
 */
void Tracing_LeftOnly(TRACE_TYPE_enum TRACE_OTHER)
{
    if (Image_LeftLine_Lost == 0)
        TRACE_TYPE = TRACE_LEFT_MIDLINE;
    else
        TRACE_TYPE = TRACE_OTHER;
}

/**
 * @brief 边线选择 优先外线
 * 
 * @param TRACE_OTHER 丢线情况选择
 */
void Tracing_OuterFirst(TRACE_TYPE_enum TRACE_OTHER)
{
    if (Image_LeftDir | Image_RightDir == TURNDIR_LEFT) // 使用或运算，我真天才吧 --linnuofan-2024/4/12
        Tracing_RightFirst(TRACE_OTHER);

    else if (Image_LeftDir | Image_RightDir == TURNDIR_RIGHT)
        Tracing_LeftFirst(TRACE_OTHER);
    
    else
        Tracing_LeftFirst(TRACE_OTHER); // 结果为0x00(直道)或0x03(?)时任选一边即可，此处根据我的习惯选左
}
