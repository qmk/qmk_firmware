# FnRow v1 

A keyboard featuring a single horizontal row of switches in the style of a "function row" layout.

* Keyboard Maintainer: [Dino Fizzotti](https://www.dinofizzotti.com)
* [PCB Schematic and layout](https://github.com/dinofizz/fnrow-pcb)
* [Blog post](https://www.dinofizzotti.com/blog/2021-02-07-fnrow-v1-a-configurable-function-row-layout-mechanical-keyboard/)

##  Features

* USB-C
* USB ESD and overcurrent protection
* Dedicated reset switch to enable DFU mode
* Optional status LED

## Compilation

Make compilation example for this keyboard (after setting up your build environment):

    make dinofizz/fnrow/v1:default

# Flashing

The FnRow features a hardware reset push-button to the left of the USB-C port. To flash new firmware you will need to enter the bootloader mode first. Plug the FnRow in to your computer using a USB cable and press the reset button momentarily. The board will then show up as an STM32 flash bootloader device. You can then use the following command to flash new firmware to the board.
    
    make dinofizz/fnrow/v1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
