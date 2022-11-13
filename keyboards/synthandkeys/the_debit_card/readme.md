# synthandkeys/the_debit_card

![synthandkeys/the_debit_card](https://i.imgur.com/8dpEv73.jpeg)

The Debit Card is a 10-key programmable mechanical keyboard that could fit in your wallet. The ultra-thin, ultra-portable macropad is powered by the XIAO RP2040 and can support KMK, QMK, or VIAL open-source keyboard firmware.

* Keyboard Maintainer: [Synth and Keys](https://github.com/Synth-and-Keys)
* Hardware Supported: The Debit Card PCB, Seeed XIAO MCU
* Hardware Availability: https://etsy.me/3UslJQF, https://www.seeedstudio.com/XIAO-RP2040-v1-0-p-5026.html

Make example for this keyboard (after setting up your build environment):

    make synthandkeys/the_debit_card:default

Flashing example for this keyboard:

    make synthandkeys/the_debit_card:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Press the button on the Seeed XIAO microcontroller twice.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
