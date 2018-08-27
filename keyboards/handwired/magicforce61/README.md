Magicforce "61" Handwired
=======================

Basically I cut 7 keys off the magicforce68 and handwired everything to a
teensy++ 2.0 to make it a ~60% board.

## Wiring Layout

![Wiring Layout](https://imgur.com/gallery/RxYyA)

## Pinout

The following pins are used:

  ```
  #define MATRIX_ROW_PINS { D0, D1, D2, D3, D4 }
  #define MATRIX_COL_PINS { B5, B4, B3, B2, B1, B0, E7, E6, F0, F1, F2, F3, F4, F5 } 
  ```

## Compiling and loading the firmware

To build the firmware, run `make handwired/magicforce61`.

Flash the firmware using the teensy loader or avrdude.
