/* Includes ------------------------------------------------------------------*/

#include "Steer.hpp"

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
    return ((x > 0) ? x : -x);
}

/**
 * @brief ��ʼ�����
 *
 * @param __Driver_PWM_TIM ���������ʱ�����
 * @param __Driver_PWM_TIM_Channel_x ���������ʱ��ͨ��
 */
void Class_Steer::Init(TIM_HandleTypeDef __Driver_PWM_TIM, uint8_t __Driver_PWM_TIM_Channel_x)
{
    Driver_PWM_TIM = __Driver_PWM_TIM;
    Driver_PWM_TIM_Channel_x = __Driver_PWM_TIM_Channel_x;
    HAL_TIM_PWM_Start(&__Driver_PWM_TIM, __Driver_PWM_TIM_Channel_x);
}

/**
 * @brief �趨���ռ�ձ�, �ɴ�ȷ�����
 *
 * @param output ����ĽǶ�
 */
void Class_Steer::Set_Out(float __Out)
{
    //ռ�ձȶ�Ӧʱ��, ռ�ձ�
    float time;
    time = STEER_PWM_MIDDLE + (__Out - Max_Angle / 2) / (Max_Angle / 2) * STEER_PWM_EXTREME_TO_MIDDLE;
    Out = time / STEER_PWM_PERIOD * STEER_PWM_PRESCALER;
}

/**
 * @brief
 *
 */
void Class_Steer::Output()
{
    Math_Constrain(&Out, (int32_t)(STEER_PWM_PRESCALER * STEER_PWM_LEFT), (int32_t)(STEER_PWM_PRESCALER * STEER_PWM_RIGHT));
    __HAL_TIM_SetCompare(&Driver_PWM_TIM, Driver_PWM_TIM_Channel_x, Out);
}

/* Function prototypes -------------------------------------------------------*/