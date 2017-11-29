# Quantum Mechanical Keyboard Firmware

## What is QMK Firmware? {#what-is-qmk-firmware}

QMK (*Quantum Mechanical Keyboard*) is an open source community that maintains QMK Firmware, QMK Flasher, qmk.fm, and these docs. QMK Firmware is a keyboard firmware based on the [tmk\_keyboard](http://github.com/tmk/tmk_keyboard) with some useful features for Atmel AVR controllers, and more specifically, the [OLKB product line](http://olkb.com), the [ErgoDox EZ](http://www.ergodox-ez.com) keyboard, and the [Clueboard product line](http://clueboard.co/). It has also been ported to ARM chips using ChibiOS. You can use it to power your own hand-wired or custom keyboard PCB.

## How to get it {#how-to-get-it}

If you plan on contributing a keymap, keyboard, or features to QMK, the easiest thing to do is [fork the repo through Github](https://github.com/qmk/qmk_firmware#fork-destination-box), and clone your repo locally to make your changes, push them, then open a [Pull Request](https://github.com/qmk/qmk_firmware/pulls) from your fork.

Otherwise, you can either download it directly ([zip](https://github.com/qmk/qmk_firmware/zipball/master), [tar](https://github.com/qmk/qmk_firmware/tarball/master)), or clone it via git (`git@github.com:qmk/qmk_firmware.git`), or https (`https://github.com/qmk/qmk_firmware.git`).

## How to compile {#how-to-compile}

Before you are able to compile, you'll need to [install an environment](getting_started_build_tools.md) for AVR or/and ARM development. Once that is complete, you'll use the `make` command to build a keyboard and keymap with the following notation:

    make planck/rev4:default

This would build the `rev4` revision of the `planck` with the `default` keymap. Not all keyboards have revisions (also called subprojects or folders), in which case, it can be omitted:

    make preonic:default

## How to customize {#how-to-customize}

QMK has lots of [features](features.md) to explore, and a good deal of [reference documentation](http://docs.qmk.fm) to dig through. Most features are taken advantage of by modifying your [keymap](keymap.md), and changing the [keycodes](keycodes.md).
