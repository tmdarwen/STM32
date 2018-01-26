## Cross-compilation commands 
CC      = arm-none-eabi-gcc
LD      = arm-none-eabi-gcc
AS      = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

OBJDIR=obj

VPATH = ./source \
        $(STM32CubeDir)/Middlewares/ST/STM32_USB_Host_Library/Core/Src \
        $(STM32CubeDir)/Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src \
        $(STM32CubeDir)/Middlewares/Third_Party/FatFs/src \
        $(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Src \
        $(STM32CubeDir)/Utilities/Log \
        $(STM32CubeDir)/Drivers/BSP/STM32F429I-Discovery \
        $(STM32CubeDir)/Drivers/BSP/Components/ili9341

# Define object files
LOCAL_OBJS = main.o startup_stm32f429xx.o stm32f4xx_it.o system_stm32f4xx.o usbh_diskio_dma.o usbh_conf.o syscalls.o 
USB_OBJS = usbh_core.o usbh_ctlreq.o usbh_ioreq.o usbh_pipes.o usbh_msc.o usbh_msc_bot.o usbh_msc_scsi.o
FATFS_OBJS = diskio.o ff.o ff_gen_drv.o 
HAL_OBJS = stm32f4xx_hal.o stm32f4xx_hal_cortex.o stm32f4xx_hal_dma.o stm32f4xx_hal_dma2d.o stm32f4xx_hal_dma_ex.o \
          stm32f4xx_hal_flash_ex.o stm32f4xx_hal_flash.o stm32f4xx_hal_gpio.o stm32f4xx_hal_hcd.o stm32f4xx_hal_i2c.o \
          stm32f4xx_hal_i2c_ex.o stm32f4xx_hal_ltdc.o stm32f4xx_hal_pwr.o stm32f4xx_hal_pwr_ex.o stm32f4xx_hal_rcc_ex.o \
          stm32f4xx_hal_rcc.o stm32f4xx_hal_sdram.o stm32f4xx_hal_spi.o 
LL_OBJS = stm32f4xx_ll_fmc.o stm32f4xx_ll_usb.o 
BSP_OBJS = ili9341.o stm32f429i_discovery_sdram.o stm32f429i_discovery.o stm32f429i_discovery_lcd.o
UTIL_OBJS = lcd_log.o
OBJECTS = $(addprefix $(OBJDIR)/, $(LOCAL_OBJS) $(USB_OBJS) $(FATFS_OBJS) $(HAL_OBJS) $(LL_OBJS) $(BSP_OBJS) $(UTIL_OBJS))

INCLUDE_PATHS= -I. \
               -I./include \
               -I$(STM32CubeDir)/Drivers/CMSIS/Device/ST/STM32F4xx/Include \
               -I$(STM32CubeDir)/Drivers/CMSIS/Include \
               -I$(STM32CubeDir)/Drivers/STM32F4xx_HAL_Driver/Inc \
               -I$(STM32CubeDir)/Drivers/BSP/Components \
               -I$(STM32CubeDir)/Drivers/BSP/Components/ili9341 \
               -I$(STM32CubeDir)/Drivers/BSP/STM32F429I-Discovery \
               -I$(STM32CubeDir)/Middlewares/ST/STemWin/inc \
               -I$(STM32CubeDir)/Middlewares/ST/STemWin/Config \
               -I$(STM32CubeDir)/Middlewares/Third_Party/FatFs/src \
               -I$(STM32CubeDir)/Middlewares/ST/STM32_USB_Host_Library/Core/Inc \
               -I$(STM32CubeDir)/Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc

LIB_PATHS = -L$(STM32CubeDir)/Middlewares/ST/STemWin/Lib/ 

CFLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F429xx -DSTM32F429I-DISCO \
         -DDEBUG -DSTM32F429xx -DUSE_STM32F429I_DISCO -DUSE_HAL_DRIVER -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP $(INCLUDE_PATHS)

LFLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -T"source/STM32F429ZITx_FLASH.ld" -specs=nosys.specs -specs=nano.specs -Wl,-Map=output.map -Wl,--gc-sections ${LIB_PATHS}

all: dirs main.elf main.bin size 

main.elf : $(OBJECTS) 
	$(LD) $(LFLAGS) -o main.elf $(OBJECTS) -l:STemWin540_CM4_GCC.a

main.bin: main.elf
	$(OBJCOPY) -O binary "main.elf" "main.bin"

size: main.elf
	$(SIZE) $< 

# Apparently $< expands to the VPATH
$(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) -o $@ $<

# Apparently $< expands to the VPATH
$(OBJDIR)/%.o : %.s
	$(CC) $(CFLAGS) -o $@ $<

dirs:
	 -@ if NOT EXIST "obj" mkdir "obj"

clean :
	del *.o *.d *.elf *.bin *.map
	del $(OBJDIR)\*.o
	del $(OBJDIR)\*.d
	rmdir $(OBJDIR)
