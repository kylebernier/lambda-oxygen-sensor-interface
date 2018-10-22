# @file Makefile
# @author Kyle Bernier and Daeghan Elkin
# @date 2018 May 27
#
# @brief Makefile to compile STM32L4 project with dependencies


# System configuration
CC = arm-none-eabi-gcc
RM = rm -f
MKDIR = mkdir -p

# Hardware architecture
ARCH = STM32L475xx
ARCH_LOW = stm32l475xx

# Assembler, Compiler and Linker flags and linker script settings
LINKER_FLAGS = -lm -mthumb -mhard-float -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -Wl,--gc-sections -T$(LINK_SCRIPT) -static -Wl,--start-group -lc -lm -Wl,--end-group -specs=nano.specs -specs=nosys.specs
LINK_SCRIPT = linker_script.ld
ASSEMBLER_FLAGS = -c -g -O0 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -mhard-float -specs=nano.specs -D"$(ARCH)" -x assembler-with-cpp $(INCLUDE_FLAGS)
COMPILER_FLAGS = -c -g -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -O0 -Wall -ffunction-sections -fdata-sections -mthumb -mhard-float -specs=nano.specs -D"$(ARCH)" $(INCLUDE_FLAGS)

# Define directories
BIN_DIR = bin
SRC_DIR = src
LIB_DIR = lib

# CMSIS directories
CMSIS_DIR = $(LIB_DIR)/cmsis
CMSIS_DEV_DIR = $(CMSIS_DIR)/device
CMSIS_INC_DIR = $(CMSIS_DIR)/inc
CMSIS_SRC_DIR = $(CMSIS_DIR)/src

# FreeRTOS directories
#FREERTOS_DIR = $(LIB_DIR)/freertos
#FREERTOS_INC_DIR = $(FREERTOS_DIR)/include
#FREERTOS_PRT_DIR = $(FREERTOS_DIR)/portable

# HAL directories
HAL_DIR = $(LIB_DIR)/hal
HAL_INC_DIR = $(HAL_DIR)/inc
HAL_SRC_DIR = $(HAL_DIR)/src
HAL_SRC_LEG_DIR = $(HAL_SRC_DIR)/Legacy

# Define include flags
INCLUDE_FLAGS = -I$(SRC_DIR) -I$(CMSIS_DEV_DIR) -I$(CMSIS_INC_DIR) -I$(CMSIS_SRC_DIR) -I$(FREERTOS_DIR) -I$(FREERTOS_INC_DIR) -I$(FREERTOS_PRT_DIR) -I$(HAL_DIR) -I$(HAL_INC_DIR) -I$(HAL_SRC_DIR)

# Define sources
SRCS := $(wildcard $(HAL_SRC_DIR)/*.c) \
	$(wildcard $(HAL_SRC_LEG_DIR)/*.c) \
	$(wildcard $(SRC_DIR)/*.c)
SRCSASM := $(CMSIS_SRC_DIR)/startup_$(ARCH_LOW).s

# Define objects
OBJS := $(SRCSASM:%.s=$(BIN_DIR)/%.o) $(SRCS:%.c=$(BIN_DIR)/%.o)

# Define the target file
TARGET = $(BIN_DIR)/main

all: $(TARGET)

# Link the objects into the target
$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LINKER_FLAGS)

# Compile c files
$(BIN_DIR)/%.o: %.c
	$(MKDIR) -p $(dir $@) 2> /dev/null
	$(CC) $(COMPILER_FLAGS) $< -o $@

# Compile assembly files
$(BIN_DIR)/%.o: %.s
	$(MKDIR) -p $(dir $@) 2> /dev/null
	$(CC) $(ASSEMBLER_FLAGS) $< -o $@

# Remove only src directory object files
clean:
	$(RM) $(wildcard $(BIN_DIR)/$(SRC_DIR)/*.o)

# Remove all object files and the target
cleaner:
	$(RM) $(OBJS) $(TARGET)
