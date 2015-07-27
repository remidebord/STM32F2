#include "main.h"
	
DigitalOut led1(PC8);
DigitalOut led2(PC9);
	
// DigitalIn pushButton(PA0);
InterruptIn pushButton(PA0);

void Push(void)
{
	led2 = !led2;
}

int main(void)
{
	Systick_Init();
	
	pushButton.rise(&Push);
	
  while (1)
  {
		led1 = !led1;
		Delay(100);
		
// 		if(pushButton) led2 = 1;
// 		else led2 = 0;
  }
}
