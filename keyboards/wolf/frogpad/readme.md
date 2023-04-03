# Frog Pad

The following is the QMK Firmware for the Frog Pad PCB.

The PCB features:
* QMK & VIA compatibility
* 2 Encoders

---

* Keyboard Maintainer: [ToastyStoemp](https://github.com/ToastyStoemp)

Make example for this keyboard (after setting up your build environment):

    make wolf/frogpad:default

Flashing example for this keyboard:

    make wolf/frogpad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader Enter the bootloader in 3 ways: 
* **Bootmagic reset**: Hold down the key ESC key and plug in the keyboard (Top Left most switch)
* **Reset Pads**: Briefly short the pads labeled `QK_BOOT` on the back of the PCB
