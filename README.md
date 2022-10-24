# UART transmission of ASCII characters with Serial Port
Designed for Atmega16.
Takes input from command line and generates assembly file to transmit desired string throgh Serial Port B. All required instructions already put in file. Cmd output shows ASCII values with their binary representation. Binary output is reversed due to UART being little-endian (being printed in actual send order).

![uart3](https://user-images.githubusercontent.com/81091594/197532143-a20593e3-4371-4884-a714-1225e8208339.png)

Procedure for actual transmission is *PB0_STRING*. Additional procedure *LOOP_104* creates delay required for CPU, bit change instruction delay is taken into account. **THIS WAS CALCULATED FOR 8 MHz CLOCK!** Transmission is handled with #0 line of Serial Port B. Can be adapted to any other pin or port. Start and stop signals included.

*Yes, it was university task to code such transmitter. But as code is very repetitive it can write itseslf on its own...*
