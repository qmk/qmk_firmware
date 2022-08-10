# mlego/m20

![mlego/m20](https://i.imgur.com/B4jLOdnh.jpeg)

part of a collection of fun and not only, mlego keyboards are simple, plateless, pcb mounted using
lego as cases. As MCU this uses rp2040 based mcu comptatible with original rpico shape and pins.
It supports small variations in pins from original, eg weact, estardyn or tenstar clones. It uses tinyuf2
as bootloader. Layout is 5 rows 4 columns, supports both cherry mx&clones and kailh choco v2 switches.
All project is opensource. See [homepage of the project](https://gitlab.com/m-lego/m65)
for more details.

* Keyboard Maintainer: [alin elena](https://github.com/alinelena)
* Hardware Supported: custom made pcbs, with rp2040 mcu, raspberry pico, we act, etc.
* Hardware Availability: [mlego/m20](https://gitlab.com/m-lego/m20)

Make example for this keyboard (after setting up your build environment):

    make mlego/m20/rev1:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Physical reset button**: press twice fast the reset button on the rp2040 board, mount the device then copy the firmware.
* **Keycode in layout**: press in the same time LOWER, RAISE and 0, practically switches 1, 2 and 4 on the bottom row, mount the
  device and copy firmware.
* **Physical boot button**: unplug keyboard, press boot button, plug keyboard, release boot button, mountr the device then copy the
  firmware
