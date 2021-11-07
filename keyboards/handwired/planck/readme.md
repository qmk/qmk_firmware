# Plank Handwired

![plank handwired](https://i.imgur.com/khseWs7.jpeg)

A compact 40% (12x4) ortholinear keyboard kit sold by OLKB before they developed the rev1 PCB.

Keyboard Maintainer: [Wholteza](https://github.com/wholteza)
Hardware Supported: [Teensy 2.0](https://www.pjrc.com/store/teensy.html)
Hardware Availability: [PJRC](https://www.pjrc.com/store/teensy.html)

Make example for this keyboard (after setting up your build environment):

    make planck/rev4:default

Flashing example for this keyboard:

    make planck/rev4:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

-   **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
-   **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
-   **Keycode in layout**: Press the key mapped to `RESET` if it is available

## Teensy pinout

Can be changed in the `config.h`

Where `C0` and `R0` is **top left** when looking at the wiring of your keyboard (upside down).

| **COL/ROW** | **PIN** |
| ----------- | ------- |
| **C0**      | F0      |
| **C1**      | F1      |
| **C2**      | F4      |
| **C3**      | F5      |
| **C4**      | F6      |
| **C5**      | F7      |
| **C6**      | B6      |
| **C7**      | B5      |
| **C8**      | B4      |
| **C9**      | D7      |
| **C10**     | D6      |
| **C11**     | C7      |
| **R0**      | E6      |
| **R1**      | B3      |
| **R2**      | D1      |
| **R3**      | D0      |

neiorsnteioarstn
