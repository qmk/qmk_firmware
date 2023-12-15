# Lotus 58 Glow

![lotus58](https://i.imgur.com/WWgpp0Sh.jpeg)

* Lotus 58 Glow is a fully programmable 58-key split, ortho-columnar keyboard with a 4x6 main matrix and 4+1 thumb-keys per hand. Optional support for one OLED screen per hand/side showing information such as active layer, CapsLock/NumLock etc. as well as one Rotary Encoder per hand, with optional placement.

* Keyboard Maintainer: [TweetyDaBird](https://github.com/TweetyDaBird)
* Hardware Supported: *Lotus 58 Glow v1.11 - 1.2x PCB, Pro Micro or pin-compatible*
* Hardware Availability: [Lectronz Store](https://lectronz.com/stores/tweetys-wild-thinking)
* Hardware Design: [GitHub](https://github.com/TweetyDaBird/Lotus58)


#### This keyboard firmware contains three different versions, all for the same PCB/hardware, but depending on your choice of controller/bootloader. 


* promicro - This uses the default Caterina bootloader.
* elite_c - This uses the Atmel-DFU bootloader.
* nanoBoot - A tiny 512 byte bootloader giving far more usable memory for features (can be used on both Elite C and Pro Micro).


Make example for this keyboard (after setting up your build environment):

    make tweetydabird/lotus58/promicro:default

Flashing example for this keyboard:

    make tweetydabird/lotus58/elite_c:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top outer key for each hand as it is plugged in
* **Physical reset**: Briefly short the marked pads on PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if mapped (not in default keymap)
