# DZ60 60% Mechanical Keyboard PCB

![DZ60](https://cdn.shopify.com/s/files/1/1473/3902/products/c_1.jpg)

## A Customizable 60% Mechanical Keyboard PCB

![A Customizable 60% Mechanical Keyboard PCB](https://cdn.shopify.com/s/files/1/1473/3902/files/1_03_abb48769-9486-44bd-a761-7cd39d7e1bda.jpg)

* Keyboard Maintainer: QMK Community
* Hardware Supported: DZ60 60% Mechanical Keyboard PCB
* Hardware Availability: [KBDfans](https://kbdfans.com/collections/60/products/dz60-60-pcb)

There are two versions of the DZ60 PCB. Please use the appropriate firmware for your board.

* V1: 1.6mm thickness PCB;
* V2: 1.2mm thickness PCB

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

Make example for this keyboard (after setting up your build environment):

    make dztech/dz60/v1:default
    make dztech/dz60/v2:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
