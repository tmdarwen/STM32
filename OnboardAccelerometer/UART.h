// Allows for sending UART data to a terminal program using STM32F411 pin
// PA2.  To use, setup a serial terminal (like Putty) at 9598 baud rate,
// 8 data bits, 1 stop bit, no parity or flow control.  Then call UartInit()
// and send strings to the terminal using SendString().

#pragma once

void UartInit();
void SendString(char* string);
