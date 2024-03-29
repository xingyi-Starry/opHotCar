#ifndef CODE_OPHOT_IMAGE_PROCESSING_H_
#define CODE_OPHOT_IMAGE_PROCESSING_H_

#include "zf_common_headfile.h"
#include "opHotCar.h"
#include "opHot_basic_function.h"

// CAMERA_SELECTION���ݽ���   --����ֻ������磬����ѧ������û��Ĵ�ӣ������� --linnuofan-2024/3/22
// Ϊ 1 ��ʱ��,ѡ�������
// Ϊ 2 ��ʱ��,ѡ��С���
// Ϊ 3 ��ʱ��,ѡ����ͫ
#define CAMERA_SELECTION (1)
#if CAMERA_SELECTION == 1 // ѡ�������
#define IMAGE_HEIGHT (120)
#define IMAGE_WIDTH (188)
#elif CAMERA_SELECTION == 2 // ѡ��С���
#define IMAGE_HEIGHT (OV7725_H)
#define IMAGE_WIDTH (OV7725_W)
#elif CAMERA_SELECTION == 3 // ѡ����ͫ
#define IMAGE_HEIGHT (SCC8660_H)
#define IMAGE_WIDTH (SCC8660_W)
#endif

#define INVERTED_TRACING_Y (70)     // б��Ѳ����ʼy����
#define IMAGE_LINE_MAX_NUM (90)     // ͼƬ�������ص�������
#define IMAGE_RESAMPLE_MAX_NUM (60) // �ز����������ص�������
#define TURN_JUDGE_ANGLE (25)  // ����жϽǶ�
//------------------------------------------------------------
// ����״̬��
extern uint8 Image_Process_Status;
extern uint8 Image_Init_flag;
//------------------------------------------------------------
// ��������
extern uint16 Image_threSum;
//------------------------------------------------------------
// ��������
// 1. ԭͼ���ұ���
// 2. ������������
extern uint8 Image_iptsLeft[90][2];  // ���������洢 - 0����x����,1����y����
extern uint8 Image_iptsRight[90][2]; // �ұ�������洢
extern uint8 Image_iptsLeftNum;      // ��������ص����
extern uint8 Image_iptsRightNum;     // �ұ������ص����
extern uint8 Image_iptsLeftNum_Bak;  // ��������ص��������
extern uint8 Image_iptsRightNum_Bak; // �ұ������ص��������
// ��͸�ӱ任����
extern uint8 Image_rptsLeft[90][2];  // �����ȥ����+��͸�ӱ任����洢
extern uint8 Image_rptsRight[90][2]; // �ұ���ȥ����+��͸�ӱ任����洢
extern uint8 Image_rptsLeftNum;      // �����ȥ����+��͸�ӱ任���ص����
extern uint8 Image_rptsRightNum;     // �ұ���ȥ����+��͸�ӱ任���ص����
//------------------------------
// �㼯�����˲����
extern const uint8 Image_linerBlurKernel; // �����˲�ʱ�������߳�
extern uint8 Image_rptsLeftb[90][2];      // �����˲�������������洢
extern uint8 Image_rptsRightb[90][2];     // �����˲�����ұ�������洢
extern uint8 Image_rptsLeftbNum;          // �����˲��������߳���
extern uint8 Image_rptsRightbNum;         // �����˲�����ұ��߳���
//------------------------------
// �Ⱦ�������
extern const float Image_sampleDist;                      // �Ⱦ���ò����ľ���
extern uint8 Image_rptsLefts[IMAGE_RESAMPLE_MAX_NUM][2];  // �Ⱦ����������������洢
extern uint8 Image_rptsRights[IMAGE_RESAMPLE_MAX_NUM][2]; // �Ⱦ��������ұ�������洢
extern uint8 Image_rptsLeftsNum;                          // �Ⱦ�����������߳���
extern uint8 Image_rptsRightsNum;                         // �Ⱦ��������ұ��߳���
extern uint8 Image_LeftLine_Lost;                         // ����߶�ʧ��־λ
extern uint8 Image_RightLine_Lost;                        // ����߶�ʧ��־λ

//------------------------------
// ͼ�����
extern uint8 LeftLine_raw_show[2][IMAGE_LINE_MAX_NUM];  // ͼ��ԭʼ�����
extern uint8 RightLine_raw_show[2][IMAGE_LINE_MAX_NUM]; // ͼ��ԭʼ�ұ���
extern uint8 LeftLine_show[2][IMAGE_RESAMPLE_MAX_NUM];  // ͼ�������
extern uint8 RightLine_show[2][IMAGE_RESAMPLE_MAX_NUM]; // ͼ���ұ���
extern uint8 MidLine_show[2][IMAGE_RESAMPLE_MAX_NUM];   // ͼ������
extern uint8 Image_show_NE;                             // ͼ����־λ
extern uint8 image_bak[MT9V03X_H][MT9V03X_W];           // ԭͼ����
//------------------------------
// ���߾ֲ��Ƕȱ仯�����
extern const float Image_angleDist; // �������ת��ʱ,���������ľ���
extern float Image_rptsLefta[90];   // ����߶�Ӧ�㴦�ĽǶȴ�С
extern float Image_rptsRighta[90];  // �ұ��߶�Ӧ�㴦�ĽǶȴ�С
extern uint8 Image_rptsLeftaNum;    // ����ߵ�ĸ���
extern uint8 Image_rptsRightaNum;   // �ұ��ߵ�ĸ���
//------------------------------
// �Ƕȱ仯�ʷǼ����������
extern float Image_rptsLeftan[90];  // ������������Ǵ洢
extern float Image_rptsRightan[90]; // �ұ����������Ǵ洢
extern uint8 Image_rptsLeftanNum;   // ����ߵ�ĸ���
extern uint8 Image_rptsRightanNum;  // �ұ��ߵ�ĸ���
//------------------------------
// ���ұ��߸������
// extern uint8 Image_rptsLeftc[IMAGE_RESAMPLE_MAX_NUM][2];  // ����߸��ٵõ�����������
// extern uint8 Image_rptsRightc[IMAGE_RESAMPLE_MAX_NUM][2]; // �ұ��߸��ٵõ�����������
extern uint8 Image_MidLine[IMAGE_RESAMPLE_MAX_NUM][2]; // ��������
extern uint8 Image_RsMidLine[IMAGE_RESAMPLE_MAX_NUM][2]; // �Ⱦ���������������
// extern uint8 Image_rptsLeftcNum;                          // ����߸��ٵõ������ߵ��߳�
// extern uint8 Image_rptsRightcNum;                         // �ұ��߸��ٵõ������ߵ��߳�
extern uint8 Image_MidLineNum; // �����߳�

//------------------------------�ǵ�Ѱ�����------------------------------
//------------------------------
// �ǵ����
extern uint8 Image_cornerNumLeft;  // �ǵ����
extern uint8 Image_cornerNumRight; // �ǵ����
// L�ǵ�
extern uint8 Image_LptLeft_rptsLefts_id;   // �����L�ǵ�id
extern uint8 Image_LptRight_rptsRights_id; // �ұ���L�ǵ�id
extern bool Image_LptLeft_Found;           // �����L�ǵ��ҵ��ж�
extern bool Image_LptRight_Found;          // �ұ���L�ǵ��ҵ��ж�
//------------------------------
// ��ֱ��
extern bool Image_isStraightLeft;  // ������Ƿ�Ϊֱ��
extern bool Image_isStraightRight; // �ұ����Ƿ�Ϊֱ��
//------------------------------
// ���
extern uint8 Image_LeftDir;
extern uint8 Image_RightDir;
//------------------------------���Բ�������------------------------------
// ���ڵ��ԵĲ���(Ϊ��������,����ı�ͷ��ʼ��ĸ��Сд����, ͬʱʹ���»���������)
extern uint8 image_thre;             // ���ߴ���ĳ�ʼ��ֵ
extern uint8 image_begin_x;          // ���ߴ������ʼx����ƫ�����ĵľ���
extern uint8 image_begin_y;          // ���ߴ�����ʼ��y����
extern uint8 image_block_size;       // �����ֵ��������߳�
extern uint8 image_block_clip_value; // �����ľ������(һ��Ϊ2~5)

//-----------����-----------
uint8 IMAGE_AT(uint8 *image, int16 x, int16 y);
void Image_LineCut(void);
void Image_Init(void);
void Image_Process(uint8 *image);

#endif