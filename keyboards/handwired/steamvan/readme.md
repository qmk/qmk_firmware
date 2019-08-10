# SteamVan

The SteamVan is a 40% PCB that aims to meet the following goals:

* Switches oriented such that the LEDs are South-facing, for
  compatibility with Cherry profile keycaps.
* USB Type-C support in both A to C and C to C configurations.
* QMK support.
* ESD protection circuitry, including data line protection and a
  polyfuse on the VCC line.
* Support for per-switch LED backlighting.
* Fits in MiniVan keyboard cases.

More info on the project, including all of the design files, can be found [here](https://github.com/jmdaly/steamvan).

Keyboard Maintainer: [jmdaly](https://github.com/jmdaly)  
Hardware Supported: SteamVan PCB rev1  
Hardware Availability: Through group buys.

Make example for this keyboard (after setting up your build environment):

    make handwired/steamvan/rev1:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
