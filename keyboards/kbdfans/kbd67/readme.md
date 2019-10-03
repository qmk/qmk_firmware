# KBD67

A 65% keyboard sold in four variants. 
1. Rev1: Typical keyboard that had to be soldered together, supporting multiple layouts. The rev1 PCB is sold under the name "KBD65".  
2. HotSwap: Released in late 2018, Hotswap single layout keyboard. 
3. Rev2: Released in April/May 2019, the Rev2 also needs to be soldered together and supports multiple layouts. 
4. MKII RGB: Released in September 2019. ARM powered hotswap board. 

 **Firmware files are SPECIFIC to each board. Firmware files from one, will not work on the other.** Please use the `.hex` or `.bin` appropriate for your board.

Keyboard Maintainer: [MechMerlin](https://github.com/mechmerlin), [moyi4681](https://github.com/moyi4681)  
Hardware Supported: KBD67 rev1, rev2, hotswap, mkiirgb  
Hardware Availability: KBDFans  

Make examples for this keyboard (after setting up your build environment):

    make kbdfans/kbd67/rev1:default
    make kbdfans/kbd67/rev2:default
    make kbdfans/kbd67/hotswap:default
    make kbdfans/kbd67/mkiirgb:default  

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
