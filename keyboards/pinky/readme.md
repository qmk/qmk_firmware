# Pinky

A split keyboard with 3 or 4 x7 vertically staggered keys and 4 thumb keys.
An idea is inspired from [crkbd](https://github.com/foostan/crkbd), [Lily58](https://github.com/kata0510/Lily58), [Ergo42](https://github.com/Biacco42/Ergo42) and [Helix](https://github.com/MakotoKurauchi/helix).

* Keyboard Maintainer: [Masayuki Sunahara](https://github.com/tamanishi/) [@tamanishi](https://twitter.com/tamanishi)
* Hardware Supported: [Pinky3 (3rows)](3/) or [Pinky4 (4rows)](4/) PCB, Pro Micro
* Hardware Availability: [Pinky3 PCB & Case Data](https://github.com/tamanishi/Pinky3), [Pinky4 PCB & Case Data](https://github.com/tamanishi/Pinky4)

Make example for this keyboard (after setting up your build environment):

    make pinky/3:default  # for Pinky3
    make pinky/4:default  # for Pinky4

Flashing example for this keyboard:

    make pinky/3:default:flash  # for Pinky3
    make pinky/4:default:flash  # for Pinky4

To reset the board into bootloader mode, double-tap the Reset switch mounted on the PCB.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
