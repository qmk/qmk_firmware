# IDOBAO Montex V2

![MMONTEX V2](https://idobao.github.io/assets/img/idobao-id27.png)

A hotswap RGB numpad from IDOBAO.

* Keyboard Maintainer:
    - [IBNobody](https://github.com/IBNobody)
    - [vinorodrigues](https://github.com/vinorodrigues)
* Hardware Supported: IDOBAO Montex V2
* Hardware Availability: https://idobao.net/products/idobao-montex-pad-hot-swappable-keyboard-kit-%E7%9A%84%E5%89%AF%E6%9C%AC

Make example for this keyboard (after setting up your build environment):

    make idobao/montex/v2:default

Flashing example for this keyboard:

    make idobao/montex/v2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
