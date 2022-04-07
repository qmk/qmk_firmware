# IDOBAO ID67

![id67](https://i.imgur.com/9roQ4Mih.jpeg)

A 65% hotswap keyboard from IDOBAO.

## ANSI support:

* Keyboard Maintainer: Tybera
* Hardware Supported: IDOBAO ID67
* Hardware Availability: [IDOBAO-website](https://www.idobao.net/products/idobao-id67-65-hot-swappable-mechanical-keyboard-kit-1)

## Layout

![ID67 layout](https://i.imgur.com/Ge6Uxao.png)


## Compiling and flashing

Make example for this keyboard (after setting up your build environment):

    make id67/rgb:default

Flashing example for this keyboard:

    make id67/rgb:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the `Escape` key and plug in the keyboard.
* **Physical reset button**: Briefly press the button on the back of the PCB.
* **Keycode in layout**: Press the key mapped to `RESET` (FN+Z).
