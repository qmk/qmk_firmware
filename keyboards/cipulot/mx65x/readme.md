# MX65X

A 65% solder and hotswap PCB.

Solder

![MX65X Solder](https://i.imgur.com/M2lyPuo.png)

Hotswap

![MX65X Hotswap](https://i.imgur.com/18DnNrw.png)


* Keyboard Maintainer: [cipulot](https://github.com/cipulot)
* Hardware Supported: MX65X Solder and Hotswap
* Hardware Availability: [Clever Keebs](https://cleverkeebs.com)

Make example for this keyboard (after setting up your build environment):

    make cipulot/mx65x/solder:default
    make cipulot/mx65x/hotswap:default

Flashing example for this keyboard:

    make cipulot/mx65x/solder:default:flash
    make cipulot/mx65x/hotswap:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is configured.
* **Physical reset button**: Long press the reset button soldered on the PCB.
* **Bootmagic reset**: Hold down the top left key and plug in the controller.
