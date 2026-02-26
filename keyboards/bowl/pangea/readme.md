# Bowl Pangea

![pangeaimg](https://imgur.com/Fes8PXw.jpg)

The pangea is a fullsize keyboard by Bowl, with a flippable construction so that the numpad can be put in normal or southpaw position.

* Keyboard Maintainer: [gondolindrim](https://github.com/gondolindrim)
* Hardware Supported: Pangea has two PCB variants (solderable and hotswap), both based on STM32F401
* Hardware Availability: at the [bowlkeyboards store](https://bowlkeyboards.com/pages/pangea-full-size)

Make example for this keyboard (after setting up your build environment):

    make bowl/pangea/<version>:default

Where `<version>` can be either `pngs` or `pngh`. Flashing example for this keyboard:

    make bowl/pangea/<version>:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Escape) and plug in the keyboard
* **Physical reset button**: press and hold the button on the back of the PCB for five seconds
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
