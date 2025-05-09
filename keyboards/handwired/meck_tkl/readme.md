# meck_tkl

![meck_tkl](https://i.imgur.com/eIpQTjQ.jpeg)

A standard tenkeyless keyboard, using STM32 Blackpill.

* Keyboard Maintainer: [Gabriel Kim](https://github.com/gabrielkim13)
* Hardware Supported: Blackpill F401
* Hardware Availability: [Thingiverse: Mechanical Keyboard - MECH - TKL](https://www.thingiverse.com/thing:4225961)

Make example for this keyboard (after setting up your build environment):

    make handwired/meck_tkl:default

Flashing example for this keyboard:

    make handwired/meck_tkl:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

## Wiring instructions

- On Blackpill boards, **avoid** using the following pins, since they will cause either USB enumeration or the DFU bootloader to not work correctly:
  - **USB-related pins:** `PA10`, `PA11`, `PA12`
  - **BOOT1 pin:** `PB2`

Sample wiring:

![wiring](https://i.imgur.com/jIDmsNy.jpg)
