#include QMK_KEYBOARD_H

extern rgblight_config_t rgblight_config;
extern keymap_config_t keymap_config;

#define _PS 0 // This is the Photoshop Layer
#define _AI 1 // This is the Illustrator Layer
#define _PR 2 // This is the Premier Layer
#define _XD 3 // This is the Experience Design Layer

enum custom_keycodes {
  PS = SAFE_RANGE,
  AI,
  PR,
  MACRO_0,
};

#define PS TO(0)
#define AI TO(1)
#define PR TO(2)
#define XD TO(3)

// Mix of Photoshop, Illustrator, Premiere, and Experience Design shortcuts.
#define SAVE  LCTL(KC_S)
#define OPEN  LCTL(KC_O)
#define COPY  LCTL(KC_C)
#define PAST  LCTL(KC_V)
#define CUNDO LCTL(LALT(KC_Z))
#define INVERT LCTL(LSFT(KC_I))
#define NLAYER LSFT(LCTL(KC_N))
#define UNDO LCTL(KC_Z)
#define TRANS LCTL(KC_T)
#define ALIGNL LCTL(LSFT(KC_L))
#define ALIGNC LCTL(LSFT(KC_C))
#define ALIGNR LCTL(LSFT(KC_R))
#define BRINGF LCTL(KC_RBRC)
#define BRINGB LCTL(KC_LBRC)

// Illustrator layer shortcuts.
#define SHAPE LSFT(KC_M)
#define RULER LCTL(LALT(KC_R))

// Premiere layer shortcuts.
#define REDO LCTL(LSFT(KC_Z))
#define EXPORT LCTL(KC_M)
#define IMPORT LCTL(KC_I)
#define PCOPY LCTL(KC_V)
#define PPASTE LCTL(LSFT(KC_V))

// Experience Design layer shortcuts. (can be used with others too.)
#define NEW LCTL(KC_N)
#define LOCK LCTL(KC_L)
#define SYMB LCTL(KC_K)
#define HIDE LCTL(KC_SCLN)
#define REPEAT LCTL(KC_R)
#define MASK LCTL(LSFT(KC_M))
#define GROUP LCTL(KC_G)
#define UNGRP LCTL(LSFT(KC_G))
#define VIEW LCTL(KC_TAB)
#define HORZ LSFT(KC_C)
#define VERT LSFT(KC_M)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Photoshop layer
  [_PS] = LAYOUT_ortho_3x10(
    SAVE,    KC_W, KC_E, KC_T,  KC_U,   KC_I,   KC_P,   INVERT,  CUNDO,   NLAYER,
    UNDO,    KC_H, KC_L, TRANS, ALIGNL, ALIGNC, ALIGNR, BRINGB,  BRINGF,  OPEN,
    KC_LSFT, COPY, PAST, KC_Z,  KC_C,   KC_V,   KC_B,   KC_LBRC, KC_RBRC, AI
  ),

  // Illustrator layer
  [_AI] = LAYOUT_ortho_3x10(
    _______, MACRO_0, RULER,   _______, KC_G,    _______, _______, KC_Q,  KC_MINS, KC_PLUS,
    _______, _______, _______, KC_E,    _______, _______, _______, SHAPE, KC_O,    OPEN,
    _______, _______, _______, _______, _______, _______, _______, KC_M,  KC_SLSH, PR
  ),

  // Premiere layer
  [_PR] = LAYOUT_ortho_3x10(
    _______, KC_Q,  KC_W,   KC_I,   KC_O, KC_P, IMPORT, EXPORT,  KC_MINS,  KC_EQL,
    _______, REDO,  KC_D,   KC_F,   KC_H, KC_M, KC_ENT, KC_LBRC, KC_RBRC,  OPEN,
    _______, PCOPY, PPASTE, KC_SPC, KC_Z, KC_C, KC_V,   KC_LEFT, KC_RIGHT, XD
  ),

  // Experience Design layer
  [_XD] = LAYOUT_ortho_3x10(
    _______, KC_E,    KC_R,  KC_T,  KC_P, KC_A, KC_L, KC_V, KC_DEL, NEW,
    _______, REDO,    GROUP, UNGRP, VIEW, HORZ, VERT, KC_Z, KC_ENT, OPEN,
    _______, KC_LCTL, COPY,  PAST,  SYMB, LOCK, MASK, HIDE, REPEAT, PS
  ),

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void matrix_init_user(void) {
  rgblight_enable();
}

void matrix_scan_user(void) {
  #ifdef RGBLIGHT_ENABLE

  static uint8_t old_layer = 255;
  uint8_t new_layer = biton32(layer_state);

  // Color of the Icons.
  if (old_layer != new_layer) {
    switch (new_layer) {
      case _PS:
        // #31C5F0
        rgblight_setrgb(49, 197, 240);
      break;
      case _AI:
        // #FF8011
        rgblight_setrgb(255, 128, 17);
      break;
      case _PR:
        // #E788FF
        rgblight_setrgb(231, 136, 255);
      break;
      case _XD:
        // #FF2BC2
        rgblight_setrgb(255, 43, 194);
      break;
    }
    old_layer = new_layer;
  }
  #endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if (record->event.pressed) {
		switch(keycode) {
			case MACRO_0:
        // Save for Web Macro.
				SEND_STRING(SS_LSFT(SS_LALT(SS_LCTRL("s"))));
				return false;
		}
	}
	return true;
};
