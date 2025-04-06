# wilba.tech WT45-H1

![WT45-H1 PCB](https://i.imgur.com/33lWN3p.png)

WT45-H1 is a mostly-base-kit-compatible hotswap 40% keyboard PCB with split left shift and split spacebar options.

Initially designed for the [HIBI CHOPPER](https://hibi.mx/products/chopper)

-   Keyboard Maintainer: [wilba](https://github.com/wilba)
-   Hardware Supported: wilba.tech WT45-H1 (atmega32u4, atmel-dfu)
-   Hardware Availability: [HIBI](https://hibi.mx/products/chopper)

Make example for this keyboard (after setting up your build environment):

    make wilba_tech/wt45_h1:default

Flashing example for this keyboard:

    make wilba_tech/wt45_h1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard. This will also clear EEPROM, so it is a good first step if the keyboard is misbehaving.
* **Physical reset button**: Press the button labeled S1 on the back of the PCB, near the MCU.
* **Keycode in layout**: There is no key mapped to `QK_BOOT` in the pre-created keymaps, but you may assign this key in any keymaps you create.
