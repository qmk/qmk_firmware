#include QMK_KEYBOARD_H

#include "debug.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ALT_LAYER 4
#define _ADJUST 16

// control when held; esc when tapped
#define KC_CESC LCTL_T(KC_ESC)
// control when held; enter when tapped
#define KC_CNTR LCTL_T(KC_ENT)
// control when held; single quote when tapped; not used as shifted gives @
//define KC_CQUT LCTL_T(KC_QUOT)
// just a ^
#define MY_HAT LSFT(KC_6)
// less than (<)
#define MY_LTHN LSFT(KC_COMM)
// greater than (>)
#define MY_GTHN LSFT(KC_DOT)
// shift NUHS for PIPE
#define MY_PIPE LSFT(KC_NUBS)
// shift NUHS for tilde
#define MY_TLDE LSFT(KC_NUHS)
// shift quote for @
#define MY_AT LSFT(KC_QUOTE)

// undo 
#define KC__UDO LCTL(KC_Z)
// cut
#define KC__CUT LCTL(KC_X)
// copy
#define KC__CPY LCTL(KC_INS)
// paste
#define KC__PST LSFT(KC_INS)
// forward word
#define KC__FWD LCTL(KC_RGHT)
// backward word
#define KC__BWD LCTL(KC_LEFT)

#define ALT_LYR LM(_ALT_LAYER, MOD_LALT)


#define MODS_SHIFT_MASK (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))
#define SHIFT_HELD (get_mods() & MODS_SHIFT_MASK)


enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    ADJUST,
    VIM_G,
    ANSI_2,
    ANSI_QT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(  // Base layer
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                    ┌────────┬────────┬────────┬────────┬────────┬────────┐
     ALT_LYR,  KC_1,   ANSI_2,   KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_NUBS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_CESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, ANSI_QT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐  ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LGUI,    KC_RGUI, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘  └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    RAISE  , LOWER,   KC_SPC,              KC_CNTR,  ADJUST,   KC_LALT
                                // └────────┴────────┴────────┘           └────────┴────────┴────────┘
  ),

  [_LOWER] = LAYOUT(  // numpad layer  (LOWER)
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                    ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_TILD, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
     RESET,   KC_F11,  KC_F12,  KC_NO,   KC_NO,   KC_NO,                        KC_PLUS, KC_7,    KC_8,    KC_9,    KC_PERC, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   _______, KC_LEFT, KC_RGHT, KC_UP,   KC_LBRC,                      KC_MINS, KC_4,    KC_5,    KC_6,    KC_ASTR, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐  ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_EQL,  KC_EQL,  KC_1,    KC_2,    KC_3,    KC_SLSH, KC_SPC,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘  └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, KC_DEL,              KC_DOT,   KC_P0,  KC_COMM
                                // └────────┴────────┴────────┘           └────────┴────────┴────────┘
  ),

  [_RAISE] = LAYOUT(  // bracket layer (RAISE)
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                    ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   MY_LTHN, MY_GTHN, KC_NO,   KC_NO,   KC_NO,  
  //├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                      KC_EXLM, KC_LPRN, KC_RPRN, MY_AT,   KC_NUBS,  KC_DEL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL, KC_MPRV, KC_MNXT, KC_VOLU, KC_PGUP, KC_UNDS,                      KC_NUHS, KC_LBRC, KC_RBRC, MY_PIPE, MY_TLDE, KC_GRV,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐  ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_MUTE, KC_MSTP, KC_MPLY, KC_VOLD, KC_PGDN, KC_MINS, KC_LPRN,    _______, KC_AMPR, KC_LCBR, KC_RCBR,  KC_DLR,   MY_HAT, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘  └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, KC_UNDS,             _______, KC_UNDS, _______
                                // └────────┴────────┴────────┘           └────────┴────────┴────────┘
  ),

  [_ADJUST] = LAYOUT(  // move layer (ADJUST)
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                    ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_CAPS,  KC_NO,  KC__FWD,  KC_UP,   KC_NO,   KC_NO,                       _______, _______, KC_PSCR, KC_SLCK, KC_PAUS,  KC_DEL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______,  KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, VIM_G,                       KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐  ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC__UDO, KC__CUT, KC__CPY, KC__PST, KC__BWD, _______,    _______, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, KC_MUTE, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘  └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,             _______, _______, _______
                                // └────────┴────────┴────────┘           └────────┴────────┴────────┘
  ),

  [_ALT_LAYER] = LAYOUT(  // entered when the top left "esc" key is held
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                    ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                    ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, KC_RCTL,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐  ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘  └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     KC_NO,    KC_NO,   KC_NO,              KC_NO,   KC_NO,   KC_NO
                                // └────────┴────────┴────────┘           └────────┴────────┴────────┘
  ),
};


void key_press(uint8_t key) {
    add_key(key);
    send_keyboard_report();
}


void key_press_with_ctrl(uint8_t key) {
    add_key(LCTL(key));
    send_keyboard_report();
}


void key_release(uint8_t key) {
    del_key(key);
    send_keyboard_report();
}


bool action_function_vim_g(keyrecord_t *record) {
    uint8_t shift_held = SHIFT_HELD;
    if (record->event.pressed) {
        if (shift_held) {
            del_mods(shift_held);
            key_press_with_ctrl(KC_END);
            add_mods(shift_held);
        } else {
            key_press_with_ctrl(KC_HOME);
        }
    } else {
        key_release(shift_held ? KC_END : KC_HOME);
    }
    return false;
}


bool action_function_altered_shift(keyrecord_t *record, uint8_t base_key, uint8_t shifted_key) {
    // TODO do we need to worry about the tap count / interrupted states here?
    uint8_t shift_held = SHIFT_HELD;
    uint8_t key = base_key;
    if (shift_held) {
        key = shifted_key;
    }
    if (record->event.pressed) {
        key_press(key);
    } else {
        key_release(key);
    }
    return false;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
            break;
        case VIM_G:
            return action_function_vim_g(record);
            break;
        case ANSI_2:
            return action_function_altered_shift(record, KC_2, KC_QUOT);
            break;
        case ANSI_QT:
            return action_function_altered_shift(record, KC_QUOT, KC_2);  // really want ctrl on hold XXX
            break;
    }
    return true;
}
