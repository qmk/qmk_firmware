# Brick

![Brick, top view](https://i.imgur.com/BLJ6Tumh.jpg)
![Brick, layout options](https://i.imgur.com/JhsWzY7h.png)

Brick is a 12u, 4 row ortholinear keyboard designed as a drop in replacement for PCBs like the Niu Mini. Brick features a USB-C port, an ATMega32u4, RGB underglow, three possible rotary encoder locations, and multiple ortho layout options.

* Keyboard Maintainer: [pauper](https://github.com/pauperboards)
* Hardware Supported:
    * Brick v0.1 - prototype first run with red solder mask and needing a bodge wire across the top row encoder location.
    * Brick v0.2 - same layout and components as v0.1, but with the bodge fixed. This version was run as part of Cervello group buy by [P3DStore](http://p3dstore.com).
* Hardware Availability: Some remaining pcbs might be available for purchase from [P3D](http://p3dstore.com/collections/pcbs/products/cervello-pcb-only-group-buy).

Make example for this keyboard (after setting up your build environment):

    make pauperboards/brick:default

Flashing example for this keyboard:
    
    make pauperboards/brick:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader
Enter the bootloader in one of 2 ways:

* **Physical Reset Button**: Briefly press the button on the underside of the pcb, near the MCU.
* **Keycode**: Press the key mapped to `QK_BOOT` in your keymap, if available.
