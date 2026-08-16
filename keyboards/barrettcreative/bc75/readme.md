# Barett Creative BC-75

A 75% pcb with an optional encoder or OLED

* Keyboard Maintainer: [DeskDaily](https://github.com/DeskDaily), [gregandcin](https://github.com/gregandcin)
* Hardware Availability: Wooden Cases by Barrett Creative

Make example for this keyboard (after setting up your build environment):

    make barrettcreative/bc75:default

Flashing example for this keyboard:

    make barrettcreative/bc75:default:flash

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the upper left key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
