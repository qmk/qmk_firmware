Tritium Numpad
===

Keyboard Maintainer: QMK Community  
Hardware Supported: Handwired 6x4 numpads using promicro controller  
Hardware Availability: https://www.thingiverse.com/thing:2855938

Wiring is accomplished on the Pro Micro board using the following pins as rows:
* D2 : Row 1
* D3 : Row 2
* D4 : Row 3
* D5 : Row 4
* D6 : Row 5
* D7 : Row 6

and the following pins as columns:
* A3 : Col 1
* A1 : Col 2
* D15 : Col 3
* D16 : Col 4

Make example for this keyboard (after setting up your build environment):

    make tritium_numpad:default

Bootmagic is enabled.  Press the key at 0,0 (usually escape or numlock in the top left corner) while plugging the keyboard in to jump to bootloader.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
