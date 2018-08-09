Handwired ABNT2 - 83 Alps
=========================

This firmware is for a Handwired ABNT2 keyboard, using a Teensy 2.0

ABNT2EX
~~~~
/* ABNT2EX - Default
  * Primeira Linha - Layer Principal ML
  * Segunda Linha - Layer Secundario FN
      * ,-------------------------------------------------------------------------------------------------------------------------------------.
      * |   \   |  1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  -   |   =  |    Bksp     |TAB   |   /  |  *   |   -   |
      * |  ESC  |  F1 |   F2 |   F3 |   F4 |   F5 |   F6 |   F7 |   F8 |   F9 |  F10 | F11  |  F12 |    Delete   |PScren|      |      | RESET |
      * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------|
      * | Tab   |  Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  ´   |   [  |     Enter   |   7  |   8  |  9   |   +   |
      * |       |     |      |      |      |      |      |      |      |      |      |      |      |             |      |      |      |       |
      * |-------+-----+------+------+------+-------------+------+------+------+------+------+------+------+      +------+------+------+-------|
      * | _FN   |  A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ç  |  ˜   |    }        |      |   4  |   5  |  6   |   =   |
      * | CAPS  |     |      |      |      |      |      |      |      |      |      |      |             |      |      |      |      |       |
      * |-------+-----+------+------+------+------|------+------+------+------+------+------+------+------+------+------+------+------+-------|
      * | Shift |  '  |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   ;  |   Rshift    |  UP  |   1  |   2  |  3   |       |
      * |       |     |      |      |      |      |      |      |      |      |      |      |      /      | PGUP |      |      |      |       |
      * |-------+-----+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+ Enter |
      * | Lctrl | Lgui| LAlt |                    Space                       | Ralt | Rgui | _FN  | Left | Down | Right|   0  |  .   |       |
      * |       |     |      |                                                |      |      |      |      | PGDw |      |      |      |       |
      * `-------------------------------------------------------------------------------------------------------------------------------------/
      */
~~~~

## Pinout

The following pins are used:
- Columns 1-15: B7, D2, D3, C6, C7, D5, D4, D6, D7, B4, B5, B6, F7, F6, F5, F4, F1, F0
- Rows 1-5: B0, B1, B2, B3, E6
But you can change these at MATRIX_ROW_PINS and MATRIX_COL_PINS at config.h

## To-DO

Implement a generic OLED screen for the keyboard using SSD1306. Since I am using a Teensy 2.0 to handwire it the pins should be:
- D0 (SCL), D1 (SCA), GND, VCC


Make example for this keyboard (after setting up your build environment):

	make handwired/abnt2_83:default

See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.
