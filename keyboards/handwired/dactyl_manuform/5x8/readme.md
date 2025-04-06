# handwired/dactyl_manuform/5x8

![Dactyl_manuform 5x8](https://i.imgur.com/DtawD9r.jpeg)

* Keyboard Maintainer: [iliorik](https://github.com/iliorik)

I made this keyboard so that the buttons on the right side of the right half would replicate the standard keyboard.
I put macros on the left buttons of the left side keyboard for rec and play keypresses

Make example for this keyboard (after setting up your build environment):

    make handwired/dactyl_manuform/5x8:default

Flashing example for this keyboard:

    make handwired/dactyl_manuform/5x8:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Keycode in layout**: Press the key mapped to `QK_BOOT`
* **Reset pro micro**: Connect RST and GND pins on plate
