/*
 * MicroSat.h
 *
 * Created: 2013-12-30 03:17:06
 *  Author: rexina
 */ 


#ifndef MICROSAT_H_
#define MICROSAT_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include "SD.h"
#include "Timer.h"
#include "Thermistor.h"

#define sbi(port, pin) port |= (1 << pin)

extern volatile bool Interrupt;
extern volatile uint8_t TimeTick;
extern volatile bool ThermistorRequest;

#endif /* MICROSAT_H_ */