# Atreus

![Atreus](https://atreus.technomancy.us/photos/1.jpg)

A small mechanical keyboard that is based around the shape of the human hand.

Keyboard Maintainer: [Phil Hagelberg](https://github.com/technomancy)  
Hardware Supported: Atreus, PCB-based or hand-wired  
Hardware Availability: https://atreus.technomancy.us

These configuration files are specifically for the Atreus keyboards created by Phil Hagelberg (@technomancy). This keyboard is available in two variants: one powered by a Teensy 2 (usually hand-wired), one powered by an A-Star (usually using a PCB). You will need to use different `make` commands depending on the variant you have; see examples below.

Make example for this keyboard (after setting up your build environment):

    make atreus:default:avrdude

If you would like to use one of the alternative controllers:

    make atreus/astar:default:avrdude
    make atreus/teensy2:default:teensy

If your keyboard layout is a mirror image of what you expected (i.e. you do not get QWERTY on the left but YTREWQ on the right), then you have an A-Star powered Atreus (older than March 2016) with PCB labels facing *down* instead of up. Specify that by adding `PCBDOWN=yes` to your `make` commands, e.g.

    make PCBDOWN=yes atreus:default:avrdude

*Unlike the TMK firmware, these commands should be run from the root of the repository, not the directory containing this readme.*

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
