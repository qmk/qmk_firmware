# Dactyl Kinesis

Essentially a Dactyl CC physical key layout with an additional top row, further emulating the Kinesis Advantage (*1|2*) physical key layout.

* Keyboard Maintainer: [dmik](https://github.com/dmik)
* Hardware Supported: Pro Micro controller, or clone of

Make example for this keyboard (after setting up your build environment):

    make handwired/dactyl_kinesis:default

Flashing example for this keyboard:

    make handwired/dactyl_kinesis:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Kinesis Advantage Keymap

### About

This keymap is designed after Kinesis Advantage's QWERTY layout with the following key differences:
 - There are only 10 F-keys in the main layer, F1 and F2 are moved to additional LOWER layer.
 - The INS key acts like a LOWER layer activation key and Del in LOWER layer ats like INS.
 - LCtl is placed where CAPS should be and CAPS is moved to a free key after F10.
 - Brigtness and volume control keys are added to LOWER layer.

 The keymap file also contains RAISE layer but it is currently equivalent to LOWER layer and does
 not have an activation key mapped. It is intended for possible extensions.

### Keymap

       Main QUERTY layer:
       ,-------------------------------------------.                           ,-------------------------------------------.
       | ESC    |  F1  |  F2  |  F3  |  F4  |  F5  |                           |  F6  |  F7  |  F8  |  F9  |  F10 | CAPS   |
       |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
       | =      |   1  |   2  |   3  |   4  |   5  |                           |   6  |   7  |   8  |   9  |   0  |   -    |
       |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
       | Tab    |   Q  |   W  |   E  |   R  |   T  |                           |   Y  |   U  |   I  |   O  |   P  |   \    |
       |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
       | LCtl   |   A  |   S  |   D  |   F  |   G  |                           |   H  |   J  |   K  |   L  |   ;  |   '    |
       |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
       | LShift |   Z  |   X  |   C  |   V  |   B  |                           |   N  |   M  |   ,  |   .  |   /  | RShift |
       `--------+------+------+------+------+------'                           `------+------+------+------+------+--------'
                |   `  | LOWER| Left | Rght |                                         |  Up  |  Dn  |   [  |   ]  |
                `---------------------------'                                         `---------------------------'
                                               ,-------------.      ,-------------.
                                               | LGui | LAlt |      | RCtl | RGui |
                                        ,------|------|------|      |------+------+------.
                                        |      |      | Home |      | PgUp |      |      |
                                        | BkSp | Del  |------|      |------|Enter |Space |
                                        |      |      | End  |      | PgDn |      |      |
                                        `--------------------'      `--------------------'

       LOWER layer:
       ,-------------------------------------------.                           ,-------------------------------------------.
       |        |  F11 |  F12 |      |      |      |                           |BriDn |BriUp |VMute |VolDn |VolUp |        |
       |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
       |        |      |      |      |      |      |                           |      |      |      |      |      |        |
       |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
       |        |      |      |      |      |      |                           |      |      |      |      |      |        |
       |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
       |        |      |      |      |      |      |                           |      |      |      |      |      |        |
       |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
       |        |      |      |      |      |      |                           |      |      |      |      |      |        |
       `--------+------+------+------+------+------'                           `------+------+------+------+------+--------'
                |      |      |      |      |                                         |      |      |      |      |
                `---------------------------'                                         `---------------------------'
                                               ,-------------.      ,-------------.
                                               |      |      |      |      |      |
                                        ,------|------|------|      |------+------+------.
                                        |      |      |      |      |      |      |      |
                                        |      | INS  |------|      |------|      |      |
                                        |      |      |      |      |      |      |      |
                                        `--------------------'      `--------------------'

### Key Matrix Wiring

The below picture shows correspondence between the keys and the row/column wires of the left and
right halves:

       ,-------------------------------------------.                           ,-------------------------------------------.
       |  L00   | L01  | L02  | L03  | L04  | L05  |                           | R00  | R01  | R02  | R03  | R04  |  R05   |
       |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
       |  L10   | L11  | L12  | L13  | L14  | L15  |                           | R10  | R11  | R12  | R13  | R14  |  R15   |
       |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
       |  L20   | L21  | L22  | L23  | L24  | L25  |                           | R20  | R21  | R22  | R23  | R24  |  R25   |
       |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
       |  L30   | L31  | L32  | L33  | L34  | L35  |                           | R30  | R31  | R32  | R33  | R34  |  R35   |
       |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
       |  L40   | L41  | L42  | L43  | L44  | L45  |                           | R40  | R41  | R42  | R43  | R44  |  R45   |
       `--------+------+------+------+------+------'                           `------+------+------+------+------+--------'
                | L50  | L51  | L52  | L53  |                                         | R52  | R53  | R54  | R55  |
                `---------------------------'                                         `---------------------------'
                                               ,-------------.      ,-------------.
                                               | L64  | L65  |      | R60  | R61  |
                                        ,------|------|------|      |------+------+------.
                                        |      |      | L63  |      | R62  |      |      |
                                        | L54  | L55  |------|      |------| R50  | R51  |
                                        |      |      | L62  |      | R63  |      |      |
                                        `--------------------'      `--------------------'

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
