#ifndef PID_HPP
#define PID_HPP

/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "limits.h"

/* Exported macros -----------------------------------------------------------*/

//PID��ʱ������, s
const float PID_CALCULATE_PERIOD = 0.1f;

/* Exported types ------------------------------------------------------------*/

/**
 * @brief ΢������
 *
 */
enum Enum_D_First
{
    D_First_NO = 0,
    D_First_YES
};

class Class_PID
{
public:

    void Init(float __K_P, float __K_I, float __K_D, float __I_Out_Max, float __Out_Max);

    void Set_K_P(float __K_P);
    void Set_K_I(float __K_I);
    void Set_K_D(float __K_D);
    void Set_I_Out_Max(float __I_Out_Max);
    void Set_Out_Max(float __Out_Max);
    void Set_Target(float __Target);
    void Set_Now(float __Now);
    void Set_Dead_Zone(float __Dead_Zone);
    void Set_Variable_Speed_I_A(float __Variable_Speed_I_A);
    void Set_Variable_Speed_I_B(float __Variable_Speed_I_B);
    void Set_I_Separate_Threshold(float __I_Separate_Threshold);
    void Set_D_First(Enum_D_First __D_First);

    float Get_Out();

    void Adjust_TIM_PeriodElapsedCallback();

protected:

    //PID��ʱ������, s
    float D_T = PID_CALCULATE_PERIOD;

    //PID��P
    float K_P;
    //PID��I
    float K_I;
    //PID��D
    float K_D;
    //�����޷�, 0Ϊ������
    float I_Out_Max;
    //����޷�, 0Ϊ������
    float Out_Max;

    //Ŀ��ֵ
    float Target = 0;
    //��ǰֵ
    float Now = 0;
    //���
    float Error = 0;
    //���ֵ
    float Out = 0;

    //ǰ��ֵ
    float Pre_Value;
    //����ֵ
    float Integral_Error;
    //ǰ�����
    float Pre_Error;

    //PID�������
    //P���
    float P_Out = 0;
    //I���
    float I_Out = 0;
    //D���
    float D_Out = 0;

    //����, Error�������ֵ�ڲ����
    float Dead_Zone = 0;

    //���ٻ���, A��BΪ����
    //A��B��Ϊ0, ��ͨ����
    //Error <= B, ��ͨ����
    //B < Error <= A + B, ���ٻ���
    //A + B < Error, ������
    //�����ڶ���ֵ, 0Ϊ������
    float Variable_Speed_I_A = 0;
    //��������, 0Ϊ������
    float Variable_Speed_I_B = 0;

    //���ַ�����ֵ����Ϊ����, 0Ϊ������
    float I_Separate_Threshold = 0;

    //΢������
    Enum_D_First D_First = D_First_NO;
};

/* Exported variables --------------------------------------------------------*/

/* Exported function declarations --------------------------------------------*/

#endif