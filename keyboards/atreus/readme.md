Atreus
===

A small mechanical keyboard that is based around the shape of the human hand.

These configuration files are specifically for the Atreus keyboards created by Phil Hagelberg (@technomancy). This keyboard is available in two variants: one powered by a Teensy 2, (usually hand-wired) one powered by an A-Star. (usually using a PCB) This repository currently assumes that you have an A-Star powered Atreus. If you are using a Teensy2, specify that by adding `TEENSY2=yes` to your `make` commands.

Keyboard Maintainer: QMK Community
Hardware Supported: Atreus PCB
Hardware Availability: https://atreus.technomancy.us

Make example for this keyboard (after setting up your build environment):

    make atreus-default-avrdude

See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.
