# Obi

![obi](https://i.imgur.com/btQPol1h.png)

A 40% keyboard inspired by the TMOv2 and Nightmare boards.

# General info

* Keyboard Maintainer: [Arturo Avila](https://github.com/ADPenrose)
* Hardware Supported: Obi v1 PCB
* Hardware Availability: [Arturo Avila](https://github.com/ADPenrose)

Make example for this keyboard (after setting up your build environment):

    make adpenrose/obi:default

Flashing example for this keyboard:

    make adpenrose/obi:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
