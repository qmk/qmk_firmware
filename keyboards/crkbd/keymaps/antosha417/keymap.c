// Copyright 2021 Anton Kavalkou (@antosha417)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "sendstring_dvorak.h"

typedef union {
  uint32_t raw;
  struct {
    bool is_macos :1;
  };
} user_config;

user_config config;

enum layers {
  _QWERTY,
  _DVORAK,
  _LOWER,
  _RAISE,
  _TOP,
  _BOTTOM,
};

enum keycodes {
  QWERTY = SAFE_RANGE,

  RUS_LANG,
  EN_LANG,
  HEB_LANG,

  VIM_SAVE,

  CHNGE_OS,
  DELETE_WORD,

#define MOD_TAP_KEY(keycode, tap_action, mod_on_action, mod_off_action)   \
  keycode,
#include "mod_tap_keys.h"
#undef MOD_TAP_KEY
};


#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define TOP MO(_TOP)
#define BOTTOM MO(_BOTTOM)
#define LANG  TG(_DVORAK)
#define KC_CAD LALT(LCTL(KC_DEL))
#define KC_CAH LALT(LCTL(KC_HOME))

#define E_SFT LSFT_T(KC_E)
#define D_SFT LSFT_T(KC_D)
#define A_ALT LALT_T(KC_A)
#define O_GUI LGUI_T(KC_O)
#define U_CTRL LCTL_T(KC_U)

#define T_SFT RSFT_T(KC_T)
#define K_SFT RSFT_T(KC_K)
#define S_ALT RALT_T(KC_S)
#define N_GUI RGUI_T(KC_N)
#define H_CTRL RCTL_T(KC_H)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_ESC,  A_ALTQ,  S_GUIQ,   D_SFT,  F_CTLQ,    KC_G,                         KC_H,  J_CTLQ,   K_SFT,  L_GUIQ,  SCLN_Q, KC_QUOT,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
					BOTTOM,   KC_SPC,   LOWER,      RAISE,  KC_SPC,     TOP
				    //`--------------------------'  `--------------------------'
),

[_DVORAK] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_TAB, KC_QUOT, KC_COMM,  KC_DOT,    KC_P,    KC_Y,                         KC_F,    KC_G,    KC_C,    KC_R,    KC_L, KC_BSPC,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_LCTL,   A_ALT,   O_GUI,   E_SFT,  U_CTRL,    KC_I,                         KC_D,  H_CTRL,   T_SFT,   N_GUI,   S_ALT, KC_QUOT,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_LSFT, KC_SCLN,    KC_Q,    KC_J,    KC_K,    KC_X,                         KC_B,    KC_M,    KC_W,    KC_V,   KC_Z,  KC_ESC,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
					_______, _______, _______,    _______, _______, _______
				    //`--------------------------'  `--------------------------'
),

[_LOWER] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_F11, KC_UNDS, KC_MINS, KC_TILD, KC_PERC, KC_QUOT,                      _______, KC_CIRC,  KC_GRV, KC_BSLS, KC_PIPE, KC_MINS,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_DEL, KC_LBRC, KC_LCBR, KC_PLUS, KC_LPRN,  KC_EQL,                      KC_ASTR, KC_RPRN, KC_EXLM, KC_RCBR, KC_RBRC, KC_BSPC,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    _______,  KC_CAD,  KC_CAH, _______,    LANG, _______,                      _______,HEB_LANG, EN_LANG,RUS_LANG, _______, _______,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
					_______, _______, _______,    _______, _______, _______
				    //`--------------------------'  `--------------------------'
                                                        //^^^^^^^
),


[_RAISE] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_F11, _______, _______, KC_DLR,  KC_AMPR, _______,                     KC_COLON, KC_QUES,   KC_AT, KC_HASH, KC_SLSH, KC_F12,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    _______,    KC_7,    KC_5,    KC_3,    KC_1,    KC_9,                         KC_0,    KC_2,    KC_4,    KC_6,    KC_8, KC_BSPC,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    _______,   KC_F7,   KC_F5,   KC_F3,   KC_F1,   KC_F9,                       KC_F10,   KC_F2,   KC_F4,   KC_F6,   KC_F8, _______,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
					_______, _______, _______,    _______, _______, _______
				    //`--------------------------'  `--------------------------'
                                                                    //^^^^^^^
),

[_TOP] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
    _______,CHNGE_OS, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD,                      RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    _______, _______, _______, KC_DOWN, KC_UP,   _______,                      _______, _______, _______, _______, _______, _______,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
					_______, _______, _______,    _______, _______, _______
				    //`--------------------------'  `--------------------------'
                                                                                      //^^^^^^^
),

[_BOTTOM] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
    _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, KC_RGHT, _______,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    _______, _______, _______, _______, _______, _______,                      _______, KC_LEFT, _______, _______, _______, _______,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    _______, _______, _______, _______, _______, _______,                      _______, KC_VOLD, KC_VOLU, _______, _______, _______,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
					_______, _______, _______,    _______, _______, _______
				    //`--------------------------'  `--------------------------'
                                      //^^^^^^^
)

};

enum combo_events {
  // combos for dvorak layer
  RU_COMBO,
  EN_COMBO,
  HEB_COMBO,
  ESC_COMBO,
  TAB_COMBO,
  ENT_COMBO,
  DEL_COMBO,
  SAVE_COMBO,
  BSPC_COMBO,
  BSPCW_COMBO,

  // combos for qwerty layer
  RUQ_COMBO,
  ENQ_COMBO,
  HEBQ_COMBO,
  ESCQ_COMBO,
  TABQ_COMBO,
  ENTQ_COMBO,
  DELQ_COMBO,
  SAVEQ_COMBO,
  BSPCQ_COMBO,
  BSPCWQ_COMBO,

  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM ru_combo[] = {KC_R, U_CTRL, COMBO_END};
const uint16_t PROGMEM en_combo[] = {U_CTRL, S_ALT, COMBO_END};
const uint16_t PROGMEM heb_combo[] = {KC_I, KC_V, COMBO_END};
const uint16_t PROGMEM esc_combo[] = {H_CTRL, U_CTRL, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {T_SFT, A_ALT, COMBO_END};
const uint16_t PROGMEM ent_combo[]= {E_SFT, N_GUI, COMBO_END};
const uint16_t PROGMEM del_combo[] = {KC_D, E_SFT, COMBO_END};
const uint16_t PROGMEM bspc_combo[] = {KC_C, H_CTRL, COMBO_END};
const uint16_t PROGMEM bspcw_combo[] = {N_GUI, U_CTRL, COMBO_END};
const uint16_t PROGMEM save_combo[] = {O_GUI, H_CTRL, COMBO_END};

const uint16_t PROGMEM ruq_combo[] = {KC_O, F_CTLQ, COMBO_END};
const uint16_t PROGMEM enq_combo[] = {F_CTLQ, SCLN_Q, COMBO_END};
const uint16_t PROGMEM hebq_combo[] = {KC_G, KC_DOT, COMBO_END};
const uint16_t PROGMEM escq_combo[] = {F_CTLQ, J_CTLQ, COMBO_END};
const uint16_t PROGMEM tabq_combo[] = {K_SFT, A_ALTQ, COMBO_END};
const uint16_t PROGMEM entq_combo[] = {D_SFT, L_GUIQ, COMBO_END};
const uint16_t PROGMEM delq_combo[] = {KC_H, D_SFT, COMBO_END};
const uint16_t PROGMEM bspcq_combo[] = {KC_I, J_CTLQ, COMBO_END};
const uint16_t PROGMEM bspcwq_combo[] = {L_GUIQ, F_CTLQ, COMBO_END};
const uint16_t PROGMEM saveq_combo[] = {S_GUIQ, J_CTLQ, COMBO_END};

combo_t key_combos[] = {
    [RU_COMBO] = COMBO(ru_combo, RUS_LANG),
    [EN_COMBO] = COMBO(en_combo, EN_LANG),
    [HEB_COMBO] = COMBO(heb_combo, HEB_LANG),
    [ESC_COMBO] = COMBO(esc_combo, KC_ESC),
    [TAB_COMBO] = COMBO(tab_combo, KC_TAB),
    [ENT_COMBO] = COMBO(ent_combo, KC_ENT),
    [DEL_COMBO] = COMBO(del_combo, KC_DEL),
    [BSPC_COMBO] = COMBO(bspc_combo, KC_BSPC),
    [SAVE_COMBO] = COMBO(save_combo, VIM_SAVE),
    [BSPCW_COMBO] = COMBO(bspcw_combo, DELETE_WORD),

    [RUQ_COMBO] = COMBO(ruq_combo, RUS_LANG),
    [ENQ_COMBO] = COMBO(enq_combo, EN_LANG),
    [HEBQ_COMBO] = COMBO(hebq_combo, HEB_LANG),
    [ESCQ_COMBO] = COMBO(escq_combo, KC_ESC),
    [TABQ_COMBO] = COMBO(tabq_combo, KC_TAB),
    [ENTQ_COMBO] = COMBO(entq_combo, KC_ENT),
    [DELQ_COMBO] = COMBO(delq_combo, KC_DEL),
    [BSPCQ_COMBO] = COMBO(bspcq_combo, KC_BSPC),
    [SAVEQ_COMBO] = COMBO(saveq_combo, VIM_SAVE),
    [BSPCWQ_COMBO] = COMBO(bspcwq_combo, DELETE_WORD),
};
 

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

void oled_render_layer_state(void) {
    oled_write_P(PSTR("layer: "), false);
    switch (get_highest_layer(layer_state|default_layer_state)) {
      case _QWERTY:
        oled_write_ln_P(PSTR("qwerty"), false);
        break
      case _DVORAK:
        oled_write_ln_P(PSTR("dvorak"), false);
        break;
      case _LOWER:
        oled_write_ln_P(PSTR("lower"), false);
        break;
      case_RAISE:
        oled_write_ln_P(PSTR("raise"), false);
        break;
      case _TOP:
        oled_write_ln_P(PSTR("top"), false);
        break;
      case _BOTTOM:
        oled_write_ln_P(PSTR("bottom"), false);
        break;
      default:
        oled_write_ln_P(PSTR("unknown"), false);
        break;
    }
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_ln_P(PSTR("nice cock"), false);
        oled_render_layer_state();
    } else {
        oled_render_logo();
    }
    return false;
}

#endif // OLED_ENABLE

void keyboard_post_init_user(void) {
  config.raw = eeconfig_read_user();
  layer_on(_DVORAK);
}

void set_english_language(void) {
  layer_on(_DVORAK);
  tap_code16(LSFT(LCTL(LGUI(KC_1))));
}

void set_russian_language(void) {
  layer_off(_DVORAK);
  tap_code16(LSFT(LCTL(LGUI(KC_2))));
}

void set_hebrew_language(void) {
  layer_off(_DVORAK);
  tap_code16(LSFT(LCTL(LGUI(KC_3))));
}

void delete_word(void) {
  if (config.is_macos) {
    tap_code16(A(KC_BSPC));
  } else {
    tap_code16(C(KC_BSPC));
  }
}

#define CASE(keycode, key_pressed_action, key_released_action)   \
  case (keycode):                                               \
    if (record->event.pressed) {                                \
      key_pressed_action;                                       \
    } else {                                                    \
      key_released_action;                                      \
    }                                                           \
    return false;                                               \
    break;

#define CASE_PRESSED(keycode, key_pressed_action) CASE(keycode, key_pressed_action, {});

#define CASE_MOD_TAP_KEY(keycode, tap_action, mod_off_action) \
  CASE(keycode, {                                  \
    keycode ## _TIMER = timer_read();                         \
    IS_ ## keycode ## _ACTIVE = true;                         \
  }, {                                                        \
    if(IS_ ## keycode ## _MOD_ACTIVE) {                       \
      mod_off_action;                          		      \
    } else if (IS_ ## keycode ## _ACTIVE) {                   \
      tap_action;                                             \
    }                                                         \
    IS_ ## keycode ## _MOD_ACTIVE = false; 		      \
    IS_ ## keycode ## _ACTIVE = false;                        \
  });

#define MOD_TAP_KEY(keycode, tap_action, mod_on_action, mod_off_action) \
uint16_t keycode ## _TIMER = 0;                                 	\
bool IS_ ## keycode ## _ACTIVE = false; 		                \
bool IS_ ## keycode ## _MOD_ACTIVE = false;
#include "mod_tap_keys.h"
#undef MOD_TAP_KEY

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  #ifdef OLED_ENABLE
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
#endif //OLED_ENABLE

  switch (keycode) {
    CASE_PRESSED(EN_LANG, set_english_language());
    CASE_PRESSED(RUS_LANG, set_russian_language());
    CASE_PRESSED(HEB_LANG, set_hebrew_language());

    CASE_PRESSED(VIM_SAVE, {set_english_language(); SEND_STRING(SS_TAP(X_ESC)SS_LSFT(SS_TAP(X_SCLN))SS_TAP(X_W)SS_TAP(X_ENT));});

    CASE_PRESSED(CHNGE_OS, {config.is_macos ^= 1; eeconfig_update_user(config.raw);});
    CASE_PRESSED(DELETE_WORD, delete_word());

    #define MOD_TAP_KEY(keycode, tap_action, mod_on_action, mod_off_action) \
    CASE_MOD_TAP_KEY(keycode, tap_action, mod_off_action);
    #include "mod_tap_keys.h"
    #undef MOD_TAP_KEY
  }

  #define MOD_TAP_KEY(keycode, tap_action, mod_on_action, mod_off_action) \
  if (IS_ ## keycode ## _ACTIVE && !IS_ ## keycode ## _MOD_ACTIVE) {      \
    if (timer_elapsed(keycode ## _TIMER) <= TAPPING_TERM) {               \
      tap_action;                                                         \
      IS_ ## keycode ## _ACTIVE = false;                                  \
    }                                                    		  \
  }
  #include "mod_tap_keys.h"
  #undef MOD_TAP_KEY

  return true;
}

void matrix_scan_user(void) {
  #define MOD_TAP_KEY(keycode, tap_action, mod_on_action, mod_off_action) \
  if (IS_ ## keycode ## _ACTIVE) {                                        \
    if (timer_elapsed(keycode ## _TIMER) > TAPPING_TERM) {                \
      mod_on_action;                                                      \
      IS_ ## keycode ## _MOD_ACTIVE = true;                               \
    }                                                    		  \
  }
  #include "mod_tap_keys.h"
  #undef MOD_TAP_KEY
}

