# Rii 518BT

![Rii 518BT](https://i.imgur.com/bj3WmLd.png)

*A custom PCB for the Rii 518BT keyboard*

* Keyboard Maintainer: [Tim / Tangles](https://github.com/tim-eastwood)
* Hardware Supported: [Custom USB/STM32F072 PCB for Rii 518bt](https://github.com/tim-eastwood/rii-518bt-usb-qmk-pcb)
* Hardware Availability: Build it yourself using any PCBA service using the source files / BoM located at [https://github.com/tim-eastwood/rii-518bt-usb-qmk-pcb](https://github.com/tim-eastwood/rii-518bt-usb-qmk-pcb)

Purchasing a Rii 518BT is required to obtain the housing, key membrane, and adhesive sheet of dome switches.

Make example for this keyboard (after setting up your build environment):

    make rii/518bt:default
    or
    qmk compile -kb rii/518bt -km default

Flashing example for this keyboard:

    make rii/518bt:default:flash
    or
    qmk flash -kb rii/518bt -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (5,0) in the matrix (Function key) and plug in the keyboard
* **Physical reset button**: Short the pads on the back of the PCB while plugging in the keyboard