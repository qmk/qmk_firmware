# Synovia PCB QMK firmware

![synoviaimg](https://i.imgur.com/SHNnuMk.jpg)

The Synovia was a TKL keyboard designed by Baionlenja, managed by CTRL. This firmware is for the second PCB made for this keyboard, designed by Gondolindrim. The first PCB being the one of the [initial groupbuy](https://geekhack.org/index.php?topic=118781.0). 

* Keyboard Maintainer: [gondolindrim](https://github.com/gondolindrim)
* Hardware Supported: two PCB versions, one solderable and one hotswap, both based on STM32F411.
* Hardware Availability: this keyboard was sold on [bowlkeyboards website](https://bowlkeyboards.com/pages/synovia-landing-page).

Make example for this keyboard (after setting up your build environment):

    make synovia/<version>:default

Where `<version>` can be either `sino_s` for solderable or `sino_h` for hotswap. Flashing example for this keyboard:

    make synovia/<version>:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Escape) and plug in the keyboard
* **Physical reset button**: press and hold the button on the back of the PCB for at least 5 seconds
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
