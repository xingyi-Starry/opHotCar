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
#define SEEKFREE_ASSISTANT_MODE 1

uint32 duty = STEER_MID;

uint8 test_value = 0;

uint8 ImageInit_flag = 0;
uint8 data_buffer[32];
uint8 data_len;
uint8 pit_state = 0;

int core0_main(void)
{
    clock_init(); // ��ȡʱ��Ƶ��<��ر���>
    debug_init(); // ��ʼ��Ĭ�ϵ��Դ���
    // �˴���д�û����� ���������ʼ�������

    // Ӳ����ʼ��
    gpio_init(KEY1, GPI, GPIO_HIGH, GPI_PULL_UP); // ������ʼ��
    mt9v03x_init();
    mt9v03x_set_exposure_time(100);
    ips200_init(IPS200_TYPE_PARALLEL8);
    wireless_uart_init();
    Motor_Init();
    imu660ra_init();
    Gyroscope_Init(GYROSCOPE_IMU660RA, 5);
    Encoder_Init();
    Steer_Init();

    // ������ֳ�ʼ�����˴�ѡ�����ߴ��ڣ����ʽ������������ɹ���ѡ��һЩ�����ٵ���λ������������ֲ��λ��
    seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_WIRELESS_UART);
    // �������ͼ��ģʽ����
#if (0 == SEEKFREE_ASSISTANT_MODE) // ��͸�ӱ��ߴ���
    seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, NULL, MT9V03X_W, MT9V03X_H);
    seekfree_assistant_camera_boundary_config(XY_BOUNDARY, 45, LeftLine_show[0], RightLine_show[0], MidLine_show[0], LeftLine_show[1], RightLine_show[1], MidLine_show[1]);
#elif (1 == SEEKFREE_ASSISTANT_MODE) // ԭͼ�����ߴ���
    seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, image_bak, MT9V03X_W, MT9V03X_H);
    seekfree_assistant_camera_boundary_config(XY_BOUNDARY, 90, LeftLine_raw_show[0], RightLine_raw_show[0], NULL, LeftLine_raw_show[1], RightLine_raw_show[1], NULL);
#endif

    // ��Ļ��ʼ��
    ips200_set_dir(IPS200_PORTAIT);
    ips200_set_font(IPS200_8X16_FONT);
    ips200_set_color(RGB565_WHITE, RGB565_BLACK);
    ips200_full(RGB565_BLACK);

    //-----------��ʱ�жϳ�ʼ��---------------
    pit_ms_init(CCU60_CH0, 5); // ccu60_ch0(cpu0) ���������ݲɼ�&���PID
    pit_ms_init(CCU60_CH1, 1000);

    // PID��ʼ��
    Motor_PID_Init();
    Steer_PID_Init();
    Steer_PID_Set(STEER_PID_P, STEER_PID_I, STEER_PID_D, STEER_PID_SL, STEER_PID_UL, 1);
    // Motor1_PID_Set(MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_P, MOTOR_PID_SL, MOTOR_PID_UL, 1);
    // Motor2_PID_Set(MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_P, MOTOR_PID_SL, MOTOR_PID_UL, 1);

    // Image_Init();

    cpu_wait_event_ready(); // �ȴ����к��ĳ�ʼ�����
    while (gpio_get_level(KEY1))
        ;
    ImageInit_flag = 1;
    Image_Init();
    Motor1_PID_Set(MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D, MOTOR_PID_SL, MOTOR_PID_UL, 1);
    Motor2_PID_Set(MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D, MOTOR_PID_SL, MOTOR_PID_UL, 1);

    while (TRUE)
    {
        // ��������
        seekfree_assistant_data_analysis();
        if (seekfree_assistant_parameter_update_flag[0])
        {
            seekfree_assistant_parameter_update_flag[0] = 0;
            trace_central = seekfree_assistant_parameter[0];
        }
        if (seekfree_assistant_parameter_update_flag[1])
        {
            seekfree_assistant_parameter_update_flag[1] = 0;
            trace_kde = seekfree_assistant_parameter[1];
        }
        if (seekfree_assistant_parameter_update_flag[2])
        {
            seekfree_assistant_parameter_update_flag[2] = 0;
            length_of_car = seekfree_assistant_parameter[2];
        }
        if (seekfree_assistant_parameter_update_flag[3])
        {
            seekfree_assistant_parameter_update_flag[3] = 0;
            TRACE_TYPE = seekfree_assistant_parameter[3];
        }
        if (seekfree_assistant_parameter_update_flag[4])
        {
            seekfree_assistant_parameter_update_flag[4] = 0;
            tracing_aim = seekfree_assistant_parameter[4];
        }

        //  �˴���д��Ҫѭ��ִ�еĴ���
        /*
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
            case 's':
                Motor_Init();
                break;

            default:
                break;
            }
            memset(data_buffer, 0, 32);
        }*/

        if (Image_show_NE == 1)
        {
            //memcpy(image_bak[0], mt9v03x_image[0], MT9V03X_IMAGE_SIZE);
            ips200_show_gray_image(0, 0, image_bak[0], MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H, 0);
            Image_ShowResampleLine(0, 0);
            ips200_draw_line(64, 50, 124, 50, RGB565_PURPLE);
            // Image_ShowArray(0, 0, 119, Image_rptsLefta, 90, RGB565_PURPLE);
            //seekfree_assistant_camera_send();
            Image_show_NE = 0;
        }
        ips200_show_float(0, 120, 0, 3, 2);
        ips200_show_float(0, 136, 0, 3, 2);
        ips200_show_float(0, 152, Acc_corrZ, 3, 2);
        ips200_show_float(0, 168, Gyro_corrX, 3, 2);
        ips200_show_float(0, 184, Gyro_corrY, 3, 2);
        ips200_show_float(0, 200, Gyro_corrZ, 3, 2);
        ips200_show_float(0, 216, Image_LeftTurnAngle, 3, 2);
        ips200_show_float(0, 232, Image_RightTurnAngle, 3, 2);

        ips200_show_int(188, 120, image_thre, 5);
        // ips200_show_int(0, 136, test_value, 5);
        ips200_show_int(188, 152, (int16)Err, 5);
        ips200_show_int(188, 168, Encoder_sum_Motor2, 5);
        ips200_show_int(188, 184, TRACE_TYPE, 5);
        ips200_show_int(188, 200, OVERALL_STATE, 5);
        ips200_show_int(188, 216, CIRCLE_STATE, 5);
        ips200_show_int(188, 232, CrossLine_ChangeCount, 5);

        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}

#pragma section all restore

// **************************** �������� ****************************
