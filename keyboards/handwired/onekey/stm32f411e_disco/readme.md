# STM32F411 Discovery kit onekey

Supported Hardware: <https://www.st.com/en/evaluation-tools/32f411ediscovery.html>  

To trigger keypress, short together pins *B4* and *B5*.

## Power
There are 2 main ways to connect the dev board to the host machine:
1. Plug in both mini (st-link) and micro (USB USER) USB sockets
2. Plug in mini USB and connect *5V* to *PA9*

## Bootloader
To get the dev board to enter the dfu bootloader:
1. Add jumper between BOOT0 and VDD
2. Add jumper between PB2 and GND
3. Plug in device
