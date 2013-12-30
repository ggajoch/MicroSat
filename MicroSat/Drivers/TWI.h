/*
 * TWI.h
 *
 * Created: 2013-01-21 10:17:54
 *  Author: rexina
 */ 


#ifndef TWI_H_
#define TWI_H_

#ifdef __cplusplus
extern "C" {
#endif
#include <util/twi.h>
#include <avr/io.h>

uint8_t TWI_Init(uint32_t TWI_Bitrate); //initialize TWI line. do it BEFORE every operation on TWI.
//1 if succes, 0 if fault

uint8_t TWI_Start(uint8_t address, uint8_t TWI_Type); //start stransmission to adress, TWI_Type == TWI_WRITE || TWI_READ
//1 if succes, 0 if fault

void TWI_Stop (); //stop TWI controller

uint8_t TWI_Write(uint8_t toSend); //write byte to line
//1 if succes, 0 if fault

uint8_t TWI_ReadAck(); //i want more data, data, data!
//return readed data

uint8_t TWI_ReadNack(); //stop reading data
//return readed data

#ifdef __cplusplus
};
#endif
#endif /* TWI_H_ */