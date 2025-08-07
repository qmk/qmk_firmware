# jcpm2

![jcpm2](https://i.imgur.com/EM5JoGC.jpeg)

An 8-key macro pad with rotary encoder, RGB backlighting and underlighting. Made and sold by JCC LLC.

* Keyboard Maintainer: [jeremyscook](https://github.com/jeremyscook)
* Hardware Supported: JCPM2 PCB, Pro Micro
* Hardware Availability: [Tindie.com](https://www.tindie.com/products/25414)

Make example for this keyboard (after setting up your build environment):

    make jcpm2:default

Flashing example for this keyboard:

    make jcpm2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the rotary encoder and plug in the keyboard
* **Physical reset button**: Double-click the small inside button on top of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
