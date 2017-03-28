# Quantum Mechanical Keyboard Firmware

[![Build Status](https://travis-ci.org/qmk/qmk_firmware.svg?branch=master)](https://travis-ci.org/qmk/qmk_firmware) [![Gitter](https://badges.gitter.im/qmk/qmk_firmware.svg)](https://gitter.im/qmk/qmk_firmware?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)

This is a keyboard firmware based on the [tmk_keyboard firmware](http://github.com/tmk/tmk_keyboard) with some useful features for Atmel AVR controllers, and more specifically, the [OLKB product line](http://olkb.com), the [ErgoDox EZ](http://www.ergodox-ez.com) keyboard, and the [Clueboard product line](http://clueboard.co/).

## Official website (currently under construction with the move to the wiki)

For an easy-to-read version of this document and the repository, check out [http://qmk.fm](http://qmk.fm). Nicely formatted keyboard and keymap listings are also available there, along with the ability to download .hex files instead of having to setup a build environment and compile them.

## Included Keyboards

* [Planck](/keyboards/planck/)
* [Preonic](/keyboards/preonic/)
* [Atomic](/keyboards/atomic/)
* [ErgoDox EZ](/keyboards/ergodox/)
* [Clueboard](/keyboards/clueboard/)
* [Cluepad](/keyboards/cluepad/)

The project also includes community support for [lots of other keyboards](/keyboards/).

## Maintainers

QMK is developed and maintained by Jack Humbert of OLKB with contributions from the community, and of course, [Hasu](https://github.com/tmk). This repo used to be a fork of [TMK](https://github.com/tmk/tmk_keyboard), and we are incredibly grateful for his founding contributions to the firmware. We've had to break the fork due to purely technical reasons - it simply became too different over time, and we've had to start refactoring some of the basic bits and pieces. We are huge fans of TMK and Hasu :)

This documentation is edited and maintained by Erez Zukerman of ErgoDox EZ. If you spot any typos or inaccuracies, please [open an issue](https://github.com/qmk/qmk_firmware/issues/new).

The OLKB product firmwares are maintained by [Jack Humbert](https://github.com/jackhumbert), the Ergodox EZ by [Erez Zukerman](https://github.com/ezuk), and the Clueboard by [Zach White](https://github.com/skullydazed).

## Documentation roadmap

This is not a tiny project. While this is the main readme, there are many other files you might want to consult. Here are some points of interest:

* [**The Wiki**](https://github.com/qmk/qmk_firmware/wiki) - the entirety of the readme has been moved here
* The readme for your own keyboard: This is found under `keyboards/<your keyboards's name>/`. So for the ErgoDox EZ, it's [here](keyboards/ergodox/ez/); for the Planck, it's [here](keyboards/planck/) and so on.
* The list of possible keycodes you can use in your keymap is actually spread out in a few different places:
  * [doc/keycode.txt](doc/keycode.txt) - an explanation of those same keycodes.
  * [quantum/quantum_keycodes.h](quantum/quantum_keycodes.h) - this is where the QMK-specific aliases are all set up. Things like the Hyper and Meh key, the Leader key, and all of the other QMK innovations. These are also explained and documented below, but `quantum_keycodes.h` is where they're actually defined.
* The [TMK documentation](doc/TMK_README.md). QMK is based on TMK, and this explains how it works internally.
