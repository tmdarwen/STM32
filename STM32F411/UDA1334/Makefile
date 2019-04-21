
## Cross-compilation commands 
CC      = arm-none-eabi-gcc
LD      = arm-none-eabi-gcc
AS      = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

VPATH = . $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src

# Define object files
LOCAL_OBJS = main.o system_stm32f4xx.o startup_stm32f411xe.o 
HAL_OBJS = stm32f4xx_hal.o stm32f4xx_hal_cortex.o stm32f4xx_hal_dma.o stm32f4xx_hal_dma_ex.o stm32f4xx_hal_flash.o \
           stm32f4xx_hal_flash_ex.o stm32f4xx_hal_flash_ramfunc.o stm32f4xx_hal_gpio.o stm32f4xx_hal_i2s.o \
           stm32f4xx_hal_i2s_ex.o stm32f4xx_hal_pwr.o stm32f4xx_hal_pwr_ex.o stm32f4xx_hal_rcc.o stm32f4xx_hal_rcc_ex.o \
            stm32f4xx_hal_tim.o stm32f4xx_hal_tim_ex.o
OBJECTS = $(addprefix ./, $(LOCAL_OBJS) $(HAL_OBJS))

INCLUDE_PATHS= -I. \
               -I$(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Inc \
               -I$(STM32CubeDir)/Drivers/CMSIS/Device/ST/STM32F4xx/Include \
               -I$(STM32CubeDir)/Drivers/CMSIS/Include

CFLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F411xE -O0 -g3 -Wall \
         -fmessage-length=0 -ffunction-sections -c -MMD -MP $(INCLUDE_PATHS)

LFLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -specs=nosys.specs -specs=nano.specs \
         -T"STM32F411VETx_FLASH.ld" -Wl,-Map=output.map -Wl,--gc-sections 

all: dirs main.elf main.bin size 

main.elf : $(OBJECTS) 
	$(LD) $(LFLAGS) -o main.elf $(OBJECTS) 

main.bin: main.elf
	$(OBJCOPY) -O binary "main.elf" "main.bin"

size: main.elf
	$(SIZE) $< 

# Apparently $< expands to the VPATH
./%.o : %.c
	$(CC) $(CFLAGS) -o $@ $<

# Apparently $< expands to the VPATH
./%.o : %.s
	$(CC) $(CFLAGS) -o $@ $<

dirs:
	 -@ if NOT EXIST "obj" mkdir "obj"

clean :
	rm *.o *.d *.elf *.bin *.map
