# FUYU

![FUYU](https://i.imgur.com/uWB5EqJh.png)

A F12 TKL H87-Compat Type-C PCB for the Geon F1-8K

* Keyboard Maintainer: [Zykrah](https://github.com/zykrah)
* Hardware Supported: Fuyu rev1 PCB
* Hardware Availability: [Github Repo](https://github.com/zykrah/fuyu), [GEON Store](https://geon.works/products/fuyu-pcb-for-f1-8k), [CustomKBD](https://customkbd.com/products/fuyu-pcb-for-f1-8k)

Make example for this keyboard (after setting up your build environment):

    make zykrah/fuyu:default

Flashing example for this keyboard:

    make zykrah/fuyu:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly short the `RST` and `GND` pads on the SWD header twice, or short the `BOOT` header and plug in keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
