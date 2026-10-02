# ForaZ Signature Hope

![hopeimg](https://imgur.com/NLPSeg3.jpg)

The Hope is a TKL keyboard by ForaZ.

* Keyboard Maintainer: [gondolindrim](https://github.com/gondolindrim)
* Hardware Supported:two PCB variants (solderable and hotswap), both based on STM32F411
* Hardware Availability: not yet available for purchase as of november 2025.

Make example for this keyboard (after setting up your build environment):

    make foraz/hope/<version>:default

Where `<version>` can be either `hopes` or `hopeh`. Flashing example for this keyboard:

    make foraz/hope/<version>:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Escape) and plug in the keyboard
* **Physical reset button**: press and hold the button on the back of the PCB for five seconds
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
