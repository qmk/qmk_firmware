# XealouS Brown

My first handwired keyboard. Originally used TMK, now ported in full glory to QMK.

Build log at:
https://sites.google.com/site/xaelous/keyboards/handwired-keyboard

* Keyboard Maintainer: [alex-ong](https://github.com/alex-ong)
* Hardware Supported: Arduino Pro Micro or clone

Make example for this keyboard (after setting up your build environment):

    make handwired/xealousbrown:default


The brief list of speedhacks to make this keyboard blazing fast:
1) bit-bash implementation of scanning rows, columns. Very short delay between pin waiting.
2) Compiling with a few extra flags
3) Eager-per-key Debouncing algorithm (no 5ms delay before message is sent)
4) 1000hz polling

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
