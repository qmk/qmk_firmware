# Keymap Wrappers

> Pattern adapted from users/drashna/wrapper.h

Defines several object macros for common keycode sets. Each macro typically
covers 5 keycodes with a left- or right-hand orientation, and macros are
generally grouped into rows of three or four.

> TODO: Use keymap builder to generate images.

## Example

```
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// clang-format off
[_MODS] = LAYOUT_wrapper(
    _______, ___________________BLANK___________________, ...
    ...
),
//clang-format on
}
```

Substitute the appropriate `LAYOUT` function, e.g., `LAYOUT_planck_grid` for your board.

## Wrappers

> **How to Read the Tables**
>
> - Headers are numbered when wrapper is not hand-specific
> - Headers use `L` and `R` to indicate handedness
> - Headers use `P`, `R`, `M`, and `I` to indicate pinky, ring, middle, and index, respectively
> - Wrappers define a maximum of **five** keycodes -- hands are shown on the same row for readability

### Alpha: Colemak mod-DH

| #   | LP  | LR  | LM  | LI  | LI+ | RI+ | RI  | RM  | RR  | RP  |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 1   | Q   | W   | F   | P   | B   | J   | L   | U   | Y   | ;ˆ  |
| 2   | A°  | R°  | S°  | T°  | G   | M   | N°  | E°  | I°  | O°  |
| 3   | Z   | X   | C   | D   | V˜  | K   | H   | ,   | .   | /   |

- **ˆ:** (Optional) Replace `;` with `'` (top-right)
- **°:** (Optional) Home row modifiers on tap-hold (GACS, SCAG)
- **˜:** (Optional) Tap-hold `shift` on `v`

### Alpha: QWERTY

| #   | LP  | LR  | LM  | LI  | LI+ | RI+ | RI  | RM  | RR  | RP  |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 1   | Q   | W   | E   | R   | T   | Y   | U   | I   | O   | P   |
| 2   | A   | S   | D   | F   | G   | H   | J   | K   | L   | ;   |
| 3   | Z   | X   | C   | V   | B   | N   | M   | ,   | .   | /   |

### Blank(-ish)

Defines macros for common filler.

| 1    | 2    | 3    | 4    | 5    |
| ---- | ---- | ---- | ---- | ---- |
| TRNS | TRNS | TRNS | TRNS | TRNS |
| xxxx | xxxx | xxxx | xxxx | xxxx |

| LP   | LR   | LM   | LI   | LI+  | RI+  | RI   | RM   | RR   | RP   |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| LGUI | LALT | LCTL | LSFT | TRNS | TRNS | RSFT | RCTL | LALT | RGUI |

### Adjust

| #   | LP     | LR    | LM   | LI    | LI+    | RI+  | RI     | RM     | RR   | RP   |
| --- | ------ | ----- | ---- | ----- | ------ | ---- | ------ | ------ | ---- | ---- |
| 1   | Reset  | Debug | xxxx | Term+ | Term-  | xxxx | AGNORM | AGSWAP | xxxx | xxxx |
| 2   | RgbTog | Hue+  | Sat+ | Val+  | RgbMod | xxxx | CLMKDH | QWERTY | xxxx | xxxx |
| 3   | xxxx   | Hue-  | Sat- | Val-  | xxxx   | xxxx | xxxx   | xxxx   | xxxx | xxxx |

> Recommend: Define Right side per-board

### Function

| #   | 1   | 2   | 3   | 4   |
| --- | --- | --- | --- | --- |
| 1   | F1  | F2  | F3  | F4  |
| 2   | F5  | F6  | F7  | F8  |
| 3   | F9  | F10 | F11 | F12 |

### Media

| #   | 1     | 2     | 3     | 4    | 5    |
| --- | ----- | ----- | ----- | ---- | ---- |
| 1   | AuOn  | MiOn  | MuOn  | Brm+ | Vol+ |
| 2   | AuOff | MiOff | MuOff | Brm- | Vol- |
| 3   | Play  | Stop  | Next  | Prev | Mute |

### Nav

| #   | RI+   | RI   | RM    | RR    | RP    |
| --- | ----- | ---- | ----- | ----- | ----- |
| 1   | Pg Up | Home | Wh Dn | Wh Up | End   |
| 2   | Pg Dn | Left | Down  | Up    | Right |
| 3   | xxxx  | xxxx | xxxx  | xxxx  | xxxx  |

### Numpad

- `X Y` indicates the character `X` on keypress and character `Y` on `shift` keypress
- Second table shows characters with `alt` keypress

| #   | RI+   | RI    | RM    | RR    | RP    |
| --- | ----- | ----- | ----- | ----- | ----- |
| 1   | Del   | `7 &` | `8 _` | `9 (` |       |
| 2   | `- _` | `4 $` | `5 %` | `6 ^` | `*`   |
| 3   | `= +` | `1 !` | `2 @` | `3 #` | `, <` |
| 4   |       | `0 )` | `. >` |       |       |

| #   | RI+   | RI    | RM    | RR    | RP    |
| --- | ----- | ----- | ----- | ----- | ----- |
| 1   |       | `¶ ‡` | `• °` | `ª ·` | `« »` |
| 2   | `– —` | `¢ ›` | `∞ ﬁ` | `§ ﬂ` | `° °` |
| 3   | `≠ ±` | `¡ ⁄` | `™ €` | `£ ‹` | `≤ ¯` |
| 4   |       |       | `º ‚` |       |       |

### Symbols

| #   | LP   | LR   | LM   | LI   | LI+  |
| --- | ---- | ---- | ---- | ---- | ---- |
| 1   | ~    | \`   | (    | )    |      |
| 2   | LGUI | LALT | \[ ° | \] ° | \_ - |
| 3   | xxxx | xxxx | {    | }    | LSFT |

- **°:** Home row modifiers on tap-hold (GACS, SCAG)

### VIM

| #   | LP  | LR  | LM  | LI  | LI+ |
| --- | --- | --- | --- | --- | --- |
| 1   | Q°  | W°  | :   |     |     |

- **°:** Via transparency

## Typical Layers

My keymaps typically use the following layers.

| #   | Name       | Via           | Left      | Right  |
| --- | ---------- | ------------- | --------- | ------ |
| 0   | Colemak DH | Adjust        |           |        |
| 1   | QWERTY     | Adjust        |           |        |
| 2   | Mouse      | tap-dance     | n/a       | n/a    |
| 3   | Lower      | L home thumb  | symbols   | numpad |
| 4   | Raise      | L outer thumb |           |        |
| 5   | Nav        | R home thumb  | home mods | nav    |
| 6   | Adjust     | tap-dance     | RGB       | MEDIA  |
