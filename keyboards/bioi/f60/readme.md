# BIOI F60

![f60](https://i.imgur.com/xOcgowIl.jpg)

60% PCB used in the Percent Trio HHKB

* Keyboard Maintainer: [kb-elmo](https://github.com/kb-elmo)
* Hardware Supported: BIOI F60v1.0 PCB
* Hardware Availability: (Ended groupbuy) https://percent.studio/trio-60

Make example for this keyboard (after setting up your build environment):

    make bioi/f60:default

Flashing example for this keyboard:

    make bioi/f60:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

* **Bootmagic reset**: Hold down the top left key (ESC) and plug in the keyboard
* **Physical reset button**: Short the two small pads labeled `RESET` the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
