# Devil68 Pro

Support Atmega32u4 keyboard.

* Keyboard Maintainer: [HorrorTroll](https://github.com/HorrorTroll)
* Hardware Supported: Atmega32u4

Make example for this keyboard (after setting up your build environment):

    make horrortroll/chinese_pcb/devil68_pro:default

Flashing example for this keyboard:

    make horrortroll/chinese_pcb/devil68_pro:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (3,6) in the matrix (B key) and plug in the keyboard
* **Reset by wire**: Using a wire, 1 head to GND hole and other one to Reset pin on MCU
* **Keycode in layout**: Press the key mapped to RESET if it is available
