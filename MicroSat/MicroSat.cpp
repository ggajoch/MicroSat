/*
 * MicroSat.cpp
 *
 * Created: 2013-12-28 01:26:11
 *  Author: rexina
 */ 


#include "MicroSat.h"
#include "LED.h"


LED_ LED;

int main(void)
{
	_delay_ms(10);
	LED.init();
	LED.toogle();
	_delay_ms(100);
	LED.toogle();
	
	LED.blink(100000L, 30);
	/*SD.init();
	SD.tick();
	uint8_t x = 10;
	while(x--)
	{
		SD.write_data('M',(uint8_t)125);
	}
	SD.end_block();
	
	
	Timer2A.begin(Presc64); // 512 Hz TimeStamp
	Timer0.begin(Presc1);
	
	
    while(1)
    {
        //TODO:: Please write your application code - Ta.
		if ( Interrupt )
		{
			while ( TimeTick-- )
			{
				SD.tick();
			}
			if ( ThermistorRequest ) // [todo] -timer do zliczania
			{
				ThermistorRequest = false;
				Thermistor.init();
			}
			if ( Thermistor.NewData )
			{
				Thermistor.end();
				SD.end_block();
			}
		}
    }*/
	while(1){}
}