set OpenOCDPath=c:\OpenOCD

c:\OpenOCD\bin\openocd -f "%OpenOCDPath%\share\openocd\scripts\interface\stlink-v2.cfg" -f %OpenOCDPath%\share\openocd\scripts\target\stm32f4x.cfg -s "%OpenOCDPath%\share\openocd\scripts"
