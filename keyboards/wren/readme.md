# Wren

![Wren PCB](https://raw.githubusercontent.com/walterhanley/wren-keyboard/main/images/wren-universal.png)
![Wren Layout](https://raw.githubusercontent.com/walterhanley/wren-keyboard/main/images/author-layout.png)

A split ergonomic "system keyboard" aimed at providing numpad and nav cluster functionality. For more information, please see the [project repo](https://github.com/walterhanley/wren-keyboard).

* Keyboard Maintainer: [Walter Hanley](https://github.com/walterhanley)
* Hardware Supported: Wren Universal PCB and Elite C (Pro Micro configurations likely supported but not tested)
* Hardware Availability: Source files available at [project repository](https://github.com/walterhanley/wren-keyboard)

Make example for this keyboard (after setting up your build environment):

    make wren:default

Flashing example for this keyboard:

    make wren:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button on the front of the PCB below the microcontroler
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
