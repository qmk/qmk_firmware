# Chameleon 

![chameleon](imgur.com image replace me!)

* Chameleon is a 46-60 Key Grid Ortho Keyboard with optional 5x12 or 4x12 layouts *

* Keyboard Maintainer: [TweetyDaBird](https://github.com/TweetyDaBird)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: [Lectronz Store](https://lectronz.com/stores/tweetys-wild-thinking)
* Hardware Design: [GitHub](https://github.com/TweetyDaBird/Chameleon)

Make example for this keyboard (after setting up your build environment):

    make tweetydabird/chameleon:default

Flashing example for this keyboard:

    make tweetydabird/chameleon:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (top left) and plug in the keyboard
* **Physical reset/boot buttons**: Hold the 'BOOT' button and briefly press 'RESET' on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if available on your keymap
