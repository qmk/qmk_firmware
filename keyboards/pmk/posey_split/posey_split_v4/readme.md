# posey_split_v4

![posey_split_v4](https://i.imgur.com/g3yf6al.png)

*A short description of the keyboard/project*

* Keyboard Maintainer: [Javier Oliver](https://github.com/joliverMI)
* Hardware Supported: posey_split_v4 and logic_module_v1
* Hardware Availability: poseysmechanicalkeyboards.com

Make example for this keyboard (after setting up your build environment):

    make posey_split_v4:default

Flashing example for this keyboard:

    make posey_split_v4:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key Escape and plug in the keyboard
* **Physical reset button**: Hold the button on the bottom of the keyboard while you plug in the USB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
