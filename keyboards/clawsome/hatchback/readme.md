# SUV

This is TKL keyboard that can be converted down into a 75% keyboard and a 13key macropad (see "luggage rack")

- Keyboard Maintainer: [AAClawson](https://github.com/AlisGraveNil)
- Hardware Supported: Hatchback, Elite-C (as TKL); Pro-Micro and nice!nano (as 75%)
- Hardware Availability: In stock within the next month

Make example for this keyboard (after setting up your build environment):

    make clawsome/hatchback:default
    Connect your board to your computer; connect the "GND" and "RST" pins on your controller using a wire or a pair of tweezers and hold it for 3 seconds to force the controller into bootloader mode. Then use QMK Toolbox to flash the .hex you downloaded from the QMK website. If using an Elite-C, there's a small black reset button on the PCB you can press instead of trying to connect the two pins.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
