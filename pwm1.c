#include "main.h"

#define FREQUENCY 10000 // 1kHz
//#define FREQUENCY 50 // 50Hz

PwmOut pwm(PA9, FREQUENCY, TIM1_CH2);
//PwmOut pwm(PA8, FREQUENCY, TIM1_CH1);
//PwmOut pwm(PA0, FREQUENCY, TIM2_CH1);
//PwmOut pwm(PA3, FREQUENCY, TIM2_CH4);
//PwmOut pwm(PB0, FREQUENCY, TIM3_CH3);
//PwmOut pwm(PB7, FREQUENCY, TIM4_CH2);
//PwmOut pwm(PA0, FREQUENCY, TIM5_CH1);
//PwmOut pwm(PC9, FREQUENCY, TIM8_CH4);
//PwmOut pwm(PA3, FREQUENCY, TIM9_CH2);
//PwmOut pwm(PB8, FREQUENCY, TIM10_CH1);
//PwmOut pwm(PB9, FREQUENCY, TIM11_CH1);
//PwmOut pwm(PB15, FREQUENCY, TIM12_CH2);
//PwmOut pwm(PA6, FREQUENCY, TIM13_CH1);
//PwmOut pwm(PA7, FREQUENCY, TIM14_CH1);

int main(void)
{
  Systick_Init();
	
	// Set duty cycle to 50%
	pwm = 0.5;
	
  while (1)
  {
  }
}
