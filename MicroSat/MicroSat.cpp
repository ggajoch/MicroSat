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
bool accelHasNewData;

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
	SD.log("print mest.");
	while(x--)
	{
		sprintf(buffer,"MEST%d\n",x);
		SD.write_buffer();
	}
	
	//SD.end_block();
	
	SD.log("doing twi init.");
	TWI_Init(400000L);
	
	SD.log("twi ok.");
	
	Thermistor.main_init();
	
	SD.log("termistor ok.");
	
	ADXL345_Initialize();
	SD.log("imu ok.");
	ADXL345_SetResolution(res_8g);
	SD.log("imu setr.");
	Timer2A.begin(Presc1); // 128 Hz TimeStamp
	Timer0.begin(Presc1);
	
	LED.blink(10,50);
	
	TimeTick = 0;
	int32_t globalTime = 0;
	SD.log("before sei.");
	sei();
	SD.log("main loop.");
    while(1)
    {
        //TODO:: Please write your application code - Ta.
		if ( Interrupt )
		{
			globalTime ++;
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
			if(globalTime % 2 == 0)
				accelHasNewData = true;
			if(accelHasNewData) {
				unsigned int x = ADXL345_X();
				unsigned int y = ADXL345_Y();
				unsigned int z = ADXL345_Z();
				sprintf(buffer,"XYZ%ud,%ud,%ud\n",x,y,z);
				SD.write_buffer();
				accelHasNewData = false;
			}
		}
    }
}