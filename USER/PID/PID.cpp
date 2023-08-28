/* Includes ------------------------------------------------------------------*/

#include "PID.hpp"

/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function declarations ---------------------------------------------*/

/**
 * @brief �޷�����
 *
 * @tparam Type
 * @param x ��������
 * @param Min ��Сֵ
 * @param Max ���ֵ
 */
template <typename Type>
void Math_Constrain(Type* x, Type Min, Type Max)
{
    if (*x < Min)
    {
        *x = Min;
    }
    else if (*x > Max)
    {
        *x = Max;
    }
}

/**
 * @brief �����ֵ
 *
 * @tparam Type
 * @param x ��������
 * @return Type x�ľ���ֵ
 */
template <typename Type>
Type Math_Abs(Type x)
{
    return((x > 0) ? x : -x);
}

/**
 * @brief PID��ʼ��
 *
 * @param __K_P Pֵ
 * @param __K_I Iֵ
 * @param __K_D Dֵ
 * @param __I_Out_Max �����޷�
 * @param __Out_Max ����޷�
 */
void Class_PID::Init(float __K_P, float __K_I, float __K_D, float __I_Out_Max, float __Out_Max)
{
    K_P = __K_P;
    K_I = __K_I;
    K_D = __K_D;
    I_Out_Max = __I_Out_Max;
    Out_Max = __Out_Max;
}

/**
 * @brief �趨PID��P
 *
 * @param __K_P PID��P
 */
void Class_PID::Set_K_P(float __K_P)
{
    K_P = __K_P;
}

/**
 * @brief �趨PID��I
 *
 * @param __K_I PID��I
 */
void Class_PID::Set_K_I(float __K_I)
{
    K_I = __K_I;
}

/**
 * @brief �趨PID��D
 *
 * @param __K_D PID��D
 */
void Class_PID::Set_K_D(float __K_D)
{
    K_D = __K_D;
}

/**
 * @brief �趨�����޷�, 0Ϊ������
 *
 * @param __I_Out_Max �����޷�, 0Ϊ������
 */
void Class_PID::Set_I_Out_Max(float __I_Out_Max)
{
    I_Out_Max = __I_Out_Max;
}

/**
 * @brief �趨����޷�, 0Ϊ������
 *
 * @param __Out_Max ����޷�, 0Ϊ������
 */
void Class_PID::Set_Out_Max(float __Out_Max)
{
    Out_Max = __Out_Max;
}

/**
 * @brief �趨Ŀ��ֵ
 *
 * @param __Target Ŀ��ֵ
 */
void Class_PID::Set_Target(float __Target)
{
    Target = __Target;
}

/**
 * @brief �趨��ǰֵ
 *
 * @param __Now ��ǰֵ
 */
void Class_PID::Set_Now(float __Now)
{
    Now = __Now;
}

/**
 * @brief �趨����, Error�������ֵ�ڲ����
 *
 * @param __Dead_Zone ����, Error�������ֵ�ڲ����
 */
void Class_PID::Set_Dead_Zone(float __Dead_Zone)
{
    Dead_Zone = __Dead_Zone;
}

/**
 * @brief �趨�����ڶ���ֵ, 0Ϊ������
 *
 * @param __Variable_Speed_I_A �����ڶ���ֵ, 0Ϊ������
 */
void Class_PID::Set_Variable_Speed_I_A(float __Variable_Speed_I_A)
{
    Variable_Speed_I_A = __Variable_Speed_I_A;
}

/**
 * @brief �趨��������, 0Ϊ������
 *
 * @param __Variable_Speed_I_B ��������, 0Ϊ������
 */
void Class_PID::Set_Variable_Speed_I_B(float __Variable_Speed_I_B)
{
    Variable_Speed_I_B = __Variable_Speed_I_B;
}

/**
 * @brief �趨���ַ�����ֵ����Ϊ����, 0Ϊ������
 *
 * @param __I_Separate_Threshold ���ַ�����ֵ����Ϊ����, 0Ϊ������
 */
void Class_PID::Set_I_Separate_Threshold(float __I_Separate_Threshold)
{
    I_Separate_Threshold = __I_Separate_Threshold;
}

/**
 * @brief �趨΢������
 *
 * @param __D_First ΢������
 */
void Class_PID::Set_D_First(Enum_D_First __D_First)
{
    D_First = __D_First;
}

/**
 * @brief ��ȡ���ֵ
 *
 * @return float ���ֵ
 */
float Class_PID::Get_Out()
{
    return(Out);
}

/**
 * @brief PID����ֵ
 *
 * @return float ���ֵ
 */
void Class_PID::Adjust_TIM_PeriodElapsedCallback()
{
    float Abs_Error;
    Error = Target - Now;
    Abs_Error = Math_Abs(Error);

    //�ж�����
    if (Abs_Error < Dead_Zone)
    {
        Out = 0;
        return;
    }

    //����p��
    P_Out = K_P * Error;

    //����i��
    //���Ա��ٻ���
    float Speed_Ratio;
    if (Variable_Speed_I_A == 0 && Variable_Speed_I_A == 0)
    {
        Speed_Ratio = 1;
    }
    else
    {
        if (Abs_Error < Variable_Speed_I_B)
        {
            Speed_Ratio = 1;
        }
        else if (Variable_Speed_I_B <= Abs_Error < Variable_Speed_I_A + Variable_Speed_I_B)
        {
            Speed_Ratio = (Variable_Speed_I_A + Variable_Speed_I_B - Abs_Error) / Variable_Speed_I_A;
        }
        if (Abs_Error >= Variable_Speed_I_B)
        {
            Speed_Ratio = 0;
        }
    }
    Integral_Error += Speed_Ratio * D_T * Error;
    if (I_Out_Max != 0)
    {
        Math_Constrain(&Integral_Error, -I_Out_Max / K_I, I_Out_Max / K_I);
    }
    //���ַ���
    if (I_Separate_Threshold == 0)
    {
        I_Out = K_I * Integral_Error;
    }
    else
    {
        if (Abs_Error < I_Separate_Threshold)
        {
            I_Out = K_I * Integral_Error;
        }
        else
        {
            I_Out = 0;
        }
    }

    //����d��
    if (D_First == D_First_YES)
    {
        D_Out = K_D * (Now - Pre_Value);
    }
    else
    {
        D_Out = K_D * (Error - Pre_Error);
    }

    //�ƺ���
    Pre_Error = Error;
    Pre_Value = Now;
    Out = P_Out + I_Out + D_Out;
    if (Out_Max != 0)
    {
        Math_Constrain(&Out, -Out_Max, Out_Max);
    }


}

/* Function prototypes -------------------------------------------------------*/