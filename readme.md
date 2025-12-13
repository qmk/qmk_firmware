# Quantum Mechanical Keyboard Firmware

[![Current Version](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![Discord](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/qmk)
[![Docs Status](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![GitHub contributors](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![GitHub forks](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

This is a keyboard firmware based on the [tmk\_keyboard firmware](https://github.com/tmk/tmk_keyboard) with some useful features for Atmel AVR and ARM controllers, and more specifically, the [OLKB product line](https://olkb.com), the [ErgoDox EZ](https://ergodox-ez.com) keyboard, and the Clueboard product line.

## 🚨 Forked firmware remarks

**This fork holds keyboards not officially supported by the official QMK tree and have been incorporated by myself from other sources and/or adjusted to compile. Not all keyboards here have been tested and work 100% as the original firmware. Always know what you are doing and have a backup plan in case it doesn't work (know how to but your keyboard in BOOTLOADER mode and have the official firmware to revert).**

Also there might be different revisions of the same keyboard so I can't assure the firmware works for all keyboards of a specific model.

They keyboards that have been incorporated are:

### Tested Keyboards

- Epomaker TH40
- Epomaker Luma40
- Akko Monsgeek M1 V5
- Evoworks EVO80

These are keyboards I own or have been tested and reported back to work. There might be differences to the official firmware in keymaps, sleep times, battery consumption and other factors but the main features should work as the original (wireless, LEDs, etc).

### Untested Keyboards

- Epomaker Tide Alice66
- Epomaker Tide65
- Epomaker Tide75
- Epomaker Galaxy100
- Epomaker Luma84
- Epomaker Tide49
- Chosfox Geonix R2 (still on a PR)

These untested keyboards compile but haven't been tested for all it's functionality so wireless, backlights, RGB or other functions might not work as expected or as the official firmware.

I welcome testers and PRs to have a broad open-source support of them.

## Documentation

* [See the official documentation on docs.qmk.fm](https://docs.qmk.fm)

The docs are powered by [VitePress](https://vitepress.dev/). They are also viewable offline; see [Previewing the Documentation](https://docs.qmk.fm/#/contributing?id=previewing-the-documentation) for more details.

You can request changes by making a fork and opening a [pull request](https://github.com/qmk/qmk_firmware/pulls).

## Supported Keyboards

* [Planck](/keyboards/planck/)
* [Preonic](/keyboards/preonic/)
* [ErgoDox EZ](/keyboards/ergodox_ez/)
* [Clueboard](/keyboards/clueboard/)
* [Cluepad](/keyboards/clueboard/17/)
* [Atreus](/keyboards/atreus/)

The project also includes community support for [lots of other keyboards](/keyboards/).

## Maintainers

QMK is developed and maintained by Jack Humbert of OLKB with contributions from the community, and of course, [Hasu](https://github.com/tmk). The OLKB product firmwares are maintained by [Jack Humbert](https://github.com/jackhumbert), the Ergodox EZ by [ZSA Technology Labs](https://github.com/zsa), the Clueboard by [Zach White](https://github.com/skullydazed), and the Atreus by [Phil Hagelberg](https://github.com/technomancy).

## Official Website

[qmk.fm](https://qmk.fm) is the official website of QMK, where you can find links to this page, the documentation, and the keyboards supported by QMK.
