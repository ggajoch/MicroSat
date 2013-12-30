/*
 * BMP085.cpp
 *
 * Created: 2013-01-21 10:32:36
 *  Author: rexina
 */ 

#include "Press.h"

extern "C" {
	#include "TWI.h"
};

#define BMP085_ADDRESS 0x77

const unsigned char OSS = 3;  // Oversampling Setting

// Calibration values
int BMP_ac1;
int BMP_ac2;
int BMP_ac3;
unsigned int BMP_ac4;
unsigned int BMP_ac5;
unsigned int BMP_ac6;
int BMP_b1;
int BMP_b2;
int BMP_mb;
int BMP_mc;
int BMP_md;

// BMP_b5 is calculated in bmp085GetTemperature(...), this variable is also used in bmp085GetPressure(...)
// so ...Temperature(...) must be called before ...Pressure(...).
long BMP_b5;

/*void setup()
{
	Serial.begin(9600);
	Wire.begin();
	bmp085Calibration();
}*/

/*void loop()
{
	temperature = bmp085GetTemperature(bmp085ReadUT());
	pressure = bmp085GetPressure(bmp085ReadUP());
	Serial.print("Temperature: ");
	Serial.print(temperature, DEC);
	Serial.println(" *0.1 deg C");
	Serial.print("Pressure: ");
	Serial.print(pressure, DEC);
	Serial.println(" Pa");
	Serial.println();
	_delay_ms(1000);
}*/

// Stores all of the bmp085's calibration values into global variables
// Calibration values are required to calculate temp and pressure
// This function should be called at the beginning of the program
void bmp085Calibration()
{
	BMP_ac1 = bmp085ReadInt(0xAA);
	BMP_ac2 = bmp085ReadInt(0xAC);
	BMP_ac3 = bmp085ReadInt(0xAE);
	BMP_ac4 = bmp085ReadInt(0xB0);
	BMP_ac5 = bmp085ReadInt(0xB2);
	BMP_ac6 = bmp085ReadInt(0xB4);
	BMP_b1 = bmp085ReadInt(0xB6);
	BMP_b2 = bmp085ReadInt(0xB8);
	BMP_mb = bmp085ReadInt(0xBA);
	BMP_mc = bmp085ReadInt(0xBC);
	BMP_md = bmp085ReadInt(0xBE);
}

// Calculate temperature given ut.
// Value returned will be in units of 0.1 deg C
short bmp085GetTemperature(unsigned int ut)
{
	long x1, x2;
	
	x1 = (((long)ut - (long)BMP_ac6)*(long)BMP_ac5) >> 15;
	x2 = ((long)BMP_mc << 11)/(x1 + BMP_md);
	BMP_b5 = x1 + x2;

	return ((BMP_b5 + 8)>>4);
}
short bmp085ReadTemperature()
{
	return	bmp085GetTemperature(bmp085ReadUT());
}
long bmp085ReadPressure()
{
	return 	bmp085GetPressure(bmp085ReadUP());
}

// Calculate pressure given up
// calibration values must be known
// BMP_b5 is also required so bmp085GetTemperature(...) must be called first.
// Value returned will be pressure in units of Pa.
long bmp085GetPressure(unsigned long up)
{
	long x1, x2, x3, b3, b6, p;
	unsigned long b4, b7;
	
	b6 = BMP_b5 - 4000;
	// Calculate B3
	x1 = (BMP_b2 * (b6 * b6)>>12)>>11;
	x2 = (BMP_ac2 * b6)>>11;
	x3 = x1 + x2;
	b3 = (((((long)BMP_ac1)*4 + x3)<<OSS) + 2)>>2;
	
	// Calculate B4
	x1 = (BMP_ac3 * b6)>>13;
	x2 = (BMP_b1 * ((b6 * b6)>>12))>>16;
	x3 = ((x1 + x2) + 2)>>2;
	b4 = (BMP_ac4 * (unsigned long)(x3 + 32768))>>15;
	
	b7 = ((unsigned long)(up - b3) * (50000>>OSS));
	if (b7 < 0x80000000)
	p = (b7<<1)/b4;
	else
	p = (b7/b4)<<1;
	
	x1 = (p>>8) * (p>>8);
	x1 = (x1 * 3038)>>16;
	x2 = (-7357 * p)>>16;
	p += (x1 + x2 + 3791)>>4;
	
	return p;
}

// Read 1 byte from the BMP085 at 'address'
char bmp085Read(unsigned char address)
{
	/*Wire.beginTransmission(BMP085_ADDRESS);
	Wire.send(address);
	Wire.endTransmission();*/
	TWI_Start(BMP085_ADDRESS, TW_WRITE);
	TWI_Write(address);
	TWI_Stop();
	
	//Wire.requestFrom(BMP085_ADDRESS, 1);
	//while(!Wire.available());
	TWI_Start(BMP085_ADDRESS, TW_READ);
	uint8_t Readed = TWI_ReadNack();
	TWI_Stop();
	return Readed;
}

// Read 2 bytes from the BMP085
// First byte will be from 'address'
// Second byte will be from 'address'+1
int bmp085ReadInt(unsigned char address)
{
	unsigned char msb, lsb;
	
	/*Wire.beginTransmission(BMP085_ADDRESS);
	Wire.send(address);
	Wire.endTransmission();*/
	
	TWI_Start(BMP085_ADDRESS, TW_WRITE);
	TWI_Write(address);
	TWI_Stop();
	
	
	//Wire.requestFrom(BMP085_ADDRESS, 2);
	//while(Wire.available()<2);
	/*TWI_Start(BMP085_ADDRESS, TW_WRITE);
	TWI_Write(address);
	TWI_Stop();*/
	
	
	TWI_Start(BMP085_ADDRESS, TW_READ);
	msb = TWI_ReadAck();//Wire.receive();
	lsb = TWI_ReadNack(); //receive();
	TWI_Stop();
	
	return (int) msb<<8 | lsb;
}

// Read the uncompensated temperature value
unsigned int bmp085ReadUT()
{
	unsigned int ut;
	
	// Write 0x2E into Register 0xF4
	// This requests a temperature reading
	/*Wire.beginTransmission(BMP085_ADDRESS);
	Wire.send(0xF4);
	Wire.send(0x2E);
	Wire.endTransmission();*/
	TWI_Start(BMP085_ADDRESS, TW_WRITE);
	TWI_Write(0xF4);
	TWI_Write(0x2E);
	TWI_Stop();
	
	// Wait at least 4.5ms
	_delay_ms(5);
	
	// Read two bytes from registers 0xF6 and 0xF7
	ut = bmp085ReadInt(0xF6);
	return ut;
}

// Read the uncompensated pressure value
unsigned long bmp085ReadUP()
{
	unsigned char msb, lsb, xlsb;
	unsigned long up = 0;
	
	// Write 0x34+(OSS<<6) into register 0xF4
	// Request a pressure reading w/ oversampling setting
	//Wire.beginTransmission(BMP085_ADDRESS);
	//Wire.send(0xF4);
	//Wire.send(0x34 + (OSS<<6));
	//Wire.endTransmission();
	TWI_Start(BMP085_ADDRESS, TW_WRITE);
	TWI_Write(0xF4);
	TWI_Write(0x34 + (OSS<<6));
	TWI_Stop();
	
	// Wait for conversion, delay time dependent on OSS
	_delay_ms(2 + (3<<OSS));
	
	// Read register 0xF6 (MSB), 0xF7 (LSB), and 0xF8 (XLSB)
	//Wire.beginTransmission(BMP085_ADDRESS);
	//Wire.send(0xF6);
	//Wire.endTransmission();
	
	TWI_Start(BMP085_ADDRESS, TW_WRITE);
	TWI_Write(0xF6);
	TWI_Stop();
	
	
	//Wire.requestFrom(BMP085_ADDRESS, 3);
	// Wait for data to become available
	//while(Wire.available() < 3);
	TWI_Start(BMP085_ADDRESS, TW_READ);
	
	
	msb = TWI_ReadAck();//Wire.receive();
	lsb = TWI_ReadAck(); //.receive();
	xlsb = TWI_ReadNack(); //Wire.receive();
	
	up = (((unsigned long) msb << 16) | ((unsigned long) lsb << 8) | (unsigned long) xlsb) >> (8-OSS);
	
	return up;
}




void bmp085StartMeasurePressure()
{
	
	
	// Write 0x34+(OSS<<6) into register 0xF4
	// Request a pressure reading w/ oversampling setting
	//Wire.beginTransmission(BMP085_ADDRESS);
	//Wire.send(0xF4);
	//Wire.send(0x34 + (OSS<<6));
	//Wire.endTransmission();
	TWI_Start(BMP085_ADDRESS, TW_WRITE);
	TWI_Write(0xF4);
	TWI_Write(0x34 + (OSS<<6));
	TWI_Stop();
	
	// Wait for conversion, delay time dependent on OSS
}

long bmp085ReadMeasuredPressure()	
{
	unsigned char msb, lsb, xlsb;
	unsigned long up = 0;
	//_delay_ms(2 + (3<<OSS));
	
	// Read register 0xF6 (MSB), 0xF7 (LSB), and 0xF8 (XLSB)
	//Wire.beginTransmission(BMP085_ADDRESS);
	//Wire.send(0xF6);
	//Wire.endTransmission();
	
	TWI_Start(BMP085_ADDRESS, TW_WRITE);
	TWI_Write(0xF6);
	TWI_Stop();
	
	
	//Wire.requestFrom(BMP085_ADDRESS, 3);
	// Wait for data to become available
	//while(Wire.available() < 3);
	TWI_Start(BMP085_ADDRESS, TW_READ);
	
	
	msb = TWI_ReadAck();//Wire.receive();
	lsb = TWI_ReadAck(); //.receive();
	xlsb = TWI_ReadNack(); //Wire.receive();
	
	up = (((unsigned long) msb << 16) | ((unsigned long) lsb << 8) | (unsigned long) xlsb) >> (8-OSS);
	
	
	long x1, x2, x3, b3, b6, p;
	unsigned long b4, b7;
	
	b6 = BMP_b5 - 4000;
	// Calculate B3
	x1 = (BMP_b2 * (b6 * b6)>>12)>>11;
	x2 = (BMP_ac2 * b6)>>11;
	x3 = x1 + x2;
	b3 = (((((long)BMP_ac1)*4 + x3)<<OSS) + 2)>>2;
	
	// Calculate B4
	x1 = (BMP_ac3 * b6)>>13;
	x2 = (BMP_b1 * ((b6 * b6)>>12))>>16;
	x3 = ((x1 + x2) + 2)>>2;
	b4 = (BMP_ac4 * (unsigned long)(x3 + 32768))>>15;
	
	b7 = ((unsigned long)(up - b3) * (50000>>OSS));
	if (b7 < 0x80000000)
	p = (b7<<1)/b4;
	else
	p = (b7/b4)<<1;
	
	x1 = (p>>8) * (p>>8);
	x1 = (x1 * 3038)>>16;
	x2 = (-7357 * p)>>16;
	p += (x1 + x2 + 3791)>>4;
	
	return p;
}


void bmp085StartMeasureTemperature()
{
	TWI_Start(BMP085_ADDRESS, TW_WRITE);
	TWI_Write(0xF4);
	TWI_Write(0x2E);
	TWI_Stop();	
}

long bmp085ReadMeasuredTemperature()
{	
	// Read two bytes from registers 0xF6 and 0xF7
	long ut = bmp085ReadInt(0xF6);
	
	long x1, x2;
	
	x1 = (((long)ut - (long)BMP_ac6)*(long)BMP_ac5) >> 15;
	x2 = ((long)BMP_mc << 11)/(x1 + BMP_md);
	BMP_b5 = x1 + x2;

	return ((BMP_b5 + 8)>>4);
}