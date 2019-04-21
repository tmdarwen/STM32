STM32 UDA1334A DAC Audio Output
===============================

This example was written for the [STM32F411 development board](http://www.st.com/en/microcontrollers/stm32f411.html?querycriteria=productId=LN1877).  It shows how to interface an STM32F4 with [Adafruit's I2S Stereo Decoder UDA1334A breakout board](https://www.adafruit.com/product/3678).  

 

**Foreword**

I currently (Spring 2019) use Windows as my main development machine, however, I'm fairly certain all of the following steps can be similarly done using a typical Linux distro and probably MacOS.

 

**Prerequisites**

1.   An [STMF32F411](http://www.st.com/en/microcontrollers/stm32f411.html?querycriteria=productId=LN1877) development board.  Currently they can be ordered from the usual sites for around $15 USD plus shipping.
1.   Download and install the [GNU Arm Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads)
1.   Download and install [GNU Make for Windows](http://gnuwin32.sourceforge.net/packages/make.htm)
1.   Download and install the [STM32 ST-Link Utility](http://www.st.com/en/development-tools/stsw-link004.html).

 

**Compiling and Flashing the Program to the Dev Board**

1.   Open a GCC Command Prompt.  Note that a "GCC Command Prompt" option was installed when installing the GNU Arm Embedded Toolchain and should be available from Windows Start Menu.
1.   Change to the UDA1334A directory and run "make".  This will result in main.bin, the actual binary that will run on the STM32F411.
1.   Open the STM32 ST-Link Utility and select "Program" from the "Target" pulldown menu.
1.   Navigate to the UDA1334A directory and select main.bin.
1.   Click "Start" to flash main.bin to the development board.  After this is done you should hear a sine tone from speakers or headphones plugged into the UDA1334A board.
