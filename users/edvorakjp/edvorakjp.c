#include "eeprom.h"
#include "edvorakjp.h"

bool japanese_mode;
uint16_t time_on_pressed;

edvorakjp_config_t edvorakjp_config;

uint8_t eeconfig_read_edvorakjp(void) {
  return eeprom_read_byte(EECONFIG_EDVORAK);
}

void eeconfig_update_edvorakjp(uint8_t val) {
  eeprom_update_byte(EECONFIG_EDVORAK, val);
}

void dvorakj_layer_off(void) {
  layer_off(_EDVORAKJ1);
  layer_off(_EDVORAKJ2);
}

void update_japanese_mode(bool new_state) {
  japanese_mode = new_state;
  if (japanese_mode) {
    if (edvorakjp_config.enable_kc_lang) {
      SEND_STRING(SS_TAP(X_LANG1));
    } else {
      SEND_STRING(SS_LALT("`"));
    }
  } else {
    dvorakj_layer_off();
    if (edvorakjp_config.enable_kc_lang) {
      SEND_STRING(SS_TAP(X_LANG2));
    } else {
      SEND_STRING(SS_LALT("`"));
    }
  }
}

void matrix_init_user(void) {
  japanese_mode = false;
  time_on_pressed = 0;
  edvorakjp_config.raw = eeconfig_read_edvorakjp();

  matrix_init_keymap();
}

__attribute__ ((weak))
void matrix_init_keymap() {}

uint32_t layer_state_set_user(uint32_t state) {
  state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
  return layer_state_set_keymap(state);
}

__attribute__ ((weak))
uint32_t layer_state_set_keymap(uint32_t state) {
  return state;
}

/*
 * Each process_record_* methods defined here are
 * return false if handle edvorak_keycodes, or return true others.
 */
__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_edvorakjp_ext(uint16_t keycode, keyrecord_t *record) {
  if (!(edvorakjp_config.enable_jp_extra_layer &&\
        (default_layer_state == 1UL<<_EDVORAK) &&\
        japanese_mode &&\
        record->event.pressed)) {
    return true;
  }

  // consonant keys
  // layer_on(J1) or layer_on(J2) are defined based on key positions.
  switch (keycode) {
    // right hand's left side w/o N
    case KC_F:
    case KC_G:
    case KC_R:
    case KC_D:
    case KC_T:
    case KC_B:
    case KC_H:
    case KC_J:
      layer_on(_EDVORAKJ1);
      register_code(keycode);
      unregister_code(keycode);
      return false;

    // N: toggle layer
    case KC_N:
      biton32(layer_state) == _EDVORAK ? layer_on(_EDVORAKJ1) : dvorakj_layer_off();
      register_code(keycode);
      unregister_code(keycode);
      return false;

    // left hand and right hand's right side
    case KC_X:
    case KC_C:
    case KC_V:
    case KC_Z:
    case KC_P:
    case KC_Y:
    case KC_W:
    case KC_Q:
    case KC_S:
    case KC_M:
    case KC_K:
    case KC_L:
      layer_on(_EDVORAKJ2);
      register_code(keycode);
      unregister_code(keycode);
      return false;
  }

  // vowel keys, symbol keys and modifier keys
  dvorakj_layer_off();
  switch (keycode) {
    // combination vowel keys
    case KC_AI:
      SEND_STRING("ai");
      return false;
    case KC_OU:
      SEND_STRING("ou");
      return false;
    case KC_EI:
      SEND_STRING("ei");
      return false;
    case KC_ANN:
      SEND_STRING("ann");
      return false;
    case KC_ONN:
      SEND_STRING("onn");
      return false;
    case KC_ENN:
      SEND_STRING("enn");
      return false;
    case KC_INN:
      SEND_STRING("inn");
      return false;
    case KC_UNN:
      SEND_STRING("unn");
      return false;

    // AOEIU and other (symbol, modifier) keys
    default:
      return true;
  }
}

bool process_record_edvorakjp_config(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_MAC:
      edvorakjp_config.enable_kc_lang = true;
      eeconfig_update_edvorakjp(edvorakjp_config.raw);
      return false;
    case KC_WIN:
      edvorakjp_config.enable_kc_lang = false;
      eeconfig_update_edvorakjp(edvorakjp_config.raw);
      return false;
    case KC_EXTON:
      edvorakjp_config.enable_jp_extra_layer = true;
      eeconfig_update_edvorakjp(edvorakjp_config.raw);
      return false;
    case KC_EXTOFF:
      edvorakjp_config.enable_jp_extra_layer = false;
      eeconfig_update_edvorakjp(edvorakjp_config.raw);
      return false;
  }
  return true;
}

bool process_record_layer(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case EDVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_EDVORAK);
      }
      return false;
    case QWERTY:
      if (record->event.pressed) {
        dvorakj_layer_off();
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        time_on_pressed = record->event.time;
      } else {
        layer_off(_LOWER);

        if (TIMER_DIFF_16(record->event.time, time_on_pressed) < TAPPING_TERM) {
          update_japanese_mode(false);
        }
        time_on_pressed = 0;
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        time_on_pressed = record->event.time;
      } else {
        layer_off(_RAISE);

        if (TIMER_DIFF_16(record->event.time, time_on_pressed) < TAPPING_TERM) {
          update_japanese_mode(true);
        }
        time_on_pressed = 0;
      }
      return false;
    default:
      return true;
  }
}

bool process_record_ime(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_JPN:
      if (record->event.pressed) {
        update_japanese_mode(true);
      }
      return false;
    case KC_ENG:
      if (record->event.pressed) {
        update_japanese_mode(false);
      }
      return false;
    default:
      return true;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  return process_record_keymap(keycode, record) &&\
         process_record_edvorakjp_ext(keycode, record) &&\
         process_record_edvorakjp_config(keycode, record) &&\
         process_record_layer(keycode, record) &&\
         process_record_ime(keycode, record);
}
