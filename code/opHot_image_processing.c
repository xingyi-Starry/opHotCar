#include "opHot_image_processing.h"

//------------------------------------------------------------
// ͼ������Ϊ
// :------------------>x
// |
// |
// |
// |
// |
// |
// V
// y
// �Թ�Ѳ���������
/*
 * ǰ��������:
 *  0
 *3   1
 *  2
 */
//------------------------------------------------------------
// ������Ϣ˵��
// 1. ���ص���ʵ�ʾ���Ķ�Ӧ
//      45cm ~ 45pixel
// 2. ��������˵��
//      �涨,������������ 0 ����x����; 1 ����y����
// 3. �Ƕȱ仯�ʷǼ����������
//      �����ڷǼ���ǵĽ�����Ϊ��0

//------------------------------�õ��ĺ�------------------------------
#define IMAGE_ANGLE_CHANGE_UP_KEY (P22_3)
#define IMAGE_ANGLE_CHANGE_DOWN_KEY (P22_2)
#define IMAGE_ANGLE_LINE_SELCET_KEY (P21_1)
#define IMAGE_ANGLE_COLOR (RGB565_YELLOW)

//------------------------------״̬��------------------------------
uint8 Image_Process_Status = 0;
uint8 Image_isUsefulData_Status = 0;

//------------------------------����------------------------------
//------------------------------
// ��������
const float Image_pixelPreMeter = 100;     // ÿ��118.42�����ص�(38cm ~ 45pixel)
const float Image_roadWidth = 0.45;        // �����Ŀ��� - (��λΪm)
const float Image_PI = 3.14159265358;      // PI(�ִ��)
uint8 Image_disPictureCnt = 0;             // ����ͼƬ����������
const uint8 Image_disPictureCnt_Thre = 10; // ����ͼƬ��������ֵ
uint16 Image_threSum = 0;                  // ͼƬ��ֵ����
uint8 Image_threCnt_Thre = 10;             // ���������򷨵�ͼƬ����

//------------------------------ͼƬ�������------------------------------
//------------------------------
// �����ұ���
uint8 Image_iptsLeft[IMAGE_LINE_MAX_NUM][2];                                   // ���������洢 - 0����x����,1����y����
uint8 Image_iptsRight[IMAGE_LINE_MAX_NUM][2];                                  // �ұ�������洢
uint8 Image_iptsLeft_Bak[IMAGE_LINE_MAX_NUM][2];                               // ��������걸�� - ��¼��һ�δ�����Ľ��
uint8 Image_iptsRight_Bak[IMAGE_LINE_MAX_NUM][2];                              // �ұ������걸��
uint8 Image_iptsLeftNum;                                                       // ��������ص����
uint8 Image_iptsRightNum;                                                      // �ұ������ص����
uint8 Image_iptsLeftNum_Bak;                                                   // ��������ص��������
uint8 Image_iptsRightNum_Bak;                                                  // �ұ������ص��������
static int8 Image_dir_front[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};        // ת��Ϊǰ��ʱת��ģ��
static int8 Image_dir_frontLeft[4][2] = {{-1, -1}, {1, -1}, {1, 1}, {-1, 1}};  // ת��Ϊ��ǰ��ʱת��ģ��
static int8 Image_dir_frontRight[4][2] = {{1, -1}, {1, 1}, {-1, 1}, {-1, -1}}; // ת��Ϊ��ǰ��ʱת��ģ��
//------------------------------
// �ѱ��߽���ȥ����+��͸�ӱ任
uint8 Image_rptsLeft[IMAGE_LINE_MAX_NUM][2];  // �����ȥ����+��͸�ӱ任����洢
uint8 Image_rptsRight[IMAGE_LINE_MAX_NUM][2]; // �ұ���ȥ����+��͸�ӱ任����洢
uint8 Image_rptsLeftNum;                      // �����ȥ����+��͸�ӱ任���ص����
uint8 Image_rptsRightNum;                     // �ұ���ȥ����+��͸�ӱ任���ص����
uint8 Image_rptsLeftrNum = 0;                 // �����ʵ�����õĵ�ĸ���
uint8 Image_rptsRightrNum = 0;                // �ұ���ʵ�����õĵ�ĸ���
//------------------------------
// �㼯�����˲����
const uint8 Image_linerBlurKernel = 7;         // �����˲�ʱ�������߳�
uint8 Image_rptsLeftb[IMAGE_LINE_MAX_NUM][2];  // �����˲�������������洢
uint8 Image_rptsRightb[IMAGE_LINE_MAX_NUM][2]; // �����˲�����ұ�������洢
uint8 Image_rptsLeftbNum;                      // �����˲��������߳���
uint8 Image_rptsRightbNum;                     // �����˲�����ұ��߳���
//------------------------------
// �Ⱦ�������
const float Image_sampleDist = 0.01;               // �Ⱦ���ò����ľ���
uint8 Image_rptsLefts[IMAGE_LINE_MAX_NUM][2];      // �Ⱦ����������������洢
uint8 Image_rptsRights[IMAGE_LINE_MAX_NUM][2];     // �Ⱦ��������ұ�������洢
uint8 Image_rptsLefts_Bak[IMAGE_LINE_MAX_NUM][2];  // �Ⱦ����������������洢 - ����
uint8 Image_rptsRights_Bak[IMAGE_LINE_MAX_NUM][2]; // �Ⱦ��������ұ�������洢 - ����
uint8 Image_rptsLeftsNum;                          // �Ⱦ�����������߳���
uint8 Image_rptsRightsNum;                         // �Ⱦ��������ұ��߳���
uint8 Image_rptsLeftsNum_Bak;                      // �Ⱦ�����������߳���    - ����
uint8 Image_rptsRightsNum_Bak;                     // �Ⱦ��������ұ��߳���    - ����

uint8 Lboundary_trans[2][IMAGE_LINE_MAX_NUM];       //ͼ�������
uint8 Rboundary_trans[2][IMAGE_LINE_MAX_NUM];       //ͼ���ұ���
//------------------------------
// ���߾ֲ��Ƕȱ仯�����
const float Image_angleDist = 0.1;          // �������ת��ʱ,���������ľ���
float Image_rptsLefta[IMAGE_LINE_MAX_NUM];  // ����߶�Ӧ�㴦�ĽǶȴ�С
float Image_rptsRighta[IMAGE_LINE_MAX_NUM]; // �ұ��߶�Ӧ�㴦�ĽǶȴ�С
uint8 Image_rptsLeftaNum;                   // ����ߵ�ĸ���
uint8 Image_rptsRightaNum;                  // �ұ��ߵ�ĸ���
//------------------------------
// �Ƕȱ仯�ʷǼ����������
float Image_rptsLeftan[IMAGE_LINE_MAX_NUM];  // ������������Ǵ洢
float Image_rptsRightan[IMAGE_LINE_MAX_NUM]; // �ұ����������Ǵ洢
uint8 Image_rptsLeftanNum;                   // ����ߵ�ĸ���
uint8 Image_rptsRightanNum;                  // �ұ��ߵ�ĸ���
//------------------------------
// ���ұ��߸������
uint8 Image_rptsLeftc[IMAGE_LINE_MAX_NUM][2];      // ����߸��ٵõ�����������
uint8 Image_rptsRightc[IMAGE_LINE_MAX_NUM][2];     // �ұ��߸��ٵõ�����������
uint8 Image_rptsLeftc_Bak[IMAGE_LINE_MAX_NUM][2];  // ����߸��ٵõ�����������  -   ����
uint8 Image_rptsRightc_Bak[IMAGE_LINE_MAX_NUM][2]; // �ұ��߸��ٵõ�����������  -   ����
uint8 Image_rptsLeftcNum;                          // ����߸��ٵõ������ߵ��߳�
uint8 Image_rptsRightcNum;                         // �ұ��߸��ٵõ������ߵ��߳�
uint8 Image_rptsLeftcNum_Bak;                      // ����߸��ٵõ������ߵ��߳� -   ����
uint8 Image_rptsRightcNum_Bak;                     // �ұ��߸��ٵõ������ߵ��߳� -   ����

//------------------------------�ǵ�Ѱ�����------------------------------
//------------------------------
// �ǵ����
uint8 Image_cornerNumLeft = 0;  // �ǵ����
uint8 Image_cornerNumRight = 0; // �ǵ����
//------------------------------
// Y�ǵ�
uint8 Image_YptLeft_rptsLefts_id;   // �����Y�ǵ�id
uint8 Image_YptRight_rptsRights_id; // �ұ���Y�ǵ�id
bool Image_YptLeft_Found;           // �����Y�ǵ��ҵ��ж�
bool Image_YptRight_Found;          // �ұ���Y�ǵ��ҵ��ж�
//------------------------------
// L�ǵ�
uint8 Image_LptLeft_rptsLefts_id;   // �����L�ǵ�id
uint8 Image_LptRight_rptsRights_id; // �ұ���L�ǵ�id
bool Image_LptLeft_Found;           // �����L�ǵ��ҵ��ж�
bool Image_LptRight_Found;          // �ұ���L�ǵ��ҵ��ж�
//------------------------------
// ��ֱ��
bool Image_isStraightLeft;  // ������Ƿ�Ϊֱ��
bool Image_isStraightRight; // �ұ����Ƿ�Ϊֱ��
//------------------------------
// ���
bool Image_isTurnLeft;  // ������Ƿ�Ϊ���
bool Image_isTurnRight; // �ұ����Ƿ�Ϊ���
//------------------------------
// ��ȡѡ�нǵ�����
uint8 Image_angleCntLeft = 0;  // ��¼��ǰѡ�е��ǵڼ����� - �����
uint8 Image_angleCntRight = 0; // ��¼��ǰѡ�е��ǵڼ����� - �ұ���
uint8 Image_lineSeclet = 0;    // ����ѡ��:0 - �����; 1 - �ұ���
uint8 Image_angleBlockLen = 3; // ��ʾ����ı��߳���

//------------------------------Ԫ���ж����------------------------------
bool Image_isGrage = 0;                                            // ����Ƿ��ǳ���
bool Image_isCircle = 0;                                           // ����Ƿ��ǻ���
bool Image_LjudgeFinish = 0;                                       // L�ǵ�Ԫ���ж����״̬��
IMAGE_LCORNER_JUDGE Image_LCornerJude_Status = IMAGE_LCORNER_NONE; // L�ǵ��ж�
uint16 Image_GrageJudge_Thre = 10000;                              // �����жϵı��������־���

//------------------------------���Բ�������------------------------------
// ���ڵ��ԵĲ���(Ϊ��������,����ı�ͷ��ʼ��ĸ��Сд����, ͬʱʹ���»���������)
uint8 image_thre = 120;                     // ���ߴ����ĳ�ʼ��ֵ
uint8 image_begin_x = IMAGE_WIDTH / 2 + 15; // ���ߴ�������ʼx����ƫ�����ĵľ���
uint8 image_begin_y = IMAGE_HEIGHT - 30;    // ���ߴ�����ʼ��y����
uint8 image_block_size = 7;                 // �����ֵ��������߳�
uint8 image_block_clip_value = 4;           // �����ľ������(һ��Ϊ2~5)

/**
 * @brief                   ��ȡͼ������
 * @param image             ͼƬ
 * @param x                 ���ص��x����
 * @param y                 ���ص��y����
 * @return                  ���ص�ĻҶ�ֵ
 */
uint8 IMAGE_AT(uint8 *image, int16 x, int16 y)
{
    return *(image + y * IMAGE_WIDTH + x);
}

/**
 * @brief                   �Թ�Ѳ�� - �Զ���ֵ������
 * @param image             ͼƬ
 * @param block_size        ����Ӧ��ֵ�����򳤶�(����Ϊ����)
 * @param clip_value        ��ֵ������ֵ(����ֵ,һ��Ϊ2-5)
 * @param x                 ����(��ʼ)x����
 * @param y                 ����(��ʼ)y����
 * @return                  ��
 * @example                 Image_FindLine_LeftHand_Adaptive(image, image_block_size, image_block_clip_value, x1, y1);
 */

static void Image_FindLine_LeftHand_Adaptive(uint8 *image, uint8 block_size, int8 clip_value, uint8 x, uint8 y)
{
    // ����Ŀ�ĳ��ȱ���Ϊ����!
    int8 half = block_size / 2;
    uint8 step = 0;
    uint8 dir = 0, turn = 0;
    while (step < Image_iptsLeftNum && half < x && x < IMAGE_WIDTH - half - 1 && half < y && y < IMAGE_HEIGHT - half - 1 && turn < 4)
    {
        // ʹ������Ӧ��ֵ�������ֵ
        // clip_valueΪ���鳣��,һ��ȡ2~5
        int16 localThres = 0;
        for (int16 dy = -half; dy <= half; ++dy)
        {
            for (int16 dx = -half; dx <= half; ++dx)
            {
                localThres += IMAGE_AT(image, x + dx, y + dy);
            }
        }
        localThres /= block_size * block_size;
        localThres -= clip_value;

        // ����ֵ�ж�
        uint8 frontValue = IMAGE_AT(image, x + Image_dir_front[dir][0], y + Image_dir_front[dir][1]);
        uint8 frontLeftValue = IMAGE_AT(image, x + Image_dir_frontLeft[dir][0], y + Image_dir_frontLeft[dir][1]);

        if (frontValue < localThres)
        {
            // ǰ���Ǻ�ɫ"ǽ��" -- ����ת
            // ����ı�,��¼ת��һ��
            // ����ת�� ˳ʱ�� - ����Ҫ(+1)%4����
            dir = (dir + 1) % 4;
            ++turn;
        }
        else if (frontLeftValue < localThres)
        {
            // ǰ���ǰ�ɫ,������ǰ����"��ɫ" - �����������ֱ����
            x += Image_dir_front[dir][0];
            y += Image_dir_front[dir][1];
            Image_iptsLeft[step][0] = x;
            Image_iptsLeft[step][1] = y;
            ++step;
            turn = 0;
        }
        else
        {
            // ǰ���ǰ�ɫ,ͬʱ��ǰ��Ҳ��"��ɫ" - ���������˵����Ҫ����ת��"��ǽ��"
            x += Image_dir_frontLeft[dir][0];
            y += Image_dir_frontLeft[dir][1];
            // ����ת�� ��ʱ�� - ����Ҫ(+3)%4���� (����˵(-1)%4����)
            dir = (dir + 3) % 4;
            Image_iptsLeft[step][0] = x;
            Image_iptsLeft[step][1] = y;
            ++step;
            turn = 0;
        }
    }
    Image_iptsLeftNum = step;
}

/**
 * @brief                   �Թ�Ѳ�� - �Զ���ֵ������
 * @param image             ͼƬ
 * @param block_size        ����Ӧ��ֵ�����򳤶�(����Ϊ����)
 * @param clip_value        ��ֵ������ֵ(����ֵ,һ��Ϊ2-5)
 * @param x                 ����(��ʼ)x����
 * @param y                 ����(��ʼ)y����
 *                          ����:1.��ֹ���߹����������
 *                              2.���߽϶̵�ʱ��ı�num,��ֹ�ⲿ���ʵ�"�Ƿ�"����
 * @return                  ��
 * @example                 Image_FindLine_RightHand_Adaptive(image, image_block_size, image_block_clip_value, x2, y2);
 */
static void Image_FindLine_RightHand_Adaptive(uint8 *image, uint8 block_size, uint8 clip_value, uint8 x, uint8 y)
{
    // ����Ŀ�ĳ��ȱ���Ϊ����!
    uint8 half = block_size / 2;
    uint8 step = 0;
    uint8 dir = 0, turn = 0;
    while (step < Image_iptsRightNum && half < x && x < IMAGE_WIDTH - half - 1 && half < y && y < IMAGE_HEIGHT - half - 1 && turn < 4)
    {
        // ʹ������Ӧ��ֵ�������ֵ
        // clip_valueΪ���鳣��,һ��ȡ2~5
        int16 localThres = 0;
        for (int16 dy = -half; dy <= half; ++dy)
        {
            for (int16 dx = -half; dx <= half; ++dx)
            {
                localThres += IMAGE_AT(image, x + dx, y + dy);
            }
        }
        localThres /= block_size * block_size;
        localThres -= clip_value;

        // ����ֵ�ж�
        uint8 frontValue = IMAGE_AT(image, x + Image_dir_front[dir][0], y + Image_dir_front[dir][1]);
        uint8 frontRightValue = IMAGE_AT(image, x + Image_dir_frontRight[dir][0], y + Image_dir_frontRight[dir][1]);

        if (frontValue < localThres)
        {
            // ǰ���Ǻ�ɫ"ǽ��" -- ����ת
            // ����ı�,��¼ת��һ��
            // ����ת�� ˳ʱ�� - ����Ҫ(+3)%4����(����˵(-1)%4����)
            dir = (dir + 3) % 4;
            ++turn;
        }
        else if (frontRightValue < localThres)
        {
            // ǰ���ǰ�ɫ,ͬʱ����ǰ����"��ɫ" - �����������ֱ����
            x += Image_dir_front[dir][0];
            y += Image_dir_front[dir][1];
            Image_iptsRight[step][0] = x;
            Image_iptsRight[step][1] = y;
            ++step;
            turn = 0;
        }
        else
        {
            // ǰ���ǰ�ɫ,������ǰ��Ҳ��"��ɫ" - ���������˵����Ҫ����ת��"��ǽ��"
            x += Image_dir_frontRight[dir][0];
            y += Image_dir_frontRight[dir][1];
            // ����ת�� ˳ʱ�� - ����Ҫ(+1)%4����
            dir = (dir + 1) % 4;
            Image_iptsRight[step][0] = x;
            Image_iptsRight[step][1] = y;
            ++step;
            turn = 0;
        }
    }
    Image_iptsRightNum = step;
}

/**
 * @brief               ���ǵ㼯�˲�
 * @param pts_in        ��Ҫ�˲�����������
 * @param lineNum       ���ߵĳ���
 * @param pts_out       �˲����
 * @param kernel        "�����εױ߳�"
 * @example
 */
void Image_BlurPoints(uint8 pts_in[][2], uint8 lineNum, uint8 pts_out[][2], uint8 kernerl)
{
    int8 half = kernerl / 2;
    uint16 tmpPtsOut[2];
    for (int i = 0; i < lineNum; ++i)
    {
        tmpPtsOut[0] = 0;
        tmpPtsOut[1] = 0;
        // ���漸�����ֱ�Ӳ�����
        for (int j = -half; j < half; ++j)
        {
            tmpPtsOut[0] += pts_in[bf_clip(i + j, 0, lineNum - 1)][0] * (half + 1 - abs(j));
            tmpPtsOut[1] += pts_in[bf_clip(i + j, 0, lineNum - 1)][1] * (half + 1 - abs(j));
        }
        pts_out[i][0] = tmpPtsOut[0] / ((2 * half + 2) * (half + 1) / 2);
        pts_out[i][1] = tmpPtsOut[1] / ((2 * half + 2) * (half + 1) / 2);
    }
}

/**
 * @brief               �㼯�Ⱦ����(���߹��Ĳ���ǰ���߶εľ���Ϊdist)
 * @param pts_in        ��Ҫ��������
 * @param num1          �������ߵĳ���
 * @param pts_out       �����������
 * @param num2          ������鳤���޷�
 * @param dist          ʵ�ʾ���(��λΪm)
 * @example
 */
void Image_ResamplePoints(uint8 pts_in[][2], uint8 num1, uint8 pts_out[][2], uint8 *num2, float dist)
{
    float remain = 0;
    uint8 len = 0;
    for (uint8 i = 0; i < num1 - 1 && len < *num2; ++i)
    {
        uint8 x0 = pts_in[i][0];
        uint8 y0 = pts_in[i][1];
        float dx = (float)(pts_in[i + 1][0] - x0);
        float dy = (float)(pts_in[i + 1][1] - y0);
        float dn = sqrt(dx * dx + dy * dy);
        dx /= dn;
        dy /= dn;

        // ���еȾ����
        while (remain < dn && len < *num2)
        {
            x0 += (uint8)(dx * remain);
            pts_out[len][0] = x0;
            y0 += (uint8)(dy * remain);
            pts_out[len][1] = y0;

            ++len;
            dn -= remain;
            remain = dist;
        }
        remain -= dn;
    }
    *num2 = len;
}

/**
 * @brief               ���㼯�ֲ��Ƕȱ仯��
 * @param pts_in        ��Ҫ��������
 * @param num           �ߵĳ���
 * @param angle_out     �Ƕ����ֵ
 * @param dist          �ǶȲ����ľ���(ʵ�ʾ���)
 * @formula             tan(x + y) = (tan(x) - tan(y)) / (1 + tan(x) * tan())
 */
void Image_LocalAnglePoints(uint8 pts_in[][2], uint8 num, float angle_out[], uint16 dist)
{
    for (uint8 i = 0; i < num; ++i)
    {
        if (i <= 0 || i >= num - 1)
        {
            // �ߵı�Եû�нǶ�,���д�������Ϊ0
            angle_out[i] = 0;
            continue;
        }
        // �������ķ�������
        // ��������ʵ�Ƕ�Ӧ�Ĳ���
        // ��Ϊ���ֱ�Ӽ����Ϊ�������������Ļ�,��ôֱ�����������180��,ʵ������Ҫ����0��
        float dx1 = pts_in[i][0] - pts_in[bf_clip(i - dist, 0, num - 1)][0];
        float dy1 = pts_in[i][1] - pts_in[bf_clip(i - dist, 0, num - 1)][1];
        float dn1 = sqrtf(dx1 * dx1 + dy1 * dy1);
        float dx2 = pts_in[bf_clip(i + dist, 0, num - 1)][0] - pts_in[i][0];
        float dy2 = pts_in[bf_clip(i + dist, 0, num - 1)][1] - pts_in[i][1];
        float dn2 = sqrtf(dx2 * dx2 + dy2 * dy2);
        float c1 = dx1 / dn1;
        float s1 = dy1 / dn1;
        float c2 = dx2 / dn2;
        float s2 = dy2 / dn2;
        angle_out[i] = atan2f(c1 * s2 - c2 * s1, c2 * c1 + s2 * s1) * 180 / Image_PI;
    }
}

/**
 * @brief               �Ƕȱ仯�ʷǼ�������(�����������鿴��ֵ)
 * @param angle_in      ��Ҫ�����ĽǶ�����
 * @param num           �ߵĳ���
 * @param angle_out     �Ƕ����(ֻ����������ֵ)
 * @param kernel        ����߳�
 * @param cornerNum     �ǵ����
 * @example
 */
void Image_NmsAngle(float angle_in[], uint8 lineNum, float angle_out[], uint8 kernel, uint8 *cornerNum)
{
    int8 half = kernel / 2;
    *cornerNum = lineNum;
    for (uint8 i = 0; i < lineNum; ++i)
    {
        angle_out[i] = angle_in[i];
        for (int8 j = -half; j <= half; ++j)
        {
            if (fabs(angle_in[bf_clip(i + j, 0, lineNum - 1)]) > fabs(angle_out[i]))
            {
                angle_out[i] = 0;
                --(*cornerNum);
                break;
            }
        }
    }
}

/**
 * @brief �ǵ�Ѱ��
 *
 */
void Image_FindCorners(void)
{
    // ʶ�� Y,L�յ�
    // �ѽǵ��ж���false
    Image_YptLeft_Found = false;
    Image_YptRight_Found = false;
    Image_LptLeft_Found = false;
    Image_LptRight_Found = false;
    // �ж��Ƿ���ֱ��
    // �ж��Ƿ񳬹�50�����ص�,���û�г���,�Ǿ�˵���϶�����ֱ����
    Image_isStraightLeft = Image_rptsLeftsNum > 0.5 / Image_sampleDist;
    Image_isStraightRight = Image_rptsRightsNum > 0.5 / Image_sampleDist;

    // ������ж� - ��ʼ�ǵ㲻�����ж�
    for (uint8 i = 5; i < Image_rptsLeftanNum; ++i)
    {
        if (Image_rptsLeftan[i] == 0)
            continue;
        // ����⵽�нǶȵĵ�Ȼ��ȥ�ж�
        uint8 im1 = (uint8)bf_clip(i - (uint8)round(Image_angleDist / Image_sampleDist), 0, Image_rptsLeftsNum - 1);
        uint8 ip1 = (uint8)bf_clip(i + (uint8)round(Image_angleDist / Image_sampleDist), 0, Image_rptsLeftsNum - 1);
        float conf = fabs(Image_rptsLefta[i]) - fabs(Image_rptsLefta[im1] + Image_rptsLefta[ip1]) / 2;

        // Y�ǵ��ж�
        if (Image_YptLeft_Found == false && 30 < conf && 65 > conf && i < 0.4 / Image_sampleDist)
        {
            Image_YptLeft_rptsLefts_id = i;
            Image_YptLeft_Found = true;
        }
        // L�ǵ��ж�
        if (Image_LptLeft_Found == false && 80 < conf && 130 > conf && i < 0.4 / Image_sampleDist)
        {
            Image_LptLeft_rptsLefts_id = i;
            Image_LptLeft_Found = true;
        }
        // ��ֱ���ж�
        if (conf > 15.0 && i < 0.5 / Image_sampleDist)
        {
            Image_isStraightLeft = false;
        }

        // �ҵ�һ���,�˳�
        if (Image_isStraightLeft == false && Image_LptLeft_Found == true && Image_YptLeft_Found == true)
            break;
    }

    // �ұ����ж� - ��ʼ�ǵ㲻�����ж�
    for (uint8 i = 5; i < Image_rptsRightsNum; ++i)
    {
        if (Image_rptsRightan[i] == 0.0)
            continue;
        // ����⵽�нǶȵĵ�Ȼ��ȥ�ж�
        uint8 im1 = (uint8)bf_clip(i - (uint8)round(Image_angleDist / Image_sampleDist), 0, Image_rptsRightsNum - 1);
        uint8 ip1 = (uint8)bf_clip(i + (uint8)round(Image_angleDist / Image_sampleDist), 0, Image_rptsRightsNum - 1);
        float conf = fabs(Image_rptsRighta[i]) - fabs(Image_rptsRighta[im1] + Image_rptsRighta[ip1]) / 2;
        // Y�ǵ��ж�
        if (Image_YptRight_Found == false && 30 < conf && 65 > conf && i < 0.4 / Image_sampleDist)
        {
            Image_YptRight_rptsRights_id = i;
            Image_YptRight_Found = true;
        }
        // L�ǵ��ж�
        if (Image_LptRight_Found == false && 80 < conf && 130 > conf && i < 0.4 / Image_sampleDist)
        {
            Image_LptRight_rptsRights_id = i;
            Image_LptRight_Found = true;
        }
        // ��ֱ���ж�
        if (conf > 15.0 && i < 0.5 / Image_sampleDist)
        {
            Image_isStraightRight = false;
        }

        // �ҵ�һ���,�˳�
        if (Image_isStraightRight == false && Image_LptRight_Found == true && Image_YptRight_Found == true)
            break;
    }

    // ʱ�����,�ȸ�������
    // Y�ǵ���μ��,�������ǵ���뼰�ǵ��ſ����� (�����ϲ�����Y�ǵ�� - ��Ե�ʮ�˽��������)
    if (Image_YptLeft_Found && Image_YptRight_Found)
    {
    }
    // L�ǵ���μ�� - ����L�ǵ���뼰�ǵ��ſ����� (������,���ݵ��Ѱ��,�������L�ǵ�ͬʱ���ֵ����Ҳ����������)
    if (Image_LptLeft_Found && Image_LptRight_Found)
    {
    }
}

/**
 * @brief                   ����߸�������
 * @param pts_in            ��Ҫ�����ı�������
 * @param lineNum           ���ߵĳ���
 * @param pts_out           ���ߵ��������
 * @param approx_num        ��б�ʵ�ʱ���е�����ϵ�(�µ�)�����ص����
 * @param dist              �����Ŀ���
 * @example
 */
void Image_TrackLeftLine(uint8 pts_in[][2], uint8 num, uint8 pts_out[][2], uint8 approx_num, float dist) {
    for (int i = 0; i < num; ++i) {
        float dx = (float)(pts_in[bf_clip(i + approx_num, 0, num - 1)][0] - pts_in[bf_clip(i - approx_num, 0, num-1)][0]);
        float dy = (float)(pts_in[bf_clip(i + approx_num, 0, num - 1)][1] - pts_in[bf_clip(i - approx_num, 0, num-1)][1]);
        float dn = sqrt(dx * dx + dy * dy);
        dx /= dn;
        dy /= dn;
        pts_out[i][0] = (uint8)((float)pts_in[i][0] - dy * dist);
        pts_out[i][1] = (uint8)((float)pts_in[i][1] + dx * dist);
    }
}

/**
 * @brief                   �ұ��߸�������
 * @param pts_in            ��Ҫ�����ı�������
 * @param lineNum           ���ߵĳ���
 * @param pts_out           ���ߵ��������
 * @param approx_num        ��б�ʵ�ʱ���е�����ϵ�(�µ�)�����ص����
 * @param dist              �����Ŀ���
 * @example
 */
void Image_TrackRightLine(uint8 pts_in[][2], uint8 num, uint8 pts_out[][2], uint8 approx_num, float dist) {
    for (int i = 0; i < num; ++i) {
        float dx = (float)(pts_in[bf_clip(i + approx_num, 0, num - 1)][0] - pts_in[bf_clip(i - approx_num, 0, num-1)][0]);
        float dy = (float)(pts_in[bf_clip(i + approx_num, 0, num - 1)][1] - pts_in[bf_clip(i - approx_num, 0, num-1)][1]);
        float dn = sqrt(dx * dx + dy * dy);
        dx /= dn;
        dy /= dn;
        pts_out[i][0] = (uint8)((float)pts_in[i][0] + dy * dist);
        pts_out[i][1] = (uint8)((float)pts_in[i][1] - dx * dist);
    }
}

/**
 * @brief               ��� - ͨ����䷽��,����ͼ����ж�ֵ������ֵ(�����ʱ��ʹ�õ�ƽ����,���Ǽ�Ȩƽ����)
 * @param image         ͼ��ָ��
 * @param imgHeight     ͼ��ĸ߶�
 * @param imgWidth      ͼ��Ŀ���
 * @return              ������õ�����ֵ
 * @example             Image_threshold = Image_Processing_OtsuGetThresh(mt9v03x_image[0]);
 */
uint8 Image_Processing_OtsuGetThresh(const uint8* image) {
    gpio_set_level(P20_9, 0);
    //���س�ȥ����ֵ
    uint8 threshold;

    //8bit�Ҷ�ֵ
    uint16 grayHistogram[256];

    //��С�Ҷ�ֵ
    uint8 minGrayValue;

    //���Ҷ�ֵ
    uint8 maxGrayValue;

    //�õ����ص�����
    uint16 numOfPix = IMAGE_HEIGHT * IMAGE_WIDTH;

    //�Ҷ�ֵ��ֵ
    uint32 imgTotalGrayValue = 0;

    //ǰ�����ص���
    uint16 pixelOfFore = 0;
    //�������ص���
    uint16 pixelOfBack = 0;

    //ǰ��Ԫ�ص�ռ��
    float omegaFore = 0.0;
    //����Ԫ�ص�ռ��
    float omegaBack = 0.0;

    //ǰ��Ԫ�ػҶ�ֵ��ֵ
    uint32 imgTotalGrayValueOfFore = 0;
    //����Ԫ�ػҶ�ֵ��ֵ
    uint32 imgTotalGrayValueOfBack = 0;

    //ǰ��Ԫ�ػҶ�ƽ����
    float miuFore = 0.0;
    //����Ԫ�ػҶ�ƽ����
    float miuBack = 0.0;

    //��ʱ�ķ���
    float sigmaTmp = 0.0;

    //��������󷽲����ݵķ���
    float sigma = 0.0;

    //��ʼ���Ҷ�ֱ��ͼ
    for (int i = 0; i < 256; ++i)
        grayHistogram[i] = 0;


    uint8 index = 0;

    //����ÿ���Ҷȼ�����ÿ������������ͼ�еĸ���
    for (uint8 i = 0; i < IMAGE_HEIGHT; ++i) {
        for (uint8 j = 0; j < IMAGE_WIDTH; ++j) {
            index = *(image + (i * IMAGE_WIDTH + j));
            ++grayHistogram[index];
        }
    }
    //��ȡ��С�ĻҶ�ֵ
    for (minGrayValue = 0; minGrayValue < 256 && grayHistogram[minGrayValue] == 0; ++minGrayValue);

    //��ȡ���ĻҶ�ֵ
    for (maxGrayValue = 255; maxGrayValue > minGrayValue && grayHistogram[maxGrayValue] == 0; --maxGrayValue);

    if (minGrayValue == maxGrayValue)       //ֻ��һ����ɫ
        return minGrayValue;

    if (minGrayValue + 1 == maxGrayValue)   //ֻ��������ɫ
        return minGrayValue;

    //�������� �� �Ҷ�ֵ����
    for (uint8 i = minGrayValue; i < maxGrayValue; ++i) {
        imgTotalGrayValue += grayHistogram[i] * i;
    }


    //���ж�ֵ�����㴦��
    for (uint8 i = minGrayValue; i < maxGrayValue; ++i) {
        pixelOfFore += grayHistogram[i];                    //ǰ�����ظ���
        pixelOfBack = numOfPix - pixelOfFore;               //�������ظ���

        omegaFore = (float)pixelOfFore / (float)numOfPix;   //ǰ�����ذٷֱ�
        omegaBack = 1 - omegaFore;                          //�������ذٷֱ�

        imgTotalGrayValueOfFore += grayHistogram[i] * i;                            //ǰ�����ػҶ�ֵ
        imgTotalGrayValueOfBack = imgTotalGrayValue - imgTotalGrayValueOfFore;      //�������ػҶ�ֵ

        //ǰ���Ҷ�ƽ����
        miuFore = (float)imgTotalGrayValueOfFore / (float)pixelOfFore;              //ǰ�����ػҶ�ƽ����
        miuBack = (float)imgTotalGrayValueOfBack / (float)pixelOfBack;              //�������ػҶ�ƽ����

        //������䷽��
        sigmaTmp = omegaFore * omegaBack * (miuFore - miuBack) * (miuFore - miuBack);
        if (sigmaTmp > sigma) {
            sigma = sigmaTmp;
            threshold = i;
        }
    }
    //gpio_set_level(P20_9, 1);
    return threshold;
}

/**
 * @brief               ͼ������ʼ�� - ���㴦����ֵ
 * @attention           ��Ҫ������ͷ��ʼ���Ժ��ٵ��øú���
 */
void Image_Init(void) {
    //ϵͳ��ʱһ��ʱ��,Ȼ�������
    system_delay_ms(100);
    while (1) {
        if (mt9v03x_finish_flag == 1) {
            ++Image_disPictureCnt;
            mt9v03x_finish_flag = 0;
            if (Image_disPictureCnt > Image_disPictureCnt_Thre) {
                Image_disPictureCnt = 0;
                break;
            }
        }
    }
    for (uint8 i = 0; i < Image_threCnt_Thre; ++i) {
        Image_threSum += Image_Processing_OtsuGetThresh(mt9v03x_image[0]);
    }
    image_thre = Image_threSum / Image_threCnt_Thre;
}

/**
 * @brief               ͼ����,������Ե��ȡ,ȥ����+��͸��,�˲�,�Ⱦ����,����Ƕ�,��������
 * @param image         ��Ҫ������ͼƬ
 * @example             Image_Process(mt9v03x_image[0]);
 */
void Image_Process(uint8* image) {
    Image_Process_Status = 0;

    //----------------------------------------
    //ԭͼ�����ұ���
    //----------------------------------------
    if (Image_isUsefulData_Status) {
        Image_iptsLeftNum_Bak = Image_iptsLeftNum;
        //�����ݽ��б���
        for (uint8 i = 0; i < Image_iptsLeftNum; ++i) {
            Image_iptsLeft_Bak[i][0] = Image_iptsLeft[i][0];
            Image_iptsLeft_Bak[i][1] = Image_iptsLeft[i][1];
        }
    }

    //�������
    Image_iptsLeftNum = sizeof(Image_iptsLeft) / sizeof(Image_iptsLeft[0]);
    uint8 x1 = image_begin_x;
    uint8 y1 = image_begin_y;
    for (; x1 > 0; --x1) if (IMAGE_AT(image, x1 - 1, y1) < image_thre) break;           //���ұ߽��ϵĵ�һ����
    if (IMAGE_AT(image, x1, y1) >= image_thre){//û�е��߽����������
        Image_FindLine_LeftHand_Adaptive(image, image_block_size, image_block_clip_value, x1, y1);
    }
    else
        Image_iptsLeftNum = 0;                                                          //�߽�Ļ�����0��

    //----------------------------------------
    if (Image_isUsefulData_Status) {
        Image_iptsRightNum_Bak = Image_iptsRightNum;
        //�����ݽ��б���
        for (uint8 i = 0; i < Image_iptsRightNum; ++i) {
            Image_iptsRight_Bak[i][0] = Image_iptsRight[i][0];
            Image_iptsRight_Bak[i][1] = Image_iptsRight[i][1];
        }
    }
    //���ұ���
    Image_iptsRightNum = sizeof(Image_iptsRight) / sizeof(Image_iptsRight[0]);
    uint8 x2 = image_begin_x;
    uint8 y2 = image_begin_y;
    for (; x2 < IMAGE_WIDTH - 1; ++x2) if (IMAGE_AT(image, x2 + 1, y1) < image_thre) break;     //���ұ߽��ϵĵ�һ����
    if (IMAGE_AT(image, x2, y2) >= image_thre)                                                  //û�е��߽����������
        Image_FindLine_RightHand_Adaptive(image, image_block_size, image_block_clip_value, x2, y2);
    else
        Image_iptsRightNum = 0;                                                                  //�߽�Ļ�����0��

    //----------------------------------------
    //�Ա��߽���ȥ���� + ��͸�ӱ任
    //for (uint8 i = 0; i < Image_iptsLeftNum; ++i) {
    //    Image_rptsLeft[i][0] = map_x[Image_iptsLeft[i][1]][Image_iptsLeft[i][0]];
    //    Image_rptsLeft[i][1] = map_y[Image_iptsLeft[i][1]][Image_iptsLeft[i][0]];
    //}
    //Image_rptsLeftNum = Image_iptsLeftNum;
//
    //for (uint8 i = 0; i < Image_iptsRightNum; ++i) {
    //    Image_rptsRight[i][0] = map_x[Image_iptsRight[i][1]][Image_iptsRight[i][0]];
    //    Image_rptsRight[i][1] = map_y[Image_iptsRight[i][1]][Image_iptsRight[i][0]];
    //}
    //Image_rptsRightNum = Image_iptsRightNum;
    //û�б任�����Ȳ��任�ˣ�����һ��
    for (uint8 i = 0; i < Image_iptsLeftNum; ++i) {
        Lboundary_trans[0][i] = Image_rptsLeft[i][0] = Image_iptsLeft[i][0];
        Rboundary_trans[1][i] = Image_rptsLeft[i][1] = Image_iptsLeft[i][1];
    }
    Image_rptsLeftNum = Image_iptsLeftNum;

    for (uint8 i = 0; i < Image_iptsRightNum; ++i) {
        Image_rptsRight[i][0] = Image_iptsRight[i][0];
        Image_rptsRight[i][1] = Image_iptsRight[i][1];
    }
    Image_rptsRightNum = Image_iptsRightNum;


    //ȥ��(0,0)��
    for (uint8 i = 1; i < Image_rptsLeftNum - 1; ++i) {                                         //TODO:�޸������bug
        if (Image_rptsLeft[i + 1][0] != 0 || Image_rptsLeft[i + 1][1] != 0) {
            Image_rptsLeft[i][0] = Image_rptsLeft[i + 1][0];
            Image_rptsLeft[i][1] = Image_rptsLeft[i + 1][1];
            ++Image_rptsLeftrNum;
        }
    }
    Image_rptsLeftNum = Image_rptsLeftrNum;
    Image_rptsLeftrNum = 0;
    for (uint8 i = 1; i < Image_rptsRightNum - 1; ++i) {                                        //TODO:�޸������bug
        if (Image_rptsRight[i + 1][0] != 0 || Image_rptsRight[i + 1][1] != 0) {
            Image_rptsRight[i][0] = Image_rptsRight[i + 1][0];
            Image_rptsRight[i][1] = Image_rptsRight[i + 1][1];
            ++Image_rptsRightrNum;
        }
    }
    Image_rptsRightNum = Image_rptsRightrNum;
    Image_rptsRightrNum = 0;
    //----------------------------------------
    //�����ݽ��������˲�
    //�����
    Image_BlurPoints(Image_rptsLeft, Image_rptsLeftNum, Image_rptsLeftb, Image_linerBlurKernel);
    Image_rptsLeftbNum = Image_rptsLeftNum;
    //�ұ���
    Image_BlurPoints(Image_rptsRight, Image_rptsRightNum, Image_rptsRightb, Image_linerBlurKernel);
    Image_rptsRightbNum = Image_rptsRightNum;

    //----------------------------------------
    //���˲������ݽ��еȾ����
    //----------------------------------------
    //�����ݽ��б���
    if (Image_isUsefulData_Status) {
        Image_rptsLeftsNum_Bak = Image_rptsLeftsNum;
        Image_rptsRightsNum_Bak = Image_rptsRightsNum;
        for (uint8 i = 0; i < Image_rptsLeftsNum; ++i) {
            Image_rptsLefts_Bak[i][0] = Image_rptsLefts[i][0];
            Image_rptsLefts_Bak[i][1] = Image_rptsLefts[i][1];
        }
        for (uint8 i = 0; i < Image_rptsRightsNum; ++i) {
            Image_rptsRights_Bak[i][0] = Image_rptsRights[i][0];
            Image_rptsRights_Bak[i][1] = Image_rptsRights[i][1];
        }
    }
    //----------------------------------------
    //�Ⱦ����
    Image_rptsLeftsNum = sizeof(Image_rptsLefts) / sizeof(Image_rptsLefts[0]);
    Image_ResamplePoints(Image_rptsLeftb, Image_rptsLeftbNum, Image_rptsLefts, &Image_rptsLeftsNum, Image_sampleDist * Image_pixelPreMeter);
    Image_rptsRightsNum = sizeof(Image_rptsRights) / sizeof(Image_rptsRights[0]);
    Image_ResamplePoints(Image_rptsRightb, Image_rptsRightbNum, Image_rptsRights, &Image_rptsRightsNum, Image_sampleDist * Image_pixelPreMeter);

    //----------------------------------------
    //�����߾ֲ��Ƕȱ仯��
    Image_LocalAnglePoints(Image_rptsLefts, Image_rptsLeftsNum, Image_rptsLefta, (uint16)round(Image_angleDist / Image_sampleDist));
    Image_rptsLeftaNum = Image_rptsLeftsNum;
    Image_LocalAnglePoints(Image_rptsRights, Image_rptsRightsNum, Image_rptsRighta, (uint16)round(Image_angleDist / Image_sampleDist));
    Image_rptsRightaNum = Image_rptsRightsNum;

    //----------------------------------------
    //�ԽǶȱ仯�ʽ��зǼ�������(ֻ����һ�α������������ĵ�)
    Image_NmsAngle(Image_rptsLefta, Image_rptsLeftaNum, Image_rptsLeftan, (uint16)round(Image_angleDist / Image_sampleDist) * 2 + 1, &Image_cornerNumLeft);
    Image_rptsLeftanNum = Image_rptsLeftaNum;
    Image_NmsAngle(Image_rptsRighta, Image_rptsRightaNum, Image_rptsRightan, (uint16)round(Image_angleDist / Image_sampleDist) * 2 + 1, &Image_cornerNumRight);
    Image_rptsRightanNum = Image_rptsRightaNum;

    if (Image_isUsefulData_Status) {
        Image_rptsLeftcNum_Bak = Image_rptsLeftcNum;
        for (uint8 i = 0; i < Image_rptsLeftcNum; ++i) {
            Image_rptsLeftc_Bak[i][0] = Image_rptsLeftc[i][0];
            Image_rptsLeftc_Bak[i][1] = Image_rptsLeftc[i][1];
        }

        Image_rptsRightcNum_Bak = Image_rptsRightcNum;
        for (uint8 i = 0; i < Image_rptsRightcNum; ++i) {
            Image_rptsRightc_Bak[i][0] = Image_rptsRightc[i][0];
            Image_rptsRightc_Bak[i][1] = Image_rptsRightc[i][1];
        }
    }
    //----------------------------------------
    //����������
    Image_TrackLeftLine(Image_rptsLefts, Image_rptsLeftsNum, Image_rptsLeftc, (uint8)round(Image_angleDist / Image_sampleDist), Image_pixelPreMeter * Image_roadWidth / 2);
    Image_rptsLeftcNum = Image_rptsLeftsNum;
    Image_TrackRightLine(Image_rptsRights, Image_rptsRightsNum, Image_rptsRightc, (uint8)round(Image_angleDist / Image_sampleDist), Image_pixelPreMeter * Image_roadWidth / 2);
    Image_rptsRightcNum = Image_rptsRightsNum;

    if (Image_isUsefulData_Status == 0) {
        Image_isUsefulData_Status = 1;
    }
    Image_Process_Status = 1;
}