/*
 * LED.h
 *
 * Created: 2013-12-31 01:05:39
 *  Author: rexina
 */ 


#ifndef LED_H_
#define LED_H_

#include "MicroSat.h"

class LED_
{
	public:
	bool state;
	#define LED_DDR DDRC
	#define LED_PORT PORTC
	#define LED_PIN PC2
	void init()
	{
		LED_DDR |= (1 << LED_PIN);
		this->state = false;
		setState(false);
	}
	void setState(bool state)
	{
		if( state )
		{
			sbi(PORTC, PC2);
		}
		else
		{
			cbi(PORTC, PC2);
		}
	}
	void toogle()
	{
		state = !state;
		this->setState(this->state);
	}
	void blink(uint16_t times, uint16_t delay_ms)
	{
		while(times--)
		{
			this->toogle();
			_delay_ms(delay_ms);
			this->toogle();
			_delay_ms(delay_ms);
		}
	}
};

extern LED_ LED;



#endif /* LED_H_ */