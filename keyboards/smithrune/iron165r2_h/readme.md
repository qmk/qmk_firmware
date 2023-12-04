# Iron 165R2-H QMK folder

![Iron165R2](https://i.imgur.com/jPamxKuh.jpg)

## Introduction

This is the QMK Firmware repository for the Iron165 Round 2 Hotswap PCB, designed by [Gondolindrim](http://github.com/Gondolindrim), who is also the firwmare maintainer.

The Iron 165R2-H PCB is a hotswap variant of the 65% PCB for the Iron165 keyboard by Smith and Rune.

## How to flash

### Enter bootloader

The DFU state in the bootloader can be accessed in 3 ways:

* **Bootmagic reset**: hold down the Escape key and plug in the keyboard;
* **Physical reset button**: press and hold the button on the back of the PCB for at least five seconds;
* **Keycode in layout**: press the key mapped to `QK_BOOT`; in the default layout, that is top left key ('escape') in layer 1.

### How to compile and flash

The 165R2H PCB was prototyped and tested using two microcontrollers: STM32F072 and STM32F411. Most production-run units were manufactured with the latter. 

After checking what PCB you own and setting up your build environment, you can compile the Iron 165R2 default keymap by using one of the options below.

    make smithrune/iron165r2_h:default

And use dfu-util in the command line or through a GUI like QMK toolbox to upload the firmware to the PCB. To directly flash the PCB after it is put into a DFU state, use:

    make smithrune/iron165r2_h:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## The "runes RGB" feature

The firmware for 165R2 allows the user to control the RGBs on the PCB through limiting their span according to the usage. There are four possible usages:

- "Rune RGBs" where only the RGBs under the SnR rune logo on the 165R2 case are lit up;
![runergbs](https://i.imgur.com/HzpnsdL.jpg)
- "Line RGBs" where only the RGBs on the two alpha cluster rows are lit up;
![linergbs](https://i.imgur.com/A1YThUr.jpg)
- "Luke RGBs" where the line RGBs and D25-D23 are on (to avoid hotspotting on the rune backplate); and
![lukergbs](https://i.imgur.com/PnuuX3F.jpg)
- "All RGBs" where all RGBs are turned on.
![allrgbs](https://i.imgur.com/cX9KnTP.jpg)

In order to use the "rune RGBs" option, you can turn this option on by un-commenting the respective line on the corresponding `config.h` file:
    
    #define RUNE_RGBS

If you want to use the "line RGBs" option, you can un-comment the respective lone on the corresponding `config.h` file:

    #define LINES_RGBS

If you want to use the "luke RGBs" option, you can un-comment the respective lone on the corresponding `config.h` file:

    #define LUKE_RGBS

The options supersede each other in this order. If no option is defined, then the firwmare defaults to the "all RGBs" option.
