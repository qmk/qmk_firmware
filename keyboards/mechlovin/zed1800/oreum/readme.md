# Oreum

![Oreum](https://i.imgur.com/Dxc1y0Ol.png)

A PCB for Oreum Keyboard, base on ZED1800 PCB

* Keyboard Maintainer: [mechlovin](https://github.com/mechlovin)
* Hardware Supported: The Oreum Keyboard, APM32F103
* Hardware Availability: [Reddit GB](https://www.reddit.com/r/MechanicalKeyboards/comments/xjqddx/gb_oreum_cp_gb_has_started/)

Make example for this keyboard (after setting up your build environment):

    make mechlovin/zed1800/oreum:default

Flashing example for this keyboard:

    make mechlovin/zed1800/oreum:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
