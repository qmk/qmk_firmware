# ECmacro 4H

![ECmacro 4H](https://i.imgur.com/hq8Qp6X.jpeg)

![ECmacro 4H PCB](https://i.imgur.com/aeRcTcc.jpeg)

A four-key macropad with electrostatic capacitive switches. The RP2040's PIO charges each key's electrode and times its discharge through a single resistor to ground.

* Keyboard Maintainer: [QuadState](https://github.com/QuadState)
* Hardware Supported: ECmacro 4H PCB with a Seeed Studio XIAO RP2040
* Hardware Availability: [QuadState/ECmacro](https://github.com/QuadState/ECmacro)

Make example for this keyboard (after setting up your build environment):

    make quadstate/ecmacro4h:default

Flashing example for this keyboard:

    make quadstate/ecmacro4h:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Physical reset button**: Double tap the R (RESET) button on the XIAO RP2040
* **Physical boot button**: Hold the B (BOOT) button on the XIAO while plugging in the USB cable, or hold B and press R
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
