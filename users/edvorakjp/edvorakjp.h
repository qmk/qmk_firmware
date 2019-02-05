#ifndef EDVORAKJP
#define EDVORAKJP

#include "quantum.h"
#include "action_layer.h"

#define EECONFIG_EDVORAK (uint8_t *)20

extern keymap_config_t keymap_config;

enum edvorakjp_layers {
  _EDVORAK = 0,
  _EDVORAKJ1,
  _EDVORAKJ2,
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _EXTRA,
};

enum edvorakjp_keycodes {
  EDVORAK = SAFE_RANGE,
  QWERTY,
  LOWER,
  RAISE,
  KC_MAC,
  KC_WIN,
  KC_EXTON,
  KC_EXTOFF,
  KC_JPN,
  KC_ENG,
  KC_AI,
  KC_OU,
  KC_EI,
  KC_ANN,
  KC_ONN,
  KC_ENN,
  KC_INN,
  KC_UNN,
  NEW_SAFE_RANGE
};

enum tap_dance_code {
  TD_LOWER = 0,
  TD_RAISE
};

// base
void dvorakj_layer_off(void);
void matrix_init_user(void);
void matrix_init_keymap(void);
uint32_t layer_state_set_user(uint32_t state);
uint32_t layer_state_set_keymap(uint32_t state);
bool process_record_user(uint16_t keycode, keyrecord_t *record);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

// status
void edvorakjp_status_init(void);
bool get_enable_jp_extra_layer(void);
void set_enable_jp_extra_layer(bool new_state);
bool get_enable_kc_lang(void);
void set_enable_kc_lang(bool new_state);
bool get_japanese_mode(void);
void set_japanese_mode(bool new_state);

/*
 * Each process_record_* methods defined here are
 * return false if processed, or return true if not processed.
 * You can add your original macros in process_record_keymap() in keymap.c.
 */
bool process_record_edvorakjp_ext(uint16_t keycode, keyrecord_t *record);
bool process_record_edvorakjp_swap_scln(uint16_t keycode, keyrecord_t *record);
bool process_record_edvorakjp_config(uint16_t keycode, keyrecord_t *record);
bool process_record_layer(uint16_t keycode, keyrecord_t *record);
bool process_record_ime(uint16_t keycode, keyrecord_t *record);

#endif // EDVORAKJP
