/*
 * ISRs.cpp
 *
 * Created: 2013-12-30 03:11:37
 *  Author: rexina
 */ 

#include "MicroSat.h"

ISR(TIMER0_OVF_vect)
{
	Interrupt = true;
}

ISR(TIMER1_OVF_vect)
{
	Thermistor.enableADC();
}


volatile uint16_t count = 0;
ISR(TIMER2_OVF_vect)
{
	Interrupt = true;
	++count;
	if( count % 8 == 0 )
	{
		++TimeTick;
	}
	if( count % 512 == 0 )
	{
		ThermistorRequest = true;
	}
	
	if( count == 513 ) count = 0;
}


ISR(ADC_vect)
{
	Thermistor.disable();
	Interrupt = true;
	uint16_t readed;
	readed = ADCH;
	readed <<= 8;
	readed |= ADCL;
	Thermistor.new_measurement(readed);
}