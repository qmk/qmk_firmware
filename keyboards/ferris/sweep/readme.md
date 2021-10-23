# Ferris sweep

![Ferris sweep, top view](https://i.imgur.com/5qCZUv6h.jpg)
![Ferris sweep, bottom view](https://i.imgur.com/ZC47CJth.jpg)

A version of the Ferris keyboard that uses a daughterboard, designed by the fantastic @davidphilipbarr with some input from @pierrechevalier83 for the copper pad. All PCB files are available on the [project's github page](https://github.com/davidphilipbarr/Sweep)

* Keyboard Maintainer: [Pierre Chevalier](https://github.com/pierrechevalier83)
* Hardware Supported:
	* Ferris sweep (With pro-micro. Comes in a couple of PCB edge cuts shapes, but with identical pinout)
* Hardware Availability: @iamnotyourbroom in the 40% discord chat server may have some spares for you.

Initial [EE_HANDS](https://docs.qmk.fm/#/feature_split_keyboard?id=handedness-by-eeprom) make examples for this keyboard (after setting up your build environment):

    make ferris/sweep:default:avrdude-split-left
    make ferris/sweep:default:avrdude-split-right

Subsequent make example for both sides:

    make ferris/sweep:default

[Bootmagic lite](https://docs.qmk.fm/#/feature_bootmagic?id=bootmagic-lite) is also configured on the top right key for the right halve.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
