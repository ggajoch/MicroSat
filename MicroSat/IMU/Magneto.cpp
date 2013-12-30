/*
 * Magneto.cpp
 *
 * Created: 2013-01-23 00:57:24
 *  Author: rexina
 */ 

#include "Magneto.h"
extern "C" {
	#include "TWI.h"	
};



void Magneto_Initialize()
{
	/*Wire.beginTransmission(address); //open communication with HMC5883
	Wire.send(0x02); //select mode register
	Wire.send(0x00); //continuous measurement mode
	Wire.endTransmission();*/
	
	TWI_Start(MagnetoAddress, TW_WRITE);
	TWI_Write(0x02);
	TWI_Write(0x00);
	TWI_Stop();
}


void MagnetoBeginRead()
{
	TWI_Start(MagnetoAddress, TW_WRITE);
	TWI_Write(0x03);
	TWI_Stop();
}

void MagnetoReadData(int dataOut[3])
{
	TWI_Start(MagnetoAddress, TW_READ);
	dataOut[0] = TWI_ReadAck();
	dataOut[0] <<= 8;
	dataOut[0] |= TWI_ReadAck();
	dataOut[1] = TWI_ReadAck();
	dataOut[1] <<= 8;
	dataOut[1] |= TWI_ReadAck();
	dataOut[2] = TWI_ReadAck();
	dataOut[2] <<= 8;
	dataOut[2] |= TWI_ReadNack();
	TWI_Stop();
}