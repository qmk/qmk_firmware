# Devil68 Pro

A 65% keyboard made by Chinese maker, which controlled by an ATMEGA32U4 chipset. The keyboard features per-key RGB, RGB underglow.

* Keyboard Maintainer: [HorrorTroll](https://github.com/HorrorTroll)
* Hardware Supported: ATMEGA32U4
* Hardware Availability: Unknown

Make example for this keyboard (after setting up your build environment):

    make horrortroll/chinese_pcb/devil68_pro:default

Flashing example for this keyboard:

    make horrortroll/chinese_pcb/devil68_pro:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Esc key) and plug in the keyboard
* **Reset by wire**: Using a wire, 1 head to GND hole and other one to Reset pin on MCU
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
