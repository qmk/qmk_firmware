# banime40 

![](https://i.imgur.com/sHQyMfEh.jpeg)

A hotswap gasket mount 4x10 that can support multiple layouts.

* Keyboard Maintainer: [sporewoh](https://github.com/ChrisChrisLoLo)
* Hardware Supported: Open source PCB files, Pro Micro compatible
* Hardware Availability: PCBs and Case files available [here](https://github.com/ChrisChrisLoLo/banime40)

Make example for this keyboard (after setting up your build environment):

    make sporewoh/banime40:default

Flashing example for this keyboard:

    make sporewoh/banime40:default:flash


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
