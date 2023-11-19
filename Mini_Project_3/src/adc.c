/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ATmega16 ADC driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#include "avr/io.h" /* To use the ADC Registers */
#include "adc.h"
#include "common_macros.h" /* To use the macros like SET_BIT */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void ADC_init(const ADC_ConfigType * Config_Ptr)
{

	/* ADMUX Register Bits Description:
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	switch(Config_Ptr->ref_volt)
	{
	case 0 :
		/* REFS1:0 = 00 to choose AREF
		 */
		ADMUX = 0;
		break;

	case 1 :
		/* REFS1:0 = 01 to choose AVCC
		 */
		ADMUX |= (1<<REFS0);
		break;

	case 2 :
		/* REFS1:0 = 10 Reserved
		 */
		ADMUX |= (1<<REFS1);
		break;

	case 3 :
		/* REFS1:0 = 11 Internal
		 */
		ADMUX = (1<<REFS1) | (1<<REFS0);
		break;

	default :break;

	}

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 */
	switch(Config_Ptr->prescaler)
	{
	case 0 :
		/*ADPS2:0 = 000 to choose ADC_Clock = F_CPU/2 = 1Mhz/2
		 */
		ADCSRA |= (1<<ADEN) ;
		break;

	case 1 :
		/*ADPS2:0 = 001 to choose ADC_Clock = F_CPU/2 = 1Mhz/2
		 */
		ADCSRA = (1<<ADEN) | (1<<ADPS0);
		break;

	case 2 :
		/*ADPS2:0 = 010 to choose ADC_Clock = F_CPU/4 = 1Mhz/4
		 */
		ADCSRA = (1<<ADEN) |  (1<<ADPS1);
		break;

	case 3 :
		/*ADPS2:0 = 011 to choose ADC_Clock = F_CPU/8 = 1Mhz/8
		 */
		ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0);
		break;

	case 4 :
		/*ADPS2:0 = 100 to choose ADC_Clock = F_CPU/16 = 1Mhz/16
		 */
		ADCSRA = (1<<ADEN) | (1<<ADPS2);
		break;

	case 5 :
		/*ADPS2:0 = 101 to choose ADC_Clock = F_CPU/32 = 1Mhz/32
		 */
		ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS0);
		break;

	case 6 :
		/*ADPS2:0 = 110 to choose ADC_Clock = F_CPU/64 = 1Mhz/64
		 */
		ADCSRA = (1<<ADEN) | (1<<ADPS2)| (1<<ADPS1);
		break;
	case 7 :
		/*ADPS2:0 = 111 to choose ADC_Clock = F_CPU/128 = 1Mhz/128
		 */
		ADCSRA = (1<<ADEN) | (1<<ADPS2)| (1<<ADPS1) | (1<<ADPS0);
		break;

	default : break;
	}
}

uint16 ADC_readChannel(uint8 channel_num)
{
	channel_num &= 0x07; /* Input channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX = ADMUX | channel_num; /* Choose the correct channel by setting the channel number in MUX4:0 bits */
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* Wait for conversion to complete, ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF); /* Clear ADIF by write '1' to it :) */
	return ADC; /* Read the digital value from the data register */
}
