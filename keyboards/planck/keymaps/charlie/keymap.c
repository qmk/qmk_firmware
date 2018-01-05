#include "keymap.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = { /* Native */
      {KC_ESC,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    FUNC(2)}, 
      {KC_BSPC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
     {KC_TAB,     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT},
      {KC_DEL,     KC_LCTL, KC_NO,   KC_LSFT, KC_LALT, KC_SPC,        KC_NO,   KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT}
},	  
    [1] = { /* QWERTY->PHOTOSHOP */
      {KC_DELETE,  KC_0,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    FUNC(1)},
      {KC_O,       KC_G,    KC_S,    KC_U,    KC_T,    FUNC(27),  KC_F21,  KC_F10,  KC_F11,  KC_F7,   KC_F8,   KC_F9},
      {KC_TAB,     FUNC(4), FUNC(5),  FUNC(6),  KC_F1,   FUNC(7),  KC_F18,  KC_F19,  KC_F23,  KC_F20,  KC_F22,  FUNC(9)},
      {KC_COMM,    KC_DOT,  KC_R, FUNC(11), FUNC(3),  KC_SPC,        FUNC(12), KC_F2,   FUNC(8),  KC_F3,   KC_F14}
	  },
    [2] = { /* 2: FUNC(3 PHOTOSHOP */
      {KC_ESC,    FUNC(25), FUNC(26),   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO},
      {KC_NO,      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   FUNC(19), FUNC(20), FUNC(21)}, 
      {KC_C,       KC_NO,  FUNC(22),  FUNC(5),   KC_NO,   FUNC(23), KC_NO,   KC_NO,   KC_NO,   KC_NO,   FUNC(13), KC_NO},
      {FUNC(14),    FUNC(15), FUNC(16), FUNC(17), FUNC(3),   KC_SPC,        FUNC(18), KC_NO,   KC_NO,   KC_F24,  KC_NO}
	  }
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_DEFAULT_LAYER_SET(0),                             // set Qwerty layout
    [2] = ACTION_DEFAULT_LAYER_SET(1),                             // set Photoshop presets
    [3] = ACTION_LAYER_MOMENTARY(2),                                  // Photoshop function layer
 
    [4] = ACTION_MODS_KEY(MOD_LSFT | MOD_LCTL | MOD_LALT, KC_F9),   // photo folder AHK
    [5] = ACTION_MODS_KEY(MOD_LSFT | MOD_LCTL, KC_I),              // select inverse
    [6] = ACTION_MODS_KEY(MOD_LSFT, KC_M),                         // marquee select
    [7] = ACTION_MODS_KEY(MOD_LALT, KC_BSPC),                      // fill 
    [8] = ACTION_MODS_KEY(MOD_LSFT | MOD_LCTL | MOD_LALT, KC_X),    // warp
    [9] = ACTION_MODS_KEY(MOD_LCTL | MOD_LALT | MOD_LSFT, KC_F12),  // merge all new layer
    [10] = ACTION_MODS_KEY(MOD_LCTL, KC_MINS),                     // zoom out
    [11] = ACTION_MODS_KEY(MOD_LCTL, KC_H),                        // RBG sliders
    [12] = ACTION_MODS_KEY(MOD_LCTL, KC_S),                        // save
    [13] = ACTION_MODS_KEY(MOD_LSFT | MOD_LCTL, KC_F5),           // layer mask from transparancy 
    [14] = ACTION_MODS_KEY(MOD_LCTL, KC_F2),                     // stroke
    [15] = ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT, KC_F2),                     // stroke layer
    [16] = ACTION_MODS_KEY(MOD_LCTL, KC_0),                      // zoom 0
    [17] = ACTION_MODS_KEY(MOD_LSFT | MOD_LCTL, KC_H),             // HSV sliders
    [18] = ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT, KC_S),         // save as 
    [19] = ACTION_MODS_KEY(MOD_LSFT | MOD_LCTL | MOD_LALT, KC_F7),  // gaussian blur
    [20] = ACTION_MODS_KEY(MOD_LSFT | MOD_LCTL | MOD_LALT, KC_F8),  // motion blur
    [21] = ACTION_MODS_KEY(MOD_LSFT | MOD_LCTL, KC_X),            // liquify filter
    [22] = ACTION_MODS_KEY(MOD_LSFT, KC_MINS),                     // prev layer blending
    [23] = ACTION_MODS_KEY(MOD_LSFT | MOD_LCTL, KC_BSPC),             // KC_NOrmal layer blending
    [24] = ACTION_MODS_KEY(MOD_LSFT, KC_EQL),                      // next layer blending
    [25] = ACTION_MODS_KEY(MOD_LCTL, KC_Z),                        // step back
    [26] = ACTION_MODS_KEY(MOD_LCTL, KC_Y),                        // step forward
    [27] = ACTION_MODS_KEY(MOD_LCTL, KC_R),                        // rasterize
     
};
