# pluto12

![pluto12](https://i.imgur.com/XYtwexoh.jpg)

The pluto12 is a 4x3 macropad designed for use in the Penn State IEEE Student Chapter's [2021-22 workshop series](https://github.com/psuieee/projects2021). Designed by the 2021-22 Penn State IEEE Projects Committee.

* Keyboard Maintainer: [Will McGloughlin](https://github.com/wymcg)
* Hardware Supported: Pro Micro and derivatives
* Hardware Availability: [PCB and case files](https://github.com/psuieee/pluto12)

Make example for this keyboard (after setting up your build environment):

    make psuieee/pluto12:default

Flashing example for this keyboard:

    make psuieee/pluto12:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead.
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
