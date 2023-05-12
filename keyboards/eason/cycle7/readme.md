# cycle7

* A customizable hotswap 60% keyboard.

* Keyboard Maintainer: [EASON](https://github.com/EasonQian1)
* Hardware Supported: cycle7
* Hardware Availability: [EASON](https://github.com/EasonQian1)

Make example for this keyboard (after setting up your build environment):

    make eason/cycle7:default

Flashing example for this keyboard:

    make eason/cycle7:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader Enter the bootloader in 3 ways:
* **Bootmagic reset**: Hold down ESC in the keyboard then replug
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT`
