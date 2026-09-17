# sleepy_keeb_split

![sleepy_keeb_split](https://i.imgur.com/f5VEA8C.jpeg)


The Sleepy Keeb Split is an ortholinear 4x6 split keyboard inspired by the Planck. This is a hand-wired keyboard using the pro-micro or similar microcontrollers. The keyboard is designed to be used with a 3d printed case, which is also available on the Sleepy Craft Studios website. The unique element to this design is the integrated hotswap holders present in the 3d printed plate. The plate also includes diode holders for easy soldering.

This keyboard is available as a kit as on the sleepycraftstudios.com, and is designed to be a beginner friendly hand-wired keyboard. The keyboard is also compatible with VIA, and the keymap is designed to be easily modified.

The STL files are made available under the CC BY-NC-SA 4.0 license.

* Keyboard Maintainer: [Sleepy Craft Studios](https://github.com/sleepy-craft-studios)
* Hardware Supported: Pro-micro (tested), Elite-C, any other ATMega32U4 based microcontroller should work.
* Hardware Availability: Kits can be purchased at [Sleepy Craft Studios](https://sleepycraftstudios.com/shop/sleepy-keeb-split-(diy))

Make example for this keyboard (after setting up your build environment):

    make sleepy_craft_studios/sleepy_keeb_split:default

Flashing example for this keyboard:

    make sleepy_craft_studios/sleepy_keeb_split:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Short GND and RST**: Short these two pins twice quickly with a pair of pliers or paperclip to enter the bootloader.
