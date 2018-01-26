STM32F429 Slideshow
===================

This example was written for the [STM32F429 development board](http://www.st.com/en/microcontrollers/stm32f429-439.html?querycriteria=productId=LN1806).  The original code for this project came from the [STM32CubeF4 Firmware](http://www.st.com/en/embedded-software/stm32cubef4.html) v1.18.0 example named "LTDC_AnimatedPictureFromUSB" that can be found in the Projects\STM32F429I-Discovery\Applications\Display directory.  The project will find BMP files saved on the USB drive and display the images on the LCD screen of the STM32F429.

I've streamlined the code for this project and added a makefile so that it can easily be built without an IDE (see directions below).  The software has a dependency on the [STM32 Cube Firmware v1.18.0](http://www.st.com/content/st_com/en/products/embedded-software/mcus-embedded-software/stm32-embedded-software/stm32cube-mcu-packages/stm32cubef4.html).

 

**Foreword**

I currently (Winter 2018) use Windows as my main development machine, however, I'm fairly certain the following build steps can be done using a typical Linux distro (with a few minor tweaks) and very possibly MacOS as well.

 

**Prerequisites**

1.   An [STMF32F429](http://www.st.com/en/microcontrollers/stm32f429-439.html?querycriteria=productId=LN1806) development board.  Currently they can be ordered from the usual sites for around $30 USD plus shipping.
1.   Download and install the [GNU Arm Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads)
1.   Download and install [GNU Make for Windows](http://gnuwin32.sourceforge.net/packages/make.htm)
1.   Download and install the [STM32 ST-Link Utility](http://www.st.com/en/development-tools/stsw-link004.html).
1.   Download and uncompress [STM32 Cube Firmware](http://www.st.com/content/st_com/en/products/embedded-software/mcus-embedded-software/stm32-embedded-software/stm32cube-mcu-packages/stm32cubef4.html) (I'm using v1.18.0)

 

**Compiling and Flashing the Program to the Dev Board**

1.   Open a GCC Command Prompt.  Note that a "GCC Command Prompt" option was installed when installing the GNU Arm Embedded Toolchain and should be available from the Windows Start Menu.
1.   Change to the Slideshow directory and run "make STM32CubeDir=LocationOfSTM32Cube" subsituting in the location of STM32Cube Firmware package on your machine.  This will compile the program into a bin file.
1.   Open the STM32 ST-Link Utility and select "Program" from the "Target" pulldown menu.
1.   Navigate to the Slideshow directory and select main.bin.
1.   Click "Start" to flash main.bin to the development board.  After doing so, the slideshow program will start.

