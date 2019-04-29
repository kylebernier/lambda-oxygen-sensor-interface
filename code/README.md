# Code

## Code Algorithm

The code controls a STM32L4 microcontroller on a Lambda Oxygen Sensor Interface board.

### Modules Being Used
All modules and their respective GPIO pins can be found in `hw_map.h`
* ADC: ADC1 on channels 8, 11, 12, 16 
* DMA: DMA1 on channel 1
* SPI: SPI2
* DAC: DAC1 on channel 2
* PWM: TIM8 on channel 2, IRQ on channel 1
* UART: USART1

## Build Instructions

### Required Packages
* arm-none-eabi-gcc
* arm-none-eabi-gdb
* arm-none-eabi-binutils
* openOCD

### Recommended Packages
* Visual Studio Code
    * Cortex-Debug Extension

### Compiling
* Run `make`

    or

* Run `Debug STM32L4` debugger in VSCode

### Flashing
* Run `openocd -f openocd.cfg -c "program bin/main.elf verify reset exit"`

    or

* Run `Debug STM32L4` debugger in VSCode

### Debugging
* Use gdb with openOCD

    or

* Run `Debug STM32L4` debugger in VSCode
