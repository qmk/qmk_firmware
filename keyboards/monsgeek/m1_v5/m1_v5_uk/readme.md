# M1 V5 VIA

* Keyboard Maintainer: [yangzheng20003](https://github.com/yangzheng20003)
* Hardware Supported: M1 V5 VIA
* Hardware Availability: M1 V5 VIA

Make example for this keyboard (after setting up your build environment):

    make monsgeek/m1_v5/m1_v5_uk/:default
        
Flashing example for this keyboard:

    make monsgeek/m1_v5/m1_v5_uk/:default

To reset the board into bootloader mode, do one of the following:

* Hold the Reset switch mounted on the bottom side of the PCB while connecting the USB cable
* Hold the Escape key while connecting the USB cable (also erases persistent settings)
* Fn+R_Shift+Esc will reset the board to bootloader mode if you have flashed the default QMK keymap

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

