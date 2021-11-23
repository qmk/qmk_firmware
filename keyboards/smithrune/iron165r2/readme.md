# Iron 165R2 QMK folder

![Iron165R2](https://i.imgur.com/jPamxKu.jpg)

## Introduction

This is the QMK Firmware repository for the Iron165 Round 2 PCB, a keyboard designed by [Smith and Rune](https://smithrune.com/) and PCB designed by [Gondolindrim](http://github.com/Gondolindrim), who is also the firwmare maintainer.

The Iron 165R2 PCB is a 65% PCB with support for a myriad of alternative layouts, including a 7U bottom row and ISO. It also supports in-switch single-color LEDs and RGB LEDs for underglow light.

As of November 2021, the only way to obtain an Iron165 was through the [Group Buy](https://geekhack.org/index.php?topic=110985) which is already over; extra units are still to be sold.

## How to compile

The 165R2 PCB was prototyped and tested using two microcontrollers: STM32F072 and STM32F411. Most production-run units were manufactured with the latter. 

After checking what PCB you own and setting up your build environment, you can compile the Iron 165R2 default keymap by using one of the options below.

    make smithrune/iron165r2/165r2_f072:default
    make smithrune/iron165r2/165r2_f411:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
