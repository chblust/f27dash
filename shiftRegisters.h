/*
 * shiftRegisters.h
 *
 * Created: 1/9/2019 6:20:42 PM
 *  Author: chb4299
 */ 


#ifndef SHIFT_REGISTERS_H_
#define SHIFT_REGISTERS_H_

// SR clock line - tells SRs when to shift data from the SIN line into the register
#define CLOCK  PA0

// SR data input line - the value on this line is shifted into the register on a rising edge of CLOCK
#define SIN    PA1

// SR "STROBE" line - tells the SR to set its outputs to the data within the internal register
#define STROBE PA2

// Delay in milliseconds between setting SR control pins (See shiftData function)
#define SHIFT_DELAY .001

// Total number of bits between all the shift registers on the dash
#define SR_NUM_BITS 64

void shiftData( unsigned char data );

void shiftPattern( unsigned char * pattern );

#endif /* SHIFT_REGISTERS_H_ */