# Pteron36

![Pteron36](https://i.imgur.com/PuXPWYfh.jpg)

A 36-key keyboard with a bit more natural thumb cluster.

* Keyboard Maintainer: [Harshit Goel](https://github.com/harshitgoel96)
* Hardware Supported: Pteron36 using promicro.
* Hardware Availability: Files are available in the [pteron36 repository](https://github.com/harshitgoel96/pteron36-split-keyboard/releases/tag/v1.2.0)
  * The hardware is open source; you can simply send the Gerber to a PCB manufacturer and have them made.

Make example for this keyboard (after setting up your build environment):

    make pteron36:default

Flashing example for this keyboard:

    make pteron36:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Default Keymap and Miryoku Layout support

The keyboard was designed with miryoku layout in mind. The default layout is very basic and does not have much use, modify the keymap as you see fit. Build keyboard with manna-harbour_miryoku as keymap, qmk should compile the firmare without any issue.

    make pteron36:manna-harbour_miryoku

Add miryoku params as required.
Pteron36 uses community layout, hence there is no need for separate keymap folder for any keymap that support 5x3_3 layout.

## VIA support

The VIA keymap is working as intended. 

    make pteron36:via
