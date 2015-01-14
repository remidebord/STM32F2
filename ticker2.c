#include "main.h"
	
Ticker tick1(TIM14);
DigitalOut led1(PC8);

Ticker tick2(TIM13);
DigitalOut led2(PC9);

void blink1(void)
{
	led1 = !led1;
}

void blink2(void)
{
	led2 = !led1;
}

int main(void)
{
	Systick_Init();

	tick1.attach(&blink1, 100);
	tick2.attach(&blink2, 100);
	
  while(1)
  {
		
  }
}