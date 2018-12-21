/* Copyright 2018 Othi
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

// read README.md for rundown of what does what

// #define BL 0
#define CL 0
#define NM_MODE 2
#define VI_MODE 3
#define FN3 4
#define ACCENT 5
#define ACCENT_CAP 6
enum custom_keycodes {
    MY_CUSTOM_MACRO = SAFE_RANGE,
    DE_AE, /* Ctrl + Shift + u00E4 */
    DE_SS, /* Ctrl + Shift + u00DF */
    DE_OE, /* Ctrl + Shift + u00F6 */
    DE_UE, /* Ctrl + Shift + u00FC */
    FLUSH, /* clears oneshots */
    DE_AE_CAP, /* Ctrl + Shift + u00C4 */
    DE_OE_CAP, /* Ctrl + Shift + u00D6 */
    DE_UE_CAP, /* Ctrl + Shift + u00DC */
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case MY_CUSTOM_MACRO:
                SEND_STRING("QMK is the best thing ever!"); // this is our macro!
                return false;
            case DE_AE:
                SEND_STRING(SS_DOWN(X_LCTRL) SS_DOWN(X_LSHIFT) SS_TAP(X_U) SS_UP(X_LCTRL) SS_UP(X_LSHIFT) SS_TAP(X_0) SS_TAP(X_0) SS_TAP(X_E) SS_TAP(X_4) SS_TAP(X_ENTER));
                return false;
            case DE_AE_CAP:
                SEND_STRING(SS_DOWN(X_LCTRL) SS_DOWN(X_LSHIFT) SS_TAP(X_U) SS_UP(X_LCTRL) SS_UP(X_LSHIFT) SS_TAP(X_0) SS_TAP(X_0) SS_TAP(X_C) SS_TAP(X_4) SS_TAP(X_ENTER));
                return false;
            case DE_OE:
                SEND_STRING(SS_DOWN(X_LCTRL) SS_DOWN(X_LSHIFT) SS_TAP(X_U) SS_UP(X_LCTRL) SS_UP(X_LSHIFT) SS_TAP(X_0) SS_TAP(X_0) SS_TAP(X_F) SS_TAP(X_6) SS_TAP(X_ENTER));
                return false;
            case DE_OE_CAP:
                SEND_STRING(SS_DOWN(X_LCTRL) SS_DOWN(X_LSHIFT) SS_TAP(X_U) SS_UP(X_LCTRL) SS_UP(X_LSHIFT) SS_TAP(X_0) SS_TAP(X_0) SS_TAP(X_D) SS_TAP(X_6) SS_TAP(X_ENTER));
                return false;
            case DE_UE:
                SEND_STRING(SS_DOWN(X_LCTRL) SS_DOWN(X_LSHIFT) SS_TAP(X_U) SS_UP(X_LCTRL) SS_UP(X_LSHIFT) SS_TAP(X_0) SS_TAP(X_0) SS_TAP(X_F) SS_TAP(X_C) SS_TAP(X_ENTER));
                return false;
            case DE_UE_CAP:
                SEND_STRING(SS_DOWN(X_LCTRL) SS_DOWN(X_LSHIFT) SS_TAP(X_U) SS_UP(X_LCTRL) SS_UP(X_LSHIFT) SS_TAP(X_0) SS_TAP(X_0) SS_TAP(X_D) SS_TAP(X_C) SS_TAP(X_ENTER));
                return false;
            case DE_SS:
                SEND_STRING(SS_DOWN(X_LCTRL) SS_DOWN(X_LSHIFT) SS_TAP(X_U) SS_UP(X_LCTRL) SS_UP(X_LSHIFT) SS_TAP(X_0) SS_TAP(X_0) SS_TAP(X_D) SS_TAP(X_F) SS_TAP(X_ENTER));
                return false;
        }
    }
    return true;
};

uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case NM_MODE:
        rgblight_setrgb (0x00,  0x66, 0x00);
        break;
    case VI_MODE:
        rgblight_setrgb (0x66,  0x66, 0x00);
        break;
    case ACCENT:
        rgblight_setrgb (0x7A,  0x00, 0xFF);
        break;
    case ACCENT_CAP:
        rgblight_setrgb (0x7A,  0xFF, 0xFF);
        break;
    default: //  for any other layers, or the default layer
        rgblight_setrgb (0xFF,  0x00, 0x00);
        break;
    }
  return state;
}

//Tap Dance Declarations
enum {
  CTRL_NM = 0,
  ALT_NM = 1,
  SFT_NM = 2,
  GUI_NM = 3
};

void dance_CTRL_NM_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
	register_code (KC_LCTL);
	set_oneshot_mods(MOD_LCTL);
  } else {
    register_code (KC_LCTL);
	layer_on(NM_MODE);
  }
}

void dance_CTRL_NM_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_LCTL);
  } else {
    unregister_code (KC_LCTL);
	layer_off(NM_MODE);
  }
}

void dance_GUI_NM_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
	register_code (KC_LGUI);
  } else {
    register_code (KC_LGUI);
	layer_on(NM_MODE);
  }
}

void dance_GUI_NM_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_LGUI);
  } else {
    unregister_code (KC_LGUI);
	layer_off(NM_MODE);
  }
}

void dance_ALT_NM_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
	register_code (KC_LALT);
  } else {
    register_code (KC_LALT);
	layer_on(NM_MODE);
  }
}

void dance_ALT_NM_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_LALT);
  } else {
    unregister_code (KC_LALT);
	layer_off(NM_MODE);
  }
}

void dance_SFT_NM_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
	register_code (KC_LSFT);
	set_oneshot_mods(MOD_LSFT);
  } else {
    register_code (KC_LSFT);
	layer_on(NM_MODE);
  }
}

void dance_SFT_NM_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_LSFT);
  } else {
    unregister_code (KC_LSFT);
	layer_off(NM_MODE);
  }
}


qk_tap_dance_action_t tap_dance_actions[] = {
 [CTRL_NM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_CTRL_NM_finished, dance_CTRL_NM_reset),
 [GUI_NM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_GUI_NM_finished, dance_GUI_NM_reset),
 [ALT_NM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_ALT_NM_finished, dance_ALT_NM_reset),
 [SFT_NM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_SFT_NM_finished, dance_SFT_NM_reset)
};

// Fillers to make layering clearer
#define ______ KC_TRNS

// backup
// old R3 capslock, LT(NM_MODE,KC_BSPC),
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [CL] = LAYOUT(
      KC_GESC, 					 KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,        KC_EQL,     KC_BSLS,    KC_DEL,
      MT(MOD_LGUI,KC_TAB),       LT(NM_MODE,KC_Q),    KC_W,    LT(ACCENT,KC_F),    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,     KC_LBRC, KC_RBRC, KC_BSPC,
      MT(MOD_LCTL,KC_BSPC),      KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,           KC_QUOT, KC_ENT,
      TD(SFT_NM),                KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    MT(MOD_LCTL,KC_COMM), MT(MOD_LSFT,KC_DOT),  MT(MOD_LALT,KC_SLSH),        LM(CL,MOD_LGUI|MOD_LSFT), TT(NM_MODE),
      ______, TD(GUI_NM),                     TD(ALT_NM),              		KC_SPC,    LM(CL,MOD_LGUI|MOD_LALT), OSL(ACCENT)    , ______
      ),
  [NM_MODE] = LAYOUT(
      KC_GRV,            KC_MPRV,    KC_MNXT,    KC_MPLY,    KC_END,      ______,     ______,     ______,     ______,     ______,     KC_HOME,    ______,  ______,  RESET, KC_INS,
      LGUI(KC_TAB),       ______,    LCTL(KC_RGHT),  ______,    ______,    ______,    ______,    KC_UP,    KC_PGUP,    ______,    ______,     ______, TG(CL), KC_DEL,
      ______,            KC_LEFT,    ______,    KC_RGHT,      ______,    KC_PGDN,    KC_LEFT,   KC_DOWN,   KC_RGHT,     ______,    KC_ENT,  KC_QUOT, KC_LGUI,
      KC_LSFT,     ______,    ______,    ______,      ______,    LCTL(KC_LEFT),    ______,    ______,    ______,    ______,    ______,    TG(VI_MODE), TO(CL),
      ______, TD(CTRL_NM),                     TD(ALT_NM),              		KC_SPC,    LM(CL,MOD_LGUI|MOD_LALT), OSL(ACCENT), ______
      ),

  [VI_MODE] = LAYOUT(
      KC_GRV,            KC_MPRV,  KC_MNXT, KC_MPLY,    LSFT(KC_END),          KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     LSFT(KC_HOME),    KC_F11,  KC_F12,  RESET, KC_INS,
      LGUI(KC_TAB),           ______,    LSFT(LCTL(KC_RGHT)),  ______,    ______,    ______,    ______,    LSFT(KC_UP),    ______,    ______,    ______,     ______, TG(CL), KC_BSPC,
      ______,            ______,    ______,    ______,      ______,    ______,    LSFT(LCTL(KC_LEFT)),   LSFT(KC_DOWN),   LSFT(KC_RGHT),     ______,    KC_SCLN,  KC_QUOT, KC_LGUI,
      KC_LSFT,     ______,  ______, ______,      ______,    LSFT(LCTL(KC_LEFT)),    ______,    ______,    ______,    ______,    KC_SLSH,    OSM(MOD_LSFT), TO(CL),
      ______, TD(CTRL_NM),                     TD(ALT_NM),              		KC_SPC,    LM(CL,MOD_LGUI|MOD_LALT), OSL(ACCENT), ______
      ),
  [ACCENT] = LAYOUT(
      ______,       KC_F1,  KC_F2, KC_F3,    KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,  KC_F12,  ______, ______,
      ______,         RGB_TOG,    RGB_MODE_PLAIN,  ______,    ______,    ______,    ______,    ______,    DE_UE,    ______,    ______,     ______, ______, ______,
      ______,            DE_AE,    ______,    DE_SS,      ______,    ______,    ______,   ______,   ______,     ______,    DE_OE,  ______, ______,
      OSL(ACCENT_CAP),   ______,  ______, ______,      _______,    ______,    ______,    ______,    ______,    ______,        ______, ______, TO(CL),
      ______,             ______,         ______,            ______,         ______, ______,  ______
      ),
  [ACCENT_CAP] = LAYOUT(
      ______,       ______,  ______, ______,    ______,          ______,     ______,     ______,     ______,     ______,     ______,    ______,  ______,  ______, ______,
      ______,          ______,    ______,  ______,    ______,    ______,    ______,    ______,    DE_UE_CAP,    ______,    ______,     ______, ______, ______,
      ______,            DE_AE_CAP,    ______,    DE_SS,      ______,    ______,    ______,   ______,   ______,     ______,    DE_OE_CAP,  ______, TO(CL),
      ______,     ______, ______,      _______,    ______,    ______,    ______,    ______,    ______,    ______,    ______, ______, ______,
      ______,    ______,         ______,         ______,         ______,   ______,      ______
      ),
};

