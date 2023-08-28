#ifndef MOTOR_HPP
#define MOTOR_HPP

/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "PID.hpp"

/* Exported macros -----------------------------------------------------------*/

//Բ����
const float PI = 3.14159f;

//������ٺ���תת��, rad/s
const float MOTOR_FULL_OMEGA = (190.0f / 60.0f * 2.0f * PI);

//������ٺ����������������, /rad
const float MOTOR_ENCODER_NUM_PER_RAD = (17.0f * 51.0f / 2.0f / PI);

//���PWM��ռ�ձȶ�Ӧ����ֵ
const int32_t MOTOR_CALCULATE_PRESCALER = 32767;

//���㶨ʱ��Ƶ��, s
const float MOTOR_CALCULATE_PERIOD = 0.05f;

/* Exported types ------------------------------------------------------------*/

/**
 * @brief ������Ʒ�ʽ
 *
 */
enum Enum_Control_Method
{
    Control_Method_OPENLOOP = 0,
    Control_Method_OMEGA,
    Control_Method_ANGLE
};

/**
 * @brief ������Ʒ�ʽ
 *
 */
enum Enum_Rotate_Direction
{
    CW = 0,
    CCW
};

class Class_Motor
{
public:

    void Init(TIM_HandleTypeDef __Driver_PWM_TIM, uint8_t __Driver_PWM_TIM_Channel_x, uint16_t __Output_A_GPIO_Pin, GPIO_TypeDef* __Output_A_GPIOx, uint16_t __Output_B_GPIO_Pin, GPIO_TypeDef* __Output_B_GPIOx);

    void Set_Rotate_Direction_Flag(Enum_Rotate_Direction __Rotate_Direction_Flag);
    void Set_Motor_Full_Omega(float __Motor_Full_Omega);
    void Set_Motor_PWM_Period(int32_t __Motor_PWM_Period);
    void Set_Out(int32_t __Out);

    Enum_Rotate_Direction Get_Rotate_Direction_Flag();
    float Get_Motor_Full_Omega();
    int32_t Get_Motor_PWM_Period();
    int32_t Get_Out();

    void Output();

protected:

    //���������ʱ�����
    TIM_HandleTypeDef Driver_PWM_TIM;
    //��ʱ��ͨ��
    uint8_t Driver_PWM_TIM_Channel_x;
    //�������A��
    uint16_t Output_A_GPIO_Pin;
    GPIO_TypeDef* Output_A_GPIOx;
    //�������B��
    uint16_t Output_B_GPIO_Pin;
    GPIO_TypeDef* Output_B_GPIOx;

    //���������ת����
    Enum_Rotate_Direction Rotate_Direction_Flag = CW;
    //������ٺ���תת��, rad/s
    float Motor_Full_Omega = MOTOR_FULL_OMEGA;
    //���PWM��ռ�ձȶ�Ӧ����ֵ
    int32_t Motor_PWM_Period = MOTOR_CALCULATE_PRESCALER;
    //���Ŀ�����ǿ��, �����PWMռ�ձȵķ���
    int32_t Out = 0;

};

class Class_Motor_With_Hall_Encoder : public Class_Motor
{
public:

    //����ٶȻ�PID����
    Class_PID Omega_PID;
    //����ǶȻ�PID����
    Class_PID Angle_PID;

    void Init(TIM_HandleTypeDef __Driver_PWM_TIM, uint8_t __Driver_PWM_TIM_Channel_x, uint16_t __Output_A_GPIO_Pin, GPIO_TypeDef* __Output_A_GPIOx, uint16_t __Output_B_GPIO_Pin, GPIO_TypeDef* __Output_B_GPIOx, TIM_HandleTypeDef __Calculate_EXTI_TIM, uint16_t __Input_A_GPIO_Pin, GPIO_TypeDef* __Input_A_GPIOx, uint16_t __Input_B_GPIO_Pin, GPIO_TypeDef* __Input_B_GPIOx);

    void Set_Control_Method(Enum_Control_Method Control_Method);
    void Set_Motor_Encoder_Num_Per_Rad(float Motor_Encoder_Num_Per_Rad);
    void Set_Omega_Target(float Omega_Target);
    void Set_Angle_Target(float Angle_Target);

    Enum_Control_Method Get_Control_Method();
    float Get_Omega_Now();
    float Get_Angle_Now();

    void Hall_Encoder_GPIO_EXTI_Callback();
    void Calculate_TIM_PeriodElapsedCallback();

protected:

    //���㶨ʱ�����
    TIM_HandleTypeDef Calculate_TIM;
    //��������������A
    uint16_t Input_A_GPIO_Pin;
    GPIO_TypeDef* Input_A_GPIOx;
    //��������������B
    uint16_t Input_B_GPIO_Pin;
    GPIO_TypeDef* Input_B_GPIOx;

    //������Ʒ�ʽ
    Enum_Control_Method Control_Method = Control_Method_OMEGA;
    //��������������
    int32_t Hall_Encoder_Count = 0;
    //����������ǰһ������
    int32_t Prev_Hall_Encoder_Count = 0;
    //������ٺ����������������, /rad
    float Motor_Encoder_Num_Per_Rad = MOTOR_ENCODER_NUM_PER_RAD;
    //��ǰ���ת��, rad/s
    float Omega_Now = 0;
    //Ŀ����ת��, rad/s
    float Omega_Target = 0;
    //��ǰ����Ƕ�, rad
    float Angle_Now = 0;
    //Ŀ�����Ƕ�, rad
    float Angle_Target = 0;

};

/* Exported variables --------------------------------------------------------*/

/* Exported function declarations --------------------------------------------*/

#endif