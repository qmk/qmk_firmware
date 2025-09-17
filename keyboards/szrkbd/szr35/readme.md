# SZR35 

![szr35](https://github.com/user-attachments/assets/9b85112a-782f-4a9e-a45f-c03a4d3b69d5)

*The **SZR35** is a minimalist 36-key split keyboard. It follows the popular 3x5+3 layout and is aimed at users who value ergonomic typing, portability, and open-source firmware flexibility. It ships with Vial-compatible firmware and is built around an STM32 microcontroller.*

* Keyboard Maintainer: [diegorodriguezv](https://github.com/diegorodriguezv)
* Hardware:
- **Microcontroller:** STM32F401RBT6 (Cortex-M4, 256KB Flash, 64KB RAM)
- **PCB Color:** Purple
- **Switches:** Leobog Graywood V4 Linear
- **Backlighting:** Addressable RGB (WS2812 or similar)
- **Connection:** USB-C on both halves, TRS jack for interconnect
* Hardware Availability:
- I bought this keyboard in amazon from a seller named HardToChooseOne, [here](https://www.amazon.com/gp/product/B0DD69RGHK). This is their [website](https://hardtochooseone.com). It is also sold from other websites under the SZRKBD brand.

Make example for this keyboard (after setting up your build environment):

    make szrkbd/szr35:default

If you want you can use the keymap that came with the keyboard from factory:

    make szrkbd/szr35:factory

You need to flash each half of the keyboard with the same firmware:

    make szrkbd/szr35:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Each half can enter DFU mode by holding a key while plugging in the USB cable. `Q` for the left, `P` for the right.
* **Physical reset button**: Both halves can also enter bootloader mode by shorting the reset pads while plugging in. Useful if you flash a misbehaving firmware. The reset pads are a pair of pads with holes marked within a white rectangle. Not the ones at the edge oposing the USB connectors but about 2 or 3 centimeters from that edge.
* **Keycode in layout**: Layer 1 + Layer 2 + Q
