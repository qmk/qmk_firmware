# ErgoDash

![ErgoDash](https://github.com/omkbd/picture/blob/master/Ergodash.jpg)

Keyboard Maintainer: [omkbd](https://github.com/omkbd) [@omkbd](https://twitter.com/omkbd)  
Hardware Supported: ErgoDash PCB, Pro Micro ATmega32u4  
Hardware Availability: Order your own [yourself](https://github.com/omkbd/ErgoDash)


Make example for this keyboard (after setting up your build environment):

    make omkbd/ergodash/rev1:default

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

Install Example: (for pro micro)
    `make omkbd/ergodash/rev1:default:avrdude`

Note:  
  "rev1" is for PCB ver 1.0,1.1,1.2  
  **The original Rev 1 was owned only by the designer. Therefore, Rev1 has been removed. Since the current PCB is Rev1, we changed Rev2 to Rev1 to match the firmware version.**


# Layout
![layout](https://github.com/omkbd/picture/blob/master/ergodash-layout.png)

Layout Note:  
- In thumb cluster, it is not possible to use all 5 positions as small keys. (as pictured)
- The top 2 1u keys in the thumb cluster share the same connection.
- 2u key (center) position shares with the lower 1u key position

![PCB](https://github.com/omkbd/picture/blob/master/Ergodash_PCB.jpg)
