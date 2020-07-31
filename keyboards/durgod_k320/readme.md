# durgod_k320

This is a standard fixed ANSI TKL from off the shelf Durgod Taurus K320 without Backlight.

* Keyboard Maintainer: [kuenhlee](https://github.com/kuenhlee)
* Hardware Supported: Durgod Taurus K320 board with STM32F070RBT6
* Hardware Availability: https://www.durgod.com/page9?product_id=47&_l=en
                       : 

## Instructions

### Build

Make example for this keyboard (after setting up your build environment):

    make durgod_k320:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

### Flash 

For first Flashing from initial Stock's Firmware

1. Backing up original Firmware Image.
using ST's STSW-STM32080 : https://www.st.com/en/development-tools/stsw-stm32080.html
- Unplug
- Shorting Boot0 to Vdd
- Plug In USB
- Using the DFUseDemo.exe, make a Flash Image's Backup in case you wanted to restore the Keyboard to Stock's Image

2. Using QMK ToolBox (If WinUSB Driver is installed) or to continue using DFuseDemo.exe if STTub30 driver is used.
- Flash the durgod_k320_default.bin

For repeating Flashing
- BootMagic Lite has been enabled with Assigned "Esc" key 
- Unplug USB Cable
- Holding Esc Button 
- Plug in USB Cable, Keyboard should be in ST-Bootloader state


