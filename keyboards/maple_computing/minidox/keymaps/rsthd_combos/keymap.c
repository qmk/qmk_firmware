#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _RSTHD,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum combo_events {
  TOP_L,
  TOP_R,
  MID_L,
  MID_R,
  BOT_L,
  BOT_R,
  HN_QUOT,
  TOP_CTR,
  MID_CTR,
  BOT_CTR,
};

const uint16_t PROGMEM fk_combo[] = {KC_F, KC_K, COMBO_END};
const uint16_t PROGMEM zl_combo[] = {KC_Z, KC_L, COMBO_END};
const uint16_t PROGMEM hd_combo[] = {KC_H, KC_D, COMBO_END};
const uint16_t PROGMEM mn_combo[] = {KC_M, KC_N, COMBO_END};
const uint16_t PROGMEM pb_combo[] = {KC_P, KC_B, COMBO_END};
const uint16_t PROGMEM xw_combo[] = {KC_X, KC_W, COMBO_END};
const uint16_t PROGMEM hn_combo[] = {KC_H, KC_N, COMBO_END};
const uint16_t PROGMEM kz_combo[] = {KC_K, KC_Z, COMBO_END};
const uint16_t PROGMEM dm_combo[] = {KC_D, KC_M, COMBO_END};
const uint16_t PROGMEM bx_combo[] = {KC_B, KC_X, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [TOP_L] = COMBO(fk_combo, KC_ESC),
  [TOP_R] = COMBO(zl_combo, KC_AT),
  [MID_L] = COMBO(hd_combo, KC_TAB),
  [MID_R] = COMBO_ACTION(mn_combo),
  [BOT_L] = COMBO(pb_combo, KC_HASH),
  [BOT_R] = COMBO(xw_combo, KC_AMPR),
  [HN_QUOT] = COMBO(hn_combo, KC_QUOT),
  [TOP_CTR] = COMBO_ACTION(kz_combo),
  [MID_CTR] = COMBO_ACTION(dm_combo),
  [BOT_CTR] = COMBO_ACTION(bx_combo),
};

  void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
      case MID_R:
      if (pressed) {
        tap_code16(LALT(KC_3));
      }
      break;
      case TOP_CTR:
        if (pressed) {
          set_oneshot_mods(MOD_LGUI);
        }
        break;
      case MID_CTR:
        if (pressed) {
          set_oneshot_mods(MOD_LALT);
        }
        break;
      case BOT_CTR:
        if (pressed) {
          set_oneshot_mods(MOD_LCTL);
        }
        break;
    }
  }

// Defines for task manager and such
// For insertion in keymap
#define KILL LGUI(LALT(KC_ESC)) //Force quit controls
#define SCRCAP LCTL(LSFT(LGUI(KC_5))) //Screen capture controls
#define DSK_LFT LGUI(LCTL(KC_LEFT))
#define DSK_RT  LGUI(LCTL(KC_RIGHT))


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


[_RSTHD] = LAYOUT(
    KC_J,    KC_C,    KC_Y,     KC_F, KC_K,              KC_Z,  KC_L,   KC_COMM,  KC_U,   KC_Q,
    KC_R,    KC_S,    KC_T,     KC_H, KC_D,              KC_M,  KC_N,   KC_A,     KC_I ,  KC_O,
    LCTL_T(KC_SLSH), LALT_T(KC_V), LGUI_T(KC_G), KC_P, KC_B,      KC_X,  KC_W, RGUI_T(KC_DOT), RALT_T(KC_SCLN),RCTL_T(KC_MINS),
          OSM(MOD_LSFT), LT(_LOWER, KC_BSPC), KC_E,      KC_SPC, LT(_RAISE, KC_ENT),  OSM(MOD_LSFT)
),
[_RAISE] = LAYOUT(
  KC_PAST, KC_7,    KC_8,   KC_9,  KC_PLUS,       KC_NUBS, LALT(KC_2), _______, LALT(KC_4), KC_DLR,
  KC_CIRC, KC_4,    KC_5,   KC_6,    KC_EQL,      LSFT(KC_NUBS), KC_GRV,   KC_TILD,  KC_PIPE, KC_BSLS,
  _______, RALT_T(KC_1), KC_2, KC_3,KC_PERC,      _______, _______,    _______, _______, _______,
                  _______, MO(_ADJUST), KC_0,     _______, _______, _______
),
[_LOWER] = LAYOUT(
   _______, KC_LBRC, KC_QUES, KC_RBRC, KC_BRMU,         KC_PGUP,  KC_HOME, KC_UP,   KC_END,  KC_VOLU,
   KC_ESC, KC_LPRN,  KC_EXLM, KC_RPRN, KC_BRMD,         KC_PGDN, KC_LEFT, KC_DOWN, KC_RIGHT, KC_VOLD,
   _______, _______, _______, _______, _______,         _______, KC_MPRV, KC_MPLY, KC_MNXT, KC__MUTE,
                      _______, _______, _______,        KC_DEL,  MO(_ADJUST),  _______
),
[_ADJUST] =  LAYOUT(
  _______,     KC_F7, KC_F8, KC_F9,  SCRCAP,        _______, KC_F10,  KC_F11, KC_F12, _______,
  _______,     KC_F1, KC_F2, KC_F3, _______,        _______, KC_F4, KC_F5,  KC_F6, _______,
  OSM(MOD_LCTL),_______, _______, _______, QK_BOOT,  KILL, _______, _______,  _______, OSM(MOD_RCTL),
                    _______, _______, _______,       _______, _______,  _______
)

};
