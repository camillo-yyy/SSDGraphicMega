# SSD1306 Graphic Library with I2C

This project was made as practical part of Architecture of Elaborators Course at University Of Camerino.
Documentation part is freely available for educational purpose.

The project is available on Debug Platform Wokwi at the following link: <link progetto>

The main objective of the project was to create a Library to establish a communication 
between Arduino and SSD1306 display using I2C protocol.

This repository includes two library:
- TWireMega.h: which is a general purpose I2C protocol library. It currently supports only Master Transmitter Mode
with a 32 Byte buffer (size easily customizable) and background byte transmission.
Maybe Master Receiver support in the future? 

- SSDGraphicMega.h: which defines prior functions to communicate with the display: start sequence, 
setting cursor on display, writing strings on display (supports 8x6 ascii set of chars).


# Project2305


