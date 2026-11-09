# MNT Reform USB Keyboard 4.0 (Standalone)

![MNT Reform Keyboard 4.0](https://shop.mntre.com/spree/products/500/large/kb4-black-overview.jpg?1725443064)

Standalone USB firmware for the RP2040-based MNT Reform Keyboard 4.0:
80 keys, per-key RGB Matrix backlight and an OLED lighting legend.

* Keyboard Maintainer: [Andreas Hirschauer](https://github.com/JohnnyLeone)
* Hardware Supported: MNT Reform Keyboard 4.0 RP2040 PCB, standalone USB use
* Hardware Availability: [MNT Research Shop](https://shop.mntre.com/products/mnt-reform-keyboard-40)
* Hardware Sources: [PCB](https://source.mnt.re/reform/reform/-/tree/master/reform2-keyboard4-pcb), [original firmware](https://source.mnt.re/reform/reform/-/tree/master/reform2-keyboard4-fw)

Make example for this keyboard (after setting up your build environment):

    make mntre_v4:default

Flashing example for this keyboard:

    make mntre_v4:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in any of these ways:

* **Bootmagic reset**: hold Esc (top left) while plugging in the keyboard
* **Keycode in layout**: Hyper + R (`QK_BOOT`), or Circle + X
* **Physical reset**: double-tap the RP2040 reset
* **Hardware recovery**: set the `PROG` DIP switch to `ON`, then press the
  adjacent `RESET` button. Return `PROG` to `OFF` before rebooting into the
  firmware.

## Backlight

Four static effects are available: solid colour, Alphas/Mods and the two
linear gradients. Hold Circle to show the lighting controls on the OLED.
