# EQUATOR

![EQUATOR](https://i.imgur.com/0zjj6btl.png)

An ergo 65% keyboard designed in collaboration with ronworks.

* Keyboard Maintainer: [Ramon Imbao](https://github.com/ramonimbao)
* Hardware Supported: STM32F072

Make example for this keyboard (after setting up your build environment):

    make rmi_kb/equator:default

Flashing example for this keyboard:

    make rmi_kb/equator:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Press and hold the button below the right alt and right ctrl keys
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
