## Cross-compilation commands 
CC      = arm-none-eabi-gcc
LD      = arm-none-eabi-gcc
AS      = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

OBJECTS = main.o startup_stm32f429xx.o tasks.o timers.o queue.o list.o port.o heap_4.o

INCLUDE_PATHS= -I. -I$(FreeRTOSDir)/Source/include -I$(FreeRTOSDir)/Source/portable/GCC/ARM_CM4F

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

startup_stm32f429xx.o : startup_stm32f429xx.s
	$(AS) startup_stm32f429xx.s -o startup_stm32f429xx.o

timers.o : $(FreeRTOSDir)/Source/timers.c
	$(CC) $(CFLAGS) $(FreeRTOSDir)/Source/timers.c

tasks.o : $(FreeRTOSDir)/Source/tasks.c
	$(CC) $(CFLAGS) $(FreeRTOSDir)/Source/tasks.c

queue.o : $(FreeRTOSDir)/Source/queue.c
	$(CC) $(CFLAGS) $(FreeRTOSDir)/Source/queue.c

list.o : $(FreeRTOSDir)/Source/list.c
	$(CC) $(CFLAGS) $(FreeRTOSDir)/Source/list.c

port.o : $(FreeRTOSDir)/Source/portable/GCC/ARM_CM4F/port.c
	$(CC) $(CFLAGS) $(FreeRTOSDir)/Source/portable/GCC/ARM_CM4F/port.c

heap_4.o : $(FreeRTOSDir)/Source/portable/MemMang/heap_4.c
	$(CC) $(CFLAGS) $(FreeRTOSDir)/Source/portable/MemMang/heap_4.c
 
clean :
	del *.o *.d *.elf *.bin *.map

