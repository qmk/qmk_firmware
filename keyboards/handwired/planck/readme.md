# Plank Handwired

![plank handwired](https://i.imgur.com/khseWs7.jpeg)
![plank handwired](https://i.imgur.com/Y1XIjRK.jpeg)

A compact 40% (12x4) ortholinear keyboard kit sold by OLKB before they developed the rev1 PCB.

Keyboard Maintainer: [Wholteza](https://github.com/wholteza)
Hardware Supported: [Teensy 2.0](https://www.pjrc.com/store/teensy.html)

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb handwired/planck -km wholteza

See the [newbs build environment setup](https://docs.qmk.fm/#/newbs_getting_started).

## Teensy pinout

Can be changed in the `config.h`

Where `C0` and `R0` is **top left** if looking at the wiring of your keyboard (upside down).

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
