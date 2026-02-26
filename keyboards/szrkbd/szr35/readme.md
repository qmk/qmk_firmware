# SZR35 

![szr35](https://i.ibb.co/vvQPBTF9/szr35.jpg)

*The **SZR35** is a minimalist 36-key split keyboard. It follows the popular 3x5+3 layout and is aimed at users who value ergonomic typing, portability, and open-source firmware flexibility. It ships with Vial-compatible firmware and is built around an STM32 microcontroller.*

* Keyboard Maintainer: [diegorodriguezv](https://github.com/diegorodriguezv)
* Hardware:
  * **Microcontroller:** STM32F401RBT6 (Cortex-M4, 256KB Flash, 64KB RAM)
  * **Backlighting:** Addressable RGB (WS2812 or similar)
  * **Connection:** USB-C on both halves, TRS jack for interconnect
* Hardware Availability:
  * [HardToChooseOne](https://hardtochooseone.com) on [Amazon](https://www.amazon.com/gp/product/B0DD69RGHK).
  * Alternatively sold from other websites under the SZRKBD brand.

Make example for this keyboard (after setting up your build environment):

    make szrkbd/szr35:default

If you want you can use the keymap that came with the keyboard from factory:

    make szrkbd/szr35:factory

You need to flash each half of the keyboard with the same firmware:

    make szrkbd/szr35:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Holding top left key for the left half, top right key for the right half, while plugging in the USB cable.
* **Physical reset button**: Short the reset pads, marked within a white rectangle, while plugging in. Not the ones at the edge opposing the USB connectors but about 2 or 3 centimeters from that edge.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
