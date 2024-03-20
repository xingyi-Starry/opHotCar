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
/**
 * @brief �������ͼ��ģʽ����
 * @note  0��ʾ������͸�ӱ��߼����ߣ�1��ʾ����ԭʼͼ���ԭʼ����
 * 
 */
#define SEEKFREE_ASSISTANT_MODE     0

uint32 duty = STEER_MID;

uint8 test_value = 0;

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
    Encoder_Init();
    Steer_Init();

    // ������ֳ�ʼ�����˴�ѡ�����ߴ��ڣ����ʽ������������ɹ���ѡ��һЩ�����ٵ���λ������������ֲ��λ��
    seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_WIRELESS_UART);
    // �������ͼ��ģʽ����
#if (0 == SEEKFREE_ASSISTANT_MODE)      // ��͸�ӱ��ߴ���
    seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, NULL, MT9V03X_W, MT9V03X_H);
    seekfree_assistant_camera_boundary_config(XY_BOUNDARY, 45, LeftLine_show[0], RightLine_show[0], MidLine_show[0], LeftLine_show[1], RightLine_show[1], MidLine_show[1]);
#elif (1 == SEEKFREE_ASSISTANT_MODE)    // ԭͼ�����ߴ���
    seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, NULL, MT9V03X_W, MT9V03X_H);
    seekfree_assistant_camera_boundary_config(XY_BOUNDARY, 90, LeftLine_raw_show[0], RightLine_raw_show[0], NULL, LeftLine_raw_show[1], RightLine_raw_show[1], NULL);
#endif

    // ��Ļ��ʼ��
    ips200_set_dir(IPS200_CROSSWISE);
    ips200_set_font(IPS200_8X16_FONT);
    ips200_set_color(RGB565_BLACK, RGB565_GREEN);
    ips200_full(RGB565_GREEN);

    //-----------��ʱ�жϳ�ʼ��---------------
    pit_ms_init(CCU60_CH0, 5); // ccu60_ch0(cpu0) ���������ݲɼ�
    pit_ms_init(CCU60_CH1, 500);
    pit_ms_init(CCU61_CH0, 10); // ccu61_ch0(cpu1) ͼ����

    // PID��ʼ��
    Motor_PID_Init();
    // Motor1_PID_Set(MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_P, MOTOR_PID_SL, MOTOR_PID_UL, 1);
    // Motor2_PID_Set(MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_P, MOTOR_PID_SL, MOTOR_PID_UL, 1);

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
                    // Motor1_PID_Set(MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D, MOTOR_PID_SL, MOTOR_PID_UL, 1);
                    // Motor2_PID_Set(MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D, MOTOR_PID_SL, MOTOR_PID_UL, 1);
                }
            }
            memset(data_buffer, 0, 32);
        }
        // �˴���д��Ҫѭ��ִ�еĴ���
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
                Motor1_PIDwork();
                Motor2_PIDwork();
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
        ips200_show_int(5, 101, test_value, 7);
        //seekfree_assistant_camera_send();


        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}

#pragma section all restore

// **************************** �������� ****************************
