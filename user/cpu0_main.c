/*********************************************************************************************************************
 * TC264 Opensourec Library ����TC264 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
 * Copyright (c) 2022 SEEKFREE ��ɿƼ�
 *
 * ���ļ��� TC264 ��Դ���һ����
 *
 * TC264 ��Դ�� ��������
 * �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
 * �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
 *
 * ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
 * ����û�������������Ի��ʺ��ض���;�ı�֤
 * ����ϸ����μ� GPL
 *
 * ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
 * ���û�У������<https://www.gnu.org/licenses/>
 *
 * ����ע����
 * ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
 * �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
 * ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
 * ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
 *
 * �ļ�����          cpu0_main
 * ��˾����          �ɶ���ɿƼ����޹�˾
 * �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
 * ��������          ADS v1.9.4
 * ����ƽ̨          TC264D
 * ��������          https://seekfree.taobao.com/
 *
 * �޸ļ�¼
 * ����              ����                ��ע
 * 2022-09-15       pudding            first version
 ********************************************************************************************************************/
#include "zf_common_headfile.h"
#include "opHotCar.h"
#pragma section all "cpu0_dsram"
// ���������#pragma section all restore���֮���ȫ�ֱ���������CPU0��RAM��

// �������ǿ�Դ��չ��� ��������ֲ���߲��Ը���������
// �������ǿ�Դ��չ��� ��������ֲ���߲��Ը���������
// �������ǿ�Դ��չ��� ��������ֲ���߲��Ը���������

// **************************** �������� ****************************
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
    clock_init(); // ��ȡʱ��Ƶ��<��ر���>
    debug_init(); // ��ʼ��Ĭ�ϵ��Դ���
    // �˴���д�û����� ���������ʼ�������

    // Ӳ����ʼ��
    mt9v03x_init();
    mt9v03x_set_exposure_time(100);
    ips200_init(IPS200_TYPE_PARALLEL8);
    wireless_uart_init();
    Motor_Init();
    encoder_dir_init(TIM6_ENCODER, TIM6_ENCODER_CH1_P20_3, TIM6_ENCODER_CH2_P20_0);
    Steer_Init();

    // �����ʼ��
    seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_WIRELESS_UART);
    //seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, image_bak[0], MT9V03X_W, MT9V03X_H);

    ips200_set_dir(IPS200_CROSSWISE);
    ips200_set_font(IPS200_8X16_FONT);
    ips200_set_color(RGB565_BLACK, RGB565_GREEN);
    ips200_full(RGB565_GREEN);
    // �˴���д�û����� ���������ʼ�������
    // ��ʱ�жϳ�ʼ��
    // cc61(cpu1) ͼ����
    gpio_init(LED1, GPO, GPIO_LOW, GPO_PUSH_PULL);  // ��ʼ�� LED1 ��� Ĭ�ϵ͵�ƽ �������ģʽ
    gpio_init(LED2, GPO, GPIO_HIGH, GPO_PUSH_PULL); // ��ʼ�� LED2 ��� Ĭ�ϸߵ�ƽ �������ģʽ
    // pit_ms_init(CCU60_CH0, 500);
    cpu_wait_event_ready(); // �ȴ����к��ĳ�ʼ�����

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
                    seekfree_assistant_camera_boundary_config(XY_BOUNDARY, 40, LeftLine_show[0], RightLine_show[0], NULL, LeftLine_show[1], RightLine_show[1], NULL);
                    // pit_ms_init(CCU61_CH0, 10);
                }
            }
        }
        // �˴���д��Ҫѭ��ִ�еĴ���
        if (pit_state)
        {
            gpio_toggle_level(LED1);
            gpio_toggle_level(LED2);
            pit_state = 0; // ��������жϴ�����־λ
        }
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

            default:
                break;
            }
            memset(data_buffer, 0, 32);
        }

        //        if (mt9v03x_finish_flag == 1)
        //        {
        //            Image_Process(mt9v03x_image[0]);
        //        }
        Steer_SetDuty(duty);
        memcpy(image_bak[0], mt9v03x_image[0], MT9V03X_IMAGE_SIZE);
        ips200_show_gray_image(50, 50, image_bak[0], MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H, 0);
        if (mt9v03x_finish_flag == 1)
        {
            Image_Process(mt9v03x_image[0]);
        }
        Image_ShowLine(50, 50);
        ips200_show_uint(5, 5, Image_threSum, 3);
        ips200_show_uint(5, 21, Image_iptsLeftNum, 3);
        ips200_show_uint(5, 37, Image_iptsRightNum, 3);
        ips200_show_uint(5, 53, Image_rptsLeftsNum, 3);
        ips200_show_uint(5, 69, Image_rptsRightsNum, 3);

        sf_ass_OnlyLine();
        //        if(mt9v03x_finish_flag)
        //        {
        //            mt9v03x_finish_flag = 0;
        //
        //            // �ڷ���ǰ��ͼ�񱸷��ٽ��з��ͣ��������Ա���ͼ�����˺�ѵ�����
        //            memcpy(image_bak[0], mt9v03x_image[0], MT9V03X_IMAGE_SIZE);
        //            // ����ͼ��
        //            seekfree_assistant_camera_send();
        //        }
        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}

#pragma section all restore

// **************************** �������� ****************************
