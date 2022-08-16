# Puca Pad

* Keyboard Maintainer: [Sleepdealer](https://github.com/Sleepdealr)
* Hardware Supported: Puca Pad
* Hardware Availability: [Puca GB](https://ffkeebs.com/collections/puca)

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the encoder) 
* **Physical reset button**: Briefly press the button on the front of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

Make example for this keyboard (after setting up your build environment):

    make ffkeebs/puca:default

Flashing example for this keyboard:

    make ffkeebs/puca:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
