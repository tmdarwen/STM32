STM32F429 Blink Lights Using HAL and FreeRTOS
=============================================

This example was written for the [STM32F429 development board](http://www.st.com/en/microcontrollers/stm32f429-439.html?querycriteria=productId=LN1806).  It originally came in the [STM32 Cube Firmware v1.18.0](http://www.st.com/content/st_com/en/products/embedded-software/mcus-embedded-software/stm32-embedded-software/stm32cube-mcu-packages/stm32cubef4.html) however, I've added a makefile so that it can easily be built without an IDE (see directions below).  I've also removed the dependency on the board support package (BSP) and instead communicate directly with the HAL.  Although this is a simple program - it just blinks LEDs on the board periodically - its importance is that it shows how to use [FreeRTOS](https://www.freertos.org/) with multiple threads in an STM32 project.

 

**Foreword**

I currently (Winter 2018) use Windows as my main development machine, however, I'm fairly certain the following build steps can be done using a typical Linux distro (with a few minor tweaks) and quite possibly MacOS as well.

 

**Prerequisites**

1.   An [STMF32F429](http://www.st.com/en/microcontrollers/stm32f429-439.html?querycriteria=productId=LN1806) development board.  Currently they can be ordered from the usual sites for around $30 USD plus shipping.
1.   Download and install the [GNU Arm Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads)
1.   Download and install [GNU Make for Windows](http://gnuwin32.sourceforge.net/packages/make.htm)
1.   Download and install the [STM32 ST-Link Utility](http://www.st.com/en/development-tools/stsw-link004.html).
1.   Download and uncompress [STM32 Cube Firmware](http://www.st.com/content/st_com/en/products/embedded-software/mcus-embedded-software/stm32-embedded-software/stm32cube-mcu-packages/stm32cubef4.html) (I'm using v1.18.0)

 

**Compiling and Flashing the Program to the Dev Board**

1.   Open a GCC Command Prompt.  Note that a "GCC Command Prompt" option was installed when installing the GNU Arm Embedded Toolchain and should be available from the Windows Start Menu.
1.   Change to the BlinkLightsHALAndFreeRTOS directory and run "make STM32CubeDir=LocationOfSTM32Cube" subsituting in the location of STM32Cube Firmware package on your machine.  This will compile the program into a bin file.
1.   Open the STM32 ST-Link Utility and select "Program" from the "Target" pulldown menu.
1.   Navigate to the BlinkLightsHALAndFreeRTOS directory and select main.bin.
1.   Click "Start" to flash main.bin to the development board.  After this is done you should see both of the LEDs blink in differing intervals.  See the code in main.c.  Each LED is controlled from a separate FreeRTOS thread.

