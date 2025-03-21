# Reverb

![Reverb](https://i.imgur.com/AaDUYjih.png)

A unibody split with SK6803 mini-e per key RGB, GC9A01 display and Raspberry Pi Pico.

* Keyboard Maintainer: [Dasky](https://github.com/daskygit)
* Hardware Supported: Raspberry Pi Pico, GC9A01
* Hardware Availability: https://mechboards.co.uk/products/reverb-kit

Make example for this keyboard (after setting up your build environment):

    make dasky/reverb:default

Flashing example for this keyboard:

    make dasky/reverb:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard
* **Physical boot button**: Hold down the BOOTSEL button on the Raspberry Pi Pico and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
