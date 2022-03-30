# E80-1800

![E80_1800_sample_image](https://i.imgur.com/yzCfVSth.png)

A replacement PCB for the Cherry G80-1800 keyboard. Supports ISO and ANSI, 6u offcenter or 7u bottom row, stepped and regular caps lock. Optional i2c header for OLED. Type-C on the PCB (requires some case modifications). The PCB is open source and can be found in my [Github repo](https://github.com/ebastler/E80-1800).

* Keyboard Maintainer: [ebastler](https://github.com/ebastler)
* Hardware Supported: r1 and r1.1 PCB, see Github repo linked above
* Hardware Availability: Groupbuy, otherwise feel free to order your own boards. jlcpcb compatible gerber/BOM/CPL files are included.

How to enter the Bootloader:
* No pre-flashed firmware, option 1: Bridge `BOOT` labeled pads below spacebar while plugging the board in
* No pre-flashed firmware, option 2: Bridge `BOOT` labeled pads below spacebar, then quickly short `RST` labeled pads
* Pre-flashed firmware: Use Bootmagic - keep the `ESC` (top left most) key pressed while plugging the board in

Make example for this keyboard (after setting up your build environment):

    make ebastler/e80_1800:default

Flash example for this keyboard (after setting up your build environment):

    make ebastler/e80_1800:default


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).