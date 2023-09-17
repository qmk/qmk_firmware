# The Teleport TKL

* Keyboard Maintainer: [ebastler](https://github.com/ebastler)
* Hardware Supported: The Teleport TKL PCB, Rev 1
* Hardware Availability: [The Teleport](https://www.theteleport.de/)

Make example for this keyboard (after setting up your build environment):

    make teleport/tkl:default

Flashing example for this keyboard:

    make teleport/tkl:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Escape) and plug in the keyboard
* **Physical reset**: Short reset pads on ISP header (the two upper-most one, closest to the `ISP` label)
