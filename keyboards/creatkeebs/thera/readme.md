# thera
A 75% keyboard

![thera](https://i.imgur.com/7w7ARcPh.jpg)

### Features
* Plateless PCB gasket
* Decent amount of layout compatibility - [View supported layouts](https://cdn.shopify.com/s/files/1/0481/5840/8853/products/8038a8b71a5149f5bad362b28368da3_590x.png?v=1628765539)
* Ti badge
* PVD weight (upgrade available)

### Additional Information
* Keyboard Maintainer: [Tim](https://github.com/Timliuzhaolu/qmk_firmware)
* Hardware Supported: thera PCB
* Hardware Availability: [ESCHIT.com](https://eschit.com/products/gb-thera75)

### Entering Bootloader

Enter the bootloader in 2 ways:

* Physical reset button: Press the `RESET` button on the back of the PCB.
* Keycode in layout: Press the key mapped to `RESET` if it is available.

### Building the Firmware
Make example for this keyboard (after setting up your build environment):

    make creatkeebs/thera:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
