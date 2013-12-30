/*
 * adxl345.cpp
 *
 * Created: 2013-01-22 22:48:09
 *  Author: rexina
 */

#include "Accel.h"
extern "C" {
	#include "TWI.h"
};


void ADXL345_Initialize()
{
		/*Wire.beginTransmission(ADXAddress);
		Wire.write(Register_2D);
		Wire.write(8);                //measuring enable
		Wire.endTransmission();     // stop transmitting*/
		TWI_Start(ADXAddress, TW_WRITE);
		TWI_Write(Register_2D);
		TWI_Write(8);
		TWI_Stop();
}

void ADXL345_SetResolution(ADXL345_Resolution resolution)
{
	uint8_t data = 0b01001100 | resolution;
	TWI_Start(ADXAddress, TW_WRITE);
	TWI_Write(0x31);// - config register
	TWI_Write(data);
	TWI_Stop();
}
unsigned int  ADXL345_X()
{
	TWI_Start(ADXAddress, TW_WRITE);
	TWI_Write(Register_X0);
	TWI_Write(Register_X1);
	TWI_Stop();
	TWI_Start(ADXAddress, TW_READ);
	int tmp1 = TWI_ReadAck();
	int tmp2 = TWI_ReadNack();
	
	TWI_Stop();
	return ((tmp2 << 8) | tmp1);
}


unsigned int  ADXL345_Y()
{
	TWI_Start(ADXAddress, TW_WRITE);
	TWI_Write(Register_Y0);
	TWI_Write(Register_Y1);
	TWI_Stop();
	TWI_Start(ADXAddress, TW_READ);
	int tmp1 = TWI_ReadAck();
	int tmp2 = TWI_ReadNack();
	
	TWI_Stop();
	return ((tmp2 << 8) | tmp1);
}
unsigned int  ADXL345_Z()
{
	TWI_Start(ADXAddress, TW_WRITE);
	TWI_Write(Register_Z0);
	TWI_Write(Register_Z1);
	TWI_Stop();
	TWI_Start(ADXAddress, TW_READ);
	
	int tmp1 = TWI_ReadAck();
	int tmp2 = TWI_ReadNack();
	
	TWI_Stop();
	return ((tmp2 << 8) | tmp1);
}