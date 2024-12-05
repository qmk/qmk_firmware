# Plaque80

![Plaque80](https://i.imgur.com/kgRcHTlh.png)

 A TKL keyboard sold in ParamountKeeb. Atmega32u4 soldered PCB. Sold under the name "Plaque80" with Plaque80 keyboard case. This PCB can compatible with Plaque80 keyboard case and several TKL boards like Geonworks Frog/F1-8x; KFE-CE; TGR Jane; Cloudline; Singa Jaguar; Amber80, among others.

 **Firmware files are SPECIFIC to each board. Firmware files from one, will not work on the other.** Please use the `.hex` or `.bin` appropriate for your board.

* Keyboard Maintainer: [SawnsProjects](https://github.com/MaiTheSan) [ParamountKeeb](https://paramountkeeb.com/)
* Hardware Supported: Plaque80 
* Hardware Availability: [ParamountKeeb](https://paramountkeeb.com/)

Make examples for this keyboard (after setting up your build environment):

    make sawnsprojects/plaque80:default

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).