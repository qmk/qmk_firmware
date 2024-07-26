# DP3000

![dp3000 macropad](https://i.imgur.com/uBHS8EYh.jpg)

dp3000 is a simple yet elegant macropad, 2x4 (8 keys), dual encoder, embedded with an Atmel 32u4 chip, powered by QMK.
* Rev. 1 Support RGB matrix
* Rev. 2 Support RGB light (underglow)
* Keyboard Maintainer: [Deddia Permana](https://github.com/depermana12)
* Hardware Supported: DP3000 PCB rev1 and rev2, ATmega32u4
* Hardware Availability: [tokopedia.com/gundamtricks](https://www.tokopedia.com/gundamtricks)

Make example for this keyboard (after setting up your build environment):

    make dp3000/rev1:default
    make dp3000/rev2:default

Flashing example for this keyboard:

    make dp3000/rev1:default:flash
    make dp3000/rev2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* Bootmagic reset: Hold down the key at (0,0) in the matrix (left rotary encoder push switch) and plug in the keyboard
* Physical reset button: Briefly press reset button twice, located in front of the first rotary encoder (left rotary encoder)
* Keycode in layout: Press the key mapped to QK_BOOT if it is available
