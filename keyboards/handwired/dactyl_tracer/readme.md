# Dactyl Tracer

![DactylTracer](https://i.imgur.com/ReCBppEh.jpeg)

The Dactyl Tracer is a handwired, split bodied, concave key-well, columnar keyboard. Case design is similar to the [Dactyl CC](/keyboards/handwired/dactyl_cc) though overall design is closer to the [Dactyl ManuForm](/keyboards/handwired/dactyl_manuform/). The `Q` and `P` keys are vertically offset, from `A` and `;` keys respectively, to allow for easier actuation by third/ring finger.

* Keyboard Maintainer: [Michael Johns](https://github.com/mjohns)
* Hardware Supported: Pro Micro controller, or clone of
* Hardware Availability: [Case Files](https://github.com/mjohns/tracer)

Make example for this keyboard (after setting up your build environment):

    make handwired/dactyl_tracer:default

Flashing example for this keyboard:

    make handwired/dactyl_tracer:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
