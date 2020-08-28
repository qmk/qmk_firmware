#include QMK_KEYBOARD_H

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
