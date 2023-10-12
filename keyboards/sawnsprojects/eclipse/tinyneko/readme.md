# tinyneko

![tinyneko](https://i.imgur.com/hs8RWzLh.png)

 A 60% PCB Modified for Tinyneko, can fit with all board Eclipse60 fit.

* Keyboard Maintainer: [Mai The San](https://github.com/MaiTheSan)
* Hardware Supported: TinyNeko
* Hardware Availability: [tinyneko GB](https://tinyneko.com/products/group-buy-tinyneko) [Opensource](https://github.com/MaiTheSan/EclipsePhrase160)

Make example for this keyboard (after setting up your build environment):

    make tinyneko/eclipse60:default

Flashing example for this keyboard:

    make tinyneko/eclipse60:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
