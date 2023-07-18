/*

    Camilletti Samuele - Progetto 2305

    Library for Two Wire Communication (I2C) for ATMega328P on 2-wire module

    Last update 18/07/2023
    - Adjusted TWBR according to CPU frequency: 16 Mhz -> TWBR = 72 -> 100KHz SCL Clock

*/

// Including standard avr gcc libraries
#include <avr/io.h>         // Define standard Input Output for AVR Architectures, refers to iom328p.h for ATMega328P

// Defining sbi & cbi macros: originally defined in 

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// Defining constants & macros

#define READ_BIT 1
#define WRITE_BIT 0

#define BIT_RATE 0x48 

#define ACK_SHIFT 1  // less significant bit for slave address

// Status code (in addition to util/twi.h)
#define TWI_OFF 0x0
#define TWI_READY 0x1
#define TWI_STARTED 0x2
#define TWI_SLAVE_ACK 0x3
#define TWI_DATA_ACK 0x4

#define PINSDA PINC4
#define PINSCL PINC5

#define PORTSDA PORT4
#define PORTSCL PORT5

#define BUFFER_LENGTH 32 // address + 31 bytes (smaller but slower write on analysis)

// Defining prototypes

void twBegin(); // Initilialise PORTC and I/O registers to communicate.

void twStart(uint8_t slave, uint8_t rw);

uint8_t twWrite(uint8_t msg); // Write a 8 bit message from TWDR to Slave + Receive ACK/NACK

void twClose(); // Read a 8 bit message from Slave + Send ACK/NACK


