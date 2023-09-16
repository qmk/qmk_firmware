# Alish40

![Alish40 in black](https://i.imgur.com/h9lklc9l.jpg)

A budget-friendly 40% Alice*ish* keyboard with base kit support and styl*ish* silkscreen art.

* Keyboard Maintainer: [Reed](https://github.com/NamesReed), [Kyle McCreery](https://github.com/kylemccreery)
* Hardware Supported: Alish40 v1.3
* Hardware Availability: [Alish40, fulfilled by MechWild](https://mechwild.com/product/alish/)

Make example for this keyboard (after setting up your build environment):

    make reedskeebs/alish40:default

Flashing example for this keyboard:

    make reedskeebs/alish40:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard. This will also clear EEPROM, so it is a good first step if the keyboard is misbehaving.
* **Physical reset**: Press the 6x6mm button below the "Alish 40" label, on the underside of the PCB. You may also use your Pro Micro's built-in reset mechanism if that is easier.
* **Keycode in layout**: There is no key mapped to `QK_BOOT` in the pre-created keymaps, but you may assign this key in any keymaps you create.

As a Pro Micro-compatible board, the Alish40 uses `caterina` as its bootloader by default. Many popular Pro Micro alternatives like the Elite-C, Bit-C, Sea-Micro, Puchi-C etc should be flashed with a different bootloader such as `atmel-dfu`.

**If the incorrect bootloader is specified, bootmagic reset and the `QK_BOOT` keycode will not work**.

To avoid this problem, set the correct bootloader in your custom keymap's `rules.mk` file before compiling, or flash using an appropriate target (e.g. `make reedskeebs/alish40:default:dfu`). See [flashing instructions and bootloader information](https://docs.qmk.fm/#/flashing) for more details.
