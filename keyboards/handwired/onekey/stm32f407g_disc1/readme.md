# STM32F407 Discovery kit onekey

Supported Hardware: <https://www.st.com/en/evaluation-tools/stm32f4discovery.html>  

To trigger keypress, short together pins *B4* and *B5*.

## Power
To connect the dev board to the host machine:
1. Plug in both mini (st-link) and micro (USB USER) USB sockets

## Bootloader
To get the dev board to enter the dfu bootloader:
1. Add jumper between BOOT0 and VDD
2. Plug in device
