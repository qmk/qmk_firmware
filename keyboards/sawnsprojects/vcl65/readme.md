# VCL65 solder

A 65% keyboard sold in several variants. 

1. [Solder](solder/): 06/2021. Atmega32u4 soldered keyboard. Sold under the name "VCL65" with Lotus 65 lite keyboard case. Compatible with some 65% traymount case, VCL65 and Lotus65.

 **Firmware files are SPECIFIC to each board. Firmware files from one, will not work on the other.** Please use the `.hex` or `.bin` appropriate for your board.

* Keyboard Maintainer: [SawnsProjects](https://github.com/MaiTheSan) & [Hoaq](https://github.com/itsmehoaq)
* Hardware Supported: Lotus65 lite, VCL65, 65% traymount case 
* Hardware Availability: Private Discord GB

Make examples for this keyboard (after setting up your build environment):

    make sawnsprojects/vcl65/solder:default

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).