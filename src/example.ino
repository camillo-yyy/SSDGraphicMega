#include "SSDGraphicMega.h"
#include <stdio.h>

#define SSD1306 0x3C
#define HEIGHT 64
#define WIDTH 128

float temperature = 60.00;

void setup() {

  beginDisplay();
  
}


void loop() {
  // put your main code here, to run repeatedly:
  static long startTime = 0;
  long currentTime;
  char temp[5];
  char hum[5];

  // Get current time
  currentTime = millis();
  
  // Checks 1 second passed
  if ((currentTime - startTime) > 1000) {


    startTime = currentTime;
    
    // Update temperature
    temperature +=1;

    dtostrf(temperature, 4, 2, temp); // cast float to string

    // Set cursor
    setPointer((uint8_t)0x02); // 3rd line
    // Print to display

    printString("Temperature: ");
    
    // Print to display

    printString(temp);

    // Update humidity
    float humidity = 20.00;

    dtostrf(humidity, 4, 2, hum); // cast float to string

    // Set cursor
    setPointer((uint8_t)0x05); // 5th line

    printString("Humidity: ");
    // Print to display
    printString(hum);

  }

  
}
