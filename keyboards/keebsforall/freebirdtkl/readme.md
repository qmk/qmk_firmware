# KeebsForAll FreebirdTKL

![FreebirdTKL](https://i.imgur.com/GnY639m.png)

A TKL PCB with USB-C, hotswap, and multiple layouts

* Keyboard Maintainer: [KnoblesseOblige](https://github.com/KnoblesseOblige)
* Hardware Supported: KeebsForAll FreebirdTKL
* Hardware Availability: https://keebsforall.com

Make example for this keyboard (after setting up your build environment):

    make keebsforall/freebirdtkl:default

Flashing example for this keyboard:

    make keebsforall/freebirdtkl:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
