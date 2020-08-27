# 60_ansi_arrow
This is the 60% ANSI Arrow keyboard layout. 

## Requirements

### 1. Layout Defined
A keyboard's `.h` file needs to have `LAYOUT_60_ansi_arrow` defined
```c
/* 
 * LAYOUT_60_ansi_arrow
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0e     │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │1e   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d      │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┬───┤
 * │30      │32 │33 │34 │35 │36 │37 │38 │39 │3a │3c    │3d │3e │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬───┼───┼───┤
 * │40  │41  │43  │46                      │4a │4b │4c │4d │4e │
 * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┘
 */
#define LAYOUT_60_ansi_arrow( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,      k0e, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d,      \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a,      k3c, k3d, k3e, \
    k40, k41,      k43,           k46,                k4a, k4b, k4c, k4d, k4e  \
) { \
    { k00, k01,   k02,   k03, k04,   k05,   k06, k07,   k08,   k09,   k0a, k0b,   k0c, KC_NO, k0e   }, \
    { k10, KC_NO, k12,   k13, k14,   k15,   k16, k17,   k18,   k19,   k1a, k1b,   k1c, k1d,   k1e   }, \
    { k20, KC_NO, k22,   k23, k24,   k25,   k26, k27,   k28,   k29,   k2a, k2b,   k2c, k2d,   KC_NO }, \
    { k30, KC_NO, k32,   k33, k34,   k35,   k36, k37,   k38,   k39,   k3a, KC_NO, k3c, k3d,   k3e   }, \
    { k40, k41,   KC_NO, k43, KC_NO, KC_NO, k46, KC_NO, KC_NO, KC_NO, k4a, k4b,   k4c, k4d,   k4e   }  \
}
```

### 2. Configuring rules.mk
`rules.mk` needs to have the following line:

        LAYOUTS = 60_ansi_arrow

### 3. Defining a Keymap
A keymap must be defined at         

    qmk_firmware/layouts/community/60_ansi_arrow/yourfoldername/keymap.c
This keymap must have a `LAYOUT_60_ansi_arrow` layout defined.
```c
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  
  /*
   * Default Layer [0]
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
   * │Esc│1  │2  │3  │4  │5  │6  │7  │8  │9  │0  │-  │=  │Bspc   │
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
   * │Tab  │Q  │W  │E  │R  │T  │Y  │U  │I  │O  │P  │[  │]  │\    │
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
   * │Caps L│A  │S  │D  │F  │G  │H  │J  │K  │L  │;  │'  │Enter   │
   * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┬───┤
   * │Shift   │Z  │X  │C  │V  │B  │N  │M  │,  │.  │Shift │↑  │/  │
   * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬───┼───┼───┤
   * │Ctl │OS  │Alt │          Space         │Alt│Ctl│←  │↓  │→  │
   * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┘
   */
     [0] = LAYOUT_60_ansi_arrow(KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
                                KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
                                KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
                                KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_RSFT, KC_UP, KC_SLSH,
                                KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, LT(2, KC_RALT), LT(1, KC_RCTL), KC_LEFT, KC_DOWN, KC_RGHT
     ),

  /*
   * Fn Layer [1]
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
   * │`  │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│Delete │
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
   * │Bri+ │   │   │End│Rst│   │   │   │Ins│   │P S│   │   │Eject│
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
   * │Bri-  │   │S L│   │   │   │Hm │   │   │   │   │   │Mute    │
   * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┬───┤
   * │Vol+    │   │   │Cal│   │   │N L│Ml │   │   │Pause │P U│   │
   * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬───┼───┼───┤
   * │Vol-│Rwd │F FD│           Play         │Stp│   │Prv│P D│Nxt│
   * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┘
   */
	 [1] = LAYOUT_60_ansi_arrow(KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
                                KC_BRIU, KC_TRNS, KC_TRNS, KC_END, RESET, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS, KC_TRNS, KC_PSCR, KC_TRNS, KC_TRNS, KC_EJCT,
                                KC_BRID, KC_TRNS, KC_SLCK, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE,
                                KC_VOLU, KC_TRNS, KC_TRNS, KC_CALC, KC_TRNS, KC_TRNS, KC_NLCK, KC_MAIL, KC_TRNS, KC_TRNS, KC_PAUS, KC_PGUP, KC_TRNS,
                                KC_VOLD, KC_MRWD, KC_MFFD, KC_MPLY, KC_MSTP, KC_TRNS, KC_MPRV, KC_PGDN, KC_MNXT
     ),

  /*
   * Fn Layer [2]
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
   * │   │   │   │   │   │   │   │   │   │   │   │   │   │       │
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
   * │     │R T│R M│Hu+│Hu-│Sa+│Sa-│Br+│Br-│   │   │   │   │     │
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
   * │      │   │   │   │   │   │   │   │   │   │   │   │        │
   * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┬───┤
   * │        │   │   │   │BL-│B T│BL+│B C│   │   │      │   │   │
   * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬───┼───┼───┤
   * │    │    │    │                        │   │   │   │   │   │
   * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┘
   */
	 [2] = LAYOUT_60_ansi_arrow(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                KC_TRNS, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, BL_DEC, BL_TOGG, BL_INC, BL_STEP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
     )
};
```
