# EdgeProMX keyboard

![EdgeProMX](https://www.edgepro.org/assets/images/edgepromx-assembled-cs.jpg)

A compact 40% (12x4) ortholinear keyboard kit. Keyboard is based on EdgePro1 CPU board and comes with Sharp Memory LCD 400x240, encoder, mechanical switch, battery holder and protoboard development area. It is also equiped with standard 20 pin JTAG connector for easy programming and debugging.

Keyboard Maintainer: [Jernej Turnsek](https://github.com/jturnsek)  
Hardware Supported: EdgePro1 and EdgeProMX PCB 
Hardware Availability: [crowdsupply.com](https://www.crowdsupply.com/edgepro/edgepro1)

Make example for this keyboard (after setting up your build environment):

    make edgepromx:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Flashing the target is possible with Segger JLink and EmbeddedStudio IDE. Just load the elf file with the help of IDE and flash it.
