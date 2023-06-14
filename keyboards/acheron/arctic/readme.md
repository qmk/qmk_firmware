# Acheron Aχξρων 60-SM-S-STM32-MX-TH-WI (codename "Arctic") QMK firmware

<p align="center">
  <img align="middle" src="https://raw.githubusercontent.com/Gondolindrim/acheronLibrary/master/graphics/acheronLong.png"  width="400"> 
</p>

## Introduction

This is the QMK firmware repository for the ArcticPCB, updated until [pre-revision Alpha](https://github.com/Gondolindrim/ArcticPCBn/releases/tag/pre-Alpha).

The ArcticPCB is an Open-Hardware guidelines compliant PCB which files can be found at [this link](https://github.com/Gondolindrim/ArcticPCB). Its designer and maintainer is [Gondolindrim](https://github.com/Gondolindrim).

The ArcticPCB is a collaboration between Gondolindrim and ArcticFox; its layouts and features were cherry-picked by Fox and the PCb was designed for him with these chosen features.

As of may 2020, there is no way to buy an ArcticPCB through a vendor or GroupBuy; the only possible way is ordering them directly from a manufacturer.

## Layouts

The possible layouts consist of a fixed 7U bottom row, with possibility of using split backspace, split right shift and stepped caps lock. In the pre-revision Alpha, the Fn and 1.75 RShift keys were swapped (the Fn is on the left and the RShift on the right), so keep that in mind.

## PCB Documentation

See the [AcheronDocs](https://gondolindrim.github.io/AcheronDocs/arctic/intro.html) page for the ArcticPCB full documentation. You can also check the KiCad PCB files at the [ArcticPCB GitHub repository](https://github.com/Gondolindrim/ArcticPCB).

Before using the files for personal or commercial use, please read the [Acheron Open-Hardware License V1.2](https://gondolindrim.github.io/AcheronDocs/license/license.html) under which the Arctic PCB is published.

## How to compile

After setting up your build environment, you can compile the Arctic default keymap by using:

    make acheron/arctic:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
