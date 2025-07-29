/**
 * This file contains the implementation of a custom key processing system
 * for handling "magic" keys and their associated behaviors. It includes
 * functionality for remembering the last key pressed, sending enhanced
 * strings with repeatable keycodes, and processing left and right "magic"
 * key actions. The system is designed to enhance keyboard functionality
 * by providing programmable and repeatable key sequences.
 */

/**
 * remember_last_key_user
 * -----------------------
 * Determines whether the last key pressed should be remembered based on
 * the provided keycode and key record. Certain keycodes, such as magic
 * keys and specific control keys, are excluded from being remembered.
 *
 * Parameters:
 * - keycode: The keycode of the key being processed.
 * - record: A pointer to the key record containing key press/release data.
 * - remembered_mods: A pointer to the variable storing remembered modifiers.
 *
 * Returns:
 * - true if the key should be remembered, false otherwise.
 */
bool remember_last_key_user(uint16_t keycode, keyrecord_t *record,
                            uint8_t *remembered_mods) {
  switch (keycode) {
    case CW_TOGG:
    case KC_ESC:
    case KC_BSPC:
    case KC_DEL:
    case TD(XTRA_RMAGIC):
    case TD(NAV_LMAGIC):

    case LMAGIC:
    case RMAGIC:
      return false;  // Magic keys will ignore the above keycodes.
  }
  return true;  // Other keys can be repeated.
}

/**
 * MAGIC_STRING
 * ------------
 * A macro that sends a string and sets the last keycode for repeat functionality.
 * This is an enhanced version of the SEND_STRING macro, allowing for repeatable
 * key sequences.
 *
 * Parameters:
 * - str: The string to send.
 * - repeat_keycode: The keycode to set for repeat functionality.
 */
#define MAGIC_STRING(str, repeat_keycode) \
  magic_send_string_P(PSTR(str), (repeat_keycode))

  /**
   * magic_send_string_P
   * -------------------
   * Sends a string stored in program memory with a delay between each character
   * and sets the last keycode for repeat functionality. This function is used
   * internally by the MAGIC_STRING macro.
   *
   * Parameters:
   * - str: A pointer to the string stored in program memory.
   * - repeat_keycode: The keycode to set for repeat functionality.
   */
static void magic_send_string_P(const char *str, uint16_t repeat_keycode) {
  send_string_with_delay_P(str, TAP_CODE_DELAY);  // Send the string.
  set_last_keycode(repeat_keycode);  // 2024-03-09 Disabled sending of string
                                     // for mag-rep / rep-mag consistency.
}

/**
 * LMAGIC definitions
 * ------------------
 * Processes keycodes associated with the left "magic" key. Depending on the
 * keycode, it sends specific strings or performs other actions. This function
 * is responsible for handling the behavior of left-side magic keys.
 *
 * Parameters:
 * - keycode: The keycode of the key being processed.
 * - mods: The modifier keys active during the key press.
 */
static void process_left_magic(uint16_t keycode, uint8_t mods) {
  switch (keycode) {
    case TRL_MEDIA_L: {
      MAGIC_STRING("l", KC_NO);
    } break;
    case HRM_CTRL_E: {
      MAGIC_STRING("e", KC_NO);
    } break;
    case TRL_SPECIAL_F: {
      MAGIC_STRING("unction", KC_NO);
    } break;
    case KC_I: {
      MAGIC_STRING("on", KC_NO);
    } break;
    case KC_M: {
      MAGIC_STRING("m", KC_NO);
    } break;
    case HRL_BRACKETS_N: {
      MAGIC_STRING("n", KC_NO);
    } break;
    case DE_O: {
      MAGIC_STRING("o", KC_NO);
    } break;
    case DE_U: {
      MAGIC_STRING("u", KC_NO);
    } break;

    case KC_DOT: {
      MAGIC_STRING("..", KC_NO);
    } break;
    case RCURLY: {
      SEND_STRING(SS_RALT("8"));
    } break;
  }
}
static void process_left_magic_static(void){
    process_left_magic(get_last_keycode(), get_last_mods());
}
/**
 * RMAGIC definitions
 * -------------------
 * Processes keycodes associated with the right "magic" key. Similar to the
 * left magic key function, it sends specific strings or performs other actions
 * based on the keycode. This function handles the behavior of right-side
 * magic keys.
 *
 * Parameters:
 * - keycode: The keycode of the key being processed.
 * - mods: The modifier keys active during the key press.
 */
static void process_right_magic(uint16_t keycode, uint8_t mods) {
  switch (keycode) {
    case DE_A: {
      MAGIC_STRING("a", KC_NO);
    } break;
    case KC_B: {
      MAGIC_STRING("b", KC_NO);
    } break;
    case KC_C: {
      MAGIC_STRING("c", KC_NO);
    } break;
    case KC_G: {
      MAGIC_STRING("g", KC_NO);
    } break;
    case HRM_GUI_D: {
      MAGIC_STRING("d", KC_NO);
    } break;
    case TRL_SPECIAL_F: {
      MAGIC_STRING("f", KC_NO);
    } break;
    case HRM_CTRL_E: {
      if (last_keycodes[1] == KC_O) {
        tap_code16(KC_BSPC);
        tap_code16(KC_BSPC);
        MAGIC_STRING("ö", KC_NO); // SS_TAP maybe
      }else {
        MAGIC_STRING("nt", KC_NO);
      }
    } break;
    case KC_I: {
      MAGIC_STRING("ng", KC_NO);
    case KC_M: {
      MAGIC_STRING("ent", KC_NO);
    } break;
    case TRL_MEDIA_P: {
      MAGIC_STRING("p", KC_NO);
    } break;
    case KC_R: {
      MAGIC_STRING("r", KC_NO);
    } break;
    case HRM_ALT_S: {
      MAGIC_STRING("s", KC_NO);
    } break;
    case HRL_BRACKETS_T: {
      MAGIC_STRING("t", KC_NO);
    } break;
    case DE_W: {
      MAGIC_STRING("w", KC_NO);
    } break;
    case DE_Z: {
      MAGIC_STRING("z", KC_NO);
    } break;

    case LCURLY: {
      SEND_STRING(SS_RALT("9"));
    } break;
  }
}
static void process_right_magic_static(void){
    process_right_magic(get_last_keycode(), get_last_mods());
}
