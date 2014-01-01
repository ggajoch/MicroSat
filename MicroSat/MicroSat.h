/*
 * MicroSat.h
 *
 * Created: 2013-12-30 03:17:06
 *  Author: rexina
 */ 


#ifndef MICROSAT_H_
#define MICROSAT_H_

#include <avr/io.h>
//#define __DELAY_BACKWARD_COMPATIBLE__ 
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <string.h>
#define sbi(port, pin) port |= (1 << pin)
#define cbi(port, pin) port &= ~(1 << pin)

extern volatile bool Interrupt;
extern volatile uint8_t TimeTick;
extern volatile bool ThermistorRequest;
extern char buffer[200];

static inline void Delay_ms(uint16_t x)
{
	while(x--) _delay_ms(1);
}
static inline void Delay_us(uint16_t x)
{
	while(x--) _delay_us(1);
}

#include "TWI.h"
#include "SD.h"

#include "Timer.h"
#include "Thermistor.h"
#include "LED.h"




#endif /* MICROSAT_H_ */