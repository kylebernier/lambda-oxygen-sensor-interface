# System configuration
CC = arm-none-eabi-gcc
RM=rm -f

ARCH = STM32L476xx
ARCH_LOW = stm32l476xx

# Assembler, Compiler and Linker flags and linker script settings
LINKER_FLAGS=-lm -mthumb -mhard-float -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -Wl,--gc-sections -T$(LINK_SCRIPT) -static -Wl,--start-group -lc -lm -Wl,--end-group -specs=nano.specs -specs=nosys.specs -Wl,-cref "-Wl,-Map=$(BIN_DIR)/FreeRTOS.map" -Wl,--defsym=malloc_getpagesize_P=0x1000
LINK_SCRIPT = linker_script.ld
ASSEMBLER_FLAGS=-c -g -O0 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -mhard-float -specs=nano.specs -D"$(ARCH)" -x assembler-with-cpp $(INCLUDE_FLAGS)
COMPILER_FLAGS=-c -g -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -O0 -Wall -ffunction-sections -fdata-sections -mthumb -mhard-float -specs=nano.specs -D"$(ARCH)" $(INCLUDE_FLAGS)

# Define output directory
OBJECT_DIR = bin
BIN_DIR = $(OBJECT_DIR)
SRC_DIR = src
LIB_DIR = lib

# CMSIS directories
CMSIS_DIR = $(LIB_DIR)/cmsis
CMSIS_DEV_DIR = $(CMSIS_DIR)/device
CMSIS_INC_DIR = $(CMSIS_DIR)/inc
CMSIS_SRC_DIR = $(CMSIS_DIR)/src

# FreeRTOS directories
FREERTOS_DIR = $(LIB_DIR)/freertos
FREERTOS_INC_DIR = $(FREERTOS_DIR)/include
FREERTOS_PRT_DIR = $(FREERTOS_DIR)/portable

# HAL directories
HAL_DIR = $(LIB_DIR)/hal
HAL_INC_DIR = $(HAL_DIR)/inc
HAL_SRC_DIR = $(HAL_DIR)/src

INCLUDE_FLAGS = -I$(SRC_DIR) -I$(CMSIS_DEV_DIR) -I$(CMSIS_INC_DIR) -I$(CMSIS_SRC_DIR) -I$(FREERTOS_DIR) -I$(FREERTOS_INC_DIR) -I$(FREERTOS_PRT_DIR) -I$(HAL_DIR) -I$(HAL_INC_DIR) -I$(HAL_SRC_DIR)

# Define sources
SRC := $(wildcard */*/*/*/*/*/*/*.c) \
	$(wildcard */*/*/*/*/*/*.c) \
	$(wildcard */*/*/*/*/*.c) \
	$(wildcard */*/*/*/*.c) \
	$(wildcard */*/*/*.c) \
	$(wildcard */*/*.c) \
	$(wildcard */*.c)
SRCSASM := 	$(wildcard */*/*/*/*/*/*/*/*.s) \
	$(wildcard */*/*/*/*/*/*/*.s) \
	$(wildcard */*/*/*/*/*/*.s) \
	$(wildcard */*/*/*/*/*.s) \
	$(wildcard */*/*/*/*.s) \
	$(wildcard */*/*/*.s) \
	$(wildcard */*/*.s) \
	$(wildcard */*.s)

# Only compile the target Architecture startup script
SRCSASM := $(filter-out $(wildcard $(CMSIS_SRC_DIR)/startup_*.s), $(SRCSASM))
SRCSASM := $(wildcard $(CMSIS_SRC_DIR)/startup_$(ARCH_LOW).s)

# Define objects
OBJS := $(SRC:%.c=$(OBJECT_DIR)/%.o) $(SRCSASM:%.s=$(OBJECT_DIR)/%.o)
OBJS := $(OBJS:%.S=$(OBJECT_DIR)/%.o)

###############
# Build project
# Major targets
###############
TARGET = main

all: buildelf

buildelf: $(OBJS) 
	$(CC) -o "$(BIN_DIR)/$(TARGET).elf" $(OBJS) $(LINKER_FLAGS)

clean:
	$(RM) $(OBJS)

cleaner:
	$(RM) $(OBJS) "$(BIN_DIR)/$(TARGET).elf" "$(BIN_DIR)/$(TARGET).map"


##################
# Specific targets
##################
$(OBJECT_DIR)/src/main.o: src/main.c
	@mkdir -p $(dir $@) 2> /dev/null
	$(CC) $(COMPILER_FLAGS) src/main.c -o $(OBJECT_DIR)/src/main.o 


##################
# Implicit targets
##################
$(OBJECT_DIR)/%.o: %.c
	@mkdir -p $(dir $@) 2> /dev/null
	$(CC) $(COMPILER_FLAGS) $< -o $@

$(OBJECT_DIR)/%.o: %.s
	@mkdir -p $(dir $@) 2> /dev/null
	$(CC) $(ASSEMBLER_FLAGS) $< -o $@
	
$(OBJECT_DIR)/%.o: %.S
	@mkdir -p $(dir $@) 2> /dev/null
	$(CC) $(ASSEMBLER_FLAGS) $< -o $@
