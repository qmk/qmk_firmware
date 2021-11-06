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

## LAYERS

new layer lower = arrow keys + numbers + F1-12
new layer raise = symbols

### BASE - done

| **#**  | **C0**  | **C1** | **C2** | **C3** | **C4**           | **C5** | **C6** | **C7**           | **C8** | **C9**     | **C10**  | **C11**   |
| ------ | ------- | ------ | ------ | ------ | ---------------- | ------ | ------ | ---------------- | ------ | ---------- | -------- | --------- |
| **R0** | TAB     | Q      | W      | E      | R                | T      | Y      | U                | I      | O          | P        | Å         |
| **R1** | ESC     | A      | S      | D      | F                | G      | H      | J                | K      | L          | Ö        | Ä         |
| **R2** | L_SHIFT | Z      | X      | C      | V                | B      | N      | M                | ,      | .          | -        | BACKSPACE |
| **R3** | L_CTRL  | <      | META   | L_ALT  | LAYER_HOLD_LOWER | SPACE  | NONE   | LAYER_HOLD_RAISE | ALT_GR | ARROW_DOWN | ARROW_UP | RETURN    |

### LOWER - done

| **#**  | **C0**       | **C1**       | **C2**     | **C3**      | **C4**           | **C5**           | **C6**     | **C7**            | **C8** | **C9**   | **C10** | **C11**      |
| ------ | ------------ | ------------ | ---------- | ----------- | ---------------- | ---------------- | ---------- | ----------------- | ------ | -------- | ------- | ------------ |
| **R0** | SE_PARAGRAPH | 1            | 2          | 3           | 4                | 5                | 6          | 7                 | 8      | 9        | 0       | +            |
| **R1** | ESC          | A            | ARROW_UP   | D           | F                | MOUSE_LEFT_CLICK | MOUSE_UP   | MOUSE_RIGHT_CLICK | K      | BACKTICK | UMLAUT  | SINGLE_QUOTE |
| **R2** | L_SHIFT      | ARROW_LEFT   | ARROW_DOWN | ARROW_RIGHT | V                | MOUSE_LEFT       | MOUSE_DOWN | MOUSE_RIGHT       | ,      | .        | -       | BACKSPACE    |
| **R3** | L_CTRL       | SINGLE_QUOTE | META       | L_ALT       | LAYER_HOLD_LOWER | SPACE            | NONE       | LAYER_HOLD_RAISE  | ALT_GR | VOL_DOWN | VOL_UP  | VOL_MUTE     |

### RAISE

| **#**  | **C0**       | **C1** | **C2** | **C3** | **C4**           | **C5**   | **C6**              | **C7**           | **C8** | **C9** | **C10**           | **C11**      |
| ------ | ------------ | ------ | ------ | ------ | ---------------- | -------- | ------------------- | ---------------- | ------ | ------ | ----------------- | ------------ |
| **R0** | SE_PARAGRAPH | F1     | F2     | F3     | F4               | PRNT_SCR | LAYER_TOGGLE_ARROWS | PAUSE_BREAK      | NUM_7  | NUM_8  | NUM_9             | NUM_LOCK     |
| **R1** | ESC          | F5     | F6     | F7     | F8               | INSERT   | HOME                | PAGE_UP          | NUM_4  | NUM_5  | NUM_6             | SINGLE_QUOTE |
| **R2** | L_SHIFT      | F9     | F10    | F11    | F12              | DELETE   | END                 | PAGE_DOWN        | NUM_1  | NUM_2  | NUM_3             | BACKSPACE    |
| **R3** | L_CTRL       | <      | META   | L_ALT  | LAYER_HOLD_LOWER | SPACE    | NONE                | LAYER_HOLD_RAISE | NUM_0  | .      | MEDIA_TOGGLE_PLAY | RETURN       |

### ARROWS - done

| **#**  | **C0**  | **C1** | **C2** | **C3** | **C4**           | **C5** | **C6** | **C7**           | **C8**     | **C9**     | **C10**     | **C11**   |
| ------ | ------- | ------ | ------ | ------ | ---------------- | ------ | ------ | ---------------- | ---------- | ---------- | ----------- | --------- |
| **R0** | TAB     | Q      | W      | E      | R                | T      | Y      | U                | I          | O          | P           | Å         |
| **R1** | ESC     | A      | S      | D      | F                | G      | H      | J                | K          | ARROW_UP   | Ö           | Ä         |
| **R2** | L_SHIFT | Z      | X      | C      | V                | B      | N      | M                | ARROW_LEFT | ARROW_DOWN | ARROW_RIGHT | BACKSPACE |
| **R3** | L_CTRL  | <      | META   | L_ALT  | LAYER_HOLD_LOWER | SPACE  | NONE   | LAYER_HOLD_RAISE | ALT_GR     | ARROW_DOWN | ARROW_UP    | RETURN    |
