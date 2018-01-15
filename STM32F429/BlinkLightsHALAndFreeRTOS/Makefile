## Cross-compilation commands 
CC      = arm-none-eabi-gcc
LD      = arm-none-eabi-gcc
AS      = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

OBJECTS = main.o startup_stm32f429xx.o stm32f4xx_it.o stm32f4xx_hal_timebase_tim.o system_stm32f4xx.o stm32f4xx_hal_tim_ex.o stm32f4xx_hal_tim.o \
          stm32f4xx_hal_spi.o stm32f4xx_hal_rcc_ex.o stm32f4xx_hal_rcc.o stm32f4xx_hal_pwr_ex.o stm32f4xx_hal_pwr.o stm32f4xx_hal_i2c_ex.o \
          stm32f4xx_hal_i2c.o stm32f4xx_hal_gpio.o stm32f4xx_hal_flash_ex.o stm32f4xx_hal_flash.o stm32f4xx_hal_dma.o stm32f4xx_hal_cortex.o \
          stm32f4xx_hal.o tasks.o timers.o queue.o list.o cmsis_os.o port.o heap_4.o

INCLUDE_PATHS= -I. \
               -I$(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Inc \
               -I$(STM32CubeDir)/Drivers/CMSIS/Device/ST/STM32F4xx/Include \
               -I$(STM32CubeDir)/Drivers/CMSIS/Include \
               -I$(STM32CubeDir)/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS \
               -I$(STM32CubeDir)/Middlewares/Third_Party/FreeRTOS/Source/include \
               -I$(STM32CubeDir)/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F

CFLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F429ZITx -DSTM32F429I-DISCO \
         -DDEBUG -DSTM32F429xx -DUSE_STM32F429I_DISCO -DUSE_HAL_DRIVER -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP $(INCLUDE_PATHS)

LFLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -T"STM32F429ZITx_FLASH.ld" -Wl,-Map=output.map -Wl,--gc-sections

all: main.elf main.bin size 

main.elf : $(OBJECTS) 
	$(LD) $(LFLAGS) -o main.elf $(OBJECTS)

main.bin: main.elf
	$(OBJCOPY) -O binary "main.elf" "main.bin"

size: main.elf
	$(SIZE) $< 

main.o : main.c 
	$(CC) $(CFLAGS) main.c

stm32f4xx_hal_timebase_tim.o : stm32f4xx_hal_timebase_tim.c
	$(CC) $(CFLAGS) stm32f4xx_hal_timebase_tim.c

stm32f4xx_it.o : stm32f4xx_it.c
	$(CC) $(CFLAGS) stm32f4xx_it.c

system_stm32f4xx.o : system_stm32f4xx.c
	$(CC) $(CFLAGS) system_stm32f4xx.c

stm32f4xx_hal_tim_ex.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c

stm32f4xx_hal_tim.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c

stm32f4xx_hal_spi.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c

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

stm32f4xx_hal_flash_ex.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c

stm32f4xx_hal_flash.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c

stm32f4xx_hal_dma.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c

stm32f4xx_hal_cortex.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c

stm32f4xx_hal.o : $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c 
	$(CC) $(CFLAGS) $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c 

timers.o : $(STM32CubeDir)/Middlewares/Third_Party/FreeRTOS/Source/timers.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Middlewares/Third_Party/FreeRTOS/Source/timers.c

tasks.o : $(STM32CubeDir)/Middlewares/Third_Party/FreeRTOS/Source/tasks.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Middlewares/Third_Party/FreeRTOS/Source/tasks.c

queue.o : $(STM32CubeDir)/Middlewares/Third_Party/FreeRTOS/Source/queue.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Middlewares/Third_Party/FreeRTOS/Source/queue.c

list.o : $(STM32CubeDir)/Middlewares/Third_Party/FreeRTOS/Source/list.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Middlewares/Third_Party/FreeRTOS/Source/list.c

cmsis_os.o : $(STM32CubeDir)/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c

port.o : $(STM32CubeDir)/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c

heap_4.o : $(STM32CubeDir)/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
	$(CC) $(CFLAGS) $(STM32CubeDir)/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
 
clean :
	del *.o *.d *.elf *.bin *.map

