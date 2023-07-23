# SSD1306 Graphic Library with I2C

The project was carried out as part of the Computer Architecture course (ST1213 - ARCHITETTURA DEGLI ELABORATORI) for the University of Camerino.
I agree to use libraries and docs for educational purposes.

The project is available on Debug Platform Wokwi at the following link: https://wokwi.com/projects/365263969115559937

The main objective of the project was to create a Library to establish a communication 
between Arduino AtMega328p and SSD1306 display using I2C protocol.

This repository includes two library:
- TWireMega.h: which is a general purpose I2C protocol library for Two-Wire Interface. It currently supports only Master Transmitter Mode
with a 32 Byte buffer (size easily customizable) and background byte transmission.
Maybe Master Receiver support in the future? 

- SSDGraphicMega.h: which defines prior functions to communicate with the display: start sequence, 
setting cursor on display, writing strings on display (supports 8x6 ascii set of chars).

Full documentantion on docs folder (only in italian for now).

also called Project2305, glhf


