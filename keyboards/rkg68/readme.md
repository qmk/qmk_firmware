# RK G68

![Keyboard picture](https://imgur.com/UnOJPZrh.jpg)

* Keyboard Maintainer: [Royal Kludge](https://rkgamingstore.com/)
* Hardware Supported: Royal Kludge RK G68
* Hardware Availability: [RKG 68](http://en.rkgaming.com/download/1/)

After setting up your build environment, you can compile the  default keymap by using:

    make rkg68:default

Flashing example for this keyboard:

    make rkg68:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

- **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
- **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
- **Keycode in layout**: Press the key `FN` and `Left CTRL`.

## Layouts

- ANSI layout;

![Imgur](https://i.imgur.com/l7ka1gkh.png)
