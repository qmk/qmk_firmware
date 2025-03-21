# IDOBAO ID80v3

![IDOBAO ID80](https://i.imgur.com/977ENjp.png)

A 75% hotswap keyboard from IDOBAO.

## ANSI Support

* Keyboard Maintainer: [Vino Rodrigues](https://github.com/vinorodrigues)
* Hardware Supported: **IDOBAO ID80v3**
* Hardware Availability: [IDOBAO.net](https://idobao.net/search?type=product&q=id80*)

## ANSI Layout

![](https://idobao.github.io/kle/idobao-id80.png)

## Compiling and Flashing

Make example for this keyboard (after setting up your build environment):

    make idobao/id80/v3/ansi:default

Flashing example for this keyboard:

    make idobao/id80/v3/ansi:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.
Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the [Escape] key (the top left key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
