# Silakka54

![Silakka54](https://i.imgur.com/JrsS0kY.png)

Silakka54 is a RP2040 Zero based 54-key column staggered split keyboard. PCB uses hotswap sockets. Design is inspired from REVIUNG41 and Corne keyboards.

* Keyboard Maintainer: [Squalius-cephalus](https://github.com/Squalius-cephalus)
* Hardware Supported: Silakka54 PCB
* Hardware Availability: https://github.com/Squalius-cephalus/silakka54

Make example for this keyboard (after setting up your build environment):

    make silakka54:default

Flashing example for this keyboard:

    make silakka54:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical boot button**: Hold BOOT button down and connect MCU to the PC
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
