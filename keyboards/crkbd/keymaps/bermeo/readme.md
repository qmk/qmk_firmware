# Bermeo Layout for Corne

## Features

### *Corne for neo-latin creatives*

* Usable with left hand only (Figma, Adobe, Spline, etc) to combo with mouse.
* Delete and enter keys on the left side.
* Z and X on left side with lower layer used to control the monitor's brigtness.
* Arrow keys on left hand (vim logic)
* All accentuations used in Romance (neo-latin) languages like Spanish, Portuguese, French and Italian - ` ~ ^ ' - and a direct ã and ç within one hold and tap.

### Modern OLED Support

* Non-intrusive OLED layer indicator.
* Non-intrusive OLED modifier indicators ⌘ ⇧ ⌥  ⌃.
* Fully animated Luna on left side.
  

### Full per-key RGB Matrix support

With the index of every key mapped in the table below to be used with `rgb_matrix_set_color(index, r, g, b)`;.

#### Indexes of the keys

|||||||||||||||
|:--:|:--:|:--:|:--:|:--:|:--:|--|--|:--:|:--:|:--:|:--:|:--:|:--:|
| 24 | 23 | 18 | 17 | 10 | 9 ||| 36 | 37 | 44 | 45 | 50 | 51 |
| 25 | 22 | 19 | 16 | 11 | 8 ||| 35 | 38 | 43 | 46 | 49 | 52 |
| 26 | 21 | 20 | 15 | 12 | 7 ||| 34 | 39 | 42 | 47 | 48 | 53 |
|||||            14 | 13 |  6 | 33  | 40 | 41            |||||

Each layer uses the Key's `14` LED as an visual indicator:

* ⚫️ _Default layer
* 🔵 _Lower (0)
* 🟠 _Raise (1)
* 🟢 _Numpad (2)
* ⚪️ _CTRL and Command
* 🟡 _Shift

## Usage

To compile and flash, from `qmk setup` folder, run:

    make crkbd:bermeo:flash

## Mod-taps

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

## Macros

|Layer | Name    | Description                                                                       | Keys          |
| :--: | --:     | --                                                                                | --:           |
|  🟠  | CEDILLA |  Directly outputs ç                                                               | ' + c         |
|  🟠  | AO      |  Directly outputs ã                                                               | shift + ` + a |
|  🟠  | ASPAS   |  Outputs ", since diaeresis[^1] are less used than " (for coding and quoting) | shift + ' + space |

## Layers

### QWERTY

|||||||||||||||
|:--|:--:|--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|--:|
| LCTL_T(F3)      | Q | W | E | R | T ||| Y | U | I | O | P |      GRAVE      |
| LALT_T(TAB)     | A | S | D | F | G ||| H | J | K | L | ; |        ↵        |
| LSFT_T(&larr;)  | Z | X | C | V | B ||| N | M | , | . | / | RGUI_T(&rarr;)  |
|⚫️||||  LGUI_T(&darr;) | MO(1) | SPACE |  ⌫ | MO(2)| RSFT_T( &uarr;)     |||||

### LOWER

|||||||||||||||
|:--|:--:|--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|--:|
|CTL_T(F5)   |  1  |  2  |  3  |  4  |  5  |||  6  |  7  |  8  |  9  |  0  | ESCAPE |
|ALT_T(TAB)  | &larr; | &darr; |  &uarr; | &rarr; | ↵ ||| [ | ] | \ | ' | : |   ↵   |
|ALT(&larr;) | F1 | F2 |   C |  V |  ⌫ ||| - | = | < | > | ? |   LALT(&rarr;)       |
|🔵||||      LGUI_T(PAGE_DOWN) |  | SPACE | LALT(⌫) | TG(3) | RSFT_T(PAGE_UP)   |||||

### RAISE

|||||||||||||||
|:--|:--:|--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|--:|
LCTL_T(F4) |  ! | @ | # | $ | % ||| ˆ | & | *      | ( | ) |       ˜      |
LALT_T(TAB) | Ã |   |   |   |   ||| { | } | &#124; | " | : |       ↵      |
LALT(&larr;) |  |   | Ç |   |   ||| _ | + | <      | > | ? | LALT(&rarr;) |
|🟠||||  LGUI_T(END) | TG(3) | SPACE| DEL|   | RSFT_T(HOME)           |||||

### NUMPAD

|||||||||||||||
|:--|:--:|--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
|  RGB_TOG ||         |         |         |||   | 7 | 8 | 9 | * | / |
||  RGB_HUI | RGB_SAI | RGB_VAI | RGB_SPI |||   | 4 | 5 | 6 | - | ↵ |
||  RGB_HUD | RGB_SAD | RGB_VAD | RGB_SPD ||| . | 1 | 2 | 3 | + |   |
|🟢|||                TG(3)| TG(3) | TG(3) | ⌫ | TG(3) | 0       ||||

## Compiled size

    28658/28672 (99%, 14 bytes free)

If more space is needed, start with deactivating Luna's animations.

add crkbd/keymaps/armand1m

## Credits

Guilherme Bermêo [(github)](https://git.bermeo.dev)

### Thanks

* @armand1m
* @brneor
* @drashna
* @hellsingcoder
* @soundmonster

[^1]: The diaeresis (/daɪˈɛrəsɪs, -ˈɪər-/ dy-ERR-ə-sis, -⁠EER-; also known as the trema) and the umlaut (/ˈʊmlaʊt/) are two different diacritical marks that (in modern usage) look alike. They both consist of two dots ¨ placed over a letter, usually a vowel; when that letter is an i or a j, the diacritic replaces the tittle: ï. In computer systems, both forms have the same code point (binary code). Their appearance in print or on screen may vary between typefaces but rarely within the same typeface. The "diaeresis" diacritic is used to mark the separation of two distinct vowels in adjacent syllables when an instance of diaeresis (or hiatus) occurs, so as to distinguish from a digraph or diphthong.
The "umlaut" diacritic, in contrast, indicates a sound shift phenomenon – also known as umlaut – in which a back vowel becomes a front vowel.
Neither of these phenomena occur in English, except in loanwords (like naïve) or for stylistic reasons (as in the Brontë family or Mötley Crüe).