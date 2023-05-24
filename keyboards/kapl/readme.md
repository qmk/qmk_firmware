# Kapl Keyboard

![Kapl Keyboard](https://i.imgur.com/XH8APgi.jpg)
![Kapl PCB](https://i.imgur.com/uir2nQq.jpg)

The Kapl is a split ergonomic keyboard with 70 keys (7x5).

* Keyboard Maintainer: [keyzog](https://github.com/keyzog)
* Hardware Supported: Kapl PCB / Pro Micro
* Hardware Availability:  Order PCBs with gerber files from the [repository](https://github.com/keyzog/kapl/tree/main/gerbers)

Make example for this keyboard (after setting up your build environment):

    make kapl/rev1:default

Flashing example for this keyboard:

    make kapl/rev1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the reset button on the PCB
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
