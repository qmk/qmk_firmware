#include "keymap_norwegian.h"
#include QMK_KEYBOARD_H

/***************************************************************************************************************
*
*                                ERGOMECH
*
*
***************************************************************************************************************/

enum custom_keycodes {
    VDI_HOME = SAFE_RANGE,
    DOT_DOT_SLASH,
    VOL_TOGGLE,
    LAYER_CYCLE,
    TEMPLATE,
    CODEMON,
    TILDE,
    SPREAD
};

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// QWERTY
// ┌─────┬─────┬─────┬─────┬─────┬─────┬              ┌─────┬─────┬─────┬─────┬─────┬─────┐
// │ ESC │  1  │  2  │  3  │  4  │  5  │              │  6  │  7  │  8  │  9  │  0  │ MUTE│
// ├─────┼─────┼─────┼─────┼─────┼─────┤              ├─────┼─────┼─────┼─────┼─────┼─────┤
// │ TAB │  Q  │  W  │  E  │  R  │  T  │              │  Y  │  U  │  I  │  O  │  P  │  Å  │
// ├─────┼─────┼─────┼─────┼─────┼─────┤              ├─────┼─────┼─────┼─────┼─────┼─────┤
// │ LSFT│  A  │  S  │  D  │  F  │  G  │              │  H  │  J  │  K  │  L  │  Ø  │  Æ  │
// ├─────┼─────┼─────┼─────┼─────┼─────┤              ├─────┼─────┼─────┼─────┼─────┼─────┤
// │ LCTL│  Z  │  X  │  C  │  V  │  B  │  NUBS  │ DEL │  N  │  M  │  ,  │  .  │  -  │ ENT |
// ├─────┼─────┼─────┼─────┼─────┼─────┤              ├─────┼─────┼─────┼─────┼─────┼─────┤
// │     │ LALT│LGUI │ MO(LOWER) │ SPC │              │BSPC │ MO(RAISE) │ RALT│ APL │     |
// └─────┴─────┴─────┴───────────┴─────┴──────────────┴─────┴───────────┴─────┴─────┴─────┘

[_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,    KC_2,    KC_3,       KC_4,    KC_5,                           KC_6,    KC_7,       KC_8,    KC_9,    KC_0,    KC_KB_MUTE,
  KC_TAB,   KC_Q,    KC_W,    KC_E,       KC_R,    KC_T,                           KC_Y,    KC_U,       KC_I,    KC_O,    KC_P,    KC_LBRC,
  KC_LSFT,  KC_A,    KC_S,    KC_D,       KC_F,    KC_G,                           KC_H,    KC_J,       KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LCTL,  KC_Z,    KC_X,    KC_C,       KC_V,    KC_B, KC_NUBS,        KC_DEL,   KC_N,    KC_M,       KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
            KC_LALT, KC_LGUI, MO(_LOWER), KC_SPC,                                  KC_BSPC, MO(_RAISE), KC_RALT, KC_APP
),
// LOWER
// ╔═════╦═════╦═════╦═════╦═════╦═════╗              ╔══════╦══════╦══════╦══════╦══════╦═══════╗
// ║     ║ F1  ║ F2  ║ F3  ║ F4  ║ F5  ║              ║  ""  ║  '   ║  /   ║  *   ║  -   ║ Pause ║
// ╠═════╬═════╬═════╬═════╬═════╬═════╗              ╔══════╩══════╩══════╩══════╩══════╩═══════╣
// ║ VDI ║ F6  ║ F7  ║ F8  ║ F9  ║ F10 ║              ║  |   ║  7   ║  8   ║  9   ║  +   ║       ║
// ╠═════╬═════╬═════╬═════╬═════╬═════╗              ╔══════╩══════╩══════╩══════╩══════╩═══════╣
// ║     ║ F11 ║ F12 ║ *↑* ║ DLR ║     ║              ║  ,   ║  4   ║  5   ║  6   ║  .   ║       ║
// ╠═════╬═════╬═════╬═════╬═════╬═════╩══════════════╔══════╩══════╩══════╩══════╩══════╩═══════╣
// ║     ║     ║ *←* ║ *↓* ║ *→* ║     ║      ║  ~    ║  0   ║  1   ║  2   ║  3   ║  =   ║       ║
// ╠═════╬═════╬═════╬═════╬═════╬═════╩══════╩═══════╔══════╩══════╩══════╩══════╩══════╩═══════╣
// ║     ║     ║     ║     ║     ║     ║              ║      ║      ║      ║      ║      ║       ║
// ╚═════╩═════╩═════╩═════╩═════╩═════╝              ╚══════╩══════╩══════╩══════╩══════╩═══════╝

[_LOWER] = LAYOUT(
  _______,  KC_F1,   KC_F2,        KC_F3,        KC_F4,        KC_F5,                     KC_RBRC, KC_NUHS, KC_PSLS, KC_PAST, KC_PMNS, KC_MUTE,
  VDI_HOME, KC_F6,   KC_F7,        KC_F8,        KC_F9,        KC_F10,                    KC_GRV,  KC_P7,   KC_P8,   KC_P9,   KC_PPLS,  _______,
  _______,  KC_F11,  KC_F12,       LCA(KC_UP),   KC_DLR,       _______,                   KC_PDOT, KC_P4,   KC_P5,   KC_P6,   KC_PCMM,  _______,
  _______,  _______, LCA(KC_LEFT), LCA(KC_DOWN), LCA(KC_RGHT), _______, _______,   TILDE, KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_PEQL,  _______,
            _______, _______,      _______,      _______,                                 _______, _______, _______, _______
),
// RAISE
// ╔═════╦═════╦═════╦═════╦═════╦═════╗              ╔══════╦══════╦══════╦══════╦══════╦═════════╗
// ║     ║     ║     ║     ║     ║     ║              ║  |   ║  ""  ║  ''  |  \   ║  +   ║ VOL_TGL ║
// ╠═════╬═════╬═════╬═════╬═════╬═════╗              ╔══════╩══════╩══════╩══════╩══════╩═════════╣
// ║     ║     ║     ║     ║     ║     ║              ║  §   ║      ║      ║      ║ HOME ║ PG_UP   ║
// ╠═════╬═════╬═════╬═════╬═════╬═════╗              ╔══════╩══════╩══════╩══════╩══════╩═════════╣
// ║     ║     ║     ║     ║     ║     ║              ║  §   ║  DEL ║  ↑   ║      ║ END  ║ PG_DN   ║
// ╠═════╬═════╬═════╬═════╬═════╬═════╩══════════════╔══════╩══════╩══════╩══════╩══════╩═════════╣
// ║     ║     ║     ║     ║     ║     ║      ║       ║  .   ║  ←   ║  ↓   ║  →   ║  =   ║         ║
// ╠═════╬═════╬═════╬═════╬═════╬═════╩══════╩═══════╔══════╩══════╩══════╩══════╩══════╩═════════╣
// ║     ║     ║     ║     ║     ║     ║              ║ DEL  ║      ║      ║      ║      ║         ║
// ╚═════╩═════╩═════╩═════╩═════╩═════╝              ╚══════╩══════╩══════╩══════╩══════╩═════════╝

[_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                       KC_GRV,      KC_RBRC, KC_BSLS, KC_EQL,  KC_MINS, VOL_TOGGLE,
  _______, _______, _______, _______, _______, _______,                       TILDE,       _______, _______, _______, KC_HOME, KC_PGUP,
  _______, _______, _______, _______, _______, _______,                       KC_TILD,     KC_DEL,  KC_UP,   _______, KC_END,  KC_PGDN,
  _______, _______, _______, _______, _______, _______, _______,     _______, KC_PCMM,     KC_LEFT, KC_DOWN, KC_RGHT, KC_PEQL,  _______,
           _______, _______, _______, _______,                                             KC_DEL,  _______, _______, _______
),

// ADJUST
// ╔═══════╦═════╦═════╦═════╦═════╦═════╗              ╔═══════╦══════╦══════╦══════╦══════╦═════════╗
// ║ CYCLE ║     ║     ║     ║     ║     ║              ║ PRINT ║ ../  ║´${}´ ║      ║      ║         ║
// ╠═══════╬═════╬═════╬═════╬═════╬═════╗              ╔═══════╩══════╩══════╩══════╩══════╩═════════╣
// ║ RAISE ║     ║     ║     ║     ║     ║              ║       ║      ║      ║      ║      ║         ║
// ╠═══════╬═════╬═════╬═════╬═════╬═════╗              ╔═══════╩══════╩══════╩══════╩══════╩═════════╣
// ║ QWERTY║     ║     ║     ║     ║     ║              ║       ║      ║      ║      ║      ║         ║
// ╠═══════╬═════╬═════╬═════╬═════╬═════╩══════════════╔═══════╩══════╩══════╩══════╩══════╩═════════╣
// ║ LOWER ║     ║     ║     ║     ║     ║      ║       ║       ║      ║      ║      ║      ║         ║
// ╠═══════╬═════╬═════╬═════╬═════╬═════╩══════╩═══════╔═══════╩══════╩══════╩══════╩══════╩═════════╣
// ║       ║     ║     ║     ║     ║     ║              ║       ║      ║      ║      ║      ║         ║
// ╚═══════╩═════╩═════╩═════╩═════╩═════╝              ╚═══════╩══════╩══════╩══════╩══════╩═════════╝

[_ADJUST] = LAYOUT(
  LAYER_CYCLE, _______, _______,             _______,             _______,              _______,                         KC_PSCR, DOT_DOT_SLASH, TEMPLATE, CODEMON, SPREAD, _______,
  DF(_RAISE),  _______, _______,             _______,             _______,              _______,                         _______, _______,       _______,  _______, _______, _______,
  DF(_QWERTY), _______, _______,             LCTL(LGUI(KC_UP)),   _______,              _______,                         _______, _______,       _______,  _______, _______, _______,
  DF(_LOWER),  _______, LCTL(LGUI(KC_LEFT)), LCTL(LGUI(KC_DOWN)), LCTL(LGUI(KC_RIGHT)), _______, _______,       _______, _______, _______,       _______,  _______, _______, _______,
               _______, _______,             _______,             _______,                                                        _______,       _______,  _______, _______
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false); } return false; }
#endif // OLED_ENABLE

void HYPHEN(void) {
    register_code(KC_RSFT);
    tap_code(KC_EQL);
    tap_code(KC_EQL);
    unregister_code(KC_RSFT);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t current_default_layer = get_highest_layer(default_layer_state);

    if (record->event.pressed) {
        switch (keycode) {
        case VDI_HOME:
            SEND_STRING(
                SS_TAP(X_ESC)
                SS_DELAY(200)
                SS_DOWN(X_LCTL)
                SS_DOWN(X_LALT)
                SS_TAP(X_PAUS)
                SS_UP(X_LALT)
                SS_UP(X_LCTL)
                SS_DELAY(600)
                SS_LCTL(SS_LGUI(SS_TAP(X_RIGHT)))
            );
            return false;

        case DOT_DOT_SLASH:
            send_string("..");
            tap_code16(S(KC_7));
            break;

        case SPREAD:
            SEND_STRING(SS_RALT("7")"..."SS_RALT("7")SS_RALT("0")SS_RALT("0"));
            tap_code(KC_LEFT);
            tap_code(KC_LEFT);

        break;

        case TILDE:
            register_code(KC_RALT);
            tap_code(KC_RBRC);
            tap_code(KC_RBRC);
            unregister_code(KC_RALT);
        break;

        case CODEMON:
            HYPHEN();
            HYPHEN();
            HYPHEN();
            register_code(KC_LSFT);
            tap_code(KC_ENTER);
            tap_code(KC_ENTER);
            unregister_code(KC_LSFT);
            HYPHEN();
            HYPHEN();
            HYPHEN();
            tap_code(KC_UP);
        break;

        case TEMPLATE:
            HYPHEN();
            SEND_STRING(SS_RALT("4"));
            SEND_STRING(SS_RALT("7"));
            SEND_STRING(SS_RALT("0"));
            HYPHEN();
            tap_code(KC_LEFT);
            tap_code(KC_LEFT);
            break;

        case LAYER_CYCLE:

            if (current_default_layer == _QWERTY) {

                default_layer_set(1UL << _RAISE);
            } else if (current_default_layer == _RAISE) {
                default_layer_set(1UL << _LOWER);
            } else if (current_default_layer == _LOWER) {
                default_layer_set(1UL << _ADJUST);
            } else if (current_default_layer == _ADJUST) {
                default_layer_set(1UL << _QWERTY);
            } else {


                default_layer_set(1UL << _QWERTY);
            }
            return false;

         case VOL_TOGGLE:
            // Check if Shift is held during the press
            if (get_mods() & MOD_MASK_SHIFT) {
                tap_code(KC_KB_VOLUME_DOWN); // Volume down
            } else {
                tap_code(KC_KB_VOLUME_UP); // Volume up
            }
        break;
        }

    }
    return true;
};
