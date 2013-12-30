/*
 * Magneto.h
 *
 * Created: 2013-01-23 00:57:56
 *  Author: rexina
 */ 


#ifndef MAGNETO_H_
#define MAGNETO_H_

#define MagnetoAddress 0x1E //0011110b, I2C 7bit address of HMC5883

void Magneto_Initialize(); //initialize sensor

void MagnetoBeginRead(); //begin read/convert data

void MagnetoReadData(int dataOut[3]); //returns data. 0 - X, 1-Y, 2-Z

#endif /* MAGNETO_H_ */