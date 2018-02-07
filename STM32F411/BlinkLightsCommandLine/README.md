STM32 BlinkLightsCommandLine
============================

This example was written for the [STM32F411 development board](http://www.st.com/en/microcontrollers/stm32f411.html?querycriteria=productId=LN1877).  Although a simple program - it just blinks the four LEDs on the board periodically - its importance is that it shows how to compile and debug entirely on the command line using GCC and GDB.  

 

**Foreword**

I currently (Fall 2017) use Windows as my main development machine, however, I'm fairly certain all of the following steps can be similarly done using a typical Linux distro or possibly even MacOS.

 

**Prerequisites**

1.   An [STMF32F411](http://www.st.com/en/microcontrollers/stm32f411.html?querycriteria=productId=LN1877) development board.  Currently they can be ordered from the usual sites for around $15 USD plus shipping.
1.   Download and install the [GNU Arm Embedded Toolchain](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads)
1.   Download and install [GNU Make for Windows](http://gnuwin32.sourceforge.net/packages/make.htm)
1.   Download [OpenOCD](http://openocd.org/) and uncompress it (preferably to c:\OpenOCD).
1.   Download and install the [STM32 ST-Link Utility](http://www.st.com/en/development-tools/stsw-link004.html).

 

**Compiling and Flashing the Program to the Dev Board**

1.   Open a GCC Command Prompt.  Note that a "GCC Command Prompt" option was installed when installing the GNU Arm Embedded Toolchain and should be available from Windows Start Menu.
1.   Change to the BlinkLightCommandLine directory and run "make".  This will compile the C program (main.c) and the startup assembly file (startup_stm32.s) and use the LinkerScript.ld file to create the ELF file which is then converted to main.bin - the actual binary that will run on the STM32F411.
1.   Open the STM32 ST-Link Utility and select "Program" from the "Target" pulldown menu.
1.   Navigate to the BlinkLightCommandLine directory and select main.bin.
1.   Click "Start" to flash main.bin to the development board.  After this is done you should see all four LEDs on the development board blinking (i.e. the program is running on the board).


 

**Debugging from the Command Line**

1.   Make sure to close the STM32 ST-Link Utility so OpenOCD will be able to connect to the dev board.
1.   Open another command prompt.
1.   Change directory to the BlinkLightCommandLine directory.
1.   Run StartOpenOCD.bat (_Note that if you did NOT uncompress OpenOCD to c:\OpenOCD you'll have to modify the first line of OpenOCD.bat to point to the directory that OpenOCD exists in_).
1.   Switch to the original GCC command prompt you opened when compiling and run arm-none-eabi-gdb.
1.   After GDB starts up, at the prompt, type "target remote localhost:3333" and press enter.  This will connect to OpenOCD.
1.   Next, type "monitor reset halt" at the GDB prompt to stop the currently running program.
1.   Then, load the ELF file into GDB by entering "file main.ELF".  It'll ask you "Are you sure you want to change the file?", answer "y" for "yes".
1.   Set a breakpoint at main by typing "b main"
1.   Restart the program by typing "c" (this is short for "continue").  This will cause the program to run until the first line of main.
1.   Set a breakpoint on the line that toggles the LEDs.  Currently this is line 25 of main.c.  We can set a breakpoint by typing "b 25".
1.   Enter "c" to run the program to this new breakpoint.
1.   Continually enter "c" to pause/step at line 25 and watch the LEDs toggle as you do.
