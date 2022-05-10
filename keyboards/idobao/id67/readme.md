# IDOBAO ID67

![id67](https://i.imgur.com/9roQ4Mih.jpeg)

A 65% hotswap keyboard from IDOBAO.

## ANSI support:

* Keyboard Maintainer: Tybera *(fmr.)*, [thewerther](https://github.com/thewerther) *(curr.)*
* Hardware Supported: IDOBAO ID67, ID67V2, ID67 Crystal & ID67 Bestype
* Hardware Availability: IDOBAO website: 
* [ID67](https://www.idobao.net/products/idobao-id67-65-hot-swappable-mechanical-keyboard-kit-1)
* [ID67V2](https://idobao.net/collections/65-layout/products/idobao-id67v2-65-hot-swappable-mechanical-keyboard-kit)
* [ID67 Crystal](https://idobao.net/collections/65-layout/products/idobao-id67-crystal-keyboard-kit-gasket-mount-version)
* [ID67 Bestype](https://idobao.net/collections/65-layout/products/idobao-id67-bestype-keyboard-kit-aluminum-with-brass-weight)

## Layout

![ID67 layout](https://i.imgur.com/Ge6Uxao.png)


## Compiling and flashing

Make example for this keyboard (after setting up your build environment):

    make id67:default

Flashing example for this keyboard:

    make id67:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the `Escape` key and plug in the keyboard.
* **Physical reset button**: Briefly press the button on the back of the PCB.
* **Keycode in layout**: Press the key mapped to `RESET` (FN+Z).
