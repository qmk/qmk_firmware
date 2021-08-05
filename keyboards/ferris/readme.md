# Ferris

![Ferris, familly pic](https://i.imgur.com/TCjkquRh.jpeg)

A split 34 keys column staggered keyboard named and decorated after the rustlang mascott. All PCB files and some thoughts on the design are available on the [project's github page](https://github.com/pierrechevalier83/ferris)

* Keyboard Maintainer: [Pierre Chevalier](https://github.com/pierrechevalier83)
* Hardware Supported:
	* Ferris 0.1 (With atmega32u4 chip. Comes in 4 variants: base, low, high and compact)
	* Ferris 0.2 (With stm32f072 chip. Comes in 4 variants: bling, mini, high and compact)
	* Ferris sweep (With pro-micro. Comes in a couple of PCB edge cuts shapes, but with identical pinout)
* Hardware Availability: Pierre Chevalier has been selling keyboard kits (see the #ferris channel in the 40% discord chat). Wider availability is on the horizon.

Make examples for this keyboard (after setting up your build environment):

    make ferris/0_1:default
    make ferris/0_2:default
    make ferris/sweep:default:avrdude-split-right

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
