/*
 * Thermistor.cpp
 *
 * Created: 2013-12-30 00:54:44
 *  Author: rexina
 */ 
#include "MicroSat.h"

 void Thermistor_::init()
 {
	 this->Avg = 0;
	 this->SamplesCounter = 0;
	 this->NewData = false;
 }
 
 void Thermistor_::new_measurement(uint16_t val)
 {
	 this->Avg += val;
	 ++this->SamplesCounter;
	 
	 if( this->SamplesCounter > this->AVG_SAMPLES )
	 {
		 this->NewData = true;
		 //[todo] = turn off ADC
	 }
 }
 
 void Thermistor_::end()
 {
	 //[todo] - write data to SD
 }
 
 
 Thermistor_ Thermistor;