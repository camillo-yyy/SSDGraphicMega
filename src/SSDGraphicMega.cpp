/*

 Camilletti Samuele - Progetto 2305

 Library for Graphic Display on SSD1306 through I2C

*/

// Including standard avr gcc standard libraries
#include "SSDGraphicMega.h"
#include <avr/pgmspace.h>

// Defining global variables as volatiles
static volatile uint8_t status = DISPLAY_OFF;

/*

 beginDisplay FUNCTION
 Description: 
 Initilialise screen.

*/
void beginDisplay() 
 {

  uint8_t buffer;

  twStart(SSD1306, 0); // start connection
 
  for (uint8_t i = 0; i < STARTUP_LENGTH; i++) 
   {
    buffer = pgm_read_byte_near(&startup[i]); // startup seq
		twWrite(buffer);
	 }

  twClose(); // close

  status=DISPLAY_ON; // change status

 }

/*

 setPointer FUNCTION
 Description: 
 Set Addressing mode to page address and set cursor pointer to given coordinates

 Parameters:
 uint8_t line: indicates "page" VALUE MUST BE 0-7 
 uint8_t segment: indicates "segment" VALUE MUST BE 0-127

 Return value:
 0: Everything's ok
 1: If error is caught

*/
uint8_t setPointer(uint8_t line) 
 {

  if(status == DISPLAY_ON) // check display
   {
    if(line >= 0x00 && line < 0x08) // check if line si correct
    {
    
      uint8_t buffer;

      twStart(SSD1306, 0); // start connection
      for (uint8_t i = 0; i < HOR_LENGTH; i++) 
      {
        buffer = pgm_read_byte_near(&horizontalAddr[i]);
        twWrite(buffer);
      }
      twWrite(line); //page start 
      twWrite(line); //page end
      
      twClose(); // close

      return 0;    
    }
    else return 1;
   }
  else return 1;


 }

/*

 decodeString FUNCTION
 Description: 
 scan string and send integer by integer to printAscii

 Parameters:
 uint8_t msg: pointer to array of unsigned integers


*/
void printString(char *msg) 
 {

  if(status == DISPLAY_ON) // check display
   {
    while (*msg != 0) 
    { 
      printAscii(*msg); // scroll string
      msg++;
    }
   }

 }

/*

 printAscii FUNCTION
 Description: 
 decode ascii bits then send data stream D/C bit to device then bitbang

 Parameters:
 uint8_t c: byte that indicates ascii char


*/
void printAscii(char c) 
 {

  // find correct array pos for character
  uint16_t asciiIndex = (((uint8_t)c)-32)*6; // need 16 bit since ASCII array is around 600 bytes
  uint8_t buffer;

  twStart(SSD1306, 0); // start connection

  twWrite(DATASTREAM);
  for (uint16_t i=asciiIndex; i < asciiIndex+6; i++) 
  {
   buffer = pgm_read_byte_near(&ssd1306_font[i]);
   twWrite(buffer);
  }

  twClose(); // close connection

 }


/*

 clear FUNCTION WORKING IN PROGRESS
 Description: 
 clear screen. but experimental

 Return value
 0: ok
 1: errors caught

*/
uint8_t clear(uint8_t line) 
 {

  if(status == DISPLAY_ON) 
   {
    if(line >= 0x00 && line < 0x08) 
    {
      setPointer(line);

      for(uint8_t i =0 ; i<4; i++) 
      {
        twStart(SSD1306, 0);

        twWrite(DATASTREAM);
    
        for(uint8_t j=0; j<31; j++)
          twWrite((uint8_t)0x00);


        twClose();
      }

    }
    else return 1;
   }
  else return 1;

 }