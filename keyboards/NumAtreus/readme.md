NumAtreus
===

A small mechanical keyboard that is based around the shape of the human hand.


Keyboard Maintainer: [Phil Hagelberg](https://github.com/technomancy)  
Hardware Supported: NumAtreus, PCB-based or hand-wired  
Hardware Availability: 

Make example for this keyboard (after setting up your build environment):

    make numatreus:default:avrdude

Unlike the TMK firmware, this command should be run from the root of
the repository, not the directory containing this readme.

If your keyboard layout is a mirror image of what you expected (i.e. you do not get QWERTY on the left but YTREWQ on the right), then you have an A-Star powered Atreus (older than March 2016) with PCB labels facing *down* instead of up. Specify that by adding `PCBDOWN=yes` to your `make` commands.
