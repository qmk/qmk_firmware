# Dolice EC

![Dolice EC](https://i.imgur.com/uvM0G5v.png)

The Dolice is a alice keyboard designed by Lx3 (Linworks) and yuktsi (TGR) and run by KLC. EC Version designed by Cipulot.

* Keyboard Maintainer: [cipulot](https://github.com/cipulot)
* Hardware Supported: Dolice EC
* Hardware availability: Groupbuys. Check the ongoing ones on [the KLC Discord](https://discord.gg/d2A72mGPRB) or [Webshop](https://klc-playground.com/).

Make example for this keyboard (after setting up your build environment):

    make cipulot/ec_dolice:default

Flashing example for this keyboard:

    make cipulot/ec_dolice:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset**: Long short the exposed pads on the top of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
