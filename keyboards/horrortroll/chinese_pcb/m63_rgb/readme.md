# M63 RGB

Support STM32F072CBU6 keyboard.

* Keyboard Maintainer: [HorrorTroll](https://github.com/HorrorTroll)
* Hardware Supported: STM32F072CBU6

Make example for this keyboard (after setting up your build environment):

    make horrortroll/chinese_pcb/m63_rgb:default

Flashing example for this keyboard:

    make horrortroll/chinese_pcb/m63_rgb:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (3,5) in the matrix (B key) and plug in the keyboard
* **Physical reset button**: Press and hold the button on the back of the PCB, then plug in the keyboard
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
