/*
 * MicroSat.cpp
 *
 * Created: 2013-12-28 01:26:11
 *  Author: rexina
 */ 


#include "MicroSat.h"



int main(void)
{
	_delay_ms(10);
	SD.init();
	Timer2A.begin(Presc64); // 512 Hz TimeStamp
	Timer0.begin(Presc1);
    while(1)
    {
        //TODO:: Please write your application code - Ta.
		if ( MainInterrupt )
		{
			while ( TimeTick-- )
				SD.tick();
				
			if ( false ) // [todo] -timer do zliczania
			{
				Thermistor.init();
			}
			if ( Thermistor.NewData )
			{
				Thermistor.end();
			}
		}
    }
}