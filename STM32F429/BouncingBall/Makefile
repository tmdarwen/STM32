## Cross-compilation commands 
CC      = arm-none-eabi-gcc
LD      = arm-none-eabi-gcc
AS      = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

OBJECTS = main.o startup_stm32f429xx.o stm32f4xx_it.o system_stm32f4xx.o stm32f4xx_hal_tim_ex.o stm32f4xx_hal_tim.o \
          stm32f4xx_hal_spi.o stm32f4xx_hal_sdram.o stm32f4xx_hal_rcc_ex.o stm32f4xx_hal_rcc.o stm32f4xx_hal_rng.o \
          stm32f4xx_hal_pwr_ex.o stm32f4xx_hal_pwr.o stm32f4xx_hal_i2c_ex.o stm32f4xx_hal_i2c.o stm32f4xx_hal_gpio.o \
          stm32f4xx_ll_fmc.o stm32f4xx_hal_flash_ex.o stm32f4xx_hal_flash.o stm32f4xx_hal_dma2d.o stm32f4xx_hal_dma.o \
          stm32f4xx_hal_cortex.o stm32f4xx_hal.o stm32f429i_discovery_io.o stm32f429i_discovery_lcd.o \
          stm32f429i_discovery_sdram.o stm32f429i_discovery_ts.o stm32f429i_discovery.o ili9341.o GUI_X.o stmpe811.o \
          GUIConf.o stm32f4xx_hal_ltdc.o LCDConf_stm32f429i_disco_MB1075.o

INCLUDE_PATHS= -I. \
               -I$(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Inc \
               -I$(STM32CubeDir)/Drivers/BSP/Components \
               -I$(STM32CubeDir)/Drivers/BSP/Components/ili9341 \
               -I$(STM32CubeDir)/Drivers/BSP/STM32F429I-Discovery \
               -I$(STM32CubeDir)/Middlewares/ST/STemWin/inc \
               -I$(STM32CubeDir)/Middlewares/ST/STemWin/Config \
               -I$(STM32CubeDir)/Drivers/CMSIS/Device/ST/STM32F4xx/Include \
               -I$(STM32CubeDir)/Drivers/CMSIS/Include 

LIB_PATHS = -L$(STM32CubeDir)/Middlewares/ST/STemWin/Lib/

CFLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F429xx -DSTM32F429I-DISCO \
         -DDEBUG -DSTM32F429xx -DUSE_STM32F429I_DISCO -DUSE_HAL_DRIVER -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP $(INCLUDE_PATHS)

LFLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -T"STM32F429ZITx_FLASH.ld" -specs=nosys.specs -specs=nano.specs -Wl,-Map=output.map -Wl,--gc-sections ${LIB_PATHS}

all: main.elf main.bin size 

main.elf : $(OBJECTS) 
	$(LD) $(LFLAGS) -o main.elf $(OBJECTS) -l:STemWin540_CM4_GCC.a

main.bin: main.elf
	$(OBJCOPY) -O binary "main.elf" "main.bin"

size: main.elf
	$(SIZE) $< 

main.o : main.c 
	$(CC) $(CFLAGS) main.c

stm32f4xx_it.o : stm32f4xx_it.c
	$(CC) $(CFLAGS) stm32f4xx_it.c

system_stm32f4xx.o : system_stm32f4xx.c
	$(CC) $(CFLAGS) system_stm32f4xx.c

stm32f4xx_hal_ltdc.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_ltdc.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_ltdc.c

stm32f4xx_hal_tim_ex.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c

stm32f4xx_hal_tim.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c

stm32f4xx_hal_spi.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c

stm32f4xx_hal_sdram.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sdram.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sdram.c

stm32f4xx_hal_rng.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rng.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rng.c

stm32f4xx_hal_rcc_ex.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c

stm32f4xx_hal_rcc.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c

stm32f4xx_hal_pwr_ex.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c

stm32f4xx_hal_pwr.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c

stm32f4xx_hal_i2c_ex.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.c

stm32f4xx_hal_i2c.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c

stm32f4xx_hal_gpio.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c

stm32f4xx_ll_fmc.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fmc.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fmc.c

stm32f4xx_hal_flash_ex.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c

stm32f4xx_hal_flash.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c

stm32f4xx_hal_dma2d.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma2d.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma2d.c

stm32f4xx_hal_dma.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c

stm32f4xx_hal_cortex.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c

stm32f4xx_hal.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c 
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c 

stm32f429i_discovery_io.o : $(STM32CubeDir)/Drivers/BSP/STM32F429I-Discovery/stm32f429i_discovery_io.c 
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/BSP/STM32F429I-Discovery/stm32f429i_discovery_io.c 

stm32f429i_discovery_lcd.o : $(STM32CubeDir)/Drivers/BSP/STM32F429I-Discovery/stm32f429i_discovery_lcd.c 
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/BSP/STM32F429I-Discovery/stm32f429i_discovery_lcd.c 

stm32f429i_discovery_sdram.o : $(STM32CubeDir)/Drivers/BSP/STM32F429I-Discovery/stm32f429i_discovery_sdram.c 
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/BSP/STM32F429I-Discovery/stm32f429i_discovery_sdram.c 

stm32f429i_discovery_ts.o : $(STM32CubeDir)/Drivers/BSP/STM32F429I-Discovery/stm32f429i_discovery_ts.c 
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/BSP/STM32F429I-Discovery/stm32f429i_discovery_ts.c 

stm32f429i_discovery.o : $(STM32CubeDir)/Drivers/BSP/STM32F429I-Discovery/stm32f429i_discovery.c 
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/BSP/STM32F429I-Discovery/stm32f429i_discovery.c 

ili9341.o : $(STM32CubeDir)/Drivers/BSP/Components/ili9341/ili9341.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/BSP/Components/ili9341/ili9341.c

stmpe811.o : $(STM32CubeDir)/Drivers/BSP/Components/stmpe811/stmpe811.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/BSP/Components/stmpe811/stmpe811.c

GUI_X.o : $(STM32CubeDir)/Middlewares/ST/STemWin/OS/GUI_X.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Middlewares/ST/STemWin/OS/GUI_X.c

GUIConf.o : GUIConf.c
	$(CC) $(CFLAGS) GUIConf.c

LCDConf_stm32f429i_disco_MB1075.o : LCDConf_stm32f429i_disco_MB1075.c
	$(CC) $(CFLAGS) LCDConf_stm32f429i_disco_MB1075.c

clean :
	del *.o *.d *.elf *.bin *.map
