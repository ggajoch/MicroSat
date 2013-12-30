/*
 * adxl345.h
 *
 * Created: 2013-01-22 22:47:58
 *  Author: rexina
 */ 


#ifndef ADXL345_H_
#define ADXL345_H_



#define Register_ID 0
#define Register_2D 0x2D
#define Register_X0 0x32
#define Register_X1 0x33
#define Register_Y0 0x34
#define Register_Y1 0x35
#define Register_Z0 0x36
#define Register_Z1 0x37

#define ADXAddress  83//0xA7 >> 1;  // the default 7-bit slave address

enum ADXL345_Resolution
{
	res_2g = 0,
	res_4g = 1,
	res_8g = 2,
	res_16g = 3
};

unsigned int  ADXL345_X();
unsigned int  ADXL345_Y();
unsigned int  ADXL345_Z();
void ADXL345_Initialize();
void ADXL345_SetResolution(ADXL345_Resolution resolution);



#endif /* ADXL345_H_ */