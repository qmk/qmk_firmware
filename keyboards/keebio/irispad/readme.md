# Irispad

An ergonomic gamepad based off of the Iris and sold by Keebio. [More info at Keebio](https://keeb.io).

* Keyboard Maintainer: [Bakingpy/nooges](https://github.com/nooges)
* Hardware Supported: RP2040
* Hardware Availability: [Keebio](https://keeb.io)

Make example for this keyboard (after setting up your build environment):

    make keebio/irispad/rev8:default

Example of flashing this keyboard:

    make keebio/irispad/rev8:default:flash

See [build environment setup](https://docs.qmk.fm/#/newbs_getting_started) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

A build guide for this keyboard can be found here: [Iris Build Guide](https://docs.keeb.io/iris-rev6-build-guide)

Note: The Irispad PCB is a repurposed Iris Rev. 8 PCB from a batch that had all of the diodes flipped, so if you would like to use a regular Iris Rev. 8 PCB, you will need to change `ROW2COL` to `COL2ROW` in `keyboard.json`.
