/*
 * MicroSat.h
 *
 * Created: 2013-12-30 03:17:06
 *  Author: rexina
 */ 


#ifndef MICROSAT_H_
#define MICROSAT_H_


#define sbi(port, pin) port |= (1 << pin);
#define cbi(port, pin) port &= ~(1 << pin);


#endif /* MICROSAT_H_ */