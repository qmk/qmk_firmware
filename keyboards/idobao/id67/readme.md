# IDOBAO ID67

![id67](https://i.imgur.com/XiEnksS.png)

A 65% hotswap keyboard from IDOBAO.

## ANSI support:

* Keyboard Maintainer:
  - [Tybera](https://github.com/tybera) *(fmr.)*
  - [Werther](https://github.com/thewerther) *(curr.)*
  - [Vino Rodrigues](https://github.com/vinorodrigues) *(curr.)*
* Hardware Supported:
  - **IDOBAO ID67**
  - **ID67v2**
  - **ID67 Crystal**
  - **ID67 Bestype**
* Hardware Availability: [IDOBAO.net](https://idobao.net/search?type=product&q=ID67*): 
  * [ID67](https://www.idobao.net/products/idobao-id67-65-hot-swappable-mechanical-keyboard-kit-1)
  * [ID67v2](https://idobao.net/products/idobao-id67v2-65-hot-swappable-mechanical-keyboard-kit)
  * [ID67 Crystal](https://idobao.net/products/idobao-id67-crystal-keyboard-kit-gasket-mount-version)
  * [ID67 Bestype](https://idobao.net/products/idobao-id67-bestype-keyboard-kit-aluminum-with-brass-weight)

## ANSI Layout

![ID67 Layout](https://idobao.github.io/kle/idobao-id67.png)


## Compiling and Flashing

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
