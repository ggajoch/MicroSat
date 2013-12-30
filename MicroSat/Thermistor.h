/*
 * Thermistor.h
 *
 * Created: 2013-12-30 00:54:57
 *  Author: rexina
 */ 


#ifndef THERMISTOR_H_
#define THERMISTOR_H_



class Thermistor_
{
	private:
		volatile uint32_t Avg;
		static const uint8_t AVG_SAMPLES = 10;
		volatile uint8_t SamplesCounter;
	public:
		volatile uint8_t NewData;
		void init();
		void new_measurement(uint16_t val);
		void end();
};

extern Thermistor_ Thermistor;

#endif /* THERMISTOR_H_ */