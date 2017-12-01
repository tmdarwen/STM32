// The STM32F411 comes with a LSM303DLHC 3D accelerometer on the board.  This 
// header allows for initializing the device and sending realtime acceleroemeter 
// info to a terminal via UART connected to PA2.  See UART.h for more info on 
// how data is transfered to the terminal by UART.
#pragma once

void AccelerometerInit();
void DisplayAxisValues();
