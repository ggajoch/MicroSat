/*
 * ISRs.cpp
 *
 * Created: 2013-12-30 03:11:37
 *  Author: rexina
 */ 

#include "MicroSat.h"

ISR(TIMER0_OVF_vect)
{
	MainInterrupt = true;
}


volatile uint8_t count = 0;
ISR(TIMER2_OVF_vect)
{
	MainInterrupt = true;
	++count;
	if( count >= 8 )
	{
		++TimeTick;
	}
}

