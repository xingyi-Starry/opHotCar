#ifndef CODE_OPHOT_IMAGE_PROCESSING_H_
#define CODE_OPHOT_IMAGE_PROCESSING_H_

#include "zf_common_headfile.h"
#include "opHot_basic_function.h"

//CAMERA_SELECTION���ݽ���
//Ϊ 1 ��ʱ��,ѡ�������
//Ϊ 2 ��ʱ��,ѡ��С���
//Ϊ 3 ��ʱ��,ѡ����ͫ
#define CAMERA_SELECTION        (1)
#if CAMERA_SELECTION == 1       //ѡ�������
#define IMAGE_HEIGHT            (120)
#define IMAGE_WIDTH             (188)
#elif CAMERA_SELECTION == 2     //ѡ��С���
#define IMAGE_HEIGHT            (OV7725_H)
#define IMAGE_WIDTH             (OV7725_W)
#elif CAMERA_SELECTION == 3     //ѡ����ͫ
#define IMAGE_HEIGHT            (SCC8660_H)
#define IMAGE_WIDTH             (SCC8660_W)
#endif

#define IMAGE_LINE_MAX_NUM (90)         //ͼƬ�������ص�������
//------------------------------------------------------------
//����״̬��
extern uint8 Image_Process_Status;
//------------------------------------------------------------
//��������
extern uint16 Image_threSum;
//------------------------------------------------------------
//��������
//1. ԭͼ���ұ���
//2. ������������
extern uint8   Image_iptsLeft[90][2];           //���������洢 - 0����x����,1����y����
extern uint8   Image_iptsRight[90][2];          //�ұ�������洢
extern uint8   Image_iptsLeftNum;               //��������ص����
extern uint8   Image_iptsRightNum;              //�ұ������ص����
//��͸�ӱ任����
extern uint8 Image_rptsLeft[90][2];             //�����ȥ����+��͸�ӱ任����洢
extern uint8 Image_rptsRight[90][2];            //�ұ���ȥ����+��͸�ӱ任����洢
extern uint8 Image_rptsLeftNum;                 //�����ȥ����+��͸�ӱ任���ص����
extern uint8 Image_rptsRightNum;                //�ұ���ȥ����+��͸�ӱ任���ص����
//------------------------------
//�㼯�����˲����
extern const uint8 Image_linerBlurKernel;       //�����˲�ʱ�������߳�
extern uint8 Image_rptsLeftb[90][2];            //�����˲�������������洢
extern uint8 Image_rptsRightb[90][2];           //�����˲�����ұ�������洢
extern uint8 Image_rptsLeftbNum;                //�����˲��������߳���
extern uint8 Image_rptsRightbNum;               //�����˲�����ұ��߳���
//------------------------------
//�Ⱦ�������
extern const float Image_sampleDist;           //�Ⱦ���ò����ľ���
extern uint8 Image_rptsLefts[90][2];           //�Ⱦ����������������洢
extern uint8 Image_rptsRights[90][2];          //�Ⱦ��������ұ�������洢
extern uint8 Image_rptsLeftsNum;               //�Ⱦ�����������߳���
extern uint8 Image_rptsRightsNum;              //�Ⱦ��������ұ��߳���

extern uint8 LeftLine_raw_show[2][IMAGE_LINE_MAX_NUM];         //ͼ��ԭʼ�����
extern uint8 RightLine_raw_show[2][IMAGE_LINE_MAX_NUM];        //ͼ��ԭʼ�ұ���
extern uint8 LeftLine_show[2][IMAGE_LINE_MAX_NUM];             //ͼ�������
extern uint8 RightLine_show[2][IMAGE_LINE_MAX_NUM];            //ͼ���ұ���
//------------------------------
//���߾ֲ��Ƕȱ仯�����
extern const float Image_angleDist;             //�������ת��ʱ,���������ľ���
extern float Image_rptsLefta[90];               //����߶�Ӧ�㴦�ĽǶȴ�С
extern float Image_rptsRighta[90];              //�ұ��߶�Ӧ�㴦�ĽǶȴ�С
extern uint8 Image_rptsLeftaNum;                //����ߵ�ĸ���
extern uint8 Image_rptsRightaNum;               //�ұ��ߵ�ĸ���
//------------------------------
//�Ƕȱ仯�ʷǼ����������
extern float Image_rptsLeftan[90];              //������������Ǵ洢
extern float Image_rptsRightan[90];             //�ұ����������Ǵ洢
extern uint8 Image_rptsLeftanNum;               //����ߵ�ĸ���
extern uint8 Image_rptsRightanNum;              //�ұ��ߵ�ĸ���
//------------------------------
//���ұ��߸������
extern uint8 Image_rptsLeftc[90][2];            //����߸��ٵõ�����������
extern uint8 Image_rptsRightc[90][2];           //�ұ��߸��ٵõ�����������
extern uint8 Image_rptsLeftcNum;                //����߸��ٵõ������ߵ��߳�
extern uint8 Image_rptsRightcNum;               //�ұ��߸��ٵõ������ߵ��߳�


//------------------------------�ǵ�Ѱ�����------------------------------
//------------------------------
//Y�ǵ�
extern uint8 Image_YptLeft_rptsLefts_id;                       //�����Y�ǵ�id
extern uint8 Image_YptRight_rptsRights_id;                     //�ұ���Y�ǵ�id
extern bool  Image_YptLeft_Found;                              //�����Y�ǵ��ҵ��ж�
extern bool  Image_YptRight_Found;                             //�ұ���Y�ǵ��ҵ��ж�
//------------------------------
//L�ǵ�
extern uint8 Image_LptLeft_rptsLefts_id;                       //�����L�ǵ�id
extern uint8 Image_LptRight_rptsRights_id;                     //�ұ���L�ǵ�id
extern bool  Image_LptLeft_Found;                              //�����L�ǵ��ҵ��ж�
extern bool  Image_LptRight_Found;                             //�ұ���L�ǵ��ҵ��ж�
//------------------------------
//��ֱ��
extern bool  Image_isStraightLeft;                             //������Ƿ�Ϊֱ��
extern bool  Image_isStraightRight;                            //�ұ����Ƿ�Ϊֱ��
//------------------------------
//���
extern bool  Image_isTurnLeft;                                 //������Ƿ�Ϊ���
extern bool  Image_isTurnRight;                                //�ұ����Ƿ�Ϊ���

//------------------------------���Բ�������------------------------------
//���ڵ��ԵĲ���(Ϊ��������,����ı�ͷ��ʼ��ĸ��Сд����, ͬʱʹ���»���������)
extern uint8 image_thre;                                       //���ߴ���ĳ�ʼ��ֵ
extern uint8 image_begin_x;                                    //���ߴ������ʼx����ƫ�����ĵľ���
extern uint8 image_begin_y;                                    //���ߴ�����ʼ��y����
extern uint8 image_block_size;                                 //�����ֵ��������߳�
extern uint8 image_block_clip_value;                           //�����ľ������(һ��Ϊ2~5)



typedef enum {
    IMAGE_IPS200 = 0x00,
    IMAGE_TFT180 = 0x01,
}IMAGE_SCREEN;

typedef enum {
    IMAGE_ORIGIN = 0x00,
    IMAGE_MAPPING = 0x01,
    IMAGE_MIDLINE_LEFT = 0x02,
    IMAGE_MIDLINE_RIGHT = 0x03,
    IMAGE_CLEAR_ORIGIN = 0x04,
    IMAGE_CLEAR_MAPPING = 0x05,
    IMAGE_CLEAR_MIDLINE_LEFT = 0x06,
    IMAGE_CLEAR_MIDLINE_RIGHT = 0x07,
}IMAGE_SHOW_TYPE;

typedef enum {
    IMAGE_LCORNER_NONE = 0x10,
    IMAGE_LCORNER_BEGIN_LEFT = 0x00,
    IMAGE_LCORNER_BEGIN_RIGHT = 0x01,
    IMAGE_LCORNER_IS_GRAGE_LEFT = 0x02,
    IMAGE_LCORNER_IS_GRAGE_RIGHT = 0x03,
    IMAGE_LCORNER_IS_CIRCLE_LEFT = 0x04,
    IMAGE_LCORNER_IS_CIRCLE_RIGHT = 0x05,
}IMAGE_LCORNER_JUDGE;

//-----------����-----------
void Image_Init(void);
void Image_Process(uint8* image);

#endif