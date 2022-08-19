# Chaos 65

![chaos65](https://i.imgur.com/BbrA6Tvl.jpg)

A 65% gasket mounted keyboard with some nice accents

* Keyboard Maintainer: [kb-elmo](https://github.com/kb-elmo)
* Hardware Supported: Vem Chaos PCB
* Hardware Availability: https://www.thomasltstudio.com/product-page/chaos-65-keyboard

Make example for this keyboard (after setting up your build environment):

    make chaos65:default

Flashing example for this keyboard:

    make chaos65:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard
* **Physical reset button**: Briefly press the button labeled "Reset" on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
