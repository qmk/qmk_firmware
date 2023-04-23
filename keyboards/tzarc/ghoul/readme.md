# Ghoul

![Ghoul](https://i.imgur.com/T8wp7cEh.jpg)

Planck-like development board for QMK, using SparkFun MicroMod for hot-swap MCU capability.

* Keyboard Maintainer: [tzarc](https://github.com/tzarc)
* Hardware Supported: Ghoul rev1 PCB + MicroMod STM32, MicroMod RP2040
* Hardware Availability: [Open-source](https://github.com/tzarc/ghoul)

Make example for this keyboard (after setting up your build environment):

    make tzarc/ghoul/rev1/stm32:default
    make tzarc/ghoul/rev1/rp2040:default

Flashing example for this keyboard:

    make tzarc/ghoul/rev1/stm32:default:flash
    make tzarc/ghoul/rev1/rp2040:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top-left key (usually Escape) and plug in the keyboard
* **Physical reset button**: Either press all 5 left-most keys on the bottom row, or hold `BOOT` and press `RESET`
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
