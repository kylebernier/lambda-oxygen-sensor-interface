TARGET = main

INCDIR = ../inc

OBJS  = $(INCDIR)/startup_$(ARCH).o $(INCDIR)/system_stm32l4xx.o main.o

ARCH = stm32l476xx
ARCH_DEF = STM32L476xx

CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
AS = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy

LINKSCRIPT = $(INCDIR)/linker_script.ld

CFLAGS = -mcpu=cortex-m4 -mthumb -O3 -Wall -I $(INCDIR) -D $(ARCH_DEF)

LDFLAGS = --specs=nosys.specs -Wl,-T$(LINKSCRIPT) -static
               
.PHONY : all flash clean debug

all: $(TARGET) $(TARGET).bin

debug : CFLAGS += -DDEBUG -g -Og
debug : LDFLAGS += -Wl,-Map,$(TARGET).map

debug : all

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(CFLAGS) $(LDFLAGS) $(OBJS) 

$(TARGET).bin: $(TARGET)
	$(OBJCOPY) -Obinary $(TARGET) $(TARGET).bin

flash: $(TARGET).bin
	st-flash write $(TARGET).bin 0x08000000

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).bin $(TARGET).map

