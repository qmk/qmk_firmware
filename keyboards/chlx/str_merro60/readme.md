# str.merro60

str.merro60 PCB

A standard 60% format keyboard pcb with USB-C and unified daughterboard compatibility.
Has modified cutouts to allow usage of certain tray mount cases into gummy gasket o-ring mount.
Has RGB underglow.

* Keyboard Maintainer: [Alexander Lee](https://github.com/gaclee3b)
* Hardware Supported: chlx PCB str.merro60.1.1

Enter bootloader mode by any of the following options -
- When unplugged, holding the top-left key (typically ESC) while plugging in the keyboard
- When plugged in, pressing and releasing the reset button on the pcb bottom behind the CAPSLOCK / A-key region
- When plugged in, shorting out the two reset metal contacts near the spacebar switch location (NOT the spacebar switch pin holes)

Make example for this keyboard (after setting up your build environment):

    make chlx/str_merro60:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
