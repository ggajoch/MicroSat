/*
 * Globals.cpp
 *
 * Created: 2013-12-30 04:00:24
 *  Author: rexina
 */ 

#include "MicroSat.h"

volatile bool Interrupt = 0;
volatile uint8_t TimeTick = 0;
volatile bool ThermistorRequest = 0;

char buffer[200];