#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"
#include "action_layer.h"

#define EECONFIG_EDVORAK (uint8_t *)20

extern keymap_config_t keymap_config;

typedef union {
  uint8_t raw;
  struct {
    bool enable_jp_extra_layer : 1;
    bool enable_kc_lang        : 1;  // for macOS
  };
} edvorakjp_config_t;

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

uint8_t eeconfig_read_edvorakjp(void);
void eeconfig_update_edvorakjp(uint8_t val);

void dvorakj_layer_off(void);
void update_japanese_mode(bool new_state);
void matrix_init_user(void);
void matrix_init_keymap(void);
uint32_t layer_state_set_user(uint32_t state);
uint32_t layer_state_set_keymap(uint32_t state);

/*
 * Each process_record_* methods defined here are
 * return false if processed, or return true if not processed.
 * You can add your original macros in process_record_keymap() in keymap.c.
 */
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
bool process_record_edvorakjp_ext(uint16_t keycode, keyrecord_t *record);
bool process_record_edvorakjp_config(uint16_t keycode, keyrecord_t *record);
bool process_record_layer(uint16_t keycode, keyrecord_t *record);
bool process_record_ime(uint16_t keycode, keyrecord_t *record);
bool process_record_user(uint16_t keycode, keyrecord_t *record);

#endif
