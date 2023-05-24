# KBD19x

![kbd19x](https://i.imgur.com/0hWTEnh.jpg)

**Layout possibilities for the KBD19x**

![kbd19x](https://i.imgur.com/pVaR2zY.png)

The KBD19x is a compact-1800 keyboard kit produced by KBDfans, offering a number of layout options.

* Keyboard Maintainer: [jshuf](https://github.com/jshuf), [MechMerlin](https://github.com/mechmerlin)
* Hardware Supported: KBD19x PCB
* Hardware Availability: [~~KBDfans~~](https://kbdfans.com/collections/95-kbd19x/products/kbdfans-kbd19x-pcb), [~~AliExpress~~](https://www.aliexpress.com/item/32835566884.html) (no longer available)

Make example for this keyboard (after setting up your build environment):

    make kbdfans/kbd19x:default

Flashing example for this keyboard:

    make kbdfans/kbd19x:default:flash

## Bootloader

To reset the board into bootloader mode, do one of the following:

* **Bootmagic reset**: Hold the `Esc` key while connecting the USB cable (also erases persistent settings)
* **Keycode in keymap**: Press the key mapped to `RESET` if it is available (`Fn`+`Backspace` by default)

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
