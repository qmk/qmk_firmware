# Hillside

![hillside](https://imgur.com/XW0rX13.png)

[Hillside](https://github.com/mmccoyd/hillside)
 is a split ergonomic keyboard
 with 3x6+4+2 choc-spaced keys with aggressive column stagger,
 a longer thumb arc and a breakoff outer-pinky column.

* Keyboard Maintainer: [Michael McCoyd](https://github.com/mmccoyd)
* Hardware Supported: ProMicro/Elite-C and compatible
* Hardware Availability: https://github.com/mmccoyd/hillside

Make example for this keyboard (after setting up your build environment):

    make handwired/hillside/0_1:default

Flashing example for this keyboard:

    make handwired/hillside/0_1:default:flash

## Bootloader

Enter the bootloader by either:

* **Physical reset button**: Briefly press the button on the front of the PCB.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
