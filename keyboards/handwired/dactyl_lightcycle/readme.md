# Dactyl Lightcycle

![TopElev](https://i.imgur.com/MwPhTrCh.jpg)

A handwired, split bodied, concave key-well, columnar keyboard.  
The *Dactyl Lightcycle* is a variation of the [Dactyl](/keyboards/handwired/dactyl/) keyboard, its differences are:
1. Top (number) row removed
2. Five key thumb cluster; one less than the *Dactyl's* six

This modernised rendition of the *Dactyl Lightcycle* requires two Pro Micro controllers, rather than the *Dactyl's* original implementation of a micro controller and I/O expander.

* Keyboard Maintainer: [Matt Adereth](https://github.com/adereth/)
* Hardware Supported: 2x Pro Micro micro controller, or clone of
* Hardware Availability: Case files available on [GitHub](https://github.com/adereth/dactyl-keyboard), file names beginning "lightcycle" apply

Make example for this keyboard (after setting up your build environment):

    make handwired/dactyl_lightcycle:default

Flashing example for this keyboard:

    make handwired/dactyl_lightcycle:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in keymap**: Press the key mapped to `QK_BOOT` if it is available

## QMK Layouts

The following [community layouts](/layouts/) are supported:
| Layout | Diagram |
| :---: | :---: |
| Split_3x6_3 | ![split_3x6_3](https://i.imgur.com/xBVDsqE.jpg) |
| Split_3x5_3 | ![split_3x5_3](https://i.imgur.com/nc0dbH1.jpg) |
