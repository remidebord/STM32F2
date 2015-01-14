#include "main.h"
	
Ticker tick(TIM16);
DigitalOut led1(PC8);
DigitalOut led2(PC9);

//PwmOut pwm(PA4, 1000, TIM14_CH1);
//PwmOut pwm(PB9, 1000, TIM17_CH1);
PwmOut pwm(PB10, 1000, TIM2_CH3);

void blink1(void)
{
	led1 = !led1;
}

void blink2(void)
{
	led2 = !led2;
}

int main(void)
{
	Systick_Init();

	tick.attach(&blink1, 1000);
	
	pwm.enable_irq();
	pwm.attach(&blink2);	
	
	pwm = 0.5;
	
  while(1)
  {
		
  }
}