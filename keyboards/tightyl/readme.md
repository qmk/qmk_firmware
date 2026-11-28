# Tightyl

![Tightyl Layout](https://raw.githubusercontent.com/BillyLjm/Tightyl/master/img/tightyl_layout.png)

This is the 5x6 Dactyl Manuform, but with a more compact 3-key Minidox-esque thumb cluster (and more compact case).

* Keyboard Maintainer: [BillyLjm](https://github.com/BillyLjm)
* Hardware Supported: Handwired; RP2040 & clones
* Hardware Availability: https://github.com/BillyLjm/Tightyl

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb tightyl -km default

Flashing example for this keyboard:

    qmk flash -kb tightyl -km default -bl uf2-split-left
    qmk flash -kb tightyl -km default -bl uf2-split-right

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Press and hold the "boot" button on RP2040 microcontroller while plugging it in.
