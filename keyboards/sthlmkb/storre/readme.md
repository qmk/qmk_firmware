# storre

![Storre](https://i.imgur.com/xxb9p5yh.jpeg)

Större is an easy to build 75%ish keyboard using only through hole components. It utilises a Pro Micro footprint development board to enable flexible connectivity and simplify the soldering experience (no more tricksy USB ports).

* Keyboard Maintainer: [mohoyt](https://github.com/mohoyt)
* Hardware Supported: större, development board with Pro Micro footprint  (e.g. Pro Micro, Elite-C, Nice!Nano, SparkFun Pro Micro RP2040)
* Hardware Availability: [sthlm kb](https://sthlmkb.com)

Make example for this keyboard (after setting up your build environment):

    make sthlmkb/storre:default

Flashing example for this keyboard:

    make sthlmkb/storre:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
