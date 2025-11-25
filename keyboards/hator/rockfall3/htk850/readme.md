# Rockfall 3 Wireless
![Rockfall3](https://i.imgur.com/2epEIXa.png)

TKL multimode keyboard

* Keyboard Maintainer: [koosikus](https://github.com/koosikus)
* Hardware Supported: HATOR Rockfall 3 Wireless (HTK850)
* Hardware Availability: [Rockfall 3 Wireless](https://hator.com/keyboards/rockfall-3-mecha-tkl-wireless/)

Make example for this keyboard (after setting up your build environment):

    make hator/rockfall3/htk850:default

Flashing example for this keyboard:

    make hator/rockfall3/htk850:default:flash
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the Hold down the top left key (commonly programmed as *Esc*) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
