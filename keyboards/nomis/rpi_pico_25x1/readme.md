# rpi pico 25x1

![rpi-pico-25x1 PCB](https://i.imgur.com/eOIZH3p.png)

Macropad keyboard with 25 keys in a single row/column powered by a Raspberry Pi
Pico. The default keymap is a 25 button joystick.

* Keyboard Maintainer: [Simon Arlott](https://github.com/nomis)
* Hardware Supported: Raspberry Pi Pico
* Hardware Availability: Order/manufacture the [open source PCB](https://github.com/nomis/keyboard-pcb-rpi-pico-25x1)

Make example for this keyboard (after setting up your build environment):

    make nomis/rpi_pico_25x1:default

Flashing example for this keyboard:

    make nomis/rpi_pico_25x1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top key and plug in the keyboard
* **Physical reset button**: Hold the BOOTSEL button on the Raspberry Pi Pico and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
