# GMMK3 75% (ANSI)

A keyboard made and sold by Glorious LLC. Equipped with the WestBerry Q95 microcontroller.

* Keyboard Maintainer: [Glorious](TBD)
* Hardware Supported: GMMK V3
* Hardware Availability: [GloriousPCGaming.com](https://www.pcgamingrace.com)

Make example for this keyboard (after setting up your build environment):

    make gmmk/gmmk3/p75/ansi:default

Flashing example for this keyboard:

    make gmmk/gmmk3/p75/ansi:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

The user can enter bootloader mode for the keyboard by holding down `Esc` when the keyboard is unplugged and plugging in the keyboard while this key is held down.

## About this version

This version is based on the version found in Glorious's own repository on [Gitlab](https://gitlab.com/glorious-public/qmk_firmware/-/tree/gmmk3_p75_ansi_iso_wired/keyboards/gmmk), with changes to make it compatible with the latest QMK version and to add missing features (such as changing RGB zone, which is present in Glorious's proprietary firmware and not the QMK version). See the README file of the keymaps for the key bindings for these features.
