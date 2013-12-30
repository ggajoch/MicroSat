/*
 * Timer.h
 *
 * Created: 2012-12-29 02:26:44
 *  Author: rexina
 */ 


#ifndef TIMER_H_
#define TIMER_H_


#include "MicroSat.h"

#define sbi(port, pin) port |= (1 << pin);
#define cbi(port, pin) port &= ~(1 << pin);

enum ClockPresc
{
	NOCLOCK = 0,
	Presc1 = 1,
	Presc8 = 0b10,
	Presc64 = 0b11,
	Presc256 = 0b100,
	Presc1024 = 0b101,
	T0Falling = 0b110,
	T0Rising = 0b111
};

struct Timer0_
{

	void begin(ClockPresc prescaler)
	{
		TCCR0B |= prescaler;
		sbi(TIMSK0, TOIE0);
		sei();
	}
	void end()
	{
		TCCR0B = NOCLOCK;
		cbi(TIMSK0, TOIE0);
	}
};
extern Timer0_ Timer0;
#define Timer0Int()  ISR(TIMER0_OVF_vect)


struct Timer1_
{

	void begin(ClockPresc prescaler)
	{
		TCCR1A = 0;
		TCCR1B = 0;
		TCCR1B |= prescaler;
		sbi(TIMSK1, TOIE1);
		sei();
	}
	void end()
	{
		TCCR1B = 0;
		cbi(TIMSK1, TOIE1);
	}
};
extern Timer1_ Timer1;

struct Timer2A_
{

	void begin(ClockPresc prescaler)
	{
		 TIMSK2 &= ~ _BV(TOIE2);
		 TCCR2A = _BV(prescaler);
		 ASSR |= _BV(AS2);
		 TIMSK2 |= _BV(TOIE2);
		 sei();
	}
	void end()
	{
		TIMSK2 &=~_BV(TOIE2);// Wy³. przerwania TC2
		TCCR2A = 0;
		cbi(TIMSK2, TOIE2);
	}
};

extern Timer2A_ Timer2A;


#endif /* TIMER_H_ */