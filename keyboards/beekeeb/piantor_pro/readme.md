# Piantor Pro

![Piantor Pro](https://i.imgur.com/UPRI64ch.jpg)

A 42 key hotswappable keyboard with RP2040.

* Keyboard Maintainer: [beekeeb](https://github.com/beekeeb)
* Hardware Availability: [beekeeb.shop](https://beekeeb.shop)

Make example for this keyboard (after setting up your build environment):

    make beekeeb/piantor_pro:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Flashing

To enter the bootloader mode, disconnect the keyboard from the computer. While holding the BOOT button, connect the keyboard to the computer.

Run `make beekeeb/piantor_pro:default:flash` or copy the compiled uf2 firmware to the USB mass storage device.
