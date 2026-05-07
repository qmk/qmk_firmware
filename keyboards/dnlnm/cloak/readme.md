# dnlnm/cloak

![dnlnm/cloak](https://i.imgur.com/eZCUPvK.jpeg)

* Keyboard Maintainer: [Daniel Naim](https://github.com/dnlnm)
* Hardware Supported: Cloak-XT
* Hardware Availability: https://github.com/dnlnm/cloak-xt-stm32

Make example for this keyboard (after setting up your build environment):

    make dnlnm/cloak:default

Flashing example for this keyboard:

    make dnlnm/cloak:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Hold the boot button and tap the reset button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
