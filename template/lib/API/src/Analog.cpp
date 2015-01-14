/*!
 * \file Analog.cpp
 * \brief Analog API.
 * \author Rémi.Debord
 * \version 1.0
 * \date 28 novembre 2013
 *
 * Librairie Analog (ADC et DAC).
 *
 */

#include "Analog.h"

/*!
 *  \brief Constructor
 *
 *  Constructeur de la classe AnalogIn (ADC).
 *
 *  \param GPIO_c : ADC pin
 *
 */

AnalogIn :: AnalogIn(ADC_TypeDef* adcx, GPIO_common GPIO_c)
{
	ADC_InitTypeDef       ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
  GPIO_InitTypeDef      GPIO_InitStructure;
	
	m_adc = adcx;
	m_port = GPIO_c.port;
	m_pin = GPIO_c.pin;
	m_channel = this->GetChannel(GPIO_c.port, GPIO_c.pin);
	m_value = 0;
	
  /* GPIOx Periph clock enable */
	if(m_port == GPIOA) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	else if(m_port == GPIOB) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	else if(m_port == GPIOC) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	else if(m_port == GPIOD) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	/* ADCx clock */
	if(m_adc == ADC1) RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	else if(m_adc == ADC2) RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);	
	else if(m_adc == ADC3) RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);	
  
	/* Configure "pin" in input mode */
  GPIO_InitStructure.GPIO_Pin = m_pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(m_port, &GPIO_InitStructure);
	
	/* ADCx DeInit */  
  //ADC_DeInit(); 
  
	/* ADC Common Init */
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
  ADC_CommonInit(&ADC_CommonInitStructure);
	
	/* ADCx Init */
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 1;
  ADC_Init(m_adc, &ADC_InitStructure);

  /* Enable ADCx */
  ADC_Cmd(m_adc, ENABLE);
}

/*!
 *  \brief Read ADC value
 *
 *  Conversion de la valeur de la tension en entrée.
 *
 *  \return m_value: ADC value
 */

int AnalogIn :: read()
{
	__disable_irq();

	/* Channel configuration */
	ADC_RegularChannelConfig(m_adc, m_channel, 1, ADC_SampleTime_15Cycles);

	/* Start conversion on the selected channel */
	ADC_SoftwareStartConv(m_adc);
	
	/* Wait the end of conversion (EOC) */
	while((ADC_GetFlagStatus(m_adc, ADC_FLAG_EOC) == RESET) && (ADC_GetFlagStatus(m_adc, ADC_FLAG_OVR) == RESET));
	
	if(ADC_GetFlagStatus(m_adc, ADC_FLAG_OVR) != RESET)
	{
		ADC_ClearFlag(m_adc, ADC_FLAG_OVR);
		
		__enable_irq();
		
		return 0;
	}
	else
	{
		/* Automatic stop */
	
		/* Store value */
		m_value = ADC_GetConversionValue(m_adc);
		
		__enable_irq();
		
		/* Return the converted value */
		return m_value;
	}
}

/*!
 *  \brief Read ADC value (no conversion)
 *
 *  Récupération de la dernière conversion.
 *
 *  \return m_value: ADC value
 */

AnalogIn :: operator int()
{
	return this->read();
}

/*!
 *  \brief Get ADC channel
 *
 *  Récupération du canal de l'ADC correspondant.
 *
 *  \return m_value: ADC value
 */

int AnalogIn :: GetChannel(GPIO_TypeDef* port, int pin)
{
	int channel = 0;
	
	if(port == GPIOA)
	{
		switch(pin)
		{
			case GPIO_Pin_0: channel = ADC_Channel_0; break;
			case GPIO_Pin_1: channel = ADC_Channel_1; break;
			case GPIO_Pin_2: channel = ADC_Channel_2; break;
			case GPIO_Pin_3: channel = ADC_Channel_3; break;
			case GPIO_Pin_4: channel = ADC_Channel_4; break;
			case GPIO_Pin_5: channel = ADC_Channel_5; break;
			case GPIO_Pin_6: channel = ADC_Channel_6; break;
			case GPIO_Pin_7: channel = ADC_Channel_7; break;
		}
	}	
	else if(port == GPIOB)
	{
		switch(pin)
		{
			case GPIO_Pin_0: channel = ADC_Channel_8; break;
			case GPIO_Pin_1: channel = ADC_Channel_9; break;
		}
	}	
	else if(port == GPIOC)
	{
		switch(pin)
		{
			case GPIO_Pin_0: channel = ADC_Channel_10; break;
			case GPIO_Pin_1: channel = ADC_Channel_11; break;
			case GPIO_Pin_2: channel = ADC_Channel_12; break;
			case GPIO_Pin_3: channel = ADC_Channel_13; break;
			case GPIO_Pin_4: channel = ADC_Channel_14; break;
			case GPIO_Pin_5: channel = ADC_Channel_15; break;
		}
	}
	
	return channel;
}

/*!
 *  \brief Constructor
 *
 *  Constructeur de la classe AnalogOut (DAC).
 *
 *  \param GPIO_c : DAC pin
 *
 */

AnalogOut :: AnalogOut(GPIO_common GPIO_c)
{
	DAC_InitTypeDef    DAC_InitStructure;
  GPIO_InitTypeDef   GPIO_InitStructure;

	m_port = GPIO_c.port;
	m_pin = GPIO_c.pin;
	
	if(m_pin == GPIO_Pin_4) m_channel = DAC_Channel_1;
	else if(m_pin == GPIO_Pin_5) m_channel = DAC_Channel_2;
	
  /* GPIOx Periph clock enable */
	if(m_port == GPIOA) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	else if(m_port == GPIOB) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	else if(m_port == GPIOC) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	else if(m_port == GPIOD) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	/* Configure "pin" in input mode */
  GPIO_InitStructure.GPIO_Pin = m_pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(m_port, &GPIO_InitStructure);

  /* Enable DAC clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
		
  /* DAC channelx Configuration */
  DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
  DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	
  /* DAC Channelx Init */
  DAC_Init(m_channel, &DAC_InitStructure);
  
  /* Enable DAC Channelx */
  DAC_Cmd(m_channel, ENABLE);
}

/*!
 *  \brief DAC write
 *
 *  Modification du niveau de tension.
 *
 *  \param n: DAC value
 */

void AnalogOut :: write(int n)
{
	if(m_channel == DAC_Channel_1) DAC_SetChannel1Data(DAC_Align_12b_R, n);
	else if(m_channel == DAC_Channel_2) DAC_SetChannel2Data(DAC_Align_12b_R, n);
}

/*!
 *  \brief DAC write (shorthand)
 *
 *  Modification du niveau de tension.
 *
 *  \param n: DAC value
 */

AnalogOut& AnalogOut ::  operator= (int n)
{
	this->write(n);
	return *this;
}

/*!
 *  \brief DAC read
 *
 *  Lecture du niveau de tension.
 *
 *  \return DAC value
 */

int AnalogOut :: read()
{
	return DAC_GetDataOutputValue(m_channel);
}

/*!
 *  \brief DAC read (shorthand)
 *
 *  Lecture du niveau de tension.
 *
 *  \return DAC value
 */

AnalogOut :: operator int()
{
	return this->read();
}
