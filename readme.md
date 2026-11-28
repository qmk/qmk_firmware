# Quantum Mechanical Keyboard Firmware

[![Current Version](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![Discord](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/qmk)
[![Docs Status](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![GitHub contributors](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![GitHub forks](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

This is a keyboard firmware based on the [tmk\_keyboard firmware](https://github.com/tmk/tmk_keyboard) with some useful features for Atmel AVR and ARM controllers, and more specifically, the [OLKB product line](https://olkb.com), the [ErgoDox EZ](https://ergodox-ez.com) keyboard, and the Clueboard product line.

## Documentation

* [See the official documentation on docs.qmk.fm](https://docs.qmk.fm)

The docs are powered by [VitePress](https://vitepress.dev/). They are also viewable offline; see [Previewing the Documentation](https://docs.qmk.fm/#/contributing?id=previewing-the-documentation) for more details.

You can request changes by making a fork and opening a [pull request](https://github.com/qmk/qmk_firmware/pulls).

## Supported Keyboards

* [Planck rev6 Drop](/keyboards/planck/rev6_drop/)
* [Planck EZ base](/keyboards/zsa/planck_ez/base/)
* [ErgoDox EZ base](/keyboards/ergodox_ez/base/)
* [Keychron Q8 ANSI encoder](/keyboards/keychron/q8/ansi_encoder/)

## Custom Keymaps

This fork includes personal keymaps for the following keyboards:

* Planck rev6 Drop (`planck/rev6_drop`): [keymap and layout notes](/keyboards/planck/keymaps/custom/)
* Planck EZ (`zsa/planck_ez/base`): [keymap and layout notes](/keyboards/zsa/planck_ez/keymaps/custom/)
* ErgoDox EZ (`ergodox_ez/base`): `keyboards/ergodox_ez/keymaps/custom/`
* Keychron Q8 ANSI encoder (`keychron/q8/ansi_encoder`): `keyboards/keychron/q8/ansi_encoder/keymaps/custom/`

The Planck and Planck EZ keymaps use LOWER and RAISE layers, with ADJUST active
when both are held. They provide symbol, number, navigation, media, and
brightness keys, plus shift-sensitive symbol overrides. The Planck EZ also
uses its front indicators for layer status and enables startup audio; the
Planck rev6 Drop uses layer indicators independent of underglow.

The ErgoDox EZ keymap uses the same four-layer arrangement and symbol
overrides. The Keychron Q8 keymap provides Mac and Windows base layers,
transparent function layers, and a volume encoder. The fork also
removes upstream keyboard definitions that are not used in this firmware
checkout.

The Planck rev6 Drop also has the migrated `legacy_default`, `javascript`, and
`writing` keymaps under `keyboards/planck/keymaps/`. Build them by replacing
`custom` in the Planck command below with the desired keymap name.

### Build the custom keymaps

Run these commands from the repository root with the [QMK CLI and build
environment installed](https://docs.qmk.fm/#/newbs_getting_started). Each
command compiles one target:

```sh
qmk compile -kb planck/rev6_drop -km custom
qmk compile -kb zsa/planck_ez/base -km custom
qmk compile -kb ergodox_ez/base -km custom
qmk compile -kb keychron/q8/ansi_encoder -km custom
```

To compile and flash a keyboard, use `qmk flash -kb <keyboard> -km custom`
with the appropriate target from the list above and the keyboard in its
bootloader mode. See the [QMK flashing guide](/docs/flashing.md) for
bootloader-specific instructions. Keymap source and options are under each
target's `keymaps/custom/` directory.

## Maintainers

QMK is developed and maintained by Jack Humbert of OLKB with contributions from the community, and of course, [Hasu](https://github.com/tmk). The OLKB product firmwares are maintained by [Jack Humbert](https://github.com/jackhumbert), the Ergodox EZ by [ZSA Technology Labs](https://github.com/zsa), the Clueboard by [Zach White](https://github.com/skullydazed), and the Atreus by [Phil Hagelberg](https://github.com/technomancy).

## Official Website

[qmk.fm](https://qmk.fm) is the official website of QMK, where you can find links to this page, the documentation, and the keyboards supported by QMK.
