/*
 * opHot_filter.c
 *
 *  Created on: 2024��4��5��
 *      Author: 97329
 */
#include "opHot_filter.h"

/**
 * @brief һ�׵�ͨ�˲�
 *
 * @param data      ������
 * @param last_out  �ϴ����
 * @param a         ������
 * @return float    �˲����
 */
float LowPass_Filter(float data, float last_out, float a)
{
    last_out = a * data + (1 - a) * last_out;
    return (last_out);
}

/**
 * @brief ���������˲�
 * 
 * @param data          ��������
 * @param data_weigh    �˲�Ȩ��
 * @param data_num      ���г���
 * @param data_pointer  ����ָ��
 * @param new_data      �����������
 * @return data_out     �˲����
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
