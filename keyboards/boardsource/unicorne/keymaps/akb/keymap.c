#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

#include "features/achordion.h"
#include "features/orbital_mouse.h"

#define KCX_CUT LT(__DUMMY, KC_X)
#define KCC_COPY LT(__DUMMY, KC_C)
#define KCV_PASTE LT(__DUMMY, KC_V) 
 
enum layer_names {
  _BASE,
  
  // Left hand
  __NUM,
  __SYM,
  __OPS,

  // Right hand
  __NAV,
  MOUSE,

  // Used for tap-hold keys
  __DUMMY
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  // switch (keycode) {
  //   case KCX_CUT:
  //   case KCC_COPY:
  //   case KCV_PASTE:
  //     return 100;
  //   default:
  return TAPPING_TERM;
  // }
}

// Helper for implementing tap vs. long-press keys. Given a tap-hold
// key event, replaces the hold function with `long_press_keycode`.
// static bool process_tap_or_long_press_key(keyrecord_t* record, uint16_t long_press_keycode) {
//   if (record->tap.count == 0) {  // Key is being held.
//     if (record->event.pressed) {
//       tap_code16(long_press_keycode);
//     }
//     return false;  // Skip default handling.
//   }
  
//   return true;  // Continue default handling.
// }

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (!process_orbital_mouse(keycode, record)) { return false; }

  // switch (keycode) {
  //   case KCX_CUT:  
  //     return process_tap_or_long_press_key(record, G(KC_X));
  //   case KCC_COPY: 
  //     return process_tap_or_long_press_key(record, G(KC_C));
  //   case KCV_PASTE:
  //     return process_tap_or_long_press_key(record, G(KC_V));
  // }

  return true;
}

void housekeeping_task_user(void) {
  orbital_mouse_task();
}

void matrix_scan_user(void) {
  achordion_task();
}

bool achordion_eager_mod(uint8_t mod) {
  switch (mod) {
    case MOD_LSFT:
    case MOD_RSFT:
    case MOD_LGUI:
    case MOD_RGUI:
      return true;  // Eagerly apply Shift and GUI mods.

    default:
      return false;
  }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) { 
  return OLED_ROTATION_270;
}

bool oled_task_user(void) {
  oled_clear();
  oled_set_cursor(0, 0);

  switch (get_highest_layer(layer_state)) {
    case _BASE:
      oled_write("BASE", false);
      break;
    case __NUM:
      oled_write("NUM", false);
      break;
    case __SYM:
      oled_write("SYM", false);
      break;
    case __OPS:
      oled_write("OPS", false);
      break;
    case __NAV:
      oled_write("NAV", false);
      break;
    case MOUSE:
      oled_write("MOUSE", false);
      break;
    default:
      oled_write("ERR", false);
      break;
    }

    uint8_t mod_row = 1;
    oled_set_cursor(0, mod_row);
    uint8_t mod = get_mods() | get_oneshot_mods();

    if (mod & MOD_MASK_CTRL) {
      oled_write("CTRL", false);
      oled_set_cursor(0, ++mod_row);
    }
    if (mod & MOD_MASK_ALT) {
      oled_write("ALT", false);
      oled_set_cursor(0, ++mod_row);
    }
    if (mod & MOD_MASK_GUI) {
      oled_write("GUI", false);
      oled_set_cursor(0, ++mod_row);
    }
    if (mod & MOD_MASK_SHIFT) {
      oled_write("SHIFT", false);
      oled_set_cursor(0, ++mod_row);
    }
    
    return false;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_3x6_3(
    XXXXXXX, XXXXXXX,      KC_W,         KC_E,              KC_R,              KC_T,           KC_Y,              KC_U,               KC_I,             KC_O,         XXXXXXX,         XXXXXXX, 
    KC_Q,    LCTL_T(KC_A), LALT_T(KC_S), LGUI_T(KC_D),      LSFT_T(KC_F),      KC_G,           KC_H,              RSFT_T(KC_J),       RGUI_T(KC_K),     RALT_T(KC_L), RCTL_T(KC_SCLN), KC_P, 
    XXXXXXX, KC_Z,         KCX_CUT,      KCC_COPY,          KCV_PASTE,         KC_B,           KC_N,              KC_M,               KC_COMM,          KC_DOT,       KC_SLSH,         XXXXXXX, 
                                         LT(MOUSE, KC_ESC), LT(__NAV, KC_SPC), KC_TAB,         LT(__SYM, KC_ENT), LT(__NUM, KC_BSPC), LT(__OPS, KC_DEL)
  ),
  
  [__NUM] = LAYOUT_split_3x6_3(
    XXXXXXX, XXXXXXX, KC_7,    KC_8,    KC_9,    KC_RBRC,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
    KC_LBRC, KC_QUOT, KC_4,    KC_5,    KC_6,    KC_EQL,         XXXXXXX, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL, XXXXXXX, 
    XXXXXXX, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_BSLS,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
                               KC_DOT,  KC_0,    KC_MINS,        XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [__SYM] = LAYOUT_split_3x6_3(
    XXXXXXX, XXXXXXX, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
    KC_LCBR, KC_DQUO, KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS,        XXXXXXX, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL, XXXXXXX, 
    XXXXXXX, KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_PIPE,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
                               KC_LPRN, KC_RPRN, KC_UNDS,        XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [__OPS] = LAYOUT_split_3x6_3(
    QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
    EE_CLR,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL, XXXXXXX, 
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
                               XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [__NAV] = LAYOUT_split_3x6_3(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
    XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, XXXXXXX,
                               XXXXXXX, XXXXXXX, XXXXXXX,        KC_ENT,  KC_BSPC, KC_DEL
  ),

  [MOUSE] = LAYOUT_split_3x6_3(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        OM_W_U , OM_BTNS, OM_U   , OM_DBLS, XXXXXXX, XXXXXXX, 
    XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX,        OM_W_D , OM_L   , OM_D   , OM_R   , OM_SLOW, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        OM_RELS, OM_HLDS, OM_SEL1, OM_SEL2, OM_SEL3, XXXXXXX,
                               XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX
  ),
};

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C