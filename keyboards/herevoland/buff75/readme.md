# Buff75

![Buff75](https://imgur.com/pQfzIZr.jpg)
An 75%/TenKeyLess sized keyboard with 1 RGB.

* Keyboard Maintainer: [HereVoLand](https://github.com/Vem-596)
* Hardware Supported: buff75
* Hardware Availability: [BUFF Customer-Keyboard](https://shop107132374.taobao.com)

Make example for this keyboard (after setting up your build environment):

    make herevoland/buff75:default
    
Flashing example for this keyboard:

    make herevoland/buff75:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

- **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key which is Escape in this keyboard) and plug in the keyboard
- **Keycode in layout**: Press the key mapped to `QK_BOOT` 
