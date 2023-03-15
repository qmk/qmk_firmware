# Kuro 65
<img align="right" width="118" height="207" src="https://i.imgur.com/HEDgTOk.png">
A 65% keyboard with an ISO layout, which fits the TOFU65 case (and similar) by KBDFans.

Keyboard maintainer: [0x544D](https://github.com/0x544D)<br>
Hardware availability: [0x544D/kuro65](https://github.com/0x544D/kuro65)

## Features

- Hot-swappable ISO layout
- Per key RGB LED (south facing)
- VIA compatible
- USB-C connector
- Reset button on the back of the PCB
- Compatible with TOFU65 and similar cases 

## Pictures

![kuro65_pcb](https://i.imgur.com/m5KoeQw.jpg)

![kuro65_case](https://i.imgur.com/jmoACMS.jpg)

## Building the firmware

Make example for this keyboard (after setting up your build environment):

    make kuro/kuro65:default

Flashing example for this keyboard:

    make kuro/kuro65:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard.
* **Physical reset button**: Briefly press the button on the back of the PCB.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
