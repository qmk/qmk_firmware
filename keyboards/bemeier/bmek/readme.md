# BMEK

![BMEK](https://i.imgur.com/p1KFi6ql.jpg)

BMEK combines the best of HHKB & Alice-likes. All PCB and case design files are open source.

* Keyboard Maintainer: [Bemeier](https://github.com/Bemeier)
* Hardware Supported: BMEK PCB rev1, rev2, rev3
* Hardware Availability: Case & PCB files: [github.com/bemeier/bmek](https://github.com/bemeier/bmek)

Make example for this keyboard, for an hhkb-like layout and keymap (after setting up your build environment):

    make bemeier/bmek/rev3:default

Make the VIA compatible firmware:

    make bemeier/bmek/rev3:via

The ```rev3```, denotes the version of the PCB.
Check on the PCB to find out which version you have, and set it to rev1, rev2 or rev3 accordingly (the BMEK group buy PCBs are all rev3).

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

# Layouts

Starting with rev3 (the version of the PCB to be shipped in the GB), the following layout options are supported:

![layouts](https://i.imgur.com/XuFxwthl.png)

Note that the keymap shown above may not accurately reflect the default keymap of the firmware (see the keymaps folder).
