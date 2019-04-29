# Lambda Oxygen Sensor Interface

This repository contains all code, pcb design, and verification scripts performed for the Lambda Oxygen Sensor Interface. This device uses a Bosch LSU 4.9 paired with a Bosch CJ125 to measure the oxygen content of an engine's exhaust. The value output by the device is the lambda value, which is the ratio between the stoichiometric air/fuel ratio and the air/fuel ratio measured by the sensor. The values output are between 0.65 and 1.36 and are proportional to 0 to 5V DC. A serial UART interface also outputs the lambda value, the temperature, and the voltage the sensor is being set to.  

## Repository Structure
- All code for the actual device can be found in the `code` folder.
- All simulations for hardware and software algortihms can be found in the `sim` folder.
- All PCB design files can be found in the `pcb` folder.
- All scripts and data for verifying results can be found in the `verification` folder.

## Reference Documents

* [STM32L476VG Datasheet](https://www.st.com/resource/en/datasheet/stm32l476vg.pdf)
* [STM32L475RC Datasheet](https://www.st.com/resource/en/datasheet/stm32l475rc.pdf)
* [STM32L4xx Reference Manual](https://www.st.com/content/ccc/resource/technical/document/reference_manual/02/35/09/0c/4f/f7/40/03/DM00083560.pdf/files/DM00083560.pdf/jcr:content/translations/en.DM00083560.pdf)
* [STM32L4xx Hal Reference Manual](https://www.st.com/content/ccc/resource/technical/document/user_manual/63/a8/8f/e3/ca/a1/4c/84/DM00173145.pdf/files/DM00173145.pdf/jcr:content/translations/en.DM00173145.pdf)
* [CJ125 Datasheet](http://www.bosch-semiconductors.com/media/automotive_systems_ics/pdf_1/ic_engine_management/bosch_ic_cj125.pdf)
* [LSU 4.9 Datasheet](https://www.ecotrons.com/files/Bosch_LSU49_Tech_Info.pdf)
