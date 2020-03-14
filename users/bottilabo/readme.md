# QMK Harmonize library

Copyright 2019-2020 Bottilabo [twitter @bottilabo]
                         [https://github.com/bottilabo/qmk]

# QMK Harmonize library
- enables change qwerty layout to colemac,dvorak.... dynamically
- has max 3-layout and 3-IM. You can choose them at compile time.

# IM
- for now, mainly Japanese KANA input method
- 

# how to

- ADJ + G
no IM
- ADJ + F
choose IM1
- ADJ + D
choose IM2
- ADJ + S
choose IM3

- ADJ + B
QWERTY layout
- ADJ + V
choose KBLAYOUT1
- ADJ + C
choose KBLAYOUT2
- ADJ + X
choose KBLAYOUT3

- TL2(CAPS-Lock) + D
normal input mode. No IM. KBLAYOUT is applied.
- TL2(CAPS-Lock) + F
IM input mode. KBIM is applied.



# build examples
```
cd qmk_firmware

`make crkbd:bottilabo:avrdude EXTRAFLAGS='-DNO_KANA -DKBLAYOUT1=KB_COLEMAK -DKBLAYOUT2=KB_DVORAK -DKBIM1=IM_NICOLA'`

`make numatreus:bottilabo:avrdude EXTRAFLAGS='-DNO_KANA -DKBLAYOUT1=KB_COLEMAK -DKBLAYOUT2=KB_DVORAK -DKBIM1=IM_NICOLA'`

`make projectkb/alice:bottilabo:flash EXTRAFLAGS='-DNO_KANA -DKBLAYOUT1=KB_COLEMAK -DKBLAYOUT2=KB_DVORAK -DKBIM1=IM_NICOLA'`

```



# How to build
```
make crkbd:harmonize-crkbd EXTRAFLAGS='-DKBD=KBD_HARMONIZE -DKBLAYOUT1=KB_COLEMAK -DKBLAYOUT2=KB_DVORAK -DKBLAYOUT3=KB_MSIKI -DKBIM1=IM_ROMAJI_COLEMAK -DKBIM2=IM_TRON -DKBIM3=IM_SINJIS'
```

```
make crkbd:harmonize-crkbd EXTRAFLAGS='-DKBD=KBD_HARMONIZE -DKBLAYOUT1=KB_COLEMAK -DKBIM1=IM_ROMAJI_COLEMAK'
```


# built in keyboard layout

- arensito
- Astarte
- beakl4opt-ergo
- capewell-dvorak
- colemak
- colemak-mod_dh
- dvorak
- eucalyn
- harmonix
- harmony
- M式
- mtgap
- mtgap2
- norman
- plum
- qgmlwy
- workman

# build in Japanese IM

## KANA
- Nicola thumb shift layout 
- Tron layout
- Naginata-shiki

## Romaji
- KATANA-shiki
- M-shiki
- Romaji colemak


# How to change keyboard layout

copy qmk_firmware/users/bottilabo/KBD_HARMONIZE and build your own KBD_USER.
at compile, you can choose your keybord layout by adding compile option '-DKBK=KBD_USER'


# How to embed to you own keymap.c
You need
- name your layout ar bottilabo or copy qmk_firmware/users/bottilabo to your own layout so that qmk can find harmonize library.
- mapping from virtual keyboard layout(KBD_HARMONIZE) to your keybord.
- include harmonize library
- add to matrix_init_user
- add to matrix_scan_user
- add to process_record_user


## keymap.c
```
#include QMK_KEYBOARD_H

#define HAS_THUMBROW

//      +    +    +    *                                 *    +    +    +
//4     4    3    2    1    1      1              1      1    1    2    3    4      4
#define LAYOUT_remapper( \
ESC ,   NL5, NL4, NL3, NL2, NL1,              NR1, NR2, NR3, NR4, NR5,   NR6, NR7, BSPC,  \
TAB ,   L05, L04, L03, L02, L01,              R01, R02, R03, R04, R05,   R06, R07, BSLS,   \
CAPS,   L15, L14, L13, L12, L11,              R11, R12, R13, R14, R15,   R16, R17, ENTR,  \
LSFT,   L25, L24, L23, L22, L21,              R21, R22, R23, R24, R25,   R26,      RSFT,  \
MOUS,  LCTL,LALT,LGUI,                                            RGUI,RALT,RCTL,   ADJ, \
                       TL2,                                   TR2,                       \
       PGUP,                TL1,                         TR1,                UP,         \
HOME,  PGDN,END ,                  TL0,           TR0,                 LEFT,DOWN,  RIGT, \
INS ,DEL   ,PRNT,BRK,                                                ZENHN,KANA,MHEN,HENK  \
  ) \
  LAYOUT( \
ESC , L05, L04, L03, L02, L01,                     R01, R02, R03, R04, R05, R06,BSPC, \
CAPS, L15, L14, L13, L12, L11,                     R11, R12, R13, R14, R15, ENTR , \
LCTL, L24, L23, L22, L21, L25,                     R21, R22, R23, R24, R25, ADJ, \
        LGUI ,TL1   ,      TL0,   TR0,              TR1,RCTL,RALT  \
    )
#define LAYOUT_DEF(...)                  LAYOUT_remapper(__VA_ARGS__)

#include "harmonize.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  HARMONIZE_PROC_RECORD_USER;
  return true;
}
void matrix_init_user(void) {
    harmonize_init();
}
void matrix_scan_user(void) {
   HARMONIZE_MATRIX_SCAN_USER;
}

```



# License
　GPL3


