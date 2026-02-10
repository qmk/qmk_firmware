# Vida Keyboard PCB

Vida PCB from CannonKeys

This folder has files for both the wired hotswap and solderable versions of the Vida PCB

The hotswap version does not have as much layout support as the solderable version (no ISO, no split space)
The hotswap version does not support per key LED backlighting

* Keyboard Maintainer: [Andrew Kannan](https://github.com/awkannan)
* Hardware Supported: RP2040
* Hardware Availability: [CannonKeys](https://cannonkeys.com)


Make example for this keyboard (after setting up your build environment):

    make cannonkeys/vida:hotswap:default
    
Flashing example for this keyboard:

    make cannonkeys/vida:hotswap:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Hold the "BOOTMODE" button on the back of the PCB and briefly press the "RESET" button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
