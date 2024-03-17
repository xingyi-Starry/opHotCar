/*********************************************************************************************************************
 * TC264 Opensourec Library 即（TC264 开源库）是一个基于官方 SDK 接口的第三方开源库
 * Copyright (c) 2022 SEEKFREE 逐飞科技
 *
 * 本文件是 TC264 开源库的一部分
 *
 * TC264 开源库 是免费软件
 * 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
 * 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
 *
 * 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
 * 甚至没有隐含的适销性或适合特定用途的保证
 * 更多细节请参见 GPL
 *
 * 您应该在收到本开源库的同时收到一份 GPL 的副本
 * 如果没有，请参阅<https://www.gnu.org/licenses/>
 *
 * 额外注明：
 * 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
 * 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
 * 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
 * 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
 *
 * 文件名称          cpu0_main
 * 公司名称          成都逐飞科技有限公司
 * 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
 * 开发环境          ADS v1.9.4
 * 适用平台          TC264D
 * 店铺链接          https://seekfree.taobao.com/
 *
 * 修改记录
 * 日期              作者                备注
 * 2022-09-15       pudding            first version
 ********************************************************************************************************************/
#include "zf_common_headfile.h"
#include "opHotCar.h"
#pragma section all "cpu0_dsram"
// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中

// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设

// **************************** 代码区域 ****************************
uint16 x = 9;
uint16 y = 9;
uint32 duty = 750;

uint8 ImageInit_flag = 0;
uint8 image_bak[MT9V03X_H][MT9V03X_W];
uint8 data_buffer[32];
uint8 data_len;
uint8 pit_state = 0;

int core0_main(void)
{
    clock_init(); // 获取时钟频率<务必保留>
    debug_init(); // 初始化默认调试串口
    // 此处编写用户代码 例如外设初始化代码等

    // 硬件初始化
    mt9v03x_init();
    mt9v03x_set_exposure_time(100);
    ips200_init(IPS200_TYPE_PARALLEL8);
    wireless_uart_init();
    Motor_Init();
    Encoder_Init();
    Steer_Init();

    // 逐飞助手初始化
    seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_WIRELESS_UART);
    seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, image_bak[0], MT9V03X_W, MT9V03X_H);
    seekfree_assistant_camera_boundary_config(XY_BOUNDARY, 40, LeftLine_show[0], RightLine_show[0], NULL, LeftLine_show[1], RightLine_show[1], NULL);

    // 屏幕初始化
    ips200_set_dir(IPS200_CROSSWISE);
    ips200_set_font(IPS200_8X16_FONT);
    ips200_set_color(RGB565_BLACK, RGB565_GREEN);
    ips200_full(RGB565_GREEN);

    //-----------定时中断初始化---------------
    pit_ms_init(CCU60_CH0, 5); // ccu60_ch0(cpu0) 传感器数据采集
    pit_ms_init(CCU60_CH1, 500);
    pit_ms_init(CCU61_CH0, 10); // ccu61_ch0(cpu1) 图像处理

    // PID初始化
    Motor_PID_Init();
    // Motor1_PID_Set(MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_P, MOTOR_PID_SL, MOTOR_PID_UL, 1);
    // Motor2_PID_Set(MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_P, MOTOR_PID_SL, MOTOR_PID_UL, 1);

    cpu_wait_event_ready(); // 等待所有核心初始化完毕

    while (TRUE)
    {
        while (!ImageInit_flag)
        {
            data_len = (uint8)wireless_uart_read_buffer(data_buffer, 32);
            if (data_len != 0)
            {
                if (data_buffer[0] == 's')
                {
                    ImageInit_flag = 1;
                    Image_Init();
                    Motor1_PID_Set(MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D, MOTOR_PID_SL, MOTOR_PID_UL, 1);
                    Motor2_PID_Set(MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D, MOTOR_PID_SL, MOTOR_PID_UL, 1);
                }
            }
        }
        // 此处编写需要循环执行的代码
        // ips200_show_gray_image(30, 29, mt9v03x_image, MT9V03X_W, MT9V03X_H, 188, 120, 0);
        data_len = (uint8)wireless_uart_read_buffer(data_buffer, 32);
        if (data_len != 0)
        {
            switch (data_buffer[0])
            {
            case '0':
                Motor_SetSpeed(MOTOR_1, 1000);
                Motor_SetSpeed(MOTOR_2, 1000);
                break;
            case '1':
                Motor_SetSpeed(MOTOR_1, 0);
                Motor_SetSpeed(MOTOR_2, 0);
                break;
            case '2':
                duty += 10;
                wireless_uart_send_number(duty);
                wireless_uart_send_string("\r\n");
                break;
            case '3':
                duty -= 10;
                wireless_uart_send_number(duty);
                wireless_uart_send_string("\r\n");
                break;
            case '4':
                Motor1_PIDwork(50);
                Motor2_PIDwork(50);
                break;

            default:
                break;
            }
            memset(data_buffer, 0, 32);
        }

        Steer_SetDuty(duty);
        memcpy(image_bak[0], mt9v03x_image[0], MT9V03X_IMAGE_SIZE);
        ips200_show_gray_image(50, 50, image_bak[0], MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H, 0);
        Image_ShowLine(50, 50);
        ips200_show_uint(5, 5, Image_threSum, 3);
        ips200_show_uint(5, 21, Image_iptsLeftNum, 3);
        ips200_show_uint(5, 37, Image_iptsRightNum, 3);
        ips200_show_uint(5, 53, Image_rptsLeftsNum, 3);
        ips200_show_uint(5, 69, Image_rptsRightsNum, 3);
        ips200_show_int(5, 85, Encoder_1Data, 7);
        ips200_show_int(5, 101, Encoder_2Data, 7);

        // sf_ass_OnlyLine();
        if (mt9v03x_finish_flag)
        {
            mt9v03x_finish_flag = 0;

            // 在发送前将图像备份再进行发送，这样可以避免图像出现撕裂的问题
            memcpy(image_bak[0], mt9v03x_image[0], MT9V03X_IMAGE_SIZE);
            // 发送图像
            // seekfree_assistant_camera_send();
            // sf_ass_OnlyLine();
        }
        // 此处编写需要循环执行的代码
    }
}

#pragma section all restore

// **************************** 代码区域 ****************************
