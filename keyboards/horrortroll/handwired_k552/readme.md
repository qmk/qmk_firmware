# Handwired K552 Kumara

![K552](https://i.imgur.com/XpNmJpBh.png)

A handwired K552 Kumara. Built using STM32F103RCT6 Mini

* Keyboard Maintainer: [HorrorTroll](https://github.com/HorrorTroll)
* Hardware Supported: STM32F103RCT6

Make example for this keyboard (after setting up your build environment):

    make horrortroll/handwired_k552:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (4,6) in the matrix (B key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
