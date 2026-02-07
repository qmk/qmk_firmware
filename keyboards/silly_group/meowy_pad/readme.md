# MeowyPad

![MeowyPad](https://i.imgur.com/placeholder.png)

A cute 3x3 macropad with OLED display, powered by Seeed XIAO RP2040.

* Keyboard Maintainer: [silly group](https://github.com/stwupid)
* Hardware Supported: Seeed XIAO RP2040
* Hardware Availability: Custom build

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb silly_group/meowy_pad -km default

Flashing example for this keyboard:

    qmk flash -kb silly_group/meowy_pad -km via

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Hold the BOOT button on the XIAO RP2040 while plugging in
* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (top left key) and plug in the keyboard
