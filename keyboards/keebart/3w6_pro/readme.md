# 3w6 Pro

![3w6_pro](https://raw.githubusercontent.com/Keebart/picture-cdn/main/3w6_pro/main.webp)

The Keebart 3w6 Pro is a compact 36-key split keyboard with an integrated
RP2040 microcontroller on each half. The halves communicate over full-duplex
serial, and either half can act as the USB master.

- Keyboard Maintainer: [Keebart](https://github.com/Keebart)
- Hardware Supported: RP2040
- Hardware Availability: [Keebart Shop](https://keebart.com/products/3w6)

Make example for this keyboard (after setting up your build environment):

    make keebart/3w6_pro:default

Flashing example for this keyboard:

    make keebart/3w6_pro:default:flash

See the [build environment setup](https://docs.qmk.fm/newbs_getting_started)
and the [make instructions](https://docs.qmk.fm/getting_started_make_guide) for
more information. Brand new to QMK? Start with our
[Complete Newbs Guide](https://docs.qmk.fm/newbs).

## Bootloader

Each half contains its own RP2040 and must be flashed separately using the
same firmware. Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold the outer key of the top row while connecting
  that half to USB.
* **Physical reset button**: Both BOOT and RESET buttons are accessible
  through the two small holes on the underside of the keyboard. Hold
  **BOOT**, briefly press and release **RESET**, then release **BOOT**.
* **Keycode in layout**: Press the key mapped to `QK_BOOT`, when available
  in the active keymap.
