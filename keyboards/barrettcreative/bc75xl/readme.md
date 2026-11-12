# Barett Creative BC-75 XL

A 75% pcb with extra column on the left. Optional to use 2 encoders or 1 encoder and OLED.

* Keyboard Maintainer: [DeskDaily](https://github.com/DeskDaily),[gregandcin](https://github.com/gregandcin)
* Hardware Availability: Wooden Cases by Barrett Creative

Make example for this keyboard (after setting up your build environment):

    make barrettcreative/bc75xl:default

Flashing example for this keyboard:

    make barrettcreative/bc75xl:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the upper left key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
