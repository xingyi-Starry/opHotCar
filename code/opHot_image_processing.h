#ifndef CODE_OPHOT_IMAGE_PROCESSING_H_
#define CODE_OPHOT_IMAGE_PROCESSING_H_

#include "zf_common_headfile.h"
#include "opHotCar.h"
#include "opHot_basic_function.h"

// CAMERA_SELECTION内容解释   --现在只有总钻风，这是学长挖了没填的大坑，看个乐 --linnuofan-2024/3/22
// 为 1 的时候,选择总钻风
// 为 2 的时候,选择小钻风
// 为 3 的时候,选择凌瞳
#define CAMERA_SELECTION (1)
#if CAMERA_SELECTION == 1 // 选择总钻风
#define IMAGE_HEIGHT (120)
#define IMAGE_WIDTH (188)
#elif CAMERA_SELECTION == 2 // 选择小钻风
#define IMAGE_HEIGHT (OV7725_H)
#define IMAGE_WIDTH (OV7725_W)
#elif CAMERA_SELECTION == 3 // 选择凌瞳
#define IMAGE_HEIGHT (SCC8660_H)
#define IMAGE_WIDTH (SCC8660_W)
#endif

#define INVERTED_TRACING_Y (70)     // 斜向巡线起始y坐标
#define IMAGE_LINE_MAX_NUM (90)     // 图片边线像素点最大个数
#define IMAGE_RESAMPLE_MAX_NUM (60) // 重采样边线像素点最大个数
#define TURN_JUDGE_ANGLE (25)  // 弯道判断角度
//------------------------------------------------------------
// 所有状态机
extern uint8 Image_Process_Status;
extern uint8 Image_Init_flag;
//------------------------------------------------------------
// 基本变量
extern uint16 Image_threSum;
//------------------------------------------------------------
// 基本数据
// 1. 原图左右边线
// 2. 边线左右数据
extern uint8 Image_iptsLeft[90][2];  // 左边线坐标存储 - 0代表x坐标,1代表y坐标
extern uint8 Image_iptsRight[90][2]; // 右边线坐标存储
extern uint8 Image_iptsLeftNum;      // 左边线像素点个数
extern uint8 Image_iptsRightNum;     // 右边线像素点个数
extern uint8 Image_iptsLeftNum_Bak;  // 左边线像素点个数备份
extern uint8 Image_iptsRightNum_Bak; // 右边线像素点个数备份
// 逆透视变换曲线
extern uint8 Image_rptsLeft[90][2];  // 左边线去畸变+逆透视变换坐标存储
extern uint8 Image_rptsRight[90][2]; // 右边线去畸变+逆透视变换坐标存储
extern uint8 Image_rptsLeftNum;      // 左边线去畸变+逆透视变换像素点个数
extern uint8 Image_rptsRightNum;     // 右边线去畸变+逆透视变换像素点个数
//------------------------------
// 点集三角滤波相关
extern const uint8 Image_linerBlurKernel; // 三角滤波时候的区块边长
extern uint8 Image_rptsLeftb[90][2];      // 三角滤波后的左边线坐标存储
extern uint8 Image_rptsRightb[90][2];     // 三角滤波后的右边线坐标存储
extern uint8 Image_rptsLeftbNum;          // 三角滤波后的左边线长度
extern uint8 Image_rptsRightbNum;         // 三角滤波后的右边线长度
//------------------------------
// 等距采样相关
extern const float Image_sampleDist;                      // 等距采用采样的距离
extern uint8 Image_rptsLefts[IMAGE_RESAMPLE_MAX_NUM][2];  // 等距采样后的左边线坐标存储
extern uint8 Image_rptsRights[IMAGE_RESAMPLE_MAX_NUM][2]; // 等距采样后的右边线坐标存储
extern uint8 Image_rptsLeftsNum;                          // 等距采样后的左边线长度
extern uint8 Image_rptsRightsNum;                         // 等距采样后的右边线长度
extern uint8 Image_LeftLine_Lost;                         // 左边线丢失标志位
extern uint8 Image_RightLine_Lost;                        // 左边线丢失标志位

//------------------------------
// 图传相关
extern uint8 LeftLine_raw_show[2][IMAGE_LINE_MAX_NUM];  // 图传原始左边线
extern uint8 RightLine_raw_show[2][IMAGE_LINE_MAX_NUM]; // 图传原始右边线
extern uint8 LeftLine_show[2][IMAGE_RESAMPLE_MAX_NUM];  // 图传左边线
extern uint8 RightLine_show[2][IMAGE_RESAMPLE_MAX_NUM]; // 图传右边线
extern uint8 MidLine_show[2][IMAGE_RESAMPLE_MAX_NUM];   // 图传中线
extern uint8 Image_show_NE;                             // 图传标志位
extern uint8 image_bak[MT9V03X_H][MT9V03X_W];           // 原图备份
//------------------------------
// 边线局部角度变化率相关
extern const float Image_angleDist; // 计算边线转角时,三个计算点的距离
extern float Image_rptsLefta[90];   // 左边线对应点处的角度大小
extern float Image_rptsRighta[90];  // 右边线对应点处的角度大小
extern uint8 Image_rptsLeftaNum;    // 左边线点的个数
extern uint8 Image_rptsRightaNum;   // 右边线点的个数
//------------------------------
// 角度变化率非极大抑制相关
extern float Image_rptsLeftan[90];  // 左边线区域最大角存储
extern float Image_rptsRightan[90]; // 右边线区域最大角存储
extern uint8 Image_rptsLeftanNum;   // 左边线点的个数
extern uint8 Image_rptsRightanNum;  // 右边线点的个数
//------------------------------
// 左右变线跟踪相关
// extern uint8 Image_rptsLeftc[IMAGE_RESAMPLE_MAX_NUM][2];  // 左边线跟踪得到的中线数据
// extern uint8 Image_rptsRightc[IMAGE_RESAMPLE_MAX_NUM][2]; // 右边线跟踪得到的中线数据
extern uint8 Image_MidLine[IMAGE_RESAMPLE_MAX_NUM][2]; // 中线数据
extern uint8 Image_RsMidLine[IMAGE_RESAMPLE_MAX_NUM][2]; // 等距采样后的中线数据
// extern uint8 Image_rptsLeftcNum;                          // 左边线跟踪得到的中线的线长
// extern uint8 Image_rptsRightcNum;                         // 右边线跟踪得到的中线的线长
extern uint8 Image_MidLineNum; // 中线线长

//------------------------------角点寻找相关------------------------------
//------------------------------
// 角点个数
extern uint8 Image_cornerNumLeft;  // 角点个数
extern uint8 Image_cornerNumRight; // 角点个数
// L角点
extern uint8 Image_LptLeft_rptsLefts_id;   // 左边线L角点id
extern uint8 Image_LptRight_rptsRights_id; // 右边线L角点id
extern bool Image_LptLeft_Found;           // 左边线L角点找到判定
extern bool Image_LptRight_Found;          // 右边线L角点找到判断
//------------------------------
// 长直道
extern bool Image_isStraightLeft;  // 左边线是否为直道
extern bool Image_isStraightRight; // 右边线是否为直道
//------------------------------
// 弯道
extern uint8 Image_LeftDir;
extern uint8 Image_RightDir;
//------------------------------调试参数处理------------------------------
// 用于调试的参数(为了作区分,这里的标头起始字母用小写处理, 同时使用下划线命名法)
extern uint8 image_thre;             // 边线处理的初始阈值
extern uint8 image_begin_x;          // 边线处理的起始x坐标偏离中心的距离
extern uint8 image_begin_y;          // 边线处理起始的y坐标
extern uint8 image_block_size;       // 区域二值化的区域边长
extern uint8 image_block_clip_value; // 修正的经验参数(一般为2~5)

//-----------函数-----------
uint8 IMAGE_AT(uint8 *image, int16 x, int16 y);
void Image_LineCut(void);
void Image_Init(void);
void Image_Process(uint8 *image);

#endif