# Acheron Aχξρων 1800CP-SM-S-STM32-MX-TH-WI (codename "Austin") QMK firmware

<p align="center">
  <img align="middle" src="https://raw.githubusercontent.com/Gondolindrim/acheronLibrary/master/graphics/acheronLong.png"  width="400"> 
</p>

## Introduction

This is the QMK firmware repository for the Austin, updated until [revision Alpha](https://github.com/Gondolindrim/Austin/releases/tag/Alpha).

The AustinPCB is an Open-Hardware guidelines compliant PCB which files can be found at [this link](https://github.com/Gondolindrim/Austin). Its designer and maintainer is [Gondolindrim](https://github.com/Gondolindrim).

The Austin keyboard is a collaboration between Gondolindrim, DriftingBunnies from DriftMechanics and PheonixStarr from Nightingale Studios.

See the [IC page](https://geekhack.org/index.php?topic=100883) and the [GB page](https://geekhack.org/index.php?topic=102542) for further information. The GB was the only known way to obtain an Austin from the official vendor.

## PCB Documentation

See the [AcheronDocs](https://gondolindrim.github.io/AcheronDocs/austin/intro.html) page for the AustinPCB full documentation. You can also check the KiCad PCB files at the [Austin GitHub repository](https://github.com/Gondolindrim/Austin).

Before using the files for personal or commercial use, please read the [Acheron Open-Hardware License V1.2](https://gondolindrim.github.io/AcheronDocs/license/license.html) under which the Austin PCB is published.

## How to compile

After setting up your build environment, you can compile the Austin default keymap by using:

    make acheron/austin:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).