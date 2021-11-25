# MTB60 (Hotswap Edition)

## Details

* Keyboard Maintainer: [MTBKeys](https://mtbkeys.com/)
* Hardware Supported: MTB60 PCB (Hotswap edition)
* Hardware Availability: [HB60 on MTBKeys Website](https://mtbkeys.com/)

## Building Firmware

Make example for this keyboard (after setting up your build environment):

    make mtbkeys/mtb60/hotswap:default

Flashing example for this keyboard:

    make mtbkeys/mtb60/hotswap:default:flash

## Bootloader

Enter the bootloader in 2 ways:

1. **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
2. **Physical reset button**: Briefly press the button on the back of the PCB

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
