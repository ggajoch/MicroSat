/*
 * BMP085.h
 *
 * Created: 2013-01-21 10:14:58
 *  Author: rexina
 */ 


#ifndef BMP085_H_
#define BMP085_H_


#include <util/delay.h>

void bmp085Calibration();
short bmp085GetTemperature(unsigned int ut);
short bmp085ReadTemperature();
long bmp085ReadPressure();
long bmp085GetPressure(unsigned long up);
char bmp085Read(unsigned char address);
int bmp085ReadInt(unsigned char address);
unsigned int bmp085ReadUT();
unsigned long bmp085ReadUP();
void bmp085StartMeasurePressure();
long bmp085ReadMeasuredPressure();
void bmp085StartMeasureTemperature();
long bmp085ReadMeasuredTemperature();

#endif /* BMP085_H_ */