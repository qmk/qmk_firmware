# Quantum Mechanical Keyboard Firmware - chrislewisdev fork

## Typing Speed -> RGB Animation Control

This fork of qmk_firmware contains the code I whipped up to make your keyboard's RGB animation speed match your typing speed. As of writing, this is a "first draft" version, aka the simplest implementation I could think of with the quickest/hackiest code. Beware hard-coding :)

Regardless, I'm happy to share the code and discuss improvements with anyone who'd like to contribute. I'll do my best to facilitate it in my spare time.

## Getting Started

My entire change amounts to several lines in `quantum.h`, `quantum.c` and `rgblight.c`. To see the details it's probably easiest if you look at [this commit](https://github.com/chrislewisdev/qmk_firmware/commit/2d3fbc5d0ad70309ede5cdeb9cf84380fd69baae) which contains all the changes.

I've left a couple of "Improvement:" comments around the code to indicate what I think would make it better or more "production"-ready. These could be good places to start for anyone interested in contributing.

To test it, I've just been using my DZ60 keyboard, building the firmware with `make dz60:default` and flashing with qmk_toolbox. If you're not familiar with how to do that, it's probably best you consult the [QMK documentation](https://docs.qmk.fm/#/).

Below is the original QMK readme:

# QMK

[![Current Version](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![Build Status](https://travis-ci.org/qmk/qmk_firmware.svg?branch=master)](https://travis-ci.org/qmk/qmk_firmware)
[![Discord](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/Uq7gcHh)
[![Docs Status](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![GitHub contributors](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![GitHub forks](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

This is a keyboard firmware based on the [tmk\_keyboard firmware](http://github.com/tmk/tmk_keyboard) with some useful features for Atmel AVR and ARM controllers, and more specifically, the [OLKB product line](https://olkb.com), the [ErgoDox EZ](http://www.ergodox-ez.com) keyboard, and the [Clueboard product line](http://clueboard.co/).

## Documentation

* [See the official documentation on docs.qmk.fm](https://docs.qmk.fm)

The docs are hosted on [Gitbook](https://www.gitbook.com/book/qmk/firmware/details) and [GitHub](/docs/) (they are synced). You can request changes by making a fork and [pull request](https://github.com/qmk/qmk_firmware/pulls), or by clicking the "suggest an edit" link on any page of the docs.

## Supported Keyboards

* [Planck](/keyboards/planck/)
* [Preonic](/keyboards/preonic/)
* [ErgoDox EZ](/keyboards/ergodox_ez/)
* [Clueboard](/keyboards/clueboard/)
* [Cluepad](/keyboards/clueboard/17/)
* [Atreus](/keyboards/atreus/)

The project also includes community support for [lots of other keyboards](/keyboards/).

## Maintainers

QMK is developed and maintained by Jack Humbert of OLKB with contributions from the community, and of course, [Hasu](https://github.com/tmk). The OLKB product firmwares are maintained by [Jack Humbert](https://github.com/jackhumbert), the Ergodox EZ by [Erez Zukerman](https://github.com/ezuk), the Clueboard by [Zach White](https://github.com/skullydazed), and the Atreus by [Phil Hagelberg](https://github.com/technomancy).

## Official website

[http://qmk.fm](http://qmk.fm) is the official website of QMK, where you can find links to this page, the documentation, and the keyboards supported by QMK.
