/*
 * EXT.h
 *
 * Created: 2012-12-29 02:37:02
 *  Author: rexina
 */ 


#ifndef EXT_H_
#define EXT_H_


enum WhenInterrupt
{
	lowLevel = 0,
	change = 1,
	falling = 2,
	rising = 3
};

void ExtInterrupt0begin(WhenInterrupt when)
{
	DDRD &= ~(1 << PD2);
	EICRA &= 0b11111100;
	EICRA |= when;
	EIMSK |= (1 << INT0); //enable interrupt
}

void ExtInterrupt1begin(WhenInterrupt when)
{
	DDRD &= ~(1 << PD3);
	EICRA &= 0b11110011;
	EICRA |= (when << 2);
	EIMSK |= (1 << INT1); //enable interrupt
}

void ExtInterrupt2begin(WhenInterrupt when)
{
	DDRB &= ~(1 << PB2);
	EICRA &= 0b11001111;
	EICRA |= (when << 4);
	EIMSK |= (1 << INT2); //enable interrupt
}

#endif /* EXT_H_ */