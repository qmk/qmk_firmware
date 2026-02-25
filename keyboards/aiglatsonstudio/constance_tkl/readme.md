# constance_tkl

![constance_tkl](https://i.imgur.com/TaizGjXh.jpg)

This keyboard is made of split plate, top mounted, F13 TKL. Provides multiple compatible keys.Expected to provide players with a more free and comfortable user experience.

* Keyboard Maintainer: [patipan36991](https://github.com/patipan36991)
* Hardware Supported: Constance_TKL PCB, STM32F072 
* Hardware Availability: https://aiglatsonstudio.com/

Make example for this keyboard (after setting up your build environment):

    make aiglatsonstudio/constance_tkl/hotswap:default
    make aiglatsonstudio/constance_tkl/solder:default

Flashing example for this keyboard:

    make aiglatsonstudio/constance_tkl/hotswap:default:flash
    make aiglatsonstudio/constance_tkl/solder:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
