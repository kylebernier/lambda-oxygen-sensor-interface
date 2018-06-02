# Code

## Code Algorithm

The code controls a STM32L4 microcontroller on a Lambda Oxygen Sensor Interface board.

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
