/*
 * Thermistor.h
 *
 * Created: 2013-12-30 00:54:57
 *  Author: rexina
 */ 


#ifndef THERMISTOR_H_
#define THERMISTOR_H_

#include "MicroSat.h"

#define DDR_THERM DDRA
#define PORT_THERM PORTA
#define PIN_THERM PA7

#define DDR_THERM_ON DDRC
#define PORT_THERM_ON PORTC
#define PIN_THERM_ON PC3


class Thermistor_
{
	private:
		volatile uint16_t Avg;
		static const uint8_t AVG_SAMPLES = 10;
		volatile uint8_t SamplesCounter;
	public:
		volatile uint8_t NewData;
		void init();
		void main_init();
		void new_measurement(uint16_t val);
		void end();
		
		void enableADC()
		{
			this->enable();
			ADCSRA |= (1 << ADEN);
			//sbi(ADCSRA, ADSC);
			ADCSRA |= (1 << ADSC);
		}
		void enable()
		{
			PORT_THERM_ON |= (1 << PIN_THERM_ON);
		}
		void disable()
		{
			PORT_THERM_ON &= ~(1 << PIN_THERM_ON);
		}
};

extern Thermistor_ Thermistor;

#endif /* THERMISTOR_H_ */