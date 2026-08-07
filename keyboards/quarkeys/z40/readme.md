# Quarkeys Z40 Low Profile Keyboard

![Quarkeys Z40 Pastry](https://raw.githubusercontent.com/noroadsleft/qmk_images/master/keyboards/quarkeys/z40/72b918_ef3d9bc5f32e4b2ba224b0a25bc017f4~mv2.png "Quarkeys Z40 PCB render")

A 40% Bottom mount low-profile & MX switch compatible keyboard.

* Keyboard Maintainer: [TommyZ](https://github.com/tommyamoszhao)
* Hardware Supported: Z40-ACR, Z40-Pastry
* Hardware Availability: [Quarkeys Studio](https://www.quarkeys.com/product-page/z40-extra-pcb)

## Hardware Specs

* Per-key RGBs, layer & Capslock indicators
  * For [RGB Matrix feature](https://docs.qmk.fm/#/feature_rgb_matrix): `RGB_MATRIX_ENABLE = yes`, `RGBLIGHT_ENABLE = no`.
  * For [RGB Light feature](https://docs.qmk.fm/#/feature_rgblight): `RGB_MATRIX_ENABLE = no`, `RGBLIGHT_ENABLE = yes`.

Make example for this keyboard solder version keymap(after setting up your build environment):

    make quarkeys/z40:default

Flashing example for this keyboard:

    make quarkeys/z40:default:flash

**Bootloader:** Press the `QK_BOOT` keycode at ESC position of layer 1.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
