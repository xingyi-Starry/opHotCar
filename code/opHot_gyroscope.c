/*
 * xiao_gyroscope.c
 *
 *  Created on: 2023��7��2��
 *      Author: Jayden_NaN
 */

#include "opHot_gyroscope.h"

//------------------------------��������------------------------------
// ��ʱʱ�� - ��λ ms
uint16 Gyroscope_time = 0;
// ʹ�õ��������豸(Ĭ������ΪIMU660RA)
GYROSCOPE_TYPE Gyroscope_device = GYROSCOPE_IMU660RA;
// ������ƫ����
struct GyroscopeOffset Gyro_Offset;
// y����ٶ��˲�����
float GyroY_FilterData[GYRO_FILTER_MAX];
// �˲�Ȩ��
float Gyro_FilterWeigh[GYRO_FILTER_MAX] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
// �˲�����ָ��
uint8 Gyro_FilterPointer = 0;

//------------------------------��������------------------------------
//------------------------------
// �洢���ݱ���
float Gyro_x; // ������xֵ - �Ƕ� ��λ��
float Gyro_y; // ������yֵ - �Ƕ� ��λ��
float Gyro_z; // ������zֵ - �Ƕ� ��λ��
float Acc_x;  // ���ٶ�xֵ - �ٶ� ��λm/s
float Acc_y;  // ���ٶ�yֵ - �ٶ� ��λm/s
float Acc_z;  // ���ٶ�zֵ - �ٶ� ��λm/s

float Gyro_corrX; // ������xֵ - ���ٶ� ��λ��/s
float Gyro_corrY; // ������yֵ - ���ٶ� ��λ��/s
float Gyro_corrZ; // ������zֵ - ���ٶ� ��λ��/s
float Acc_corrX;  // ���ٶ�xֵ - ���ٶ� ��λm/s^2
float Acc_corrY;  // ���ٶ�yֵ - ���ٶ� ��λm/s^2
float Acc_corrZ;  // ���ٶ�zֵ - ���ٶ� ��λm/s^2

//------------------------------
// ����״̬��
uint8 Gyro_x_status = 0; // ������xֵ����״̬��
uint8 Gyro_y_status = 0; // ������yֵ����״̬��
uint8 Gyro_z_status = 0; // ������zֵ����״̬��
uint8 Acc_x_status = 0;  // ���ٶ�xֵ����״̬��
uint8 Acc_y_status = 0;  // ���ٶ�yֵ����״̬��
uint8 Acc_z_status = 0;  // ���ٶ�zֵ����״̬��

/**
 * @brief               �����Ǵ����ʼ��
 * @param device        ʹ�õ��������豸
 * @param time          ʹ�õ��ж�ʱ�䣬��λΪ����
 * @note                z����ٶ���תΪ������תΪ��
 * @example             Gyroscope_Init(GYROSCOPE_IMU660RA, 10);
 */
void Gyroscope_Init(GYROSCOPE_TYPE device, uint16 time)
{
    // ������ƫ������ʼ������Ϊ0
    Gyro_Offset.ACC_Xdata = 0.0;
    Gyro_Offset.ACC_Ydata = 0.0;
    Gyro_Offset.ACC_Zdata = 0.0;
    Gyro_Offset.Gyro_Xdata = 0.0;
    Gyro_Offset.Gyro_Ydata = 0.0;
    Gyro_Offset.Gyro_Zdata = 0.0;

    // ����IMU660RA�Ĵ���
    if (device == GYROSCOPE_IMU660RA)
    {
        Gyroscope_device = GYROSCOPE_IMU660RA;
        // ���ݵ�ѭ������150��,ÿ����һ��,ϵͳ��ʱ10ms,���Թ���Ҫ��ʱ1.5s
        for (uint8 i = 0; i < 150; ++i)
        {
            imu660ra_get_gyro();
            imu660ra_get_acc();
            Gyro_Offset.ACC_Xdata += (float)imu660ra_acc_x;
            Gyro_Offset.ACC_Ydata += (float)imu660ra_acc_y;
            Gyro_Offset.ACC_Zdata += (float)imu660ra_acc_z;
            Gyro_Offset.Gyro_Xdata += (float)imu660ra_gyro_x;
            Gyro_Offset.Gyro_Ydata += (float)imu660ra_gyro_y;
            Gyro_Offset.Gyro_Zdata += (float)imu660ra_gyro_z;
            system_delay_ms(10);
        }
        Gyro_Offset.ACC_Xdata /= 150;
        Gyro_Offset.ACC_Ydata /= 150;
        Gyro_Offset.ACC_Zdata /= 150;
        Gyro_Offset.Gyro_Xdata /= 150;
        Gyro_Offset.Gyro_Ydata /= 150;
        Gyro_Offset.Gyro_Zdata /= 150;
    }
    // ����IMU963RA�Ĵ���
    else if (device == GYROSCOPE_IMU963RA)
    {
        Gyroscope_device = GYROSCOPE_IMU963RA;
    }
    // ����ICM20602�Ĵ���
    else if (device == GYROSCOPE_ICM20602)
    {
        Gyroscope_device = GYROSCOPE_ICM20602;
    }
    // ���������Ȳ�������,�Լ������õ����ݹ���~~~
    Gyroscope_time = time;
}

/**
 * @brief                   ��ʱ����ʼ����
 * @param   measureType     ��������
 * @example                 Gyroscope_Begin(GYROSCOPE_GYRO_X);
 *
 */
void Gyroscope_Begin(GYROSCOPE_MEASURE_TYPE measureType)
{
    // Ҫ��,ֻ�м�����ת̬Ϊ0��ʱ��,���ܿ�ʼ���м���
    if (measureType == GYROSCOPE_GYRO_X)
    {
        if (Gyro_x_status == 0)
        {
            Gyro_x_status = 1;
            Gyro_x = 0.0;
        }
    }
    else if (measureType == GYROSCOPE_GYRO_Y)
    {
        if (Gyro_y_status == 0)
        {
            Gyro_y_status = 1;
            Gyro_y = 0.0;
        }
    }
    else if (measureType == GYROSCOPE_GYRO_Z)
    {
        if (Gyro_z_status == 0)
        {
            Gyro_z_status = 1;
            Gyro_z = 0.0;
        }
    }
    else if (measureType == GYROSCOPE_ACC_X)
    {
        if (Acc_x_status == 0)
        {
            Acc_x_status = 1;
            Acc_x = 0.0;
        }
    }
    else if (measureType == GYROSCOPE_ACC_Y)
    {
        if (Acc_y_status == 0)
        {
            Acc_y_status = 1;
            Acc_y = 0.0;
        }
    }
    else if (measureType == GYROSCOPE_ACC_Z)
    {
        if (Acc_z_status == 0)
        {
            Acc_z_status = 1;
            Acc_z = 0.0;
        }
    }
}

/**
 * @brief                   ������ֹͣ����
 * @param   measureType     ��������
 * @example                 Gyroscope_End(GYROSCOPE_GYRO_X);
 *
 */
void Gyroscope_End(GYROSCOPE_MEASURE_TYPE measureType)
{
    // �ص��Ļ���ֱ�Ӱ�״̬��0��,���ÿ����Ƿ����ڹ���״̬
    if (measureType == GYROSCOPE_GYRO_X)
    {
        Gyro_x_status = 0;
    }
    else if (measureType == GYROSCOPE_GYRO_Y)
    {
        Gyro_y_status = 0;
    }
    else if (measureType == GYROSCOPE_GYRO_Z)
    {
        Gyro_z_status = 0;
    }
    else if (measureType == GYROSCOPE_ACC_X)
    {
        Acc_x_status = 0;
    }
    else if (measureType == GYROSCOPE_ACC_Y)
    {
        Acc_y_status = 0;
    }
    else if (measureType == GYROSCOPE_ACC_Z)
    {
        Acc_z_status = 0;
    }
}

void Gyroscope_GetData(void)
{
    //------------------------------��������------------------------------
    imu660ra_get_gyro();
    imu660ra_get_acc();
    Gyro_corrX = imu660ra_gyro_transition((float)imu660ra_gyro_x - Gyro_Offset.Gyro_Xdata);
    Gyro_corrY = LowPass_Filter(Sliding_Filter(GyroY_FilterData, Gyro_FilterWeigh, GYRO_FILTER_MAX, &Gyro_FilterPointer, imu660ra_gyro_transition((float)imu660ra_gyro_y - Gyro_Offset.Gyro_Ydata)), Gyro_corrY, 0.25);
    Gyro_corrZ = imu660ra_gyro_transition((float)imu660ra_gyro_z - Gyro_Offset.Gyro_Zdata);
    Acc_corrX = imu660ra_acc_transition((float)imu660ra_acc_x - Gyro_Offset.ACC_Xdata);
    Acc_corrY = imu660ra_acc_transition((float)imu660ra_acc_y - Gyro_Offset.ACC_Ydata);
    Acc_corrZ = imu660ra_acc_transition((float)imu660ra_acc_z - Gyro_Offset.ACC_Zdata);
}

void Gyroscope_Conut(void)
{
    //------------------------------����˵��------------------------------
    // ���м���,���ж�����������ݵ��ۼ�
    // �ٶȵ�λΪm/s
    // �Ƕȵ�λΪ��
    //--------------------��ȡ����--------------------
    Gyroscope_GetData();

    //--------------------���ݴ���--------------------
    if (Gyro_x_status == 1)
    {
        Gyro_x += imu660ra_gyro_transition((float)imu660ra_gyro_x - Gyro_Offset.Gyro_Xdata) * Gyroscope_time * 0.001;
    }

    if (Gyro_y_status == 1)
    {
        Gyro_y += imu660ra_gyro_transition((float)imu660ra_gyro_y - Gyro_Offset.Gyro_Ydata) * Gyroscope_time * 0.001;
    }

    if (Gyro_z_status == 1)
    {
        Gyro_z += imu660ra_gyro_transition((float)imu660ra_gyro_z - Gyro_Offset.Gyro_Zdata) * Gyroscope_time * 0.001;
    }

    if (Acc_x_status == 1)
    {
        Acc_x += imu660ra_acc_transition((float)imu660ra_acc_x - Gyro_Offset.ACC_Xdata) * Gyroscope_time * 0.001;
    }

    if (Acc_y_status == 1)
    {
        Acc_y += imu660ra_acc_transition((float)imu660ra_acc_y - Gyro_Offset.ACC_Ydata) * Gyroscope_time * 0.001;
    }

    if (Acc_z_status == 1)
    {
        Acc_z += imu660ra_acc_transition((float)imu660ra_acc_z - Gyro_Offset.ACC_Zdata) * Gyroscope_time * 0.001;
    }
}

/**
 * @brief                   ��ջ��ֵ�����
 * @param measureType       ����������
 */
void Gyroscope_Clear(GYROSCOPE_MEASURE_TYPE measureType)
{
    if (measureType == GYROSCOPE_GYRO_X)
    {
        Gyro_x = 0.0;
    }
    else if (measureType == GYROSCOPE_GYRO_Y)
    {
        Gyro_y = 0.0;
    }
    else if (measureType == GYROSCOPE_GYRO_Z)
    {
        Gyro_z = 0.0;
    }
    else if (measureType == GYROSCOPE_ACC_X)
    {
        Acc_x = 0.0;
    }
    else if (measureType == GYROSCOPE_ACC_Y)
    {
        Acc_y = 0.0;
    }
    else if (measureType == GYROSCOPE_ACC_Z)
    {
        Acc_z = 0.0;
    }
}

/**
 * @brief �������ǵĻ��������˲�
 * 
 * @param data          ��������
 * @param data_weigh    �˲�Ȩ��
 * @param data_num      ���г���
 * @param data_pointer  ����ָ��
 * @param new_data      �����������
 * @return data_out     �˲����
 */
float Gyroscope_Filter(float data[], float data_weigh[], uint8 data_num, uint8 *data_pointer, float new_data)
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
