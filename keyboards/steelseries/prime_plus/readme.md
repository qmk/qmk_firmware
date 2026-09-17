# SteelSeries Prime +

![Prime+](https://i.imgur.com/QhNHmwxh.png)

This firmware does not support the dedicated lift off sensor.

Erase with an stlink and flash this [uf2boot bootloader](https://github.com/daskygit/uf2-prime-plus), this is a a one way procedure voiding any warranty so be sure you don't want to use the original manufacturers firmware.

* Keyboard Maintainer: [Dasky](https://github.com/daskygit)
* Hardware Supported: SteelSeries Prime+
* Hardware Availability: https://steelseries.com/gaming-mice/prime-plus

Make example for this keyboard (after setting up your build environment):

    make steelseries/prime_plus:default

Flashing example for this keyboard:

    make steelseries/prime_plus:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down left mouse button and plug in.
* **Bootloader entry**: Hold the underneath button while plugging in.
