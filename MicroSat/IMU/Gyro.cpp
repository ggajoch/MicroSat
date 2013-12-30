/*
 * Gyro.cpp
 *
 * Created: 2013-01-23 00:38:07
 *  Author: rexina
 */ 

#include "Gyro.h"
#include <math.h>
extern "C" {
	#include "TWI.h"
};
// Defines ////////////////////////////////////////////////////////////////

// The Arduino two-wire interface uses a 7-bit number for the address,
// and sets the last bit correctly based on reads and writes
#define GYR_ADDRESS (0xD2 >> 1)

// Public Methods //////////////////////////////////////////////////////////////

// Turns on the L3G4200D's gyro and places it in normal mode.
void Gyroscope::enableDefault(void)
{
	// 0x0F = 0b00001111
	// Normal power mode, all axes enabled
	writeReg(L3G4200D_CTRL_REG1, 0x0F);
}

// Writes a gyro register
void Gyroscope::writeReg(unsigned char reg, unsigned char value)
{
	/*Wire.beginTransmission(GYR_ADDRESS);
	Wire.send(reg);
	Wire.send(value);
	Wire.endTransmission();*/
	TWI_Start(GYR_ADDRESS, TW_WRITE);
	TWI_Write(reg);
	TWI_Write(value);
	TWI_Stop();
}

// Reads a gyro register
unsigned char Gyroscope::readReg(unsigned char reg)
{
	unsigned char value;
	
	/*Wire.beginTransmission(GYR_ADDRESS);
	Wire.send(reg);
	Wire.endTransmission();
	Wire.requestFrom(GYR_ADDRESS, 1);
	value = Wire.receive();
	Wire.endTransmission();*/
	TWI_Start(GYR_ADDRESS, TW_WRITE);
	TWI_Write(reg);
	TWI_Stop();
	TWI_Start(GYR_ADDRESS, TW_READ);
	value = TWI_ReadNack();
	TWI_Stop();
	return value;
}

// Reads the 3 gyro channels and stores them in vector g
void Gyroscope::read()
{
	//Wire.beginTransmission(GYR_ADDRESS);
	TWI_Start(GYR_ADDRESS, TW_WRITE);
	// assert the MSB of the address to get the gyro
	// to do slave-transmit subaddress updating.
	//Wire.send(L3G4200D_OUT_X_L | (1 << 7));
	TWI_Write(L3G4200D_OUT_X_L | (1 << 7));
	TWI_Stop();
	//Wire.endTransmission();
	//Wire.requestFrom(GYR_ADDRESS, 6);
	TWI_Start(GYR_ADDRESS, TW_READ);

	//while (Wire.available() < 6);
	
	unsigned char xla = TWI_ReadAck(); //Wire.receive();
	unsigned char xha = TWI_ReadAck(); //Wire.receive();
	unsigned char yla = TWI_ReadAck(); //Wire.receive();
	unsigned char yha = TWI_ReadAck(); //Wire.receive();
	unsigned char zla = TWI_ReadAck(); //Wire.receive();
	unsigned char zha = TWI_ReadNack(); //Wire.receive();

	TWI_Stop();
	
	g.x = xha << 8 | xla;
	g.y = yha << 8 | yla;
	g.z = zha << 8 | zla;
}

void Gyroscope::vector_cross(const vector *a,const vector *b, vector *out)
{
	out->x = a->y*b->z - a->z*b->y;
	out->y = a->z*b->x - a->x*b->z;
	out->z = a->x*b->y - a->y*b->x;
}

float Gyroscope::vector_dot(const vector *a,const vector *b)
{
	return a->x*b->x+a->y*b->y+a->z*b->z;
}

void Gyroscope::vector_normalize(vector *a)
{
	float mag = sqrt(vector_dot(a,a));
	a->x /= mag;
	a->y /= mag;
	a->z /= mag;
}

