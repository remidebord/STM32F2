#include "main.h"

TimeOut timeout(TIM14);

DigitalOut led1(PC8);
DigitalOut led2(PC9);

AnalogIn ain(ADC1, PA0);

PwmOut pwm(PB10, 1000, TIM2_CH3);

int value;

void blink1(void)
{
	led1 = !led1;
	led2 = 0;
	
	timeout.start();
}

void blink2(void)
{
	led2 = 1;
	
	value = ain.read();
}

int main(void)
{
	Systick_Init();

	pwm.enable_irq();
	pwm.attach(&blink1);	
	pwm = 0.5;
	
	timeout.attach_us(&blink2, 960);
	
  while(1)
  {
		
  }
}