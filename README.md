STM32
=====

This is a repo for my various smaller [STM32 MCU](http://www.st.com/en/microcontrollers/stm32-32-bit-arm-cortex-mcus.html) projects.  So far these only pertain to the [STM32F411 development board](http://www.st.com/en/microcontrollers/stm32f411.html?querycriteria=productId=LN1877).  In these projects I *_do not_* use the STM HAL or Standard Peripheral Library.  I do this for the sake of understanding and demonstrating how the STM32F4 and peripherals work at their lowest levels.  All of these examples are well commented, explaining what each non-obvious line of code is doing, frequently referencing datasheet pages for detailed information and explanation.

Each example simply contains the source code, startup code and a makefile for the project.  No projects have external software dependencies.  Following some [simple steps](BlinkLightsCommandLine/README.md), you should be able to easily build these examples from the command line using the GNU ARM Embedded Toolchain.  Or, if you prefer, you should be able to easily load the source code into your favorite IDE/toolchain to build/run the examples from it.

**Index**

-   [**BlinkLightsCommandLine**](BlinkLightsCommandLine/README.md): This example simply blinks the onboard LEDs.  Although a simple program, its importance is that it shows how to compile and debug entirely on the command line using GCC and GDB.  
-   **HighSpeedClock**: This example shows how to configure the CPU clock speed to the maximum rate (100 MHz).
-   **OnboardAccelerometer**: The STM32F411 development board has an [LSM303DLHC accelerometer](http://www.st.com/en/mems-and-sensors/lsm303dlhc.html) included on the board.  This example initializes the accelerometer and continually reads x, y, z axes from it displaying the values in realtime to a terminal program using UART.
-   **OnboardAudioOutput**: This example outputs a stereo, 16 bit sine wave tone from the [CS43L22 DAC](https://www.cirrus.com/products/cs43l22/) which comes onboard the STM32F411 development board.
-   [**OnboardGyroAccel**](OnboardGyroAccel/README.md): This is a combination of the OnboardGyroscope and OnboardAccelerometer projects that displays values of both devices in realtime to a terminal program.
-   **OnboardGyroscope**: The STM32F411 development board has an [L3GD20 gyroscope](http://www.st.com/en/mems-and-sensors/l3gd20.html) included on the board.  This example initializes the gyroscope and continually reads x, y, z axes from it displaying the values in realtime to a terminal program using UART.
-   **SystickInterruptCommandLine**: This example shows how to configure the systick register and use the systick interrupt.
-   **TimerInterruptCommandLine**: Shows how to configure a timer interrupt.
-   **UARTBlockingBidirectional**: Shows how to do bidirectional communication using UART.
-   **UARTBlockingTransfer**: Shows how to transfer data using UART.
-   **UARTDMABidirectional**: This example shows how to do bidirectional UART communication using DMA for both transferring and receiving data.  This project uses a terminal program to receive a keypress character and then display the character on the terminal screen.
-   **UARTDMATransfer**: Shows how to transfer data using UART and DMA.
-   **UARTReceiveInterrupt**: Shows how to receive data using an interrupt with UART to avoid blocking calls.

 

**Licensing**

The MIT License applies to this software and its supporting documentation:

*Copyright (c) 2017 - Terence M. Darwen - tmdarwen.com*

*Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:*

*The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.*

*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*
