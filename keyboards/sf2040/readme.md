# sf2040

![sf2040 Image](https://i.imgur.com/DZ9N17ph.png)

The sf2040 is a mechanical 76-key keyboard based on the [RP2040](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf) microcontroller from Raspberry Pi.

* Keyboard Maintainer: [strayfade](https://github.com/strayfade)
* Hardware Availability: https://github.com/strayfade/sf2040

Make example for this keyboard (after setting up your build environment):

    make sf2040:default

Flashing example for this keyboard:

    make sf2040:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

**Bootmagic reset**: To enter the bootloader, hold down the key at (0,0) in the matrix (the top left key or Escape) and plug in the keyboard.
