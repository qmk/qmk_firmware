# IDOBAO Abacus ID42

![IDOBAO Abacus ID42](https://idobao.github.io/assets/img/idobao-id42.png)

Sized just right at 40% — with a compact configuration the IDOBAO Abacus ID42 makes a great fit for any desk.

## 42 Keys

* Keyboard Maintainer: [Vino Rodrigues](https://github.com/vinorodrigues)
* Hardware Supported: **IDOBAO Abacus ID42**
* Hardware Availability: [IDOBAO.net](https://idobao.net/search?type=product&q=ID42*)

## Layout

![](https://cdn.jsdelivr.net/gh/Idobao/idobao.github.io/kle/idobao-id42-all.png)

## Compiling and Flashing

Make example for this keyboard (after setting up your build environment):

    make idobao/id42:default

Flashing example for this keyboard:

    make idobao/id42:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. <br>Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the [Esc] key and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to *`RESET`* *(Default = `[Fn]`+`[R]`)* if it is available
