/*

    Camilletti Samuele - Progetto 2305

    Library for Two Wire Communication (I2C) for ATMega328P on 2-wire module

*/

// Including standard avr gcc standard libraries
#include <avr/interrupt.h>         // Define standard interrupts vector for AVR Architectures
#include <util/twi.h>
#include "TWireMega.h"

// Defining global variables as volatiles
static volatile uint8_t twiStatus = TWI_OFF;

static volatile uint8_t arrayBuffer [ BUFFER_LENGTH ]; // array of 8 bit integer

static volatile uint8_t bufferSize; // size to array of integer

static volatile uint8_t bufferIndex; // size to array of integer

/*

  twBegin FUNCTION
  Description: 
  Initilialise PORTC and I/O registers to communicate.
  Set status to TWI_READY

*/
void twBegin() 
 {

  twiStatus = TWI_READY;

  sbi(SREG, 7); // enable global interrupt

  // Set port as high
  sbi(PORTC, PORTSDA);
  sbi(PORTC, PORTSCL);

  TWDR = 0xFF;  // release

  TWBR = BIT_RATE; // As defined in docs (http://ww1.microchip.com/downloads/en/appnotes/00002480a.pdf 1.2.2)

  // set prescaler to 0
  cbi(TWSR, TWPS1);
  cbi(TWSR, TWPS0);
  
  TWCR = (0 << TWINT) |      
            (0 << TWEA) |
            (0 << TWSTA) |
            (0 << TWSTO) |
            (0 << TWWC) |
            (1 << TWEN) |      // Enable TWI Module as I2C
            (0 << TWIE);

 }


/*

  twStart FUNCTION
  Description: 
  Send START signal then leave then clears interrupt flag
  Set slaveaddress and buffer array pointer
  Set status to TWI_START_SENT

  Parameters:
  uint8_t slaveaddress: slave address
  uint8_t rw: read/write bit

*/
void twStart(uint8_t slave, uint8_t rw) 
 {

  if(twiStatus == TWI_OFF) twBegin();

  while(twiStatus != TWI_READY); // check busy

  // set or clear LSB depending on Write or Read bit (0 = Write, 1 = Read)
  if(rw == WRITE_BIT) arrayBuffer[0] = (slave << ACK_SHIFT);
  else arrayBuffer[0] = 0x01 | (slave << ACK_SHIFT);

  bufferSize = 0;
  bufferIndex = 0;

  twiStatus = TWI_STARTED;

 }


/*

  twWrite FUNCTION
  Description: 
  Set 8 bit integer to TWDR then clears interrupt flag
  Set status to TWI_WAITING_MESSAGE_ACK

  Parameters:
  uint8_t msg: 8 bit integer

  Return value:
  0: Everything's ok
  1: If error is caught or buffer size limit

*/
uint8_t twWrite(uint8_t msg) 
 {

  // check if ready
  if(twiStatus == TWI_STARTED && bufferSize < BUFFER_LENGTH - 1) 
   {

    arrayBuffer[++bufferSize] = msg;

    return 0;
    
   }
   else return 1;
   
 }


/*

    twClose FUNCTION
    Description: 
    Send STOP condition

*/
void twClose() 
 {

  if(twiStatus == TWI_STARTED)
   {

    // Set START condition bit on TWCR as defined on docs
    TWCR = (1 << TWINT) |      
            (1 << TWSTA) |
            (1 << TWEN) |      // Enable TWI Module as I2C
            (1 << TWIE);

   }

 }


/* 

TWI_vector routine

depending of the state of TWI Module do the routine as described:
-

*/
ISR(TWI_vect) 
 {
  switch(TW_STATUS) 
   {
    case TW_REP_START:
    case TW_START:
    case TW_MT_SLA_ACK:
    case TW_MT_DATA_ACK:

     twiStatus = TWI_DATA_ACK;

     if(bufferIndex <= bufferSize) 
      {
       TWDR = arrayBuffer[bufferIndex++]; // Set 8 bit in the TWDR reg

       TWCR = (1 << TWINT) | // Set interrupt bit   
                (0 << TWSTA) |  // Start condition
                (1 << TWIE) | // Interrupt enable
                (1 << TWEN);
      }
     else 
      {

       TWCR = (1 << TWINT) |      
                (0 << TWEA) |
                (0 << TWSTA) |
                (1 << TWSTO) |    // Transmitting stop condition
                (0 << TWWC) |
                (1 << TWEN) |      // Enable TWI Module as I2C
                (0 << TWIE);    // Disable interrupts

       twiStatus = TWI_READY; 
      }

    break;

    case TW_MR_SLA_NACK:

    case TW_MR_DATA_NACK:

     TWCR = (1 << TWINT) |      
            (0 << TWEA) |
            (0 << TWSTA) |
            (1 << TWSTO) |    // Transmitting stop condition
            (0 << TWWC) |
            (1 << TWEN) |      // Enable TWI Module as I2C
            (0 << TWIE);    // Disable interrupts

     twiStatus = TWI_READY; 

    break;



   }
 }