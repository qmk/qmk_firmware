Atreus
===

A small mechanical keyboard that is based around the shape of the human hand.

These configuration files are specifically for the Atreus keyboards created by Phil Hagelberg (@technomancy). This keyboard is available in two variants: one powered by a Teensy 2, (usually hand-wired) one powered by an A-Star. (usually using a PCB) This repository currently assumes that you have an A-Star powered Atreus. If you are using a Teensy2, specify that by adding `TEENSY2=yes` to your `make` commands.

Keyboard Maintainer: [Phil Hagelberg](https://github.com/technomancy)  
Hardware Supported: Atreus, PCB-based or hand-wired  
Hardware Availability: https://atreus.technomancy.us

Make example for this keyboard (after setting up your build environment):

    make atreus:default:avrdude

Unlike the TMK firmware, this command should be run from the root of
the repository, not the directory containing this readme.

If your keyboard layout is a mirror image of what you expected (i.e. you do not get QWERTY on the left but YTREWQ on the right), then you have an A-Star powered Atreus (older than March 2016) with PCB labels facing *down* instead of up. Specify that by adding `PCBDOWN=yes` to your `make` commands.

See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.
