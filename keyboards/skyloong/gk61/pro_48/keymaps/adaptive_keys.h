static uint8_t prior_saved_mods = 0;
static uint16_t prior_keycode = KC_NO;
static uint16_t adaptive_magic_default = QK_REP;
static int marked_layer = -1;

enum adaptive_keycodes {
  KC_ADAPTIVE_MAGIC = SAFE_RANGE,
};

void set_adaptive_magic_default(uint16_t default_key) {
    adaptive_magic_default = default_key;
}

bool should_process_key_adaptive(uint16_t keycode) {
    return !(keycode == KC_LCTL || keycode == KC_RCTL || keycode == KC_LGUI || keycode == KC_RGUI || keycode == KC_LALT || keycode == KC_RALT || keycode == KC_LSFT || keycode == KC_RSFT || keycode == KC_CAPS || keycode == KC_SCRL || keycode == KC_PSCR || keycode == KC_NUM || keycode == CW_TOGG || keycode == OS_LSFT || keycode == OS_RSFT);
}

bool process_adaptive_magic(uint16_t keycode, const keyrecord_t *record) {
      switch(keycode) {
    case KC_ADAPTIVE_MAGIC:
      if (adaptive_magic_default == QK_REP) {
        if (get_repeat_key_count()) {
                return true;
        }
        repeat_key_invoke(&record->event);
        return false;
      } else {
        if (record->event.pressed) {
          tap_code(adaptive_magic_default);
          return false;
        }
      }
      break;
    }
    return true;
}

void tap_code_adaptive(uint16_t keycode, const keyrecord_t *record) {
    if (keycode == KC_ADAPTIVE_MAGIC) {
        process_adaptive_magic(keycode, record);
    } else {
        tap_code(keycode);
    }
}

bool is_marked_layer(int layer) {
    return marked_layer == -1 || marked_layer == layer;
}

bool process_adaptive_swap(uint16_t keycode, const keyrecord_t *record) {
    if (!should_process_key_adaptive(keycode)) {
            return true;
    }

  bool should_process_key = true;
  uint8_t current_layer = get_highest_layer(layer_state | default_layer_state);

  if (record->event.pressed) {
    uint8_t saved_mods = get_mods();
    if (saved_mods & MOD_MASK_CAG) {
      return true;
    }
      unregister_code(KC_LSFT);
      unregister_code(KC_RSFT);
      uint16_t keycode_base = keycode & 0xFF;
      uint16_t first = KC_NO;
      uint16_t second = KC_NO;

      if (keycode != KC_ADAPTIVE_MAGIC) {
        keycode = keycode_base;
      }

      switch (prior_keycode) {
      case KC_NO:
        switch (keycode_base) {
#define CAPTURE(key, def_key, layer) \
  default: \
    marked_layer = layer; \
    should_process_key = true; \
    tap_code_adaptive(first, record); \
    } \
    break; \
  case key: \
    marked_layer = layer; \
    if (is_marked_layer(current_layer)) { \
     first = def_key; \
     should_process_key = false; \
     } \
    switch (keycode) {

#define ON(layer, key) CAPTURE(key, KC_NO, layer)
#define ON_ALL(key) CAPTURE(key, KC_NO, -1)

#define REPLACE(second_key, replaced_key) \
    case second_key: \
        second = replaced_key; \
        break;

#define SWAP(second_key, replaced_key) \
    REPLACE(second_key, replaced_key) \
    REPLACE(replaced_key, second_key)

#include "adaptive_keys.def"
        default:
          should_process_key = true;
          tap_code_adaptive(first, record);
        }
      }

      if (should_process_key) {
            set_mods(saved_mods);
      } else {
        set_mods(prior_saved_mods);
        tap_code_adaptive(first, record);

#ifdef CAPS_WORD_ENABLE
        if (is_caps_word_on() && !caps_word_press_user(second)) {
            add_weak_mods(MOD_BIT(KC_LSFT));
        }
#endif

        tap_code_adaptive(second, record);
	if (second != KC_ADAPTIVE_MAGIC) {
        	set_last_keycode(second);
	}
      }
    switch (keycode) {
#undef CAPTURE
#undef ON
#undef ON_ALL
#undef REPLACE
#undef SWAP
#define CAPTURE(key, ...) \
  case key: \
    should_process_key = !is_marked_layer(current_layer) \
    break;
#define ON_ALL(...)
#define ON(...)
#define REPLACE(...)
#define SWAP(...)
#include "adaptive_keys.def"
    }
    prior_saved_mods = saved_mods;
    prior_keycode = keycode;
  }
  return should_process_key;
}

#undef CAPTURE
#undef ON
#undef ON_ALL
#undef REPLACE
#undef SWAP

bool remember_last_key_adaptive(uint16_t keycode, keyrecord_t* record, uint8_t* remembered_mods) {
    switch (keycode) {
        case KC_ADAPTIVE_MAGIC:
            return false;
    }

    return true;
}
