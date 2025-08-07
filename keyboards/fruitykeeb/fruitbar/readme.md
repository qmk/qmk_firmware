# Fruitbar

![Fruitbar](https://i.imgur.com/MlJudRrh.jpeg)

A budget-oriented 40% with base kit compatibility. Perfect for those who have always wanted to try a 40% but worried about the lack of punctuation and arrow keys.

* Keyboard Maintainer: [The QMK Community](https://github.com/qmk)
* Hardware Supported:
  * Fruitbar PCB R1 (atmega32u4)
    * If the keyboard was built with an Elite-C, use the `fruitykeeb/fruitbar/r1/elite_c` firmware for RGB and encoder support.
  * Fruitbar PCB R2 (RP2040, rp2040)
* Hardware Availability:
  * R1 Group Buy took place between 2021-10-01 and 2021-10-24 on [FruityKeeb](https://fruitykeeb.xyz/).
  * R2 Group Buy took place between 2023-02-01 1400 UTC and 2023-03-04 0359 UTC on [P3DStore](https://p3dstore.com)(US), [42keebs.eu](https://42keebs.eu)(EU), [CustomKBD](https://customkbd.com)(AU).

Make example for this keyboard (after setting up your build environment):

    make fruitykeeb/fruitbar/r1:default
    make fruitykeeb/fruitbar/r2:default

Flashing example for this keyboard:

    make fruitykeeb/fruitbar/r1:default:flash
    make fruitykeeb/fruitbar/r2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard. This will also clear EEPROM/emulated EEPROM, so it is a good first step if the keyboard is misbehaving.
* **Physical reset**:
  - R1: Short the RST and GND pins on the Pro Micro.
  - R2: While holding down the `Boot` button, press the `Reset` button.
* **Keycode in layout**: Press the key mapped to `QK_BOOT`. In the default keymap it is on the second layer, replacing the Left Control key in the bottom left.
