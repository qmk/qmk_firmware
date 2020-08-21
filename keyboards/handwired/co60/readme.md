# co60

The CO60 is a 60% PCB that aims to meet the following goals:

* Switches oriented such that the LEDs are South-facing, for
  compatibility with Cherry profile keycaps.
* USB Type-C support in both A to C and C to C configurations.
* QMK support.
* A variety of split spacebar configurations, including split 6.25U
  space and split 7U space.
* ESD protection circuitry, including data line protection and a
  polyfuse on the VCC line.
* Support for per-switch LED backlighting.
* Fits in standard 60% keyboard cases.

More info on the project, including all of the design files, can be found [here](https://github.com/jmdaly/CO60).

Keyboard Maintainer: [jmdaly](https://github.com/jmdaly)  
Hardware Supported: Supports the CO60 PCB rev1, rev6, rev7  
Hardware Availability: Through group buys.

Make example for this keyboard (after setting up your build environment):

    make handwired/co60/rev7:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
