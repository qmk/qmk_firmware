# glacier
A 80% keyboard

![glacier](https://i.imgur.com/BeyreN1.png)

### Features
* PCB gasket
* Nickel-cobalt weight

### Additional Information
* Keyboard Maintainer: [Tim](https://github.com/Timliuzhaolu/qmk_firmware)
* Hardware Supported: glacier PCB
* Hardware Availability: [ESCHIT.com](https://eschit.com/products/gb-thera75)

### Entering Bootloader

Enter the bootloader in 2 ways:

* Physical reset button: Press the `RESET` button on the back of the PCB.
* Keycode in layout: Press the key mapped to `RESET` if it is available.

### Building the Firmware
Make example for this keyboard (after setting up your build environment):

    make creatkeebs/glacier:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
