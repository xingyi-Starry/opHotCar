/*
 * opHot_Osci.c
 *
 *  Created on: 2024��4��4��
 *      Author: 97329
 */

#include "opHot_osci.h"

seekfree_assistant_oscilloscope_struct osci_data;

/**
 * @brief ����ʾ������ʼ��
 * @note  ��4��ͨ�� ch0-�����ٶ� ch1-�����ٶ� ch2-����Ŀ�� ch3-����Ŀ��
 * 
 */
void Osci_Init(void)
{
    osci_data.channel_num = 4;    
}

/**
 * @brief ʾ������������
 * 
 */
void Osci_Send(void)
{
    osci_data.data[0] = Encoder_1Data;
    osci_data.data[1] = Encoder_2Data;
    osci_data.data[2] = Motor1_target;
    osci_data.data[3] = Motor2_target;
    seekfree_assistant_oscilloscope_send(&osci_data);
}


