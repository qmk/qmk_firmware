# IDOBAO ID63

![IDOBAO ID63](https://i.imgur.com/DxlOr9xh.png)

*The ID63 Keyboard Kit brings a tailored gasket-mounted build to an ultra-compact 60% layout with a unique ribbed side texture.*

## ANSI Support

* Keyboard Maintainer: [Vino Rodrigues](https://github.com/vinorodrigues)
* Hardware Supported: **IDOBAO ID63**
* Hardware Availability: [Drop.com](https://drop.com/buy/idobao-id63-60-gasket-hot-swappable-aluminum-mechanical-keyboard-kit) & [IDOBAO.net](https://idobao.net/search?type=product&q=id63*)

## Layout

![IDOBAO ID63](https://idobao.github.io/kle/idobao-id63.png)

## Compiling and Flashing

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb idobao/id63 -km default

*{..or..}*

    make idobao/id63:default

Flashing example for this keyboard:

    make idobao/id63:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. <br>Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the [Escape] key and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET`, default is [Fn]+[B]
