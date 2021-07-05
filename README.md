STM32
=====

This is a repo for my various smaller [STM32 MCU](http://www.st.com/en/microcontrollers/stm32-32-bit-arm-cortex-mcus.html) projects.  Below you'll see a number of examples for the [STM32F411 development board](http://www.st.com/en/microcontrollers/stm32f411.html?querycriteria=productId=LN1877) and the [STM32F429 dev board](http://www.st.com/en/evaluation-tools/32f429idiscovery.html).  For many of these projects I *_do not_* use the STM HAL or Standard Peripheral Library.  I do this for the sake of understanding and demonstrating how the STM32F4 and peripherals work at their lowest levels.  All of these examples are well commented, explaining what each non-obvious line of code is doing, frequently referencing datasheet pages for detailed information and explanation.

Each example simply contains the source code, startup code and a makefile for the project.  Few of the projects have external software dependencies.  Those that do will be noted in the description.  Following [simple steps](STM32F411/BlinkLightsCommandLine/README.md), you should be able to easily build these examples from the command line using the GNU ARM Embedded Toolchain.  Or, if you prefer, you should be able to easily load the source code into your favorite IDE/toolchain to build/run the examples from it.

**STM32F411 Index**
-   [**ArmCortexM4Analysis**](STM32F411/ArmCortexM4Analysis/README.md): This program is used in my blog post [In Depth Analysis of an ARM Cortex-M4 Program](https://www.tmdarwen.com/latest/in-depth-analysis-of-an-arm-cortex-m-program).
-   [**BlinkLightsCommandLine**](STM32F411/BlinkLightsCommandLine/README.md): This example simply blinks the onboard LEDs.  Although a simple program, its importance is that it shows how to compile and debug entirely on the command line using GCC and GDB.  
-   **HighSpeedClock**: This example shows how to configure the CPU clock speed to the maximum rate (100 MHz).
-   **OnboardAccelerometer**: The STM32F411 development board has an [LSM303DLHC accelerometer](http://www.st.com/en/mems-and-sensors/lsm303dlhc.html) included on the board.  This example initializes the accelerometer and continually reads x, y, z axes from it displaying the values in realtime to a terminal program using UART.
-   [**OnboardAudioOutput**](STM32F411/OnboardAudioOutput): This example outputs a stereo, 16 bit sine wave tone from the [CS43L22 DAC](https://www.cirrus.com/products/cs43l22/) which comes onboard the STM32F411 development board.
-   [**OnboardGyroAccel**](STM32F411/OnboardGyroAccel/README.md): This is a combination of the OnboardGyroscope and OnboardAccelerometer projects that displays values of both devices in realtime to a terminal program.
-   **OnboardGyroscope**: The STM32F411 development board has an [L3GD20 gyroscope](http://www.st.com/en/mems-and-sensors/l3gd20.html) included on the board.  This example initializes the gyroscope and continually reads x, y, z axes from it displaying the values in realtime to a terminal program using UART.
-   **SystickInterruptCommandLine**: This example shows how to configure the systick register and use the systick interrupt.
-   **TimerInterruptCommandLine**: Shows how to configure a timer interrupt.
-   **UARTBlockingBidirectional**: Shows how to do bidirectional communication using UART.
-   **UARTBlockingTransfer**: Shows how to transfer data using UART.
-   **UARTDMABidirectional**: This example shows how to do bidirectional UART communication using DMA for both transferring and receiving data.  This project uses a terminal program to receive a keypress character and then display the character on the terminal screen.
-   **UARTDMATransfer**: Shows how to transfer data using UART and DMA.
-   **UARTReceiveInterrupt**: Shows how to receive data using an interrupt with UART to avoid blocking calls.
-   [**UDA1334A**](STM32F411/UDA1334A/README.md): Shows how to output stereo, 16 bit tone to an [Adafruit UDA1334A breakout board](https://www.adafruit.com/product/3678).
-   **UserButton**: Simple example showing how to use the user button on the STM32F411 development board.
-   **UserButtonInterrupt**: Uses an interrupt to detect when the user button on the STM32F411 development board is pressed/released.

**STM32F429 Index**
-   [**BlinkLightsCube32FreeRTOS**](STM32F429/BlinkLightsCube32FreeRTOS/README.md): Shows how to use [FreeRTOS](https://www.freertos.org/), as packaged in the STM32 Cube Firmware.  This example has a dependency on the [STM32 Cube Firmware](http://www.st.com/content/st_com/en/products/embedded-software/mcus-embedded-software/stm32-embedded-software/stm32cube-mcu-packages/stm32cubef4.html).
-   [**BlinkLightsFreeRTOS**](STM32F429/BlinkLightsFreeRTOS/README.md): Shows how to use [FreeRTOS](https://www.freertos.org/) without a dependency on the STM32 Cube Firmware.  This example has a dependency on the FreeRTOS package that can be currently downloaded from [here](https://www.freertos.org/).
-   [**BlinkLightsHALAndFreeRTOS**](STM32F429/BlinkLightsHALAndFreeRTOS/README.md): Shows how to use the [STM32 HAL](http://www.st.com/en/embedded-software/stm32cubef4.html) and [FreeRTOS](https://www.freertos.org/). This example has a dependency on the [STM32 Cube Firmware](http://www.st.com/content/st_com/en/products/embedded-software/mcus-embedded-software/stm32-embedded-software/stm32cube-mcu-packages/stm32cubef4.html).
-   [**BouncingBall**](STM32F429/BouncingBall/README.md): Shows how to use the STemWin GUI lib.  The example infinitely bounces a ball around the LCD screen of the STM32F429 dev board.  This example has a dependency on the [STM32 Cube Firmware](http://www.st.com/content/st_com/en/products/embedded-software/mcus-embedded-software/stm32-embedded-software/stm32cube-mcu-packages/stm32cubef4.html).
-   **ConfigureSDRAM**: Shows how to use SDRAM.
-   **HighSpeedClock**: This example shows how to configure the CPU clock speed to the maximum rate (180 MHz).
-   [**Slideshow**](STM32F429/Slideshow/README.md): Uses STM32 Cube Firmware's USB, FAT-FS and STemWin libs to allow for displaying images from a USB thumb drive onto the LCD screen of the STM32F429 dev board.  This example has a dependency on the [STM32 Cube Firmware](http://www.st.com/content/st_com/en/products/embedded-software/mcus-embedded-software/stm32-embedded-software/stm32cube-mcu-packages/stm32cubef4.html).


 

**Licensing**

The MIT License applies to this software and its supporting documentation:

*Copyright (c) 2017-2018 - Terence M. Darwen - tmdarwen.com*

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
