# Ikeygai Designs Albatross QMK firmware

![ALBT](https://i.imgur.com/3hzbqkGh.jpg)

Albatross is a TKL keyboard made by Ikeygai Designs.

* Keyboard Maintainer: [Gondolindrim](https://github.com/Gondolindrim)
* Hardware Supported: proprietary PCB using STM32F401 MCU
* Hardware Availability: group buy for the Albatross will begin on february of 2024.

## How to flash

### Enter bootloader

The DFU state in the bootloader can be accessed in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (top left key or Escape) and plug in the keyboard
* **Physical reset button**: press the button on the back of the PCB, and hold it for five seconds
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available (Escape key on the default keymap)

## Compile firmware

Albatross supported two PCB versions: hotswap (`albt_h`) and solderable (`albt_s`).

Make example for this keyboard (after setting up your build environment):

    make ikeygai/albatross/<version>:default

To directly flash the PCB after it is put into a DFU state, use

    make ikeygai/albatross/<version>:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
