# RURA66

![RURA66](https://github.com/ShinoharaTa/keyboards/blob/master/RURA66/manual/images/IMG_0236.jpg)

これは66キー備えた、シンプルな左右分割型キーボードです。あなたの肩への負担軽減をサポートします。

This is a simple left / right split keyboard with 66 keys. Supports reducing the burden on your shoulders.

* Keyboard Maintainer: [T.Shinohara](https://github.com/ShinoharaTa)
* Hardware Supported:  The RURA PCB, ProMicro supported. Using Cherry MX Profile Switches.
* Hardware Availability: [Booth (Japanese Site)](https://shino3.booth.pm/items/2643797)
* 日本国内ではBoothで入手できます: [Booth (Japanese Site)](https://shino3.booth.pm/items/2643797)

![RURA66-USE](https://github.com/ShinoharaTa/keyboards/blob/master/RURA66/manual/images/IMG_0211.jpg?raw=true)

Make example for this keyboard (after setting up your build environment):

    make rura66:default

Flashing example for this keyboard:

    make rura66:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button on the next to the TRRS jack.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

## Build Guide

[Build guide - Japanese](https://github.com/ShinoharaTa/keyboards/blob/master/RURA66/manual/build_guide_ja.md)  
