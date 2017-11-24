STM32
=====

A repo for my various smaller [STM32 MCU](http://www.st.com/en/microcontrollers/stm32-32-bit-arm-cortex-mcus.html) projects.  So far these only peraqin to the [STM32F411 development board](http://www.st.com/en/microcontrollers/stm32f411.html?querycriteria=productId=LN1877).

**Index**

-   [**BlinkLightsCommandLine**](BlinkLightsCommandLine/README.md): This example simply blinks the onboard LEDs.  Although a simple program, its importance is that it shows how to compile and debug entirely on the command line using GCC and GDB.  
-   **HighSpeedClock**: This example shows how to configure the CPU clock speed to the maximum rate (100 MHz).
-   **OnboardAudioOutput**: This example outputs a stereo, 16 bit sine wave tone from the [CS43L22 onboard DAC](https://www.cirrus.com/products/cs43l22/).  For clarity of how the board works, no HAL, Standard Peripheral or any other API is used.
-   **OnboardGyroscope**: The STM32F411 has a [L3GD20 gyroscope](http://www.st.com/en/mems-and-sensors/l3gd20.html) onboard.  This example initializes the gyroscope and continually reads x, y, z axes from it displaying the values in realtime to a terminal program using UART.
-   **SystickInterruptCommandLine**: This example shows how to configure the systick register and use the systick interrupt.
-   **TimerInterruptCommandLine**: This is a simple example showing/explaining how to configure a timer interrupt.
-   **UARTBlockingBidirectional**: This is a simple example showing how to do bidirectional communication using UART.
-   **UARTDMABidirectional**: This example shows how to do bidirectional UART communication using DMA for both transferring and receiving data.  This project uses a terminal program to receive a keypress character and then display it on the terminal screen.
-   **UARTBlockingTransfer**: This is a simple example showing how to transfer data using UART.
-   **UARTDMATransfer**: This is code showing how to transfer data using UART and DMA.
-   **UARTReceiveInterrupt**: This is an example showing how to receive data using an interrupt with UART to avoid blocking calls.

