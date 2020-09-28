#include QMK_KEYBOARD_H

//General Definitions
#define LOCKSCREEN LCTL(LSFT(KC_POWER)) // Screen Lock shortcut for OSX

// Figma Componenets
#define CREATECOMPONENT LALT(LGUI(KC_K))    // Create Components
#define SHOWCOMPONENT LALT(KC_KP_2)        // Show Components
#define TEAMLIB LALT(LGUI(KC_O))            // Team Library
#define DETACHO LALT(LGUI(KC_B))             // Detatch Library

// Figma Shortcuts
#define FIGLAYERS LALT(KC_KP_1)            // go to layers
#define SENDBACK LGUI(KC_LBRACKET)          // Send layers to back
#define BRINGFORW LGUI(KC_RBRACKET)         // Send layers to front
#define GRID LCTL(KC_G)                    // Open and close grids.
#define TEXTLEFT LALT(LGUI(KC_L))           // Text Align Left
#define TEXTRIGHT LALT(LGUI(KC_R))          // Text Align Right
#define TEXTCENTER LALT(LGUI(KC_T))         // Text Align Center
#define RUNLASTPLUG LALT(LALT(KC_P))        // Run last plugin


enum oktiboard_layers {
    _FIGMA,
    _LAB
};

enum custom_keycodes {
    M_AUTOLAY,
    M_COPYSTYLES
};

bool is_copied = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case M_AUTOLAY:
        if(!is_copied) {
            SEND_STRING(SS_LSFT(SS_TAP(X_A)));
            is_copied = true;
        } else {
            SEND_STRING(SS_LGUI(SS_LSFT(SS_TAP(X_A))));
            is_copied = false;
        }
        break;

    case M_COPYSTYLES:
        if(!is_copied) {
            SEND_STRING(SS_LGUI(SS_LALT(SS_TAP(X_C))));
            is_copied = true;
        } else {
            SEND_STRING(SS_LGUI(SS_LALT(SS_TAP(X_V))));
            is_copied = false;
        }
        break;
    }
    return true;
};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _FIGMA:
      rgblight_sethsv_noeeprom(139, 0, 139);
      break;
    case _LAB:
      rgblight_sethsv_noeeprom(255, 255, 255);
      break;
  }
  return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Figma
 * ,---------------------------.
 * |  CC  |  SC  |  TL  |  DI  |
 * |------+------+------+------|
 * |  LYR |  BF  |  SB  | SHG  |
 * |------+------+------+------|
 * | PLG  | TAL  | TAC  | TAR  |
 * |------+------+------+------|
 * | AUL  |      |  CPS | CHNG |
 * `---------------------------'
 */


[_FIGMA] = LAYOUT_ortho_4x4(
		CREATECOMPONENT, SHOWCOMPONENT, TEAMLIB, DETACHO,
		FIGLAYERS, BRINGFORW, SENDBACK, GRID,
		RUNLASTPLUG, TEXTLEFT, TEXTCENTER, TEXTRIGHT,
		M_AUTOLAY, _______ , M_COPYSTYLES, TO(_LAB)
),

/* Lab
 * ,---------------------------.
 * | FGM  |      |EEP_RS| RESET|
 * |------+------+------+------|
 * |      |AU_ON |AU_OFF|      |
 * |------+------+------+------|
 * |RGB_TG|RGB_VI|RGB_VD|      |
 * |------+------+------+------|
 * | LCK  |      |      | CHNG |
 * `---------------------------'
 */

[_LAB] = LAYOUT_ortho_4x4(
		_______, _______, EEP_RST, RESET,
		_______, AU_ON, AU_OFF, _______,
		RGB_TOG, RGB_VAI, RGB_VAD, _______,
		LOCKSCREEN, _______, _______, TO(_FIGMA)
	),
};
