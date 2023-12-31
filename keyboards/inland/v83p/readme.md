# v83p

A customizable 75% encoder keyboard.

* Keyboard Maintainer: [jonylee@hfd](https://github.com/jonylee1986)
* Hardware Supported: v83p
* Hardware Availability: [inland](https://www.microcenter.com/search/search_results.aspx?N=4294961018+4294822437)

Make example for this keyboard (after setting up your build environment):

    make inland/v83p:default

Flashing example for this keyboard:

    make inland/v83p:default:flash
    
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key) and plug in the keyboard
* **Physical BOOT contact**: Short circuit the BOOT contact located below the spacebar of the PCB and plug in the keyboard
