## Cross-compilation commands 
CC      = arm-none-eabi-gcc
LD      = arm-none-eabi-gcc
AS      = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

OBJS  = main.o startup_stm32.o

## Platform and optimization options
CFLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F429ZITx -DSTM32F429I-DISCO
CFLAGS += -DSTM32F429xx -DUSE_STM32F429I_DISCO -O3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP
LFLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -T"LinkerScript.ld" -Wl,-Map=output.map -Wl,--gc-sections

## Rules
all: main.elf main.bin size 

main.elf: $(OBJS) LinkerScript.ld
	$(LD) $(LFLAGS) -o main.elf $(OBJS)

main.bin: main.elf
	$(OBJCOPY) -O binary "main.elf" "main.bin"

size: main.elf
	$(SIZE) $< 

clean:
	del *.o *.d *.elf *.bin *.map
