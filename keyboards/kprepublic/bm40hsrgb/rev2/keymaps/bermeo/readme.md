# Bermeo Keymap

Key3map made to be personalized with per-key RGB using MATRIX_ENABLE.

The use of this keymap is based on a corne layout| focused to be used with one hand. Focused on a front-end perspective| being used with Figma| Spline and Adobe software. Also to be used with Microsoft Remote Desktop.

|RGB Matrix ||||||||||||
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
|  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 | 11 |
| 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 |
| 24 | 25 | 26 | 27 | 28 | 29 | 30 | 31 | 32 | 33 | 34 | 35 |
| 36 | 37 | 38 | 39 | 40 | 41 | 41 | 42 | 43 | 44 | 45 | 46 |

## Default Layer

|_QWERTY ||||||||||||
|:--|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|--:|
| LCTL_T(F3)      | Q | W | E | R | T | Y | U | I | O | P |      GRAVE      |
| LALT_T(TAB)     | A | S | D | F | G | H | J | K | L | ; |        ↵        |
| LSFT_T(&larr;)  | Z | X | C | V | B | N | M | , | . | / | RGUI_T(&rarr;)  |
| | | | LGUI_T(&darr;) | MO(1)| SPACE|SPACE | ⌫ | MO(2)| RSFT_T( &uarr;) |  |

## Lower Layer (cyan)

|_LOWER ||||||||||||
|:--|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|--:|
|CTL_T(F5) |  1 |   2 |   3 |  4 |    5 |   6 |   7 |   8 |   9 |   0 |   ESCAPE |
|ALT_T(TAB) | &larr; | &darr; |  &uarr; | &rarr; | ↵ | [ | ] | \ | ' | : |   ↵   |
|ALT(&larr;) |  F1 |   F2 |   C |  V |  ⌫ | - | = | < | > | ? | LALT(&rarr;)     |
| | | | LGUI_T(PAGE_DOWN)|  | SPACE|SPACE| LALT(⌫) | TG(3) | RSFT_T(PAGE_UP) |  |

## Upper Layer (orange)

|_RAISE ||||||||||||
|:--|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|--:|
LCTL_T(F4) |  ! | @ | # | $ | % | ˆ | & | *      | ( | ) |       ˜      |
LALT_T(TAB) | Ã |   |   |   |   | { | } | &#124; | " | : |       ↵      |
LALT(&larr;) |  |   | Ç |   |   | _ | + | <      | > | ? | LALT(&rarr;) |
|||| LGUI_T(END) | TG(3) | SPACE|SPACE | DEL || RSFT_T(HOME)|          |

## Numpad Layer

|_NUMPAD ||||||||||||
|:--|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
| matrix_toggle | matrix_step  |         |    |    |    |    | 7 | 8 | 9 | * |   /   |
|| increase_hue | increase_sat | RGB_VAI | increase_val ||   | 4 | 5 | 6 | - |   ↵   |
|| decrease_hue | decrease_sat | RGB_VAD | decrease_val || . | 1 | 2 | 3 | + |       |
| RESET         ||  TG(3)  |     TG(3)|TG(3)    |  TG(3) | ⌫ | TG(3) | 0 |   |       |



## Mod-taps used

For convenience, QMK includes some Mod-Tap shortcuts to make common combinations more compact in your keymap:
| Key         |                             Description |
| :--         |                                     --: |
| LCTL_T(kc)  | Left Control when held, kc when tapped. |
| LSFT_T(kc)  | Left Shift when held, kc when tapped.   |
| LALT_T(kc)  | Left Alt when held, kc when tapped.     |
| ALT(kc)     | Left Alt + kc when tapped.              |
| LGUI_T(kc)  | Left GUI when held, kc when tapped.     |
| RSFT_T(kc)  | Right Shift when held, kc when tapped.  |
| RGUI_T(kc)  | Right GUI when held, kc when tapped.    |