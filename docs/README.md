# Quantum Mechanical Keyboard Firmware

[![Current Version](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![Build Status](https://travis-ci.org/qmk/qmk_firmware.svg?branch=master)](https://travis-ci.org/qmk/qmk_firmware)
[![Discord](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/Uq7gcHh)
[![Docs Status](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![GitHub contributors](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![GitHub forks](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

## What is QMK Firmware?

QMK (*Quantum Mechanical Keyboard*) is an open source community that maintains QMK Firmware, QMK Toolbox, qmk.fm, and these docs. QMK Firmware is a keyboard firmware based on the [tmk\_keyboard](http://github.com/tmk/tmk_keyboard) with some useful features for Atmel AVR controllers, and more specifically, the [OLKB product line](http://olkb.com), the [ErgoDox EZ](http://www.ergodox-ez.com) keyboard, and the [Clueboard product line](http://clueboard.co/). It has also been ported to ARM chips using ChibiOS. You can use it to power your own hand-wired or custom keyboard PCB.

## How to Get It

If you plan on contributing a keymap, keyboard, or features to QMK, the easiest thing to do is [fork the repo through Github](https://github.com/qmk/qmk_firmware#fork-destination-box), and clone your repo locally to make your changes, push them, then open a [Pull Request](https://github.com/qmk/qmk_firmware/pulls) from your fork.

Otherwise, you can clone it directly with `git clone https://github.com/qmk/qmk_firmware`. Do not download the zip or tar files; a git repository is required to download the submodules in order to compile.

## How to Compile

Before you are able to compile, you'll need to [install an environment](getting_started_build_tools.md) for AVR or/and ARM development. Once that is complete, you'll use the `make` command to build a keyboard and keymap with the following notation:

    make planck/rev4:default

This would build the `rev4` revision of the `planck` with the `default` keymap. Not all keyboards have revisions (also called subprojects or folders), in which case, it can be omitted:

    make preonic:default

## How to Customize

QMK has lots of [features](features.md) to explore, and a good deal of [reference documentation](http://docs.qmk.fm) to dig through. Most features are taken advantage of by modifying your [keymap](keymap.md), and changing the [keycodes](keycodes.md).
