# subrezon/la_nc

![subrezon/la_nc](https://i.imgur.com/xYDcTtsh.jpg)

Loosely based on the Planck keyboard, la_nc aims to deliver a lightly split, ortho typing experience in a similar footprint, as well as an easy build process.

* Keyboard Maintainer: [Daniel Osipishin](https://github.com/subrezon)
* Hardware Supported: la_nc PCB, with an atmega32u4-based ProMicro compatible controller board
* Hardware Availability: https://github.com/subrezon/la_nc

Make example for this keyboard (after setting up your build environment):

    make subrezon/la_nc:default

Flashing example for this keyboard:

    make subrezon/la_nc:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
