# Slime88

![Slime88](https://user-images.githubusercontent.com/23428162/170985512-ec79f498-7476-4ab6-8150-877c67a25f26.png)

A Hotswap Multi-layout F13 TKL PCB (h88c compatible) powered by RP2040,

* Keyboard Maintainer: Zykrah
* Hardware Supported: Slime88 rev1 PCB
* Hardware Availability: [SLIME88](https://github.com/zykrah/slime88)

Make example for this keyboard (after setting up your build environment):

    make zykrah/slime88:default

Flashing example for this keyboard:

    make zykrah/slime88:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
