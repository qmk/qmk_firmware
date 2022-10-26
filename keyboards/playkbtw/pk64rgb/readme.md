# Play Keyboard 64RGB

![PK64RGB](https://cdn.store-assets.com/s/409567/i/25281841.png)

A 60% RGB hotswap keyboard PCB made by Play Keyboard.

* Keyboard Maintainer: [Barry Huang](https://github.com/yj7272098)
* Hardware Supported: Play Keyboard 64 RGB
* Hardware Availability: [Play Keyboard](http://play-keyboard.store/)

Make example for this keyboard (after setting up your build environment):

    make playkbtw/pk64rgb:default

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

You can get into bootloader by pressing the reset button from the back of PCB.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).