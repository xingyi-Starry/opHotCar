/*
 * opHot_Osci.c
 *
 *  Created on: 2024年4月4日
 *      Author: 97329
 */

#include "opHot_osci.h"

seekfree_assistant_oscilloscope_struct osci_data;

/**
 * @brief 虚拟示波器初始化
 * @note  共4个通道 ch0-左轮速度 ch1-右轮速度 ch2-左轮目标 ch3-右轮目标
 * 
 */
void Osci_Init(void)
{
    osci_data.channel_num = 4;    
}

/**
 * @brief 示波器发送数据
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


