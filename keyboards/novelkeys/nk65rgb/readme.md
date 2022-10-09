# NK65


![NK65](https://i.imgur.com/EXNbVpL.jpg)

This is a standard fixed layout 65% PCB. It supports VIA and full per-key RGB.

Keyboard Maintainer (for RGB_MATRIX implementation): Jean-Pascal Journet  on [GitHub](https://github.com/jjournet)   
Hardware Supported: A 65% keyboard with STM32F303CC   
Hardware Availability: https://novelkeys.xyz/

This is a re-implmentation of QMK firmware for Novelkeys NK65, based on Yiancar work, to support RGB Matrix.

Originial Keyboard Maintainer: [Yiancar](http://yiancar-designs.com/) and on [GitHub](https://github.com/yiancar)   

See ```nk65``` folder for original implementation

Only tested on revision < 1.4

## Instructions

### Build

Make example for this keyboard (after setting up your build environment):

    make novelkeys/nk65:via

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

### Reset

- Unplug
- Hold Escape
- Plug In
- Unplug
- Release Escape

### Flash

- Unplug
- Hold Escape
- Plug In
- Flash using QMK Toolbox or dfu-util (`make nk65rgb:<keymap>:dfu-util`)
