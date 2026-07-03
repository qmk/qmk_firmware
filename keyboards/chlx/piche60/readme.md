# piche60

![piche60 PCB](https://i.imgur.com/CBeJSUy.jpeg)

- 60% alice format keyboard pcb with USB-C and unified daughterboard compatibility.
- Layout adds 3 additional keys in the palm area voids of traditional alice format.
- USB-C can be snapped off and converted into an ai03 C3 compatible daughterboard.
- Left and right halves can be snapped off and connected through 14-pin JST-SH interfaces.
- PCB can be manufactured with top-side USB-C for compatibility with legacy alice PCBs. 

Keyboard Maintainer: [Alexander Lee](https://github.com/gaclee3b)
Hardware Supported: chlx PCB piche60.x.x.x; top-side USB version compatible with most keyboard cases using legacy alice format PCBs (i.e. lubrigante)
Hardware Availability: sales are typically done in-stock as bulk listings on reddit's mechanical keyboard market (r/mechmarket)

Make example for this keyboard (after setting up your build environment):

    make chlx/piche60:default

Flashing example for this keyboard:

    make chlx/piche60:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter bootloader mode by any of the following options -
- When unplugged, holding the top-left key (typically ESC) while plugging in the keyboard
- When already plugged in, pressing and releasing the reset button on the pcb bottom behind the CAPSLOCK / A-key region
- When already plugged in, shorting out the two reset metal contacts near the 'z' key (accessible through the switch LED slot)

