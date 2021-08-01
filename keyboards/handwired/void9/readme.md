# void9

![void9](https://imgur.com/a/zPjiHee)

A Hand Wired 9 key macro pad.  Now with rotary encoders.

* Keyboard Maintainer: [Jay Oursler](https://github.com/yourusername)
* Hardware Supported: Pro Micro and clones
* Hardware Availability: Amazon [BitC](https://www.amazon.com/gp/product/B087CLZ5GR) which I used or [Pro Micro clone](https://www.amazon.com/ARCELI-Atmega32U4-Bootloadered-Development-Microcontroller/dp/B07J2Q3ZD5)(link is one example)

## Origins

This is originally by https://github.com/victorlucachi but he hasn't merged the code back to the mainline of QMK.  STL files on [github](https://github.com/victorlucachi/void9) or [thingiverse](https://www.thingiverse.com/thing:4222157).  Their [fork of qmk](https://github.com/victorlucachi/qmk_firmware) is about 6 months old and this just moves the Void9 code to the main QMK branch and merges it in.


If there are any issues with it I would be happy to maintain the mainline QMK handwired/void9.

## My modifications

I took the original and added in the rotary encoder in the handwired/void9:encoder.  The basics are the same, print the case, wire the matrix, wire the encoder, screw everything together.

I wired the rotary encoder to B1 and F7 randomly then swapped pad A and B to be correct for the encoder.  Still no clue which leg controlls which direction.


## Default ReadMe below.


Make example for this keyboard (after setting up your build environment):

    make void9:default

Flashing example for this keyboard:

    make void9:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
