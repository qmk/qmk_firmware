# Akko 5075B Plus

![Akko 5075B Plus](https://raw.githubusercontent.com/rijojohn85/qmk_akko_5075Plus/main/docs/5075b_plus.jpg)

A 75% gasket-mount keyboard with a rotary encoder and per-key RGB. This is the wired-USB
configuration; the board's Bluetooth and 2.4GHz modes are handled by a separate radio module and
are not supported.

Note that this is a different PCB to the `akko/5075` sold under a similar name - the matrix pinout
and column count do not match, and the two firmwares are not interchangeable.

* Keyboard Maintainer: [rijojohn85](https://github.com/rijojohn85)
* Hardware Supported: Akko 5075B Plus
* Hardware Availability: [Akko](https://en.akkogear.com/product/5075b-via/)

Make example for this keyboard (after setting up your build environment):

    make akko/5075b_plus:default

Flashing example for this keyboard:

    make akko/5075b_plus:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Set the switch on the underside of the case to the middle (USB) position, then enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key (Escape) and plug in the keyboard
* **Physical reset button**: Short the two pads of `R23`, next to switch position `DW43` beside the MCU, while plugging in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available (`Fn` + `Del` on the default keymap)
