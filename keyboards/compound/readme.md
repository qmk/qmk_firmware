# Compound

![Compound](https://imgur.com/0DC9F9dh.jpg)

A compact 60% Compound keyboard with fixed Tsangan style layout.

* Keyboard Maintainer: [yumagulovrn](https://github.com/yumagulovrn)  
* Hardware Supported: Compound PCB
* Hardware Availability: [GeekHack IC](https://geekhack.org/index.php?topic=111187.0)

## Entering bootloader mode

Keyboard doesn't have dedicated RESET button on the PCB, however, there are alternatives:

### Bootmagic

Hold down ESC while plugging the keyboard in.

### Shorting RESET pin

Short GND and RST pads on the bottom of the keyboard. Location of the pads can be seen [here](https://imgur.com/uw7Zz7Y.jpg).


## Building keyboard firmware

Make example for this keyboard (after setting up your build environment):

    make compound:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
