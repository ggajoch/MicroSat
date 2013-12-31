/*
 * Thermistor.cpp
 *
 * Created: 2013-12-30 00:54:44
 *  Author: rexina
 */ 
#include "MicroSat.h"





 void Thermistor_::init()
 {
	 DDR_THERM &= ~_BV(PIN_THERM);
	 DDR_THERM_ON |= (1 << PIN_THERM_ON);
	 
	 this->Avg = 0;
	 this->SamplesCounter = 0;
	 this->NewData = false;
	 
	 ADMUX = (1 << REFS1) | (1 << REFS0) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0);
	 ADCSRA &= ~(1 << ADEN);
	 ADCSRA |= (1 << ADIE);
	 
	 Timer1.begin(Presc1); //~168Hz
 }
 
 
 void Thermistor_::new_measurement(uint16_t val)
 {
	 this->Avg += val;
	 ++this->SamplesCounter;
	 
	 if( this->SamplesCounter > this->AVG_SAMPLES )
	 {
		 ADCSRA &= ~(1 << ADEN);
		 this->NewData = true;
	 }
 }
 
 void Thermistor_::end()
 {
	 //[todo] - write data to SD
	 SD.write_data('A',this->Avg);
 }
 
 
 Thermistor_ Thermistor;
 