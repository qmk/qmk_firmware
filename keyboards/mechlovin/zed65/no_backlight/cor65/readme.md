# Cor65

![Cor65](https://i.imgur.com/5sJfXDWl.jpeg)

A Cor65 keyboard PCB, base on Zed65.

* Keyboard Maintainer: [Mechlovin' Studio](https://github.com/mechlovin)
* Hardware Supported: Zed65, APM32F103
* Hardware Availability: [GB](https://www.reddit.com/r/mechmarket/comments/xgb5nx/gb_saevus_cor_65_split_xt_keyboard/)

Make example for this keyboard (after setting up your build environment):

    make mechlovin/zed65/no_backlight/cor65:default

Flashing example for this keyboard:

    make mechlovin/zed65/no_backlight/cor65:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 4 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Escape) and plug in the keyboard
* **Bootloader reset**: Hold down the key at (14,0) in the matrix (Backspace) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
