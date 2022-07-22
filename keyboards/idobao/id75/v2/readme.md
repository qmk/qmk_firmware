# ID75 v2

![ID75 v2](https://i.imgur.com/KdAjS5f.jpg)

A 5x15 ortholinear keyboard with hotswap sockets and north facing in switch RGB LEDs and RGB underglow

* Keyboard Maintainer: [peepeetee](https://github.com/peepeetee)
* Hardware Supported: ID75 v2
* Hardware Availability: https://idobao.net/products/idobao-id75-crystal-hot-swap-keyboard-kit?_pos=1&_sid=8758d3561&_ss=r

Make example for this keyboard (after setting up your build environment):

    make idobao/id75/v2:default

Flashing example for this keyboard:

    make idobao/id75/v2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
