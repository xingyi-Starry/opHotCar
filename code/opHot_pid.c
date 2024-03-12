/*
 * xiao_pid.c
 *
 *  Created on: 2023��5��1��
 *      Author: Jayden_NaN
 */

#include "opHot_pid.h"
/**
 * @brief           PID��ʼ��
 * @parameter p     ����ʼ����ָ��
 * @return          NULL
 */
void PID_Init(PID* p) {
    p->kP = 0.0;
    p->kI = 0.0;
    p->kD = 0.0;
    p->kPSet = 0.0;
    p->kISet = 0.0;
    p->kDSet = 0.0;
    p->sum = 0.0;
    p->preError = 0.0;
    p->ppreError = 0.0;
    p->ut = 0.0;
    p->sumLimit = 0.0;
    p->utLimit = 0.0;
}

/**
 * @brief               ��������p�ĸ������
 * @parameter pLimit    �����޷�
 * @parameter coLimit   �����޷�
 * @return              NULL
 */
void PID_SetParameter(PID* p, float setP, float setI, float setD, float pLimit, float coLimit, float boost) {
    p->kPSet = boost * setP;
    p->kISet = boost * setI;
    p->kDSet = boost * setD;
    p->sumLimit = pLimit;
    p->utLimit = coLimit;
    p->kP =p->kPSet;
    p->kI =p->kISet;
    p->kD =p->kDSet;
}
/**
 * @brief               λ��ʽPID
 * @parameter   p       ����������PID����
 * @parameter   target  Ŀ��ֵ
 * @parameter   cur     ��ǰֵ
 */
void PID_PostionalPID(PID* p, float target, float cur) {
    float error = target - cur;
    //������
    p->sum += error * p->kI;
    //���л����޷�
    p->sum = p->sum > p->sumLimit ? p->sumLimit : p->sum;
    p->sum = p->sum < -p->sumLimit ? -p->sumLimit : p->sum;
    //���ݽ��м���
    if(-1 < error - p->preError && error - p->preError < 1){
        p->ut = p->kP * error;
    }
    else{
        p->ut = p->kP * error
            + p->sum
            + p->kD * (error - p->preError);
    }
    //���������޷�
    p->ut = p->ut > p->utLimit ? p->utLimit : p->ut;
    p->ut = p->ut < -p->utLimit ? -p->utLimit : p->ut;
    //�������ݸ���
    p->preError = error;
}

/**
 * @brief               ����ʽPID
 * @parameter p         ����������PID����
 * @parameter target    Ŀ��ֵ
 * @parameter cur      ��ǰֵ
 *
 */
void PID_IncrementalPID(PID* p, float target, float cur) {
    float error = target - cur;
    //���ݽ�������
    p->ut += p->kP * (error - p->preError)
            + p->kI * error
            + p->kD * (error - 2 * p->preError + p->preError);
    //���������޷�
    p->ut = p->ut > p->utLimit ? p->utLimit : p->ut;
    p->ut = p->ut < -p->utLimit ? -p->utLimit : p->ut;
    //�������ݸ���
    p->ppreError = p->preError;
    p->preError = error;
}

/**
 * @brief               ģ��PID
 * @parameter p         ����������PID����
 * @parameter target    Ŀ��ֵ
 * @parameter cur       ��ǰֵ
 * @parameter pidClass  ����������PIDģʽ
 * @parameter ERROR_MAX ����ӳ��ERROR���ֵ
 * @parameter DERROR_MAX ����ӳ��DERROR���ֵ��
 */
//ģ������
MEMBERSHIP_enum PRULE[7][7]={
    {PB, PB, PM, PM, PS, ZO, ZO},
    {PB, PB, PM, PS, PS, ZO, NS},
    {PM, PM, PM, PS, ZO, NS, NS},
    {PM, PM, PS, ZO, NS, NM, NM},
    {PS, PS, ZO, NS, NS, NM, NM},
    {PS, ZO, NS, NM, NM, NM, NB},
    {ZO, ZO, NM, NM, NM, NB, NB}
};
MEMBERSHIP_enum IRULE[7][7]={
    {NB, NB, NM, NM, NS, ZO, ZO},
    {NB, NB, NM, NS, NS, ZO, ZO},
    {NB, NM, NS, NS, ZO, PS, PS},
    {NM, NM, NS, ZO, PS, PM, PM},
    {NM, NS, ZO, PS, PS, PM, PB},
    {ZO, ZO, PS, PS, PM, PB, PB},
    {ZO, ZO, PS, PM, PM, PB, PB}
};
MEMBERSHIP_enum DRULE[7][7]={
    {PS, NS, NB, NB, NB, NM, PS},
    {PS, NS, NB, NM, NM, NS, ZO},
    {ZO, NS, NM, NM, NS, NS, ZO},
    {ZO, NS, NS, NS, NS, NS, ZO},
    {ZO, ZO, ZO, ZO, ZO, ZO, ZO},
    {PB, PS, PS, PS, PS, PS, PB},
    {PB, PM, PM, PM, PS, PS, PB}
};
//��������Ϣ
MEMBERSHIP object;
//PID�䶯��Χ
float P_LIMIT =0.3;
float I_LIMIT =0.3;
float D_LIMIT =0.3;
void PID_FuzzyPID(PID* p, float target, float cur, PIDCLASS_enum pidClass,float ERROR_MAX,float DERROR_MAX){
    float error = target - cur;
    float derror = error - p->preError;
    //����ӳ��
    error = error * 3 / ERROR_MAX;
    derror = derror * 3 / DERROR_MAX;
    if (error > 3) error = 3;
    else if (error < -3) error = -3;
    if (derror > 3) derror = 3;
    else if (derror < -3) derror = -3;
    //������ȷ��
    if (error >= 0) {
        object.membershipErrorLeft = (MEMBERSHIP_enum)error;
        object.membershipErrorRight = (MEMBERSHIP_enum)(object.membershipErrorLeft + 1);
        object.valueErrorLeft = object.membershipErrorRight - error;
        object.valueErrorRight = error - object.membershipErrorLeft;
        if (object.membershipErrorLeft == PB) object.membershipErrorRight = PB;
    }
    else {
        object.membershipErrorRight = (MEMBERSHIP_enum)error;
        object.membershipErrorLeft = (MEMBERSHIP_enum)(object.membershipErrorRight - 1);
        object.valueErrorLeft = object.membershipErrorRight - error;
        object.valueErrorRight = derror - object.membershipErrorLeft;
        if (object.membershipErrorRight == NB) object.membershipErrorLeft = NB;
    }
    if (derror >= 0) {
        object.membershipDerrorLeft = (MEMBERSHIP_enum)derror;
        object.membershipDerrorRight = (MEMBERSHIP_enum)(object.membershipDerrorLeft + 1);
        object.valueDerrorLeft = object.membershipDerrorRight - derror;
        object.valueDerrorRight = derror - object.membershipDerrorLeft;
        if (object.membershipDerrorLeft == PB) object.membershipDerrorRight = PB;
    }
    else {
        object.membershipDerrorRight = (MEMBERSHIP_enum)derror;
        object.membershipDerrorLeft = (MEMBERSHIP_enum)(object.membershipDerrorRight - 1);
        object.valueDerrorLeft = object.membershipDerrorRight - derror;
        object.valueDerrorRight = derror - object.membershipDerrorLeft;
        if (object.membershipDerrorRight == NB) object.membershipDerrorLeft = NB;
    }
    //ģ��������ȥģ��
    object.membershipKP = PRULE[3+object.membershipErrorLeft][3+object.membershipDerrorLeft]*object.valueErrorLeft*object.valueDerrorLeft
                         +PRULE[3+object.membershipErrorLeft][3+object.membershipDerrorRight]*object.valueErrorLeft*object.valueDerrorRight
                         +PRULE[3+object.membershipErrorRight][3+object.membershipDerrorLeft]*object.valueErrorRight*object.valueDerrorLeft
                         +PRULE[3+object.membershipErrorRight][3+object.membershipDerrorRight]*object.valueErrorRight*object.valueDerrorRight;
    object.membershipKI = IRULE[3+object.membershipErrorLeft][3+object.membershipDerrorLeft]*object.valueErrorLeft*object.valueDerrorLeft
                         +IRULE[3+object.membershipErrorLeft][3+object.membershipDerrorRight]*object.valueErrorLeft*object.valueDerrorRight
                         +IRULE[3+object.membershipErrorRight][3+object.membershipDerrorLeft]*object.valueErrorRight*object.valueDerrorLeft
                         +IRULE[3+object.membershipErrorRight][3+object.membershipDerrorRight]*object.valueErrorRight*object.valueDerrorRight;
    object.membershipKD = DRULE[3+object.membershipErrorLeft][3+object.membershipDerrorLeft]*object.valueErrorLeft*object.valueDerrorLeft
                         +DRULE[3+object.membershipErrorLeft][3+object.membershipDerrorRight]*object.valueErrorLeft*object.valueDerrorRight
                         +DRULE[3+object.membershipErrorRight][3+object.membershipDerrorLeft]*object.valueErrorRight*object.valueDerrorLeft
                         +DRULE[3+object.membershipErrorRight][3+object.membershipDerrorRight]*object.valueErrorRight*object.valueDerrorRight;
    //�������
    if(pidClass == PostionalPID){
        p->kP=p->kPSet+object.membershipKP*P_LIMIT/3;
        p->kD=p->kDSet+object.membershipKD*D_LIMIT/3;
    }
    else if(pidClass == IncrementalPID){
        p->kP=p->kPSet+object.membershipKP*P_LIMIT/3;
        p->kI=p->kISet+object.membershipKI*I_LIMIT/3;
        p->kD=p->kDSet+object.membershipKD*D_LIMIT/3;
    }

    //PID����
    if(pidClass == PostionalPID){
        PID_PostionalPID(p, target, cur);
    }
    else if(pidClass == IncrementalPID){
        PID_IncrementalPID(p, target, cur);
    }
}
