# ppr.merro60

![ppr.merro60 PCB](https://i.imgur.com/xyQA68Xh.jpg)

- Standard 60% format keyboard PCB with USB-C and unified daughterboard compatibility.
- Modified cutouts to allow usage of certain tray mount cases into gummy gasket o-ring mount.
- Additional center flex cut.
- Meant to be manufactured in 1.2mm thickness.

* Keyboard Maintainer: [Alexander Lee](https://github.com/gaclee3b)
* Hardware Supported: chlx PCB ppr.merro60.x.x.x

Make example for this keyboard (after setting up your build environment):

    make chlx/ppr_merro60:default

Flashing example for this keyboard:

    make chlx/ppr_merro60:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter bootloader mode by any of the following options -
- When unplugged, holding the top-left key (typically ESC) while plugging in the keyboard
- When plugged in, pressing and releasing the reset button on the pcb bottom behind the CAPSLOCK / A-key region
- When plugged in, shorting out the two reset metal contacts near the 'z' key (accessible through the switch LED slot)
