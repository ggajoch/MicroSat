/*
 * MicroSat.cpp
 *
 * Created: 2013-12-28 01:26:11
 *  Author: rexina
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include "SD.h"
#include "Timer.h"
#include "MicroSat.h"


ISR(USART1_RX_vect)
{
	uint8_t a = 0;
}

int main(void)
{
	_delay_ms(10);
	SD.init();
	Timer2A.begin(Presc64); // 512 Hz TimeStamp
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}