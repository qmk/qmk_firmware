# bm980

![bm980](https://imgur.com/k4NQGLx)

*A short description of the keyboard/project*

* Keyboard Maintainer: [peepeetee](https://github.com/peepeetee)
* Hardware Supported: bm980
* Hardware Availability: https://kprepublic.com/products/bm980rgb-bm980-rgb-hot-swappable-custom-mechanical-keyboard-pcb-programmed-qmk-via-firmware-full-rgb-switch-underglow-type-c
https://www.aliexpress.com/item/1005002509519466.html
https://item.taobao.com/item.htm?id=645862298692

Make example for this keyboard (after setting up your build environment):

    make kprepublic/bm980:default

Flashing example for this keyboard:

    make kprepublic/bm980:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
