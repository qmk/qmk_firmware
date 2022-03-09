# Meira

![Meira](https://i.imgur.com/kF4MFlWh.jpeg)

A 4x12 ortholinear low-profile keyboard.

* Keyboard Maintainer: [Cole Markham](https://github.com/colemarkham)
* Hardware Supported: Meira/ProMicro, Meira/FeatherBLE
* Hardware Availability: [WoodKeys.click](https://woodkeys.click/meira)

Two controllers are supported: the Pro Micro, and the Adafruit Feather BLE 32u4. Support for each is defined as a hardware revision subfolder in QMK. Main differences include processor frequencies and matrix pinouts.

Make examples for this keyboard (after setting up your build environment):

    make woodkeys/meira/featherble:default  # for Feather BLE 32u4 controllers
    make woodkeys/meira/promicro:default    # for Pro Micro controllers

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Both the Pro Micro and the Feather BLE use the Caterina bootloader, which is typically programmed using avrdude.

## Matrix

In order to have enough pins for the matrix and other functions, a custom matrix is implemented using a demultiplexer to scan the columns. Since the demux is active low, the diodes must be oriented with the cathode connected to the demux pin. When looking at the bottom of the board with the controller at the top right, the cathode mark on the diode should be toward the left.

## LED Controller

The in-switch LEDs are driven by an ISSI LED controller (IS31FL3731). The micro controller communicates with this chip using I2C. Individual LED control is possible, but currently only general backlighting support is implemented. This functionality is located in lighting.c, issi.c, and TWILib.c.
