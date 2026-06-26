# OGR R2 - 65XT Variant - for AKB

This folder contains firmware for both the Solderable and Hotswap version of the OGR R2 65XT PCB

The hotswap PCB has reduced layout support (no ISO)

* Keyboard Maintainer: [Andrew Kannan](https://github.com/awkannan)
* Hardware Supported: STM32F072CBT6

Make example for this keyboard (after setting up your build environment):

    make cannonkeys/ogr_65xt/hotswap:default
    make cannonkeys/ogr_65xt/solderable:default
    
Flashing example for this keyboard:

    make cannonkeys/ogr_65xt/hotswap:default:flash
    make cannonkeys/ogr_65xt/solderable:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Toggle the switch on the back of the pcb to "BL" and briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
