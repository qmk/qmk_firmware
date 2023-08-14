#include <stdio.h>
#include <time.h>
#include "ridingqwerty.h"
#include "dict.h"

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

__attribute__ ((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  return true;
}

/*
typedef union {
    struct {
        uint8_t aesthetic : 1,
                spongebob : 1,
                uppercase : 1,
                australia : 1,
                unusued   : 4;
    };
    uint8_t all;
} mode_config_t;
*/
mode_config_t mode = {.all = 0U};

bool randword_seed  = false;
uint8_t user_mod_state;
uint16_t rand_key;
uint16_t temp_keycode;
uint32_t user_key_timer;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
  uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif

  temp_keycode = keycode;
  if ((mode.all != 0U) && ((keycode != DB(TAB) || keycode != ED(ESC)) && ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)))) {
      temp_keycode &= 0xFF;
  }

  if (mode.spongebob) {
    switch(temp_keycode) {
      case KC_A ... KC_Z:
        if (record->event.pressed) {
          (mode.uppercase ^= 1) == 0 ? tap_code16(S(temp_keycode)) : tap_code(temp_keycode);
        }
        return false;
    }
  }

  if (mode.aesthetic) {
    switch(temp_keycode) {
#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
      case KC_A:
        if (record->event.pressed) {
          send_unicode_string("Λ ");
        }
        return false;
      case KC_E:
        if (record->event.pressed) {
          send_unicode_string("Ξ ");
        }
        return false;
#else
      case A:
      case E:
        if (record->event.pressed) {
          tap_code16(S(temp_keycode));
          tap_code(KC_SPC);
        }
      return false;
#endif
      case KC_B ... KC_D:
      case KC_F ... KC_Z:
        if (record->event.pressed) {
          tap_code16(S(temp_keycode));
          tap_code(KC_SPC);
        }
        return false;
      case KC_1 ... KC_0:
        if (record->event.pressed) {
          tap_code(temp_keycode);
          tap_code(KC_SPC);
        }
        return false;

      case KC_BSPC:
        if (record->event.pressed) {
          tap_code(KC_BSPC);
          tap_code(KC_BSPC);
        }
        return false;
      case KC_SPC:
        if (record->event.pressed) {
          tap_code(KC_SPC);
          tap_code(KC_SPC);
          tap_code(KC_SPC);
        }
        return false;
    }
  }

  if (mode.australia) {
    switch(temp_keycode) {
      // IDEMPOTENT
      case KC_L:
      case KC_O:
      case KC_S:
      case KC_Z:
      case KC_8:
      case KC_0:
        if (record->event.pressed) {
          tap_code(temp_keycode);
          tap_code(KC_LEFT);
        }
        return false;

      // INVERSE
      case KC_B:
        if (record->event.pressed) {
          tap_code(KC_Q);
          tap_code(KC_LEFT);
        }
        return false;
      case KC_Q:
        if (record->event.pressed) {
          tap_code(KC_B);
          tap_code(KC_LEFT);
        }
        return false;
      case KC_D:
        if (record->event.pressed) {
          tap_code(KC_P);
          tap_code(KC_LEFT);
        }
        return false;
      case KC_P:
        if (record->event.pressed) {
          tap_code(KC_D);
          tap_code(KC_LEFT);
        }
        return false;
      case KC_N:
        if (record->event.pressed) {
          tap_code(KC_U);
          tap_code(KC_LEFT);
        }
        return false;
      case KC_U:
        if (record->event.pressed) {
          tap_code(KC_N);
          tap_code(KC_LEFT);
        }
        return false;
      case KC_6:
        if (record->event.pressed) {
          tap_code(KC_9);
          tap_code(KC_LEFT);
        }
        return false;
      case KC_9:
        if (record->event.pressed) {
          tap_code(KC_6);
          tap_code(KC_LEFT);
        }
        return false;

      // TRANSLATE
      case KC_A:
        if (record->event.pressed) {
          register_unicode(0x0250); // ɐ
          tap_code(KC_LEFT);
          return false;
        }
        break;
      case KC_C:
        if (record->event.pressed) {
          register_unicode(0x0254); // ɔ
          tap_code(KC_LEFT);
          return false;
        }
        break;
      case KC_E:
        if (record->event.pressed) {
          register_unicode(0x01DD); // ǝ
          tap_code(KC_LEFT);
          return false;
        }
        break;
      case KC_F:
        if (record->event.pressed) {
          register_unicode(0x025F); // ɟ
          tap_code(KC_LEFT);
          return false;
        }
        break;
      case KC_G:
        if (record->event.pressed) {
          register_unicode(0x0183); // ƃ
          tap_code(KC_LEFT);
          return false;
        }
        break;
      case KC_H:
        if (record->event.pressed) {
          register_unicode(0x0265); // ɥ
          tap_code(KC_LEFT);
          return false;
        }
        break;
      case KC_I:
        if (record->event.pressed) {
          register_unicode(0x1D09); // ᴉ
          tap_code(KC_LEFT);
          return false;
        }
        break;
      case KC_J:
        if (record->event.pressed) {
          register_unicode(0x027E); // ɾ
          tap_code(KC_LEFT);
          return false;
        }
        break;
      case KC_K:
        if (record->event.pressed) {
          register_unicode(0x029E); // ʞ
          tap_code(KC_LEFT);
          return false;
        }
        break;
      case KC_M:
        if (record->event.pressed) {
          register_unicode(0x026F); // ɯ
          tap_code(KC_LEFT);
          return false;
        }
        break;
      case KC_R:
        if (record->event.pressed) {
          register_unicode(0x0279); // ɹ
          tap_code(KC_LEFT);
          return false;
        }
        break;
      case KC_T:
        if (record->event.pressed) {
          register_unicode(0x0287); // ʇ
          tap_code(KC_LEFT);
          return false;
        }
        break;
      case KC_V:
        if (record->event.pressed) {
          register_unicode(0x028C); // ʌ
          tap_code(KC_LEFT);
          return false;
        }
        break;
      case KC_W:
        if (record->event.pressed) {
          register_unicode(0x028D); // ʍ
          tap_code(KC_LEFT);
          return false;
        }
        break;
      case KC_X:
        if (record->event.pressed) {
          register_unicode(0x2717); // ✗
          tap_code(KC_LEFT);
          return false;
        }
        break;
      case KC_Y:
        if (record->event.pressed) {
          register_unicode(0x028E); // ʎ
          tap_code(KC_LEFT);
          return false;
        }
        break;
      case KC_1:
        if (record->event.pressed) {
          register_unicode(0x0269); // ɩ
          tap_code(KC_LEFT);
          return false;
        }
        break;
      case KC_2:
        if (record->event.pressed) {
          register_unicode(0x3139); // ㄹ
          tap_code(KC_LEFT);
          return false;
        }
        break;
      case KC_3:
        if (record->event.pressed) {
          register_unicode(0x0190); // Ɛ
          tap_code(KC_LEFT);
          return false;
        }
        break;
      case KC_4:
        if (record->event.pressed) {
          register_unicode(0x3123); // ㄣ
          tap_code(KC_LEFT);
          return false;
        }
        break;
      case KC_5:
        if (record->event.pressed) {
          register_unicode(0x03DB); // ϛ
          tap_code(KC_LEFT);
          return false;
        }
        break;
      case KC_7:
        if (record->event.pressed) {
          register_unicode(0x3125); // ㄥ
          tap_code(KC_LEFT);
        }
        return false;

      // CONTROLS
      case KC_ENT:
        if (record->event.pressed) {
          tap_code(KC_END);
          tap_code(KC_ENTER);
        }
        return false;
      case KC_BSPC:
        if (record->event.pressed) {
          tap_code(KC_DEL);
        }
        return false;
      case KC_SPC:
        if (record->event.pressed) {
          tap_code(KC_SPC);
          tap_code(KC_LEFT);
        }
        return false;
    }
  }

  switch(keycode) {

    case VERSION:
      if (!record->event.pressed) {
        send_string_with_delay_P(PSTR(QMK_KEYBOARD ":" QMK_KEYMAP "\nVersion:" QMK_VERSION ", built: " QMK_BUILDDATE "\n"), MACRO_TIMER);
      }
      break;

    case QWERTY ... COLEMAK:
#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
    case GREEK ... HIRAGAN:
#endif
      if (record->event.pressed) {
        //set_single_persistent_default_layer(keycode - QWERTY);
        default_layer_set(1U << (keycode - QWERTY));
      }
      break;

    case MAKE:
      if (record->event.pressed) {
        user_mod_state = get_mods() & MOD_MASK_CTRL;
        if (user_mod_state) {
          clear_mods();
          send_string_with_delay_P(PSTR("sleep 1 && "), MACRO_TIMER);
        }
        send_string_with_delay_P(PSTR("make " QMK_KEYBOARD ":" QMK_KEYMAP), MACRO_TIMER);
        if (user_mod_state) {
          send_string_with_delay_P(PSTR(":flash\n"), MACRO_TIMER);
          reset_keyboard();
        } else {
          send_string_with_delay_P(PSTR("\n"), MACRO_TIMER);
        }
      }
      break;

    case RNGWORD:
      if (randword_seed == false) {
        randword_seed = true;
        srand(timer_read32());
      }
      rand_key = rand() % NUMBER_OF_WORDS;
      if (record->event.pressed) {
        send_string(dict[rand_key]);
        tap_code(KC_SPC);
      }
      break;

    case RG_QUOT:
      if (record->event.pressed) {
#if defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE)
        user_mod_state = get_mods() & MOD_MASK_ALT;
        if (user_mod_state) {
          unregister_mods(MOD_BIT(KC_RALT));
          register_unicode(0x00B0); // °
          set_mods(user_mod_state);
          return false;
        }
#endif
        user_key_timer = timer_read32();
        layer_on(_NUMBER);
        register_mods(MOD_BIT(KC_RGUI));
      } else {
        unregister_mods(MOD_BIT(KC_RGUI));
        layer_off(_NUMBER);
        if (timer_elapsed32(user_key_timer) < TAPPING_TERM) {
          tap_code(KC_QUOT);
        }
      }
      return false; break;

    case TESTING:
      /*
      if (record->event.pressed) {
        int length = snprintf( NULL, 0, "%lu", test_number );
        char* str = malloc( length + 1 );
        snprintf( str, length + 1, "%lu", test_number );
        send_string(str);
        free(str);
        // make CFLAGS+="-lc -specs=nosys.specs" board:keymap
      }
      */
      break;

    case CCCV:  // One key copy/paste
      if (record->event.pressed) {
        user_key_timer = timer_read32();
      } else {
        if (timer_elapsed32(user_key_timer) > TAPPING_TERM) {  // Hold, copy
          register_code(KC_LCTL);
          tap_code(KC_C);
          unregister_code(KC_LCTL);
        } else {  // Tap, paste
          register_code(KC_LCTL);
          tap_code(KC_V);
          unregister_code(KC_LCTL);
        }
      }
      break;

    case SEED:
      if (record->event.pressed) {
        srand(timer_read32());
      }
      break;

    case SARCASM:
      if (record->event.pressed) {
        if (!(mode.spongebob ^= 1)) { mode.all = 0U; };
      }
      break;

    case VPRWAVE:
      if (record->event.pressed) {
        if (!(mode.aesthetic ^= 1)) { mode.all = 0U; };
      }
      break;

    case STRAYA:
      if (record->event.pressed) {
        if (!(mode.australia ^= 1)) { mode.all = 0U; };
      }
      break;
    default:
      if (record->event.pressed && record->event.key.col == 4 && record->event.key.row == 1) {
        if (get_mods() & MOD_BIT(KC_RALT)) {
          unregister_mods(MOD_BIT(KC_RALT));
          //register_unicode(0x262D); // ☭
	  tap_code(KC_BSPC);
          set_mods(MOD_BIT(KC_RALT));
          return false;
        }
      }
      break;

  }
  return process_record_keymap(keycode, record) &&
    process_record_secrets(keycode, record);
}
