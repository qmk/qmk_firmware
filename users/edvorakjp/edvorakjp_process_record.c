#include "edvorakjp.h"

#if TAP_DANCE_ENABLE != yes
static uint16_t time_on_pressed;
#endif
/*
 * Each process_record_* methods defined here are
 * return false if handle edvorak_keycodes, or return true others.
 */
bool process_record_edvorakjp_ext(uint16_t keycode, keyrecord_t *record) {
  if (!(default_layer_state == 1UL<<_EDVORAK &&
        get_enable_jp_extra_layer() && get_japanese_mode())) {
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
      if (record->event.pressed) {
        layer_on(_EDVORAKJ1);
      }
      return true;

    // N: toggle layer
    case KC_N:
      if (record->event.pressed) {
        biton32(layer_state) == _EDVORAK ? layer_on(_EDVORAKJ1) : dvorakj_layer_off();
      }
      return true;

    // left hand up and right hand's right side
    case KC_Y:
    case KC_P:
    case KC_W:
    case KC_Q:
    case KC_S:
    case KC_M:
    case KC_K:
    case KC_L:
      if (record->event.pressed) {
        layer_on(_EDVORAKJ2);
      }
      return true;
    // left hand down
    // If return true, QMK sends keycode in new layer,
    // but these keys are only available in old layer.
    case KC_X:
    case KC_C:
    case KC_V:
    case KC_Z:
      if (record->event.pressed) {
        layer_on(_EDVORAKJ2);
        tap_code(keycode);
      }
      return false;
  }

  // vowel keys, symbol keys and modifier keys
  if (record->event.pressed) {
    dvorakj_layer_off();
  }
  switch (keycode) {
    // combination vowel keys
    case KC_AI:
      if (record->event.pressed) {
        SEND_STRING("ai");
      }
      return false;
    case KC_OU:
      if (record->event.pressed) {
        SEND_STRING("ou");
      }
      return false;
    case KC_EI:
      if (record->event.pressed) {
        SEND_STRING("ei");
      }
      return false;
    case KC_ANN:
      if (record->event.pressed) {
        SEND_STRING("ann");
      }
      return false;
    case KC_ONN:
      if (record->event.pressed) {
        SEND_STRING("onn");
      }
      return false;
    case KC_ENN:
      if (record->event.pressed) {
        SEND_STRING("enn");
      }
      return false;
    case KC_INN:
      if (record->event.pressed) {
        SEND_STRING("inn");
      }
      return false;
    case KC_UNN:
      if (record->event.pressed) {
        SEND_STRING("unn");
      }
      return false;
  }
  // AOEIU and other (symbol, modifier) keys
  return true;
}

bool process_record_edvorakjp_swap_scln(uint16_t keycode, keyrecord_t *record) {
#ifdef SWAP_SCLN
  static const uint8_t shift_bits = MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT);
  static uint8_t last_mods_status;
  if (keycode == KC_SCLN) {
    if (record->event.pressed) {
      last_mods_status = get_mods();

      // invert shift_bits
      if (last_mods_status & shift_bits) {
        set_mods(last_mods_status & ~shift_bits);
      } else {
        set_mods(last_mods_status | MOD_BIT(KC_LSFT));
      }
    } else {
      set_mods(last_mods_status);
      last_mods_status = 0;
    }
  }
#endif
  return true;
}

bool process_record_edvorakjp_config(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_MAC:
    case KC_WIN:
      if (record->event.pressed) {
        set_enable_kc_lang(keycode == KC_MAC);
      }
      return false;
    case KC_EXTON:
    case KC_EXTOFF:
      if (record->event.pressed) {
        set_enable_jp_extra_layer(keycode == KC_EXTON);
      }
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
#if TAP_DANCE_ENABLE != yes
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        time_on_pressed = record->event.time;
      } else {
        layer_off(_LOWER);

        if (TIMER_DIFF_16(record->event.time, time_on_pressed) < TAPPING_TERM) {
          set_japanese_mode(false);
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
          set_japanese_mode(true);
        }
        time_on_pressed = 0;
      }
      return false;
#endif
  }
  return true;
}

bool process_record_ime(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_JPN:
    case KC_ENG:
      if (record->event.pressed) {
        set_japanese_mode(keycode == KC_JPN);
      }
      return false;
  }
  return true;
}
