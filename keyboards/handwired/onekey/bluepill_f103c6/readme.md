# STM32F103C6xx Bluepill onekey

* Supported hardware: Bluepill boards with the STM32F103C**6**xx chips

Note that STM32F103C6xx chips have only 32 KiB of flash and 10 KiB of RAM, and the stm32duino bootloader occupies 8 KiB of flash, leaving only 24 KiB for the firmware, therefore the capabilities of this board are severely restricted in comparison to proper Bluepill boards with STM32F103CBxx or STM32F103C8xx chips (128 or 64 KiB of flash and 20 KiB of RAM).  You may need to disable many features in the QMK firmware to bring its compiled size below 24 KiB.  Please avoid designing new keyboards with these MCUs unless you are stuck with some hardware that you already have and don't want to just throw away.

To trigger keypress, short together pins *B0* and *A7*.
