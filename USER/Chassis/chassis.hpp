#ifndef CHASSIS_HPP
#define CHASSIS_HPP

/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "motor.hpp"

/* Exported macros -----------------------------------------------------------*/

//�ְ뾶, m
const float WHEEL_RADIUS = 0.050f;

//������ת���ٶ�, m/s
const float WHEEL_FULL_V = (MOTOR_FULL_OMEGA * WHEEL_RADIUS);

//omega��m/sӳ��ϵ��, (���־�+���־�)/2, m/rad
const float OMEGA_TO_MS = ((0.482f + 0.500f) / 2);

//�����ٶ�����, �κ�������ܳ���
//�����ٶ�����, m/s
const float X_MAX = 1.0f;
//ǰ���ٶ�����, m/s
const float Y_MAX = 1.0f;
//��ת�ٶ�����, rad/s
const float OMEGA_MAX = 2.0f;

/* Exported types ------------------------------------------------------------*/

/**
 * @brief �ٶ����Ͷ���
 *
 */
struct SpeedTypeDef
{
    //���� m/s ��Ϊ��
    float X;
    //ǰ�� m/s ǰΪ��
    float Y;
    //��ת rad/s ��ʱ��Ϊ��
    float Omega;
};

class Class_Chassis
{
public:

    //���̶�Ӧ�ĵ��
    Class_Motor_With_Hall_Encoder Motor[4];

    void Init(TIM_HandleTypeDef __Driver_PWM_TIM, TIM_HandleTypeDef __Calculate_EXTI_TIM);

    void Set_Velocity(SpeedTypeDef __Velocity);
    void Set_Control_Method(Enum_Control_Method __Control_Method);

    void Hall_Encoder_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
    void Calculate_TIM_PeriodElapsedCallback();

protected:

    //���PWM������ʱ��
    TIM_HandleTypeDef Driver_PWM_TIM;
    //������㶨ʱ���ж�
    TIM_HandleTypeDef Calculate_TIM;

    //���̿��Ʒ�ʽ
    Enum_Control_Method Control_Method = Control_Method_OMEGA;

    //�����ٶ�
    SpeedTypeDef Velocity =
    {
        0,
        0,
        0
    };

};

/* Exported variables --------------------------------------------------------*/

/* Exported function declarations --------------------------------------------*/

#endif