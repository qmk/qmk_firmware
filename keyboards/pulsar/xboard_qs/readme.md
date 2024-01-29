# Pulsar XBOARD QS

![Pulsar XBOARD QS](https://i.imgur.com/wpTinU4h.jpg)

A 80% keyboard (/w 3 Special key, Encoder, USB Hub, switching 2 host function)

* Keyboard Maintainer: [skylupin03](https://github.com/skylupin03)
* Hardware Supported: Pulsar XBOARD QS
* Hardware Availability: [Pulsar] (https://pulsargg.kr/)

Make example for this keyboard (after setting up your build environment):

    make pulsar/xboard_qs:default

Flashing example for this keyboard:

    make pulsar/xboard_qs:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


## Bootloader
Enter the bootloader in 3 ways:

* **Bootmagic reset**: 
    1. Unplug USB Cable.
    2. Hold the "u" key.
    3. Plug in the USB Cable, the Keyboard should be in ST-Bootloader state.

* **Physical reset button**: Briefly press the button on the back of the PCB 
    1. Unplug USB Cable.
    2. Hold the Physical reset button.
    3. Plug in the USB Cable, the Keyboard should be in ST-Bootloader state.
    
* **Keycode in layout**: Press the key mapped to the `QK_BOOT` if set by the user

