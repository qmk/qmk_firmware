# Dactyl Manuform (6x6) optional 5thumb cluster

Basic guide how to build 6x6 board is in root keyboard dir. This will help you to to create your own board with 6key based cluster with promicro. [For more click here](../readme.md).

If you want to use 5thumb cluster or stm32, you also should read base guide, but please came back here after you finish 😉.

For my build I used stm32f411 black pill. It's pretty cheap board and I highly recommend you to buy one from official distributors, to support board creators. [To buy it, please go into designer site](https://github.com/WeActTC/MiniSTM32F4x1).

I recommend using stm32 boards for this project, because QMK recently added support for [tinyuf2 bootloader](https://github.com/adafruit/tinyuf2). This bootloader is great for cases where you are going to use QMK Configurator and don't want to use any command line interface. This way when you need change keyboard layout, you only need an UF2 file. Setting up board in boot mode will allow you to drag and drop it on to created STM32F flash drive.
![BlackPill Schematic](blackpill_f411/STM32F4x1_PinoutDiagram_RichardBalint.png "Schematic of stm32f4 blackpill")

For case I used 3D models form here. Big thanks to creators.

- [dactyl-manuform-mini-keyboard](https://github.com/l4u/dactyl-manuform-mini-keyboard)
- [dactyl-manuform](https://github.com/carbonfet/dactyl-manuform)
- [Good build guide](https://medium.com/swlh/complete-idiot-guide-for-building-a-dactyl-manuform-keyboard-53454845b065)

## STM32 Usage

My fixes allows for using STM32 with all keymaps located in this dir. Please note that you need to pull down and up B10 pin. I used here 68kohm resistor. Don't use bigger one then 100kohm and lower then 10kohm. Pin you should use for this it B10. [More can be found here](https://beta.docs.qmk.fm/using-qmk/hardware-features/feature_split_keyboard#setting-handedness).

### Features

- any board could be master one, and they can be used separately from each other
- it's using full usart (4 cables), mostly due to some stability and half detection problems
- easy keymaps update -> drag and drop file
- pin used for rows (B12, B13, B14, B15, A8 , A9, A10) and for cols (B1, B0, A7, A6, A5, A4)
