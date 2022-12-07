/* Copyright 2022 Even A. Nilsen (@eanilsen)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "features/customkeys.h"
#include "features/swapper.h"
#include "features/custom_shift_keys.h"

#define SYMB OSL(_SYMBOL)
#define FUNC OSL(_FUNCTION)
#define NAV TO(_NAV)
#define BASE TO(_ISRT)
#define NUM TO(_NUM)
/* #define MOD_SPC GUI_T(KC_SPC) // For DWM */
#define MOD_SPC MEH_T(KC_SPC)
#define MOD_BSP LT(0,KC_BSPC)
#define LT_UP LT(0,KC_UP)
#define LT_LEFT LT(0,KC_LEFT)
/* Home row mods */
#define HOME_I LSFT_T(KC_I)
#define HOME_S LGUI_T(KC_S)
#define HOME_R LALT_T(KC_R)
#define HOME_T LCTL_T(KC_T)
#define HOME_G LT(_NAV,KC_G)
#define HOME_P LT(_NUM,KC_P)
#define HOME_N RCTL_T(KC_N)
#define HOME_E RALT_T(KC_E)
#define HOME_A RGUI_T(KC_A)
#define HOME_O RSFT_T(KC_O)


enum layers {
    _ISRT,
    _SYMBOL,
    _FUNCTION,
    _NAV,
    _NUM
};

const custom_shift_key_t custom_shift_keys[] = {
  {KC_DOT, KC_EQL},
  {KC_COMM, KC_EXLM},
  {KC_QUOT, KC_QUES},
  {KC_SLSH, KC_BSLS},
};
uint8_t NUM_CUSTOM_SHIFT_KEYS =
  sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_ISRT] = LAYOUT(
        KC_Y,   KC_C,   KC_L,   KC_M,    KC_K,       KC_Z,   KC_F,   KC_U,    KC_COMM, KC_QUOT,
        HOME_I, HOME_S, HOME_R, HOME_T,  HOME_G,     HOME_P, HOME_N, HOME_E,  HOME_A,  HOME_O,
        KC_Q,   KC_V,   KC_W,   KC_D,    KC_J,       KC_B,   KC_H,   KC_SLSH, KC_DOT,  KC_X,
                                MOD_SPC, SYMB,       FUNC,   MOD_BSP
    ),

    [_SYMBOL] = LAYOUT(
        KC_NO,   KC_LT,   KC_GT,   KC_PLUS, KC_NO,     KC_NO, KC_UNDS, KC_PIPE, KC_TILD, KC_PERC,
        KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_AT,     ARROW, KC_AMPR, KC_ASTR, KC_DQUO, KC_DLR,
        KC_COLN, KC_SCLN, KC_LBRC, KC_RBRC, KC_NO,     KC_NO, KC_MINS, KC_HASH, GRAVE,   KC_CIRC,
                                   MOD_SPC, KC_NO,     BASE,  MOD_BSP
    ),

    [_FUNCTION] = LAYOUT(
        KC_TAB,  KC_F1, KC_F2,  KC_F3,   KC_F4,     KC_NO, KC_NO,  KC_NO, KC_NO, CG_TOGG,
        KC_ESC,  KC_F5, KC_F6,  KC_F7,   KC_F8,     KC_NO, CT_AE,  CT_OE, CT_AA, KC_ENT,
        CAPSWRD, KC_F9, KC_F10, KC_F11,  KC_F12,    KC_NO, KC_NO,  KC_NO, KC_NO, KC_NO,
                                KC_LSFT, BASE,      KC_NO, NAV
    ),

    [_NUM] = LAYOUT(
        KC_SLSH, KC_1, KC_2, KC_3,    KC_PLUS,     KC_NO, KC_NO,   KC_NO, KC_COMM,  KC_NO,
        KC_0,    KC_4, KC_5, KC_6,    KC_MINS,     KC_NO, KC_NO,   KC_NO, KC_NO,    KC_NO,
        KC_ASTR, KC_7, KC_8, KC_9,    KC_EQL,      KC_NO, KC_NO,   KC_NO, KC_DOT,   KC_NO,
                             MOD_SPC, SYMB,        FUNC,  MOD_BSP
    ),

    [_NAV] = LAYOUT(
         KC_WH_U, KC_NO,   KC_MS_U, KC_NO,   KC_NO,    KC_MUTE, KC_VOLD, LT_UP,   KC_VOLU, KC_NO,
         KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO,    KC_NO,   LT_LEFT, KC_DOWN, KC_RGHT, KC_ENT,
         SW_APP,  SW_WIN,  KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_BTN4, KC_NO,   KC_BTN5, KC_PSCR,
                                    KC_BTN1, BASE,     KC_BTN3, KC_BTN2
    )
};

bool is_mac_the_default(void) { return keymap_config.swap_lctl_lgui; }
bool is_shift_held(void) { return (get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT; }

void send_mac_or_win(uint16_t mac_code, uint16_t win_code, bool isPressed)
{
  uint16_t code = is_mac_the_default() ? mac_code : win_code;
  if (isPressed) register_code16(code);
  else unregister_code16(code);
}

void send_norwegian_letter(uint16_t keycode, uint16_t shifted_keycode, bool is_pressed, uint8_t mods)
{
  if (is_pressed) {
    if (is_mac_the_default()) SEND_STRING(SS_LCTL(SS_TAP(X_SPACE)) SS_DELAY(100));
    else SEND_STRING(SS_LCTL(SS_TAP(X_LSFT)) SS_DELAY(100));

    if (is_shift_held()) {
      del_mods(MOD_MASK_SHIFT);
      del_oneshot_mods(MOD_MASK_SHIFT);
      tap_code16(shifted_keycode); 
      set_mods(mods);
    } else tap_code16(keycode);

    if (is_mac_the_default()) SEND_STRING(SS_LCTL(SS_TAP(X_SPACE)) SS_DELAY(100));
    else SEND_STRING(SS_LCTL(SS_TAP(X_LSFT)) SS_DELAY(100));
  }
}

bool sw_app_active = false;
bool sw_win_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  bool isPressed = record->event.pressed;
  bool isHeld = !record->tap.count && isPressed;
  const uint8_t mods = get_mods();

  {
    uint16_t mod = is_mac_the_default() ? KC_LGUI : KC_LALT;
    update_swapper(&sw_app_active, mod, KC_TAB, SW_APP, keycode, record);
  }
  update_swapper(&sw_win_active, KC_LGUI, KC_GRV, SW_WIN, keycode, record);

  if (!process_custom_shift_keys(keycode, record)) { return false; }

  switch (keycode) {
  case KC_PSCR:
    send_mac_or_win(G(S(KC_4)), KC_PSCR, isPressed);
    return false;
  case LT_LEFT:
    // Guard close returning true if the key is tapped,
    // meaning the rest of the code will only run when the
    // key is held.
    if (record->tap.count) return true;
    if (isHeld) register_code16(KC_BTN1);
    else unregister_code16(KC_BTN1);
    return false;
  case CT_AA:
    send_norwegian_letter(KC_LBRC, KC_LCBR, isPressed, mods);
    return false;
  case CT_OE:
    send_norwegian_letter(KC_SCLN, KC_COLN, isPressed, mods);
    return false;
  case CT_AE:
    send_norwegian_letter(KC_QUOT, KC_DQUO, isPressed, mods);
    return false;
  case MOD_BSP:
    if (is_shift_held() && isPressed) {
      clear_mods();
      tap_code16(KC_DEL);
      set_mods(mods);
      return false;
    } else if (isHeld) {
      uint16_t code = is_mac_the_default() ? A(KC_BSPC) : C(KC_BSPC);
      tap_code16(code);
      return false;
    }
    return true;
  case GRAVE:
    if (isPressed) {
      if (is_shift_held()) {
	del_mods(MOD_MASK_SHIFT);
	del_oneshot_mods(MOD_MASK_SHIFT);
	for (uint8_t i = 0; i < 3; i++) tap_code16(KC_GRV);
	set_mods(mods);
      } else {
	tap_code16(KC_GRV);
      }
    }
    return false;
  case ARROW:
    if (isPressed) {
      if (is_shift_held()) {
	del_mods(MOD_MASK_SHIFT);
	del_oneshot_mods(MOD_MASK_SHIFT);
	SEND_STRING("=>");
	set_mods(mods);
      } else {
	SEND_STRING("->");
      }
    }
    return false;
  }
  return true;
}

#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode) {
    // Home row: ISRT
  case HOME_I: // Left shift
    return TAPPING_TERM + 60;
  case HOME_S: // Left GUI
    return TAPPING_TERM + 200;
  case HOME_R: // Left alt
    return TAPPING_TERM + 200;
  case HOME_T: // Left control
    return TAPPING_TERM + 200;
    // Middle row: GP
  case HOME_G: // Navigation layer tap
    return TAPPING_TERM + 60;
  case HOME_P: // Number layer tap
    return TAPPING_TERM + 60;
  case HOME_N: // Right control
    return TAPPING_TERM + 200;
  case HOME_E: // Right alt
    return TAPPING_TERM + 200;
  case HOME_A: // Right GUI
    return TAPPING_TERM + 200;
  case HOME_O: // Right shift
    return TAPPING_TERM + 60;
  case LT_UP:
    return TAPPING_TERM + 200;
  case MOD_SPC: // MEH key
    return TAPPING_TERM + 60;
  case MOD_BSP: // Delete word
    return TAPPING_TERM + 60;
  default:
    return TAPPING_TERM;
  }
}
#endif

#ifdef OLED_ENABLE
void omni_render_space(void) {
    oled_write_P(PSTR("     "), false);
}

void omni_render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void omni_render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}

void omni_render_logo(void) {
    static const char PROGMEM aurora_logo[] = {
        0x00, 0x00, 0x00, 0xe0, 0x00, 0xf8, 0xc0, 0xf8, 0xe0, 0xc0, 0xfc, 0x00, 0x7e, 0x18, 0x00, 0x80, 
        0x00, 0x02, 0x80, 0xf0, 0x00, 0xc0, 0x80, 0xf8, 0xc0, 0xe0, 0x70, 0x60, 0x3c, 0x38, 0x3c, 0x1c, 
        0x00, 0x3f, 0x0c, 0x0f, 0x1f, 0x03, 0x07, 0x01, 0xc3, 0x00, 0xe0, 0x80, 0x00, 0xe0, 0x80, 0xf8, 
        0x80, 0xc0, 0xf7, 0xc7, 0x6f, 0x7b, 0x39, 0x30, 0x00, 0x80, 0x00, 0xc0, 0x00, 0xc0, 0xc2, 0xe0, 
        0x00, 0x40, 0x38, 0x30, 0x38, 0x1e, 0x18, 0x1e, 0x0f, 0x0c, 0x07, 0x07, 0x07, 0x03, 0x03, 0x21, 
        0x21, 0x31, 0x30, 0x18, 0x18, 0x1c, 0x08, 0x0c, 0x0e, 0x07, 0x06, 0x07, 0x03, 0xc3, 0x03, 0x01, 
        0x4c, 0xcc, 0xc2, 0xc2, 0x41, 0x49, 0x09, 0x2b, 0x2a, 0x6a, 0x6e, 0x24, 0x24, 0x04, 0x92, 0x92, 
        0xb1, 0xf1, 0xf1, 0xf2, 0xe6, 0xa4, 0xa4, 0x04, 0x04, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28
    };
    oled_write_raw_P(aurora_logo, sizeof(aurora_logo));
    oled_set_cursor(0, 4);
}

void omni_render_os_text(void)
{
  if (is_mac_the_default()) oled_write_P(PSTR("OSX"), false);
  else oled_write_P(PSTR("GNU"), false);
}

void omni_render_layer_state(void) {
    static const char PROGMEM default_layer[] = {
        0x20, 0x94, 0x95, 0x96, 0x20,
        0x20, 0xb4, 0xb5, 0xb6, 0x20,
        0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    static const char PROGMEM raise_layer[] = {
        0x20, 0x97, 0x98, 0x99, 0x20,
        0x20, 0xb7, 0xb8, 0xb9, 0x20,
        0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    static const char PROGMEM lower_layer[] = {
        0x20, 0x9a, 0x9b, 0x9c, 0x20,
        0x20, 0xba, 0xbb, 0xbc, 0x20,
        0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
    static const char PROGMEM adjust_layer[] = {
        0x20, 0x9d, 0x9e, 0x9f, 0x20,
        0x20, 0xbd, 0xbe, 0xbf, 0x20,
        0x20, 0xdd, 0xde, 0xdf, 0x20, 0};
    if(layer_state_is(_SYMBOL)) {
        oled_write_P(lower_layer, false);
    } else if(layer_state_is(_FUNCTION)) {
        oled_write_P(raise_layer, false);
    } else if(layer_state_is(_ISRT)) {
        oled_write_P(default_layer, false);
    } else {
        oled_write_P(adjust_layer, false);
    }
}


bool oled_task_user(void) {
    if (is_keyboard_master()) {
      if (layer_state_is(_NAV)) {
	
      } else if (layer_state_is(_NUM)) {
      } else {
	  // Renders the current keyboard state (layers and mods)
	  omni_render_logo();
	  omni_render_space();
	  omni_render_layer_state();
	  omni_render_space();
	  omni_render_mod_status_gui_alt(get_mods() | get_oneshot_mods());
	  omni_render_mod_status_ctrl_shift(get_mods() | get_oneshot_mods());
	  omni_render_space();
	  omni_render_os_text();
      }
    } else {
	// clang-format off
	static const char PROGMEM aurora_art[] = {
	    0x00, 0x00, 0x00, 0x10, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x08, 0x1c, 0x08, 0x00, 0x00, 
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 
	    0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x40, 0x7f, 0x40, 0x40, 0x40, 0x00, 0x00, 0x02, 0x00, 0x40, 
	    0xe0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x80, 
	    0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x06, 0x0c, 0x10, 0x20, 0x40, 0xff, 
	    0x00, 0x00, 0x40, 0xe0, 0x90, 0x90, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 
	    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x1c, 0x12, 0x12, 0x22, 0xe0, 0x00, 0x00, 0x00, 0x00, 
	    0x00, 0x00, 0x0c, 0x08, 0x08, 0x88, 0x89, 0x87, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0xfd, 0x41, 0x40, 0x40, 0x60, 0x20, 0xfc, 
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xb3, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x03, 
	    0x00, 0x00, 0xfc, 0x18, 0x30, 0x40, 0x80, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x01, 0x01, 0x00, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x00, 
	    0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe3, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x0f, 0x08, 0x08, 0x08, 
	    0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x11, 0x11, 0x11, 0x11, 0x00, 0x00, 0x00, 
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x10, 0x10, 0x90, 0xd0, 0x00, 0x00, 
	    0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x31, 0x31, 0x53, 0xce, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x38, 0x0c, 0x0f, 0x85, 0x07, 0x38, 0x00, 
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x48, 0x48, 0x48, 0x48, 0x00, 0x00, 0x00, 
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x08, 0x08, 0x08, 0x0c, 0x04, 0x7f, 0x00, 0x00, 0x00, 
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 
	    0x00, 0x00, 0x80, 0x70, 0x0c, 0xf0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	    0x00, 0xfc, 0x03, 0x00, 0xc8, 0x72, 0xcf, 0xfc, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0xe0, 0x00, 
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x06, 0xf8, 0x00, 0x00, 0x00, 0x00, 
	    0xff, 0x00, 0x10, 0x12, 0xc9, 0xf0, 0xcf, 0xb4, 0x7f, 0x80, 0xe0, 0x1e, 0x01, 0x40, 0x65, 0x5e, 
	    0xe0, 0x00, 0x00, 0xf0, 0x0c, 0xf0, 0x00, 0x80, 0x7e, 0x01, 0x80, 0x93, 0xfc, 0xc0, 0x00, 0x00, 
	    0x00, 0x00, 0x00, 0x00, 0x89, 0x18, 0x2c, 0x46, 0x00, 0x07, 0x21, 0x10, 0x10, 0x80, 0x09, 0x13, 
	    0x31, 0xbf, 0xff, 0x00, 0x08, 0x1a, 0xf7, 0x0f, 0x00, 0x00, 0x44, 0x45, 0x34, 0xbf, 0xb8, 0x00, 
	    0x10, 0xf0, 0x08, 0xf4, 0x18, 0x11, 0xfc, 0x18, 0xfb, 0x0e, 0x10, 0xf8, 0x04, 0xf8, 0x10, 0x20, 
	    0x18, 0x09, 0xff, 0x0c, 0xea, 0x1f, 0x28, 0x60, 0x30, 0xf8, 0x20, 0xc0, 0x42, 0x33, 0x21, 0x00
	};
	// clang-format on
	oled_write_raw_P(aurora_art, sizeof(aurora_art));
    }
    return false;
}
#endif
