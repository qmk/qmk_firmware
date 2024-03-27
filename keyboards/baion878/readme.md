# Baion878

TKL PCB for Gehirn by Baionlenja 

* Keyboard Maintainer: [Liv](https://github.com/ojthetiny)
* Hardware Supported: Baion878 PCB
* Hardware Availability: Pre-Order

Baion878 Comes in 3 layouts:
    
 * 878HSA for ANSI Hotswap
 * 878HSI for ISO Hotwsap
 * 878SL for Universal Solderable


Make example for this keyboard (after setting up your build environment):

    make baion878/hsa:default
    make baion878/hsi:default
    make baion878/sl:default

Flashing example for this keyboard:

    make baion878/hsa:default:flash
    make baion878/hsi:default:flash
    make baion878/sl:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader using one of the following methods:

* **Bootmagic reset**: Hold the ESC key while connecting the USB cable
* **Physical reset button**: Hold the pins labeled 'RESET' for a while to enter bootloader.
* **Keycode in layout**: Press the key mapped to 'QK_BOOT' if it is available