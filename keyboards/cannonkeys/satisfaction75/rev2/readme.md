# Satisfaction75 - Revision 2

A new revision of the Satisfaction75 PCB.
Layout support has been streamlined.

This PCB was released in late 2023/2024. If you have a Satisfaction75 PCB from before that time, please use the rev1 satisfaction75 PCB.

The revision 2 of the PCB also has "Revision 2" printed on it.

* Keyboard Maintainer: [Andrew Kannan](https://github.com/awkannan)
* Hardware Supported: STM32F072CBT6

Make example for this keyboard (after setting up your build environment):

    make cannonkeys/satisfaction75/rev2:default
    
Flashing example for this keyboard:

    make cannonkeys/satisfaction75/rev2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Toggle the switch on the back of the pcb to "1" and briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
