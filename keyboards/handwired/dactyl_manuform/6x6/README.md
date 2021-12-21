Dactyl Manuform (6x6) optional 5thumb cluster
======

Basic guide how to build 6x6 board is in root keyboard dir, this will help you to to create your own board with 6key based cluster based on promicro. [For more click here.](../readme.md)

If you want to use 5thumb cluster or use stm32 also read base guide, but please came back here after you finish 😉.

For my build I used stm32f411 black pill. It's pretty cheap board and I highly recommend you to buy one from official distributors, to support board creators. [To buy go into manufacture site.](https://github.com/WeActTC/MiniSTM32F4x1)


I will recommend this, because QMK recently added support for [tinyuf2](https://github.com/adafruit/tinyuf2) and this bootloader is great for cases where you are going to use QMK Configurator without any command line interface.
![BlackPill Schematic](blackpill_f411/STM32F4x1_PinoutDiagram_RichardBalint.png "Schematic of stm32f4 blackpill")

For case I used 3D models form here. Big thanks to creators.
- https://github.com/l4u/dactyl-manuform-mini-keyboard
- https://github.com/carbonfet/dactyl-manuform
- [Good build guide](https://medium.com/swlh/complete-idiot-guide-for-building-a-dactyl-manuform-keyboard-53454845b065)

My fixes allows for using STM32 with all keymaps located in this dir.

# STM32 features

- any board could be master one
- it's using full usart (4 cables), mostly due to some stability and half detection problems
- easy keymaps reupload -> drag and drop file
- pin used for rows (B12, B13, B14, B15, A8 , A9, A10) and for cols (B1, B0, A7, A6, A5, A4)
