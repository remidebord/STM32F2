#include "main.h"

int value1 = 0;
int value2 = 0;
int value3 = 0;

AnalogIn ain1(ADC1, PA1);
AnalogIn ain2(ADC2, PB0);
AnalogIn ain3(ADC3, PC3);

int main(void)
{
	Systick_Init();
	
  while (1)
  {
		value1 = ain1.read();
		value2 = ain2.read();
		value3 = ain3.read();
  }
}