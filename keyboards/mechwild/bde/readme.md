# BIG DILL EXTENDED

![BIG DILL EXTENDED](https://i.imgur.com/hraQxsRh.png)

A 42 key keyboard.

* Keyboard Maintainer: [Kyle McCreery](https://github.com/kylemccreery)
* Hardware Supported: BDE Rev1 v2.3, BDE Rev2 v1.1
* Hardware Availability: [BIG DILL EXTENDED on MechWild](https://mechwild.com/product/big-dill-extended-bde/)

Make example for this keyboard (after setting up your build environment):

    make mechwild/bde:default

Flashing example for this keyboard:

    make mechwild/bde:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard. This will also clear EEPROM, so it is a good first step if the keyboard is misbehaving.
* **Physical reset**: Press the 6x6mm button on the underside of the keyboard. On Rev1, it is above the Pro Micro; on Rev2, it is below the OLED.
* **Keycode in layout**: Press the key mapped to `QK_BOOT`. In the pre-supplied keymaps it is on the second layer, replacing the R key.

As a Pro Micro-compatible board, the BDE defines `caterina` as its bootloader by default. Many popular Pro Micro alternatives like the Elite-C, Bit-C, Sea-Micro, Puchi-C etc should be flashed with a different bootloader such as `atmel-dfu`.

**If the incorrect bootloader is specified, bootmagic reset and the `QK_BOOT` keycode will not work**.

To avoid this problem, set the correct bootloader in your custom keymap's `rules.mk` file before compiling, or flash using an appropriate target (e.g. `make mechwild/bde:default:dfu`). See [flashing instructions and bootloader information](https://docs.qmk.fm/#/flashing) for more details.
