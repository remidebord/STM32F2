#ifndef __ANALOG_H
#define __ANALOG_H

/* includes ---------------------------------------------------------------- */
#include "stm32f2xx_adc.h"
#include "Common.h"

/* class ------------------------------------------------------------------- */
class AnalogIn
{
	private:
		
		ADC_TypeDef* m_adc;
		GPIO_TypeDef* m_port;
		int m_pin;
		int m_channel;
		int m_value;
	
		int GetChannel(GPIO_TypeDef* port, int pin);
	
	public:
		
		AnalogIn(ADC_TypeDef* adcx, GPIO_common GPIO_c);
		int read();												// Read (conversion)
		operator int();										// Read (no conversion)
};

class AnalogOut
{
	private:
		
		GPIO_TypeDef* m_port;
		int m_pin;
		int m_channel;
	
	public:
		
		AnalogOut(GPIO_common GPIO_c);
		void write(int n);							  // Write
		AnalogOut& operator= (int n);			// Write shorhand
		int read();												// Read
		operator int();					// Read shorthand
};

#endif
