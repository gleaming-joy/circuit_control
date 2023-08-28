/* Includes ------------------------------------------------------------------*/

#include "Chassis.hpp"

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
 * @brief ��ʼ������
 *
 * @param __Driver_PWM_TIM ���������ʱ�����
 * @param __Calculate_EXTI_TIM �ٶȼ��㶨ʱ�����
 */
void Class_Chassis::Init(TIM_HandleTypeDef __Driver_PWM_TIM, TIM_HandleTypeDef __Calculate_EXTI_TIM)
{
    Driver_PWM_TIM = __Driver_PWM_TIM;
    Calculate_TIM = __Calculate_EXTI_TIM;

    //�����ʼ��

    Motor[0].Init(__Driver_PWM_TIM, TIM_CHANNEL_1, Pin_Pushpull_MotorDirectionA1_Pin, Pin_Pushpull_MotorDirectionA1_GPIO_Port, Pin_Pushpull_MotorDirectionB1_Pin, Pin_Pushpull_MotorDirectionB1_GPIO_Port, __Calculate_EXTI_TIM, Pin_Exti_HallEncoderA1_Pin, Pin_Exti_HallEncoderA1_GPIO_Port, Pin_PullDown_HallEncoderB1_Pin, Pin_PullDown_HallEncoderB1_GPIO_Port);
    Motor[0].Set_Rotate_Direction_Flag(CCW);

    Motor[1].Init(__Driver_PWM_TIM, TIM_CHANNEL_2, Pin_Pushpull_MotorDirectionA2_Pin, Pin_Pushpull_MotorDirectionA2_GPIO_Port, Pin_Pushpull_MotorDirectionB2_Pin, Pin_Pushpull_MotorDirectionB2_GPIO_Port, __Calculate_EXTI_TIM, Pin_Exti_HallEncoderA2_Pin, Pin_Exti_HallEncoderA2_GPIO_Port, Pin_PullDown_HallEncoderB2_Pin, Pin_PullDown_HallEncoderB2_GPIO_Port);
    Motor[1].Set_Rotate_Direction_Flag(CCW);

    Motor[2].Init(__Driver_PWM_TIM, TIM_CHANNEL_3, Pin_Pushpull_MotorDirectionA3_Pin, Pin_Pushpull_MotorDirectionA3_GPIO_Port, Pin_Pushpull_MotorDirectionB3_Pin, Pin_Pushpull_MotorDirectionB3_GPIO_Port, __Calculate_EXTI_TIM, Pin_Exti_HallEncoderA3_Pin, Pin_Exti_HallEncoderA3_GPIO_Port, Pin_PullDown_HallEncoderB3_Pin, Pin_PullDown_HallEncoderB3_GPIO_Port);
    Motor[2].Set_Rotate_Direction_Flag(CCW);

    Motor[3].Init(__Driver_PWM_TIM, TIM_CHANNEL_4, Pin_Pushpull_MotorDirectionA4_Pin, Pin_Pushpull_MotorDirectionA4_GPIO_Port, Pin_Pushpull_MotorDirectionB4_Pin, Pin_Pushpull_MotorDirectionB4_GPIO_Port, __Calculate_EXTI_TIM, Pin_Exti_HallEncoderA4_Pin, Pin_Exti_HallEncoderA4_GPIO_Port, Pin_PullDown_HallEncoderB4_Pin, Pin_PullDown_HallEncoderB4_GPIO_Port);
    Motor[3].Set_Rotate_Direction_Flag(CCW);

    //���PID��ʼ��
    for (int i = 0; i < 4; i++)
    {
        Motor[i].Omega_PID.Init(2000, 3000, 25, ULONG_MAX, ULONG_MAX);
    }
}

/**
 * @brief �趨�����ٶ�
 *
 * @param __Velocity �����ٶ�
 */
void Class_Chassis::Set_Velocity(SpeedTypeDef __Velocity)
{
    Velocity = __Velocity;
}



/**
 * @brief �趨���̿��Ʒ�ʽ
 *
 * @param __Control_Method ���̿��Ʒ�ʽ
 */
void Class_Chassis::Set_Control_Method(Enum_Control_Method __Control_Method)
{
    Control_Method = __Control_Method;

    for (int i = 0; i < 4; i++)
    {
        Motor[i].Set_Control_Method(__Control_Method);
    }
}

/**
 * @brief ���̵�����������������жϴ�����
 *
 */
void Class_Chassis::Hall_Encoder_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    //�ж��ж�Դ, ��ָ�������жϴ�����
    if (GPIO_Pin == Pin_Exti_HallEncoderA1_Pin)
    {
        Motor[0].Hall_Encoder_GPIO_EXTI_Callback();
    }
    else if (GPIO_Pin == Pin_Exti_HallEncoderA2_Pin)
    {
        Motor[1].Hall_Encoder_GPIO_EXTI_Callback();
    }
    else if (GPIO_Pin == Pin_Exti_HallEncoderA3_Pin)
    {
        Motor[2].Hall_Encoder_GPIO_EXTI_Callback();
    }
    else if (GPIO_Pin == Pin_Exti_HallEncoderA4_Pin)
    {
        Motor[3].Hall_Encoder_GPIO_EXTI_Callback();
    }
}


/**
 * @brief ��ʱ���жϴ�����
 *
 */
void Class_Chassis::Calculate_TIM_PeriodElapsedCallback()
{
    //�ٶȽ���
    Math_Constrain(&Velocity.X, -X_MAX, X_MAX);
    Math_Constrain(&Velocity.Y, -Y_MAX, Y_MAX);
    Math_Constrain(&Velocity.Omega, -OMEGA_MAX, OMEGA_MAX);
    Motor[0].Set_Omega_Target((-OMEGA_TO_MS * Velocity.Omega + Velocity.X - Velocity.Y) / WHEEL_RADIUS * ((Motor[0].Get_Rotate_Direction_Flag() == CW) ? 1 : (-1)));
    Motor[1].Set_Omega_Target((-OMEGA_TO_MS * Velocity.Omega - Velocity.X - Velocity.Y) / WHEEL_RADIUS * ((Motor[1].Get_Rotate_Direction_Flag() == CW) ? 1 : (-1)));
    Motor[2].Set_Omega_Target((OMEGA_TO_MS * Velocity.Omega + Velocity.X - Velocity.Y) / WHEEL_RADIUS * ((Motor[2].Get_Rotate_Direction_Flag() == CW) ? 1 : (-1)));
    Motor[3].Set_Omega_Target((OMEGA_TO_MS * Velocity.Omega - Velocity.X - Velocity.Y) / WHEEL_RADIUS * ((Motor[3].Get_Rotate_Direction_Flag() == CW) ? 1 : (-1)));

    //������ֵ�趨�����
    for (int i = 0; i < 4; i++)
    {
        Motor[i].Calculate_TIM_PeriodElapsedCallback();
    }

}

/* Function prototypes -------------------------------------------------------*/
