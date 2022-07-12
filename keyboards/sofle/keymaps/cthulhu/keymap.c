#include QMK_KEYBOARD_H
#include <string.h>
#include "lib/lib8tion/lib8tion.h"

#ifdef OLED_ENABLE
#include <stdio.h>

char wpm_str[4];
#endif

enum sofle_layers {
    _MACOS,
    _WIN10,
    _NUMP,
    _SYMB,
    _TUNE,
    _MOUSE
};

enum custom_keycodes {
    SYMB = SAFE_RANGE,
    NUMP,
    OS,
    MAC_A,
    MAC_E,
    MAC_I,
    MAC_O,
    MAC_U,
    MAC_N,
    KC_MOUSE_BTN1,
    KC_MOUSE_BTN2
};

enum td_keycodes {
    ESCAPE,
    COMMAND,
    ALT,
    ESC_SYM
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [ESCAPE] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_DEL),
    [ALT] = ACTION_TAP_DANCE_DOUBLE(KC_ALGR, KC_LALT),
    [ESC_SYM] = ACTION_TAP_DANCE_DOUBLE(KC_GRV, KC_TILDE)
};

uint8_t MOUSE_BUTTONS;
uint16_t trackball_led_timer;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * _MACOS
 * ,--------------------------------------------.                    ,-----------------------------------------.
 * | ESC DEL |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Bspc |
 * |---------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |CTRL TAB |   '  |   ,  |   .  |   P  |   Y  |                    |   F  |   G  |   C  |   R  |   L  |  ?   |
 * |---------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL    |   A  |   O  |   E  |   U  |   I  |-------.    ,-------|   D  |   H  |   T  |   N  |   S  |  -   |
 * |---------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |SFT BLOCK|   ;  |   Q  |   J  |   K  |   X  |-------|    |-------|   B  |   M  |   W  |   V  |   Z  | ESC  |
 * `--------------------------------------------/      /     \      \-----------------------------------------'
 *              |   [  | LGUI | CMD  |SYMB  | /SPACE  /       \ ENTER\  |NUMP  |ALTGR | RALT |   ]  |
 *              |      |      |CAPS  |      |/       /         \      \ |ENTER |ALT   |      |      |
 *              `-----------------------------------'           '------''---------------------------'
 */

[_MACOS] = LAYOUT( \
  KC_GESC,          KC_1,       KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_BSPC, \
  LSFT_T(KC_TAB),   KC_QUOTE,   KC_COMM, KC_DOT,  KC_P,    KC_Y,                        KC_F,    KC_G,    KC_C,    KC_R,    KC_L,     KC_BSLS, \
  KC_LCTRL,         MAC_A,      MAC_O,   MAC_E,   MAC_U,   MAC_I,                       KC_D,    KC_H,    KC_T,    KC_N,    KC_S,     KC_QUOTE, \
  LCTL_T(KC_CAPS),  KC_SCLN,    KC_Q,    KC_J,    KC_K,    KC_X, KC_MUTE,     XXXXXXX,  KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,     RSFT_T(ALGR(KC_SLASH)), \
                 KC_LBRC ,KC_LGUI, KC_LCMD, SYMB, KC_SPC,                       KC_ENT,  MT(NUMP,KC_ENT), TD(ALT), KC_RALT, KC_RBRC \
),
/*
 * _WIN10
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   F  |   P  |   G  |                    |   J  |   L  |   U  |   Y  |   ;  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   A  |   R  |   S  |   T  |   D  |-------.    ,-------|   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   K  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |   [  | LGUI | CMD  |SYMB  | /SPACE  /       \SPACE \  |NUMP  | ALTGR| RALT |   ]  |
 *            |      |      | CAPS |      |/       /         \      \ |ENTER | ALT  |      |      |
 *            `-----------------------------------'           '------''---------------------------'
 */

[_WIN10] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, KC_E,    _______, _______,                          _______, KC_U,    KC_I,    KC_O,    _______, _______, \
  _______, KC_A,    _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______,       XXXXXXX,  KC_N,    _______, _______, _______, _______, _______, \
                    _______, _______, _______, _______, _______,                 _______, _______, _______, _______, _______ \
),
/* _NUMP
 * ,-----------------------------------------.                     ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                     |  F7  |  F8  |  F9  |  F10  | F11  | F12 |
 * |------+------+------+------+------+------|                     |------+------+------+------+------+------|
 * |   -  |   +  |  7   |   8  |  9   |  ,   |                     |  >   | HOME |   UP |  END |      |BCKSPC|
 * |------+------+------+------+------+------|                     |------+------+------+------+------+------|
 * |  /   |   *  |  4   |   5  |  6   |  .   |-------.     ,-------|  <   |LEFT  | DOWN | RIGHT|      |      |
 * |------+------+------+------+------+------|  MUTE |     |       |------+------+------+------+------+------|
 * |  ^   |   =  |  1   |   2  |  3   |  0   |-------|     |-------|      |  (   |  )   |      |      |      |
 * `-----------------------------------------/       /      \      \-----------------------------------------'
 *            |   [  | LGUI | CMD  |SYMB  | /SPACE  /        \SPACE \  |NUMP  | ALTGR| RALT |   ]  |
 *            |      |      | CAPS |ENTER |/       /          \      \ |ENTER | ALT  |      |      |
 *            `-----------------------------------'            '------''---------------------------'
 */
[_NUMP] = LAYOUT( \
  KC_F1,    KC_F2,     KC_F3,   KC_F4,   KC_F5,               KC_F6,                                   KC_F7,   KC_F8,     KC_F9,      KC_F10,   KC_F11,  KC_F12, \
  KC_MINUS, KC_PPLS,   KC_7,    KC_8,    KC_9,                KC_COMM,                                 KC_RABK, KC_HOME,   KC_UP,      KC_END,   XXXXXXX, KC_BSPC, \
  KC_SLASH, KC_ASTR,   KC_4,    KC_5,    KC_6,                KC_DOT,                                  KC_LABK, KC_LEFT,   KC_DOWN,    KC_RIGHT, XXXXXXX, XXXXXXX,
  KC_CIRC,  KC_EQUAL,  KC_1,    KC_2,    KC_3,                KC_0,            _______,       _______, XXXXXXX, LSFT(KC_9),LSFT(KC_0), XXXXXXX,  XXXXXXX, XXXXXXX, \
                       _______, _______, MT(KC_LCMD,KC_CAPS), MT(SYMB,KC_ENT), _______,       _______, _______, _______, _______, _______\
),
/* _SYMB
 * ,----------------------------------------.                      ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                     |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                     |------+------+------+------+------+------|
 * |  ` ~ |  !   |  �   |  #   |  $   | %    |                     |  &   | HOME | UP   | END  |PGUP  |BKSPCK|
 * |------+------+------+------+------+------|                     |------+------+------+------+------+------|
 * |      |  {   |  }   |  [   |  ]   |  \   |-------.     ,-------|  |   | LEFT | DOWN |RIGHT |PGDOWN|      |
 * |------+------+------+------+------+------|  MUTE |     |       |------+------+------+------+------+------|
 * |      |  (   |  )   |      |      |PCREEN|-------|     |-------| =    |   �  |      |  �   |  ~   |      |
 * `-----------------------------------------/       /      \      \-----------------------------------------'
 *            |   [  | LGUI | CMD  |SYMB  | /SPACE  /        \SPACE \  |NUMP  | ALTGR| RALT |   ]  |
 *            |      |      | CAPS |ENTER |/       /          \      \ |ENTER | ALT  |      |      |
 *            `-----------------------------------'            '------''---------------------------'
 */
[_SYMB] = LAYOUT( \
  _______,     _______,   _______,    _______, _______ ,  _______,                          _______,       _______,        _______,  _______,      _______ ,_______, \
  TD(ESC_SYM), KC_EXLM,   ALGR(KC_1), KC_HASH, KC_DOLLAR, KC_PERC,                          KC_AMPR,       KC_HOME,        KC_UP,   KC_END,        KC_PGUP, KC_DEL,
  XXXXXXX,     KC_LCBR,   KC_RCBR,    KC_LBRC, KC_RBRC,   KC_BSLS,                          LSFT(KC_BSLS), KC_LEFT,        KC_DOWN, KC_RIGHT,      KC_PGDN, XXXXXXX,
  XXXXXXX,     LSFT(KC_9),LSFT(KC_0), XXXXXXX, XXXXXXX,   KC_PSCR, _______,       XXXXXXX,  KC_EQUAL,      ALGR(KC_QUOTE), XXXXXXX, ALGR(KC_BSLS), KC_TILDE,XXXXXXX,\
                   _______, _______, MT(KC_LCMD,KC_CAPS), _______, _______,       _______, _______, _______, _______, _______ \
),
/* _TUNE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |QWERTY|COLEMAK|MACWIN|     |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | RESET|      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TOG  |  HUI |  SAI |  VAI |  SPI |  MOD |-------.    ,-------|      | MUTE | VOLD | VOLU | OS   |      |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |      |  HUD |  SAD |  VAD |  SPD |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |   [  | LGUI | CMD  |SYMB  | /SPACE  /       \SPACE \  |NUMP  | ALTGR| RALT |   ]  |
 *            |      |      | CAPS |ENTER |/       /         \      \ |ENTER | ALT  |      |      |
 *            `-----------------------------------'           '------''---------------------------'
 */
  [_TUNE] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,   RGB_MOD,                      XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, OS,      XXXXXXX, \
  XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,   XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
         _______, _______, MT(KC_LCMD,KC_CAPS) , _______, _______,    _______, _______, _______, _______, _______ \
  ),
/* _MOUSE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|MS_BT1|MS_BT2|      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |   [  | LGUI | CMD  |SYMB  | /SPACE  /       \SPACE \  |NUMP  | ALTGR| RALT |   ]  |
 *            |      |      | CAPS |ENTER |/       /         \      \ |ENTER | ALT  |      |      |
 *            `-----------------------------------'           '------''---------------------------'
 */
  [_MOUSE] = LAYOUT( \
  XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     KC_MS_BTN1, KC_MS_BTN2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                   _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______ \
  )
};


led_t led_usb_state;
uint8_t mod_state;
bool key_registered;

#ifdef OLED_ENABLE


static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
    };

    oled_write_P(qmk_logo, false);
}

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("MODE"), false);
    oled_write_ln_P(PSTR(""), false);

    if (IS_LAYER_ON(_WIN10)) {
        oled_write_ln_P(PSTR("MAC"), false);
    } else {
        oled_write_ln_P(PSTR("WIN"), false);
    }

    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _MACOS:
        case _WIN10:
            oled_write_P(PSTR("BASE\n"), false);
            break;
        case _NUMP:
            oled_write_P(PSTR("NUMP\n"), false);
            break;
        case _SYMB:
            oled_write_P(PSTR("SYMB\n"), false);
            break;
        case _TUNE:
            oled_write_P(PSTR("TUNE\n"), false);
            break;
        case _MOUSE:
            oled_write_P(PSTR("MOUSE\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef\n"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}


bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }

    return false;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SYMB:
            if (record->event.pressed) {
                layer_on(_SYMB);
                update_tri_layer(_SYMB, _NUMP, _TUNE);
            } else {
                layer_off(_SYMB);
                update_tri_layer(_SYMB, _NUMP, _TUNE);
            }
            return false;

        case MT(SYMB,KC_ENT):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_ENT);
            } else if (record->event.pressed) {
                layer_on(_SYMB);
                update_tri_layer(_SYMB, _NUMP, _TUNE);
            } else {
                layer_off(_SYMB);
                update_tri_layer(_SYMB, _NUMP, _TUNE);
            }
            return false;

        case MT(NUMP,KC_ENT):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_ENT);
            } else if (record->event.pressed) {
                layer_on(_NUMP);
                update_tri_layer(_SYMB, _NUMP, _TUNE);
            } else {
                layer_off(_NUMP);
                update_tri_layer(_SYMB, _NUMP, _TUNE);
            }
            return false;

        case MT(KC_LCMD,KC_CAPS):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_CAPS);
            } else if (record->event.pressed) {
                register_code16(KC_LCMD);
            } else {
                unregister_code16(KC_LCMD);
            }
            return false;

        case LCTL_T(KC_TAB):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_TAB);
                return false;
            }
            break;

        case LSFT_T(LSFT(KC_9)):
            if (record->tap.count && record->event.pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    tap_code16(LSFT(KC_0)); // )
                } else {
                    tap_code16(LSFT(KC_9)); // (
                }
            } else if (record->event.pressed) {
                register_code16(KC_LSFT);
            } else {
                unregister_code16(KC_LSFT);
            }
            return false;

        case RSFT_T(ALGR(KC_SLASH)):
            if (record->tap.count && record->event.pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    tap_code16(KC_QUES); // ?
                } else {
                    tap_code16(ALGR(KC_SLASH)); // �
                }
            } else if (record->event.pressed) {
                register_code16(KC_RSFT);
            } else {
                unregister_code16(KC_RSFT);
            }
            return false;

        case KC_MINUS:
           if (record->event.pressed) { // al presionar el keycode
                if (mod_state & MOD_MASK_SHIFT) { // si SHIFT esta presionado
                    del_mods(MOD_MASK_SHIFT); // desactivar SHIFT
                    tap_code16(LSFT(KC_MINUS)); // ya que LSFT(KC_MINUS) entrega el simbolo _
                    key_registered = true;
                    set_mods(mod_state); // volver a activar SHIFT
                    return false;
                }

                if (mod_state & MOD_MASK_ALT) { // si ALT esta presionado
                    del_mods(MOD_MASK_ALT); // desactivar ALT
                    tap_code16(KC_SLASH); // ya que KC_SLASH entrega el simbolo /
                    key_registered = true;
                    set_mods(mod_state); // volver a activar ALT
                    return false;
                }

                else {
                    tap_code16(KC_MINUS);
                    key_registered = true;
                    return false;
                }

            } else { // al liberar el keycode

                if (key_registered) {
                    key_registered = false;
                    return false;
                }
            }

        case KC_PLUS:
           if (record->event.pressed) { // al presionar el keycode
                if (mod_state & MOD_MASK_SHIFT) { // si SHIFT esta presionado
                    del_mods(MOD_MASK_SHIFT); // desactivar SHIFT
                    tap_code16(KC_ASTR); // ya que KC_ASTR entrega el simbolo *
                    key_registered = true;
                    set_mods(mod_state); // volver a activar SHIFT
                    return false;
                }

                if (mod_state & MOD_MASK_ALT) { // si ALT esta presionado
                    del_mods(MOD_MASK_ALT); // desactivar ALT
                    tap_code16(KC_EQUAL); // ya que KC_EQUAL entrega el simbolo =
                    key_registered = true;
                    set_mods(mod_state); // volver a activar ALT
                    return false;
                }

                else {
                    tap_code16(KC_PLUS);
                    key_registered = true;
                    return false;
                }

            } else { // al liberar el keycode

                if (key_registered) {
                    key_registered = false;
                    return false;
                }
            }

        case KC_QUOTE:
            if (record->event.pressed) { // al presionar el keycode
                if (mod_state & MOD_MASK_SHIFT) { // si SHIFT esta presionado
                    del_mods(MOD_MASK_SHIFT);
                    register_code16(KC_DQUO); // registrar "
                    register_code16(KC_SPC);
                    key_registered = true;
                    set_mods(mod_state);
                    return false; // ya que true registraria ademas el keycode quote
                } else {
                    tap_code16(KC_QUOTE);
                    tap_code16(KC_SPC);
                }
            } else { // al liberar el keycode
                if (key_registered) {
                    unregister_code16(KC_DQUO); // dejar de registrar KC_DQUO
                    unregister_code16(KC_SPC);
                    key_registered = false;
                    return false;
                }
            }
            return false;

        case KC_CIRC:
            if (record->event.pressed) {
                register_code16(KC_CIRC);
                register_code16(KC_SPC);
            } else {
                unregister_code16(KC_CIRC);
                unregister_code16(KC_SPC);
            }
            return false;

        case KC_GRV:
            if (record->event.pressed) {
                register_code16(KC_GRV);
                register_code16(KC_SPC);
            } else {
                unregister_code16(KC_GRV);
                unregister_code16(KC_SPC);
            }
            return false;

        case KC_TILDE:
            if (record->event.pressed) {
                register_code16(KC_TILDE);
                register_code16(KC_SPC);
            } else {
                unregister_code16(KC_TILDE);
                unregister_code16(KC_SPC);
            }
            return false;

        case OS:
            if (record->event.pressed) {
                if (IS_LAYER_OFF(_WIN10)) {
                    layer_on(_WIN10);
                } else {
                    layer_off(_WIN10);
                }
            } else {
                ;
            }
            return false;

        case MAC_A:
            if (record->event.pressed) { // al presionar el keycode
                if (mod_state & MOD_MASK_ALT) { // si algun ALT esta presionado
                    if (mod_state & MOD_MASK_SHIFT) {
                        del_mods(MOD_MASK_ALT);
                        del_mods(MOD_MASK_SHIFT);
                        tap_code16(ALGR(KC_E)); // registrar ALTGR + e
                        tap_code16(LSFT(KC_A)); // registrar A
                        key_registered = true;
                        set_mods(mod_state);
                        return false;
                    } else {
                        del_mods(MOD_MASK_ALT);
                        tap_code16(ALGR(KC_E)); // registrar ALTGR + e
                        tap_code16(KC_A); // registrar a
                        key_registered = true;
                        set_mods(mod_state);
                        return false;
                    }
                } else { // si no hay ningun ALT presionado
                    if (mod_state & MOD_MASK_SHIFT) { // si SHIFT esta presionado
                        del_mods(MOD_MASK_SHIFT);
                        tap_code16(LSFT(KC_A));
                        key_registered = true;
                        set_mods(mod_state);
                        return false;
                    } else { // si SHIFT no esta presionado
                        tap_code16(KC_A);
                        key_registered = true;
                        return false;
                    }
                }
            } else { // al liberar el keycode
                if (key_registered) {
                    key_registered = false;
                    return false;
                }
            }
            return false;

        case MAC_E:
            if (record->event.pressed) { // al presionar el keycode
                if (mod_state & MOD_MASK_ALT) { // si algun ALT esta presionado
                    if (mod_state & MOD_MASK_SHIFT) {
                        del_mods(MOD_MASK_ALT);
                        del_mods(MOD_MASK_SHIFT);
                        tap_code16(ALGR(KC_E)); // registrar ALTGR + e
                        tap_code16(LSFT(KC_E)); // registrar E
                        key_registered = true;
                        set_mods(mod_state);
                        return false;
                    } else {
                        del_mods(MOD_MASK_ALT);
                        tap_code16(ALGR(KC_E)); // registrar ALTGR + e
                        tap_code16(KC_E); // registrar e
                        key_registered = true;
                        set_mods(mod_state);
                        return false;
                    }
                } else { // si no hay ningun ALT presionado
                    if (mod_state & MOD_MASK_SHIFT) { // si SHIFT esta presionado
                        del_mods(MOD_MASK_SHIFT);
                        tap_code16(LSFT(KC_E));
                        key_registered = true;
                        set_mods(mod_state);
                        return false;
                    } else { // si SHIFT no esta presionado
                        tap_code16(KC_E);
                        key_registered = true;
                        return false;
                    }
                }
            } else { // al liberar el keycode
                if (key_registered) {
                    key_registered = false;
                    return false;
                }
            }
            return false;

        case MAC_I:
            if (record->event.pressed) { // al presionar el keycode
                if (mod_state & MOD_MASK_ALT) { // si algun ALT esta presionado
                    if (mod_state & MOD_MASK_SHIFT) {
                        del_mods(MOD_MASK_ALT);
                        del_mods(MOD_MASK_SHIFT);
                        tap_code16(ALGR(KC_E)); // registrar ALTGR + e
                        tap_code16(LSFT(KC_I)); // registrar I
                        key_registered = true;
                        set_mods(mod_state);
                        return false;
                    } else {
                        del_mods(MOD_MASK_ALT);
                        tap_code16(ALGR(KC_E)); // registrar ALTGR + e
                        tap_code16(KC_I); // registrar i
                        key_registered = true;
                        set_mods(mod_state);
                        return false;
                    }
                } else { // si no hay ningun ALT presionado
                    if (mod_state & MOD_MASK_SHIFT) { // si SHIFT esta presionado
                        del_mods(MOD_MASK_SHIFT);
                        tap_code16(LSFT(KC_I));
                        key_registered = true;
                        set_mods(mod_state);
                        return false;
                    } else { // si SHIFT no esta presionado
                        tap_code16(KC_I);
                        key_registered = true;
                        return false;
                    }
                }
            } else { // al liberar el keycode
                if (key_registered) {
                    key_registered = false;
                    return false;
                }
            }
            return false;

        case MAC_O:
            if (record->event.pressed) { // al presionar el keycode
                if (mod_state & MOD_MASK_ALT) { // si algun ALT esta presionado
                    if (mod_state & MOD_MASK_SHIFT) {
                        del_mods(MOD_MASK_ALT);
                        del_mods(MOD_MASK_SHIFT);
                        tap_code16(ALGR(KC_E)); // registrar ALTGR + e
                        tap_code16(LSFT(KC_O)); // registrar O
                        key_registered = true;
                        set_mods(mod_state);
                        return false;
                    } else {
                        del_mods(MOD_MASK_ALT);
                        tap_code16(ALGR(KC_E)); // registrar ALTGR + e
                        tap_code16(KC_O); // registrar o
                        key_registered = true;
                        set_mods(mod_state);
                        return false;
                    }
                } else { // si no hay ningun ALT presionado
                    if (mod_state & MOD_MASK_SHIFT) { // si SHIFT esta presionado
                        del_mods(MOD_MASK_SHIFT);
                        tap_code16(LSFT(KC_O));
                        key_registered = true;
                        set_mods(mod_state);
                        return false;
                    } else { // si SHIFT no esta presionado
                        tap_code16(KC_O);
                        key_registered = true;
                        return false;
                    }
                }
            } else { // al liberar el keycode
                if (key_registered) {
                    key_registered = false;
                    return false;
                }
            }
            return false;

        case MAC_U:
            if (record->event.pressed) { // al presionar el keycode
                if (mod_state & MOD_MASK_ALT) { // si algun ALT esta presionado
                    if (mod_state & MOD_MASK_SHIFT) {
                        del_mods(MOD_MASK_ALT);
                        del_mods(MOD_MASK_SHIFT);
                        tap_code16(ALGR(KC_E)); // registrar ALTGR + e
                        tap_code16(LSFT(KC_U)); // registrar U
                        key_registered = true;
                        set_mods(mod_state);
                        return false;
                    } else {
                        del_mods(MOD_MASK_ALT);
                        tap_code16(ALGR(KC_E)); // registrar ALTGR + e
                        tap_code16(KC_U); // registrar u
                        key_registered = true;
                        set_mods(mod_state);
                        return false;
                    }
                } else { // si no hay ningun ALT presionado
                    if (mod_state & MOD_MASK_SHIFT) { // si SHIFT esta presionado
                        del_mods(MOD_MASK_SHIFT);
                        tap_code16(LSFT(KC_U));
                        key_registered = true;
                        set_mods(mod_state);
                        return false;
                    } else { // si SHIFT no esta presionado
                        tap_code16(KC_U);
                        key_registered = true;
                        return false;
                    }
                }
            } else { // al liberar el keycode
                if (key_registered) {
                    key_registered = false;
                    return false;
                }
            }
            return false;

        case MAC_N:
            if (record->event.pressed) { // al presionar el keycode
                if (mod_state & MOD_MASK_ALT) { // si algun ALT esta presionado
                    if (mod_state & MOD_MASK_SHIFT) {
                        del_mods(MOD_MASK_ALT);
                        del_mods(MOD_MASK_SHIFT);
                        tap_code16(ALGR(KC_N)); // registrar ALTGR + n
                        tap_code16(LSFT(KC_N));
                        key_registered = true;
                        set_mods(mod_state);
                        return false;
                    } else {
                        del_mods(MOD_MASK_ALT);
                        tap_code16(ALGR(KC_N)); // registrar ALTGR + n
                        tap_code16(KC_N); // registrar n
                        key_registered = true;
                        set_mods(mod_state);
                        return false;
                    }
                } else { // si no hay ningun ALT presionado
                    if (mod_state & MOD_MASK_SHIFT) { // si SHIFT esta presionado o bloq mayus activado
                        del_mods(MOD_MASK_SHIFT);
                        tap_code16(LSFT(KC_N));
                        key_registered = true;
                        set_mods(mod_state);
                        return false;
                    } else { // si SHIFT no esta presionado ni bloq mayus activado
                        tap_code16(KC_N);
                        key_registered = true;
                        return false;
                    }
                }
            } else { // al liberar el keycode
                if (key_registered) {
                    key_registered = false;
                    return false;
                }
            }
            return false;

        case KC_MOUSE_BTN1:
            if (record->event.pressed) {
                MOUSE_BUTTONS |= (1 << 0);
            } else {
                MOUSE_BUTTONS &= ~(1 << 0);
            }
            return false;

        case KC_MOUSE_BTN2:
            if (record->event.pressed) {
                MOUSE_BUTTONS |= (1 << 1);
            } else {
                MOUSE_BUTTONS &= ~(1 << 1);
            }
            return false;
    }
    return true;
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (get_highest_layer(layer_state)) {
        case _MACOS:
        case _WIN10:
            if (index == 0) {
                if (clockwise) {
                    tap_code(KC_VOLD);
                } else {
                    tap_code(KC_VOLU);
                }
            }
        break;

        case _NUMP:
            if (index == 0) {
                if (clockwise) {
                    tap_code(KC_MPRV);
                } else {
                    tap_code(KC_MNXT);
                }
            }
        break;
    }
    return true;
}

#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _NUMP, _SYMB, _TUNE);
#ifdef RGBLIGHT_ENABLE
    switch (biton32(state)) {
    case _NUMP:
        // if (!host_keyboard_led_state().caps_lock) {
        //     rgblight_sethsv(HSV_TEAL);
        // }
        pimoroni_trackball_set_rgbw(255, 0, 0, 0.5);
        break;
    case _SYMB:
        // if (!host_keyboard_led_state().caps_lock) {
        //     rgblight_sethsv(HSV_TEAL);
        // }
        pimoroni_trackball_set_rgbw(0, 0, 255, 0.5);
        break;
    case _TUNE:
        // if (!host_keyboard_led_state().caps_lock) {
        //     rgblight_sethsv(HSV_TEAL);
        // }
        pimoroni_trackball_set_rgbw(255, 0, 255, 0.5);
        break;
    case _WIN10:
        // if (!host_keyboard_led_state().caps_lock) {
        //     rgblight_sethsv(HSV_TEAL);
        // }
        pimoroni_trackball_set_rgbw(255, 255, 255, 0.5);
        break;
    case _MACOS:
        // if (!host_keyboard_led_state().caps_lock) {
        //     rgblight_sethsv(HSV_TEAL);
        // }
        pimoroni_trackball_set_rgbw(255, 255, 255, 0.5);
        break;
    case _MOUSE:
        pimoroni_trackball_set_rgbw(0, 255, 0, 0.5);
        break;
    }
#endif
return state;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_LPRN):
        case LCTL_T(KC_TAB):
        case MT(KC_LCMD,KC_CAPS):
        case RSFT_T(ALGR(KC_SLASH)):
        case MT(SYMB,KC_ENT):
        case MT(NUMP,KC_ENT):
            return 125;

        default:
            return TAPPING_TERM;
    }
}

static report_mouse_t last_mouse_report   = {0};
static bool           is_scrolling        = false;

report_mouse_t smooth_mouse_movement(report_mouse_t mouse_report) {
    // Linear interpolation and ease-in-out
    static fract8 fract = 0.5;
    int8_t        x     = 0;
    int8_t        y     = 0;
    int8_t        h     = 0;
    int8_t        v     = 0;

    if (!is_scrolling) {
        x = ease8InOutApprox(lerp8by8(last_mouse_report.x, mouse_report.x, fract));
        y = ease8InOutApprox(lerp8by8(last_mouse_report.y, mouse_report.y, fract));
    } else {
        h = ease8InOutApprox(lerp8by8(last_mouse_report.x, mouse_report.x, fract));
        v = ease8InOutApprox(lerp8by8(last_mouse_report.y, mouse_report.y, fract));
    }

    // update the new smoothed report
    mouse_report.x = x;
    mouse_report.y = y;
    mouse_report.h = h;
    mouse_report.v = v;

    return mouse_report;
}

void keyboard_post_init_kb(void) {
    keyboard_post_init_user();
    pimoroni_trackball_set_rgbw(255, 255, 255, 0.5);
}
