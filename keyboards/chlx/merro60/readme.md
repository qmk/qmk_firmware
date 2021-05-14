# merro60

merro60.1, merro60.1.1 PCB

A standard 60% format keyboard pcb with USB-C and unified daughterboard compatibility.
Has modified cutouts to allow usage of certain tray mount cases into gummy gasket o-ring mount.

Keyboard Maintainer: [Alexander Lee](https://github.com/gaclee3b)
Hardware Supported: chlx PCB merro60.1, merro60.1.1, merro60.1.2

Enter bootloader mode by either option -
- When unplugged, holding the top-left key (typically ESC) while plugging in the keyboard
- When plugged, pressing and releasing the reset button on the pcb bottom behind the CAPSLOCK / A-key region

Make example for this keyboard (after setting up your build environment):

    make chlx/merro60:default
    make chlx/merro60:via
    make chlx/merro60:all

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

