# CSTC40

## This keyboard has 3 known hardware revisions, please be sure to flash the correct firmware for your PCB  

A 40% hotswap ortholinear RGB keyboard from KP Republic  

### Revision 1: "daughterboard"  

* STM32F402RCT6 MCU with IS31FL3733 LED driver, using `stm32-dfu` bootloader. Uses a separate daughterboard for USB connection.

* Upon entering bootloader mode QMK Toolbox will display this message:  
`STM32 DFU device connected (WinUSB): STMicroelectronics STM32  BOOTLOADER (0483:DF11:2200)`

### Revision 2: "single pcb"  

* STM32F402RCT6 MCU with IS31FL3733 LED driver, using `stm32-dfu` bootloader. Integrated USB connection.

* Upon entering bootloader mode QMK Toolbox will display this message:  
`STM32 DFU device connected (WinUSB): STMicroelectronics STM32  BOOTLOADER (0483:DF11:2200)`  

### Revision 3: "FXTwink single pcb"  

* STM32F402RCT6 MCU without separate LED driver, using `tinyuf2` bootloader. Integrated USB connection.

* Upon entering bootloader mode the board will appear in your computer's file system as a new USB mass storage device.  
