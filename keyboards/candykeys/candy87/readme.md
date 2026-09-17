# Candy87

![Candy87](https://i.imgur.com/HeCz1u8.png)

The Candy87 Hotswap PCB is a universal TKL PCB by Candykeys.
It supports ISO Hotswap by default (ANSI possible with desolering two hotswap sockets) and many layout options. 
It was mainly made for the F1-8X V2, but fits similar keyboards as well.

* Keyboard Maintainer: [RarePotato8DE](https://github.com/rarepotato8de)
* Hardware Supported: Candy87 PCB for F1-8X V2 and similar
* Hardware Availability: [Buy on Candykeys](https://candykeys.com/product/candy87-hotswap-pcb-iso)

Make example for this keyboard (after setting up your build environment):

    make candykeys/candy87:default

Flashing example for this keyboard:

    make candykeys/candy87:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Hold down the "BOOT" button on the back and double press "RESET". Release "BOOT" after
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
