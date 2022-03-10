# KB58

![kb58_pico](https://user-images.githubusercontent.com/25994266/146207912-b725e22f-92dc-4a40-9157-c2fddff45ce2.jpg)

This is 58 keys keyboard.

* Keyboard Maintainer: [beanaccle](https://github.com/beanaccle)
* Hardware Supported: KB58
* Hardware Availability: [KB58 Pico](https://github.com/beanaccle/kb58_pico)

Make example for this keyboard (after setting up your build environment):

    make kb58:default

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
