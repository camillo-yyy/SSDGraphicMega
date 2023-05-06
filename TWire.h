/* 

STANDARD LIBRARIES

*/

#include <avr/io.h>
#include <util/delay.h>

/* DEFINING CONSTANTS */

// PORT
#define PORT PORTB
#define PIN PINB
#define SDA_PIN PINB0
#define SCL_PIN PINB2
#define SDA_PORT PORTB0
#define SCL_PORT PORTB2

// functions prototype

bool tw_begin();

bool begin_transmission(__UINT8_C slaveaddress);

bool writeMsg(__UINT8_C msg);

bool do_transmission();

bool send_Master_to_Slave(__UINT8_C reg);

bool end_transmission();

__UINT8_C state; // Internal state of connections

bool multiflag; // If 1 disable state for single Master to Slave




