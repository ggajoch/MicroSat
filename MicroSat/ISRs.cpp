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
	++TimeTick;
	if( count == 64 )
	{
		ThermistorRequest = true;
		count = 0;
	}
}


ISR(ADC_vect)
{
	Thermistor.disable();
	Interrupt = true;
	Thermistor.new_measurement(ADC);
}