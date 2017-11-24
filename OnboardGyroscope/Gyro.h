// The STM32F411 comes with a L3GD20 three-axis digital output gyroscope on the
// board.  This allows for initializing it and send realtime coordinate info to a
// terminal via UART connected to PA2.  See UART.h for more info on how data is
// transfered to the terminal by UART.
#pragma once

void GyroInit();
void DisplayAxisValues();
