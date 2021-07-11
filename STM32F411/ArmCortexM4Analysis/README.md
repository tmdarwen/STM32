STM32 ArmCortexM4Analysis
=========================

This example was written for the [STM32F411 development board](http://www.st.com/en/microcontrollers/stm32f411.html?querycriteria=productId=LN1877).  It's the program used in my blog post [In Depth Analysis of an ARM Cortex-M4 Program](https://www.tmdarwen.com/latest/in-depth-analysis-of-an-arm-cortex-m-program).

 

**Foreword**

I currently (Winter 2018) use Windows as my main development machine, however, I'm fairly certain all of the following steps can be similarly done using a typical Linux distro or possibly even MacOS.

 

**Prerequisites**

1.   An [STMF32F411](http://www.st.com/en/microcontrollers/stm32f411.html?querycriteria=productId=LN1877) development board.  Currently they can be ordered from the usual sites for around $15 USD plus shipping.
1.   Download and install the [GNU Arm Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads)
1.   Download and install [GNU Make for Windows](http://gnuwin32.sourceforge.net/packages/make.htm)
1.   Download [OpenOCD](http://openocd.org/) and uncompress it (preferably to c:\OpenOCD).
1.   Download and install the [STM32 ST-Link Utility](http://www.st.com/en/development-tools/stsw-link004.html).

 

**Compiling and Flashing the Program to the Dev Board**

1.   Open a GCC Command Prompt.  Note that a "GCC Command Prompt" option was installed when installing the GNU Arm Embedded Toolchain and should be available from Windows Start Menu.
1.   Change to the ArmCortexM4Analysis directory and run "make".  This will compile the C program (main.c) and the startup assembly file (startup.s) and use the LinkerScript.ld file to create the ELF file which is then converted to out.bin - the actual binary that will run on the STM32F411.
1.   Open the STM32 ST-Link Utility and select "Program" from the "Target" pulldown menu.
1.   Navigate to the ArmCortexM4Analysis directory and select out.bin.
1.   Click "Start" to flash out.bin to the development board.  After this is done you should see LEDs on the development board blinking (i.e. the program is running on the board).


 

**Debugging from the Command Line**

1.   Make sure to close the STM32 ST-Link Utility so OpenOCD will be able to connect to the dev board.
1.   Open another command prompt.
1.   Change directory to the ArmCortexM4Analysis directory.
1.   Run OpenOCD.bat.  Note that if you did NOT uncompress OpenOCD to c:\OpenOCD you'll have to modify the first line of OpenOCD.bat to point to the directory that OpenOCD exists in.
1.   Switch to the original GCC command prompt you opened when compiling and run arm-none-eabi-gdb.
1.   After GDB starts up, at the prompt, type "target remote localhost:3333" and press enter.  This will connect to OpenOCD.
1.   Next, type "monitor reset halt" at the GDB prompt to stop the currently running program.
1.   Then, load the ELF file into GDB by entering "file out.ELF".  It'll ask you "Are you sure you want to change the file?", answer "y" for "yes".
1.   You can then use "si" to step through each instruction of the program.
