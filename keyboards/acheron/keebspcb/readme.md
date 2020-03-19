# Acheron Aχξρων 60-SM-S-STM32-MX-HS-WI (codename "KeebsPCB") QMK firmware

<p align="center">
  <img align="middle" src="https://raw.githubusercontent.com/Gondolindrim/acheronLibrary/master/graphics/acheronLong.png"  width="400"> 
</p>

## Introduction

This is the QMK firmware repository for the KeebsPCB, updated until [pre-revision Alpha](https://github.com/Gondolindrim/KeebsPCB/releases/tag/pre-Alpha).

The KeebsPCB is an Open-Hardware guidelines compliant PCB which files can be found at [this link](https://github.com/Gondolindrim/KeebsPCB). Its designer and maintainer is [Gondolindrim](https://github.com/Gondolindrim).

The KeebsPCB is a collaboration between Gondolindrim and MrKeebs; its layouts and features were cherry-picked by MrKeebs and the PCB was designed for him with these chosen features.

As of may 2020, there is no way to buy an KeebsPCB through a vendor or Group Buy; the only possible way is ordering them directly from a manufacturer.

## Layouts

The possible layouts consist of a default ANSI layout with 7U bottom row.

## PCB Documentation

See the [AcheronDocs](https://gondolindrim.github.io/AcheronDocs/keebs/intro.html) page for the KeebsPCB full documentation. You can also check the KiCad PCB files at the [KeebsPCB GitHub repository](https://github.com/Gondolindrim/KeebsPCB).

Before using the files for personal or commercial use, please read the [Acheron Open-Hardware License V1.2](https://gondolindrim.github.io/AcheronDocs/license/license.html) under which the Austin PCB is published.

## How to compile

After setting up your build environment, you can compile the KeebsPCB default keymap by using:

    make acheron/keebspcb:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
