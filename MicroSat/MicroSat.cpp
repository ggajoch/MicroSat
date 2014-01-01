/*
 * MicroSat.cpp
 *
 * Created: 2013-12-28 01:26:11
 *  Author: rexina
 */ 


#include "MicroSat.h"
#include "LED.h"
#include "Accel.h"


LED_ LED;

int main(void)
{
	/*sbi(DDRD, PD5);
	uint16_t buzz = 500;
	int8_t db = 1;
	while(true)
	{
		uint8_t x = 10;
		while(x--)
		{
			sbi(PORTD, PD5);
		
			Delay_us(buzz);
		
			cbi(PORTD, PD5);
		
			Delay_us(buzz);
		}
		buzz += db;
		if( buzz >= 500 ) db = -1;
		if( buzz <= 10 ) db = 1;
		_delay_ms(1);
	}*/
	_delay_ms(10);
	LED.init();
	TimeTick = 0;
	
	LED.toogle();
	_delay_ms(100);
	LED.toogle();
	
	SD.init();
	SD.tick();
	uint8_t x = 3;
	WORD written;
	while(x--)
	{
		sprintf(buffer,"MEST%d\n",x);
		SD.write_buffer();
	}
	
	//SD.end_block();
	
	
	LED.blink(5,30);
		
	Thermistor.main_init();
	Timer2A.begin(Presc1); // 128 Hz TimeStamp
	Timer0.begin(Presc1);
	
	TimeTick = 0;
	sei();
	
    while(1)
    {
        //TODO:: Please write your application code - Ta.
		if ( Interrupt )
		{
			Interrupt = false;
			while ( TimeTick > 0 )
			{
				SD.tick();
				--TimeTick;
			}
			if ( ThermistorRequest ) // [todo] -timer do zliczania
			{
				ThermistorRequest = false;
				Thermistor.init();
			}
			if ( Thermistor.NewData )
			{
				Thermistor.end();
				//SD.end_block();	
				LED.blink(2,30);
			}
		}
    }
}