# gleaming_joy！
 ## 电机  
绿色PWM，蓝色第一个GPIO，紫色是第二个 
- 0: 麦轮左前 Motor[2]  
tim4: CH3 PD14  
GPIO_Output: PD9 PF4  
GPIO_Input: PD8  
GPIO_EXTI10: PD10  

- 1: 麦轮右前 Motor[3]  
tim4: CH4 PD15  
GPIO_Output: PE8 PE14  
GPIO_Input: PE7  
GPIO_EXTI15: PE15   

- 2: 麦轮左后 Motor[1]  
tim4: CH2 PD13  
GPIO_Output: PD11 PB13  
GPIO_Input: PF8   
GPIO_EXTI6: PF6  

- 3: 麦轮右后 Motor[0]  
tim4: CH1 PD12  
GPIO_Output: PF5 PB12  
GPIO_Input: PF11  
GPIO_EXTI7: PF7   

- 4: 左胶轮  
tim2: CH2 PA1  
GPIO_Output: PC3 PA3  
GPIO_Input: PA5  
GPIO_EXTI4: PC4  

- 5: 右胶轮  
tim2: CH3 PA2  
GPIO_Output: PC2 PA4   
GPIO_Input: PC5   
GPIO_EXTI2: PB2   

## 舵机
机械爪舵机由下往上编号  
舵机棕色地线，红色vcc，黄色信号线  
- 木盒  
tim3: CH1 PA6  

- 机械爪5  
tim1: CH2 PE11

- 机械爪4  
tim3: CH2 PA7  

- 机械爪3  
tim3: CH3 PB0  

- 机械爪2  
tim3: CH4 PB1  

- 机械爪1  
tim1: CH1 PE9  

## 同步带滑台
tim9: CH1 PE5  


## 通信  
UASRT1_TX: PA9  
USART1_RX: PA10

## 巡线
ADC1_IN6: PA6  
ADC1_IN7: PA7  
ADC1_IN10: PC0  
ADC1_IN11: PC1