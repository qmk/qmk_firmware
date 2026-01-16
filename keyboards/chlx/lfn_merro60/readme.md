# lfn.merro60

![lfn.merro60 PCB](https://i.imgur.com/naIgvKy.jpg)

- Standard 60% format keyboard PCB with USB-C and unified daughterboard compatibility.
- Modified cutouts to allow usage of certain tray mount cases into gummy gasket o-ring mount.
- Meant to be manufactured in 2mm thickness.

* Keyboard Maintainer: [Alexander Lee](https://github.com/gaclee3b)
* Hardware Supported: chlx PCB lfn.merro60.x.x.x

Make example for this keyboard (after setting up your build environment):

    make chlx/lfn_merro60:default

Flashing example for this keyboard:

    make chlx/lfn_merro60:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter bootloader mode by any of the following options -
- When unplugged, holding the top-left key (typically ESC) while plugging in the keyboard
- After plugging in, press and release the reset button on the pcb top-side near the spacebar switch locations
- After plugging in, short out the two reset metal contacts near the 'z' key (accessible through the switch LED slot)
