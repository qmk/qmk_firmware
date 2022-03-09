# meow65

![meow65](https://i.imgur.com/M6PmjPGh.png)

Meow65 Hotswap PCB, compatible with Meow65 & Bakeneko65 V3 Keyboard

* Keyboard Maintainer: [mrninhvn](https://github.com/mrninhvn)
* Hardware Supported: Meow65, Bakeneko65 V3
* Hardware Availability: https://github.com/mrninhvn/meow65-pcb

Make example for this keyboard (after setting up your build environment):

    make meow65:default

Flashing example for this keyboard:

    make meow65:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down ESC key (the top left key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
