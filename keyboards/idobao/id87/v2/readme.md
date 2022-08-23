# ID87 v2

![ID87 v2](https://i.imgur.com/woTSycN.jpg)

A TKL keyboard with hotswap sockets and in switch RGB.

* Keyboard Maintainer: [peepeetee](https://github.com/peepeetee)
* Hardware Supported: ID87 v2
* Hardware Availability: [Drop](https://drop.com/buy/idobao-id87-v2-tkl-mechanical-keyboard-kit), [idobao](https://idobao.net/products/idobao-id87-v2-tkl-pcb-mounted-hot-swappable-mechanical-keyboard-kit)

Make example for this keyboard (after setting up your build environment):

    make idobao/id87/v2:default

Flashing example for this keyboard:

    make idobao/id87/v2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
