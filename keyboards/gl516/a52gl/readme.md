# a52gl

![a52gl](https://cdn-ak.f.st-hatena.com/images/fotolife/S/Salicylic_acid3/20210911/20210911005227.jpg)

This is 52 keys Alice style keyboard.
Use the GL516 case.

* Keyboard Maintainer: [Salicylic_acid3](https://github.com/Salicylic-acid3)
* Hardware Supported: a52gl PCB, Pro Micro
* Hardware Availability: [PCB & Case Data](https://github.com/Salicylic-acid3/GL516_Exemple), [yushakobo Shop](https://shop.yushakobo.jp/products/3342)

Make example for this keyboard (after setting up your build environment):

    make gl516/a52gl:default

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

[Build guide](https://salicylic-acid3.hatenablog.com/entry/a52gl-j73gl-build-guide)
