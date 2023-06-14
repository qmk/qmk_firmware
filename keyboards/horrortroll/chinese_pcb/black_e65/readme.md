# Black E6.5

A Exclusive E6.5 clone keyboard made by Chinese maker, which controlled by an ATMEGA32U4 chipset. The keyboard features per-key backlight, RGB underglow.

* Keyboard Maintainer: [HorrorTroll](https://github.com/HorrorTroll)
* Hardware Supported: ATMEGA32U4
* Hardware Availability: Unknown

Make example for this keyboard (after setting up your build environment):

    make horrortroll/chinese_pcb/black_e65:default

Flashing example for this keyboard:

    make horrortroll/chinese_pcb/black_e65:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Esc key) and plug in the keyboard
* **Physical reset button**: Press and hold the button on the back of the PCB, then plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
