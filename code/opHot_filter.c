/*
 * opHot_filter.c
 *
 *  Created on: 2024年4月5日
 *      Author: 97329
 */
#include "opHot_filter.h"

/**
 * @brief 一阶低通滤波
 *
 * @param data      新数据
 * @param last_out  上次输出
 * @param a         灵敏度
 * @return float    滤波输出
 */
float LowPass_Filter(float data, float last_out, float a)
{
    last_out = a * data + (1 - a) * last_out;
    return (last_out);
}

/**
 * @brief 滑动窗口滤波
 * 
 * @param data          数据序列
 * @param data_weigh    滤波权重
 * @param data_num      序列长度
 * @param data_pointer  数据指针
 * @param new_data      新输入的数据
 * @return data_out     滤波输出
 */
float Sliding_Filter(float data[], float data_weigh[], uint8 data_num, uint8 *data_pointer, float new_data)
{
    float data_out = 0;
    data[*data_pointer] = new_data;
    for (uint8 i = 0; i < data_num; i++)
    {
        uint8 index = *data_pointer - i;
        if (index < 0)
            index += data_num;
        data_out += data[index] * data_weigh[index];
    }
    *data_pointer = ((*data_pointer)++) % data_num;
    return data_out;
}
