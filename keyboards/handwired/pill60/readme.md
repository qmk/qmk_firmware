# Pill60

![Pill60](https://i.imgur.com/7WmHa6ml.png)

A 60% open source keyboard with rotary encoder, OLED screen, and Hotswap socket, using STM32F103 / Blue Pill.

* Keyboard Maintainer: [Ikta](https://github.com/IktaS)#8871 (Discord)
* Hardware Supported: Pill60 PCB, STM32F103C8T6
* Hardware Availability: [github](https://github.com/IktaS/Pill60)

Step by step guide on how to install a bootloader if your bluepill don't have one :  
1. Download [this bootloader]( https://github.com/rogerclarkmelbourne/STM32duino-bootloader/blob/master/bootloader_only_binaries/generic_boot20_pc13_fastboot.bin)
2. Flash Using FTDI Serial to USB converter or an ST-Link, as in [this](https://www.youtube.com/watch?v=Myon8H111PQ) video, but replacing the bootloader file
3. Put Boot 1 to 1, then reset the board, if you're using the same bootloader, the LED should blink
4. Flash your .bin file using dfu-util
5. Put Boot 1 back to 0, then reset again

Building Guide :
- Use `qmk compile -kb handwired/pill60 -km default` to compile default keymap and using STM32F103 as an MCU
- Use `qmk compile -kb handwired/pill60/blackpill_f401 -km default` to compile default keymap and using STM32F401 as an MCU
- Use `qmk compile -kb handwired/pill60/blackpill_f411 -km default` to compile default keymap and using STM32F411 as an MCU

## Warning: currently tested MCU is STM32F103, I am still waiting for f401 and f411 to arrive

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
