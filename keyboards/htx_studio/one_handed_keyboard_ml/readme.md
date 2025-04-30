# One-Handed_Keyboard_ML

![左手大键盘](https://imgur.com/QjQSxhP.jpg)

This is a keyboard with a fan-shaped layout and 59 keys.The commonly used buttons are placed near the thumb.

* Keyboard Maintainer：[HTX Studio](https://github.com/htx-studio)
* Hardware Supported：HTX_STUDIO_ONE-HANDEN_KEYBOARD_ML  PCB
* Hardware Availability：[One-Handed-Keyboard](https://github.com/htx-studio/One-Handed-Keyboard/tree/main/Hardware)

## How to compile

Make example for this keyboard (after setting up your build environment):

    `make htx_studio/one_handed_keyboard_ml:default`

Flashing example for this keyboard:

    `make htx_studio/one_handed_keyboard_ml:default:flash`

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Hold the "B" button on the back of the PCB (the one closest to the MCU) and briefly press the "R" button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
