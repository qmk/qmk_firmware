# VCL65 solder

![VCL65 solder](https://i.imgur.com/ofSfOTfh.jpg)

A 65% keyboard PCB made and sold under the name "VCL65 Solder" by SawnsProjects with Hoaq in Private Discord GB. 

* Keyboard Maintainer: [Mai The San](https://github.com/MaiTheSan) & [Hoaq](https://github.com/itsmehoaq)
* Hardware Supported: Lotus65 lite, VCL65, 65% traymount case
* Hardware Availability: Private Discord GB

Make example for this keyboard (after setting up your build environment):

    make sawnsprojects/vcl65/solder:default

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the front of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
