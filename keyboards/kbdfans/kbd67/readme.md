# KBD67

A 65% keyboard sold in several variants supporting KBDFan's different 65% lineups each with their own different revisions.

1. [Rev1](rev1/): Released in early 2018. Atmega32u4 soldered keyboard. Sold under the name "KBD65".
2. [HotSwap](hotswap/): Released in late 2018. Atmega32U4 hotswap single layout keyboard.
3. [Rev2](rev2/): Released in April/May 2019. Atmega32u4 soldered keyboard.
4. [MKII](mkii_soldered/): Released in September 2019, designed by ai03. Atmega32u4 soldered keyboard. ESD Protected
5. [MKII RGB V1](mkiirgb/v1/): Released in September 2019. Arm hotswap board.
6. [MKII RGB V2](mkiirgb/v2/): Released in December 2019. Atmega32u4 hotswap board. ESD Protected.
6. [MKII RGB V2*](mkiirgb/v3/): Released in March 2021. Atmega32u4 hotswap board. ESD Protected. Uses LUFA bootloader and different inswitch RGB implementation. No visible markings differentiating it from the previous V2.

 **Firmware files are SPECIFIC to each board. Firmware files from one, will not work on the other.** Please use the `.hex` or `.bin` appropriate for your board.

* Keyboard Maintainer: [MechMerlin](https://github.com/mechmerlin), [moyi4681](https://github.com/moyi4681)
* Hardware Supported: KBD67 rev1, rev2, hotswap, mkii, mkiirgb v1, mkiirgb v2, etc.
* Hardware Availability: KBDFans

Make examples for this keyboard (after setting up your build environment):

    make kbdfans/kbd67/rev1:default
    make kbdfans/kbd67/rev2:default
    make kbdfans/kbd67/hotswap:default
    make kbdfans/kbd67/mkii_soldered:default
    make kbdfans/kbd67/mkiirgb/v1:default
    make kbdfans/kbd67/mkiirgb/v2:default
    make kbdfans/kbd67/mkiirgb/v3:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
