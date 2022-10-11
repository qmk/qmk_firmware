// Copyright 2021 Nicolas Druoton (druotoni)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_french.h"
#include "transactions.h"

// global
#include "gui_state.h"
#include "boot.h"
#include "navi_logo.h"

#include "draw_helper.h"
#include "fast_random.h"

// left side
#include "layer_frame.h"
#include "burst.h"

// right side
#include "ring.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* QWERTY
* ,-----------------------------------------.                    ,-----------------------------------------.
* | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  DEL |
* |------+------+------+------+------+------|                    |------+------+------+------+------+------|
* | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  ^   |
* |------+------+------+------+------+------|                    |------+------+------+------+------+------|
* |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |RShift|
* |------+------+------+------+------+------|  "    |    |  )    |------+------+------+------+------+------|
* |LCTRL |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |  $   |
* `-----------------------------------------/       /     \      \-----------------------------------------'
*                   | LAlt |  SPE | Space| /  NAV  /       \Enter \  |BackSP| ]    | RGUI |
*                   |      |      |      |/       /         \      \ |      |      |      |
*                   `----------------------------'           '------''--------------------'
*/
    [_QWERTY] = LAYOUT(
    KC_ESC,   KC_1,   KC_2,    KC_3,          KC_4,    KC_5,                              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DELETE, 
    KC_TAB,   KC_Q,   KC_W,    KC_E,          KC_R,    KC_T,                              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    FR_CIRC, 
    KC_LSFT,  KC_A,   KC_S,    KC_D,          KC_F,    KC_G,                              KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_RSFT, 
    KC_LCTRL, KC_Z,   KC_X,    KC_C,          KC_V,    KC_B,    S(KC_Z),   FR_RPRN,       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_QUOT, 
    KC_LALT, TT(_RAISE),    KC_SPC, TT(_LOWER),                                           KC_ENT,  KC_BSPC, KC_RBRC, KC_RGUI 
    ),

 /* LOWER      
* ,---------------------------------------------.                   ,------------------------------------------------.
* |  ESC |  F1   |  F2   |  F3  |  F4   |  F5   |                   |   F6   |  F7    |  F8    |  F9   | F10  |  DEL | 
* |------+-------+-------+------+-------+-------|                   |--------+--------+--------+-------+------+------|
* |  RST |  F11  |  F12  | DEL  | paste | copy  |                   |  home  | pg up  |  print | redo  | w    |      |
* |------+-------+-------+------+-------+-------|                   |--------+--------+--------+-------+------+------|
* |      |  all  |       | SAV  | undo  | BackSP|-------.   ,-------|  left  | down   |  up    | right |      |      |
* |------+-------+-------+------+-------+-------|  enter|   |       |--------+--------+--------+-------+------+------|
* |  F9  |  F11  |  F10  | F5   | TAB   | cut   |-------|   |-------|  end   | pg dw  |        |       |      |      |
* `---------------------------------------------/       /    \       \-----------------------------------------------'
*                   |      | SPE  |          | /       /      \       \  |      | MENU |      |
*                   |      |      |          |/       /        \       \ |      |      |      |
*                   `--------------------------------'          '-------''--------------------'
*/
    [_LOWER] =  LAYOUT(
    KC_ESC, KC_F1,      KC_F2,  KC_F3,      KC_F4,          KC_F5,                          KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,         KC_DELETE,
    QK_BOOT,  KC_F11,     KC_F12, KC_DELETE,  RCTL(FR_V),     RCTL(FR_C),                     KC_HOME,    KC_PGUP,    KC_PSCR,    RCTL(FR_Y), RCTL(KC_RIGHT), _______,
    _______,RCTL(FR_A), _______,RCTL(FR_S), RCTL(FR_Z),     KC_BSPC,                        KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,   _______,        _______,
    KC_F9,  KC_F11,     KC_F10, KC_F5,      LALT(KC_TAB),   RCTL(FR_X), KC_ENT, _______,    KC_END,     KC_PGDN,    _______,    _______,    _______,        _______,
    _______,TT(_RAISE), _______, _______,                                                   _______,    _______,    KC_APP,     _______),

/* RAISE
* ,-----------------------------------------.                    ,-------------------------------------------.
* |      |      |      |      |      |      |                    |      |     |   /   |   *  |  -  | RGB TOG|
* |------+------+------+------+------+------|                    |------+------+------+------+-----+--------|
* |   `  |   [  |   ]  |      |      |      |                    |   ^  |   7  |   8  |   9  |  +  | RGB HUI|
* |------+------+------+------+------+------|                    |------+------+------+------+-----+--------|
* |      |  @   |  |   |  &   |  €   |  #   |-------.    ,-------|   $  |   4  |   5  |   6  |     |        |
* |------+------+------+------+------+------|       |    |       |------+------+------+------+-----+--------|
* |  F7  |  F8  |  F9  | F10  |  #   | F12  |-------|    |-------|      |   1  |   2  |   3  |     |        |
* `-----------------------------------------/       /     \      \------------------------------------------'
*                   |      |      |      | /       /       \      \  |       |   0  |  .   |
*                   |      |      |      |/       /         \      \ |       |      |      |
*                   `----------------------------'           '------''---------------------'
*/
    [_RAISE] = LAYOUT(
    _______, _______,    _______,    _______,    _______, _______,                   _______,    _______, KC_PSLS, KC_PAST, KC_PMNS, RGB_TOG,
    KC_GRV,  FR_LBRC,    FR_RBRC,    _______,    _______, _______,                   FR_EQL,     KC_KP_7, KC_KP_8, KC_KP_9, KC_PPLS, RGB_HUI, 
    _______, FR_AT,      FR_PIPE,    ALGR(KC_1), FR_EURO, FR_HASH,                   S(FR_EQL),  KC_KP_4, KC_KP_5, KC_KP_6, _______, _______,
    KC_F7,   KC_F8,      KC_F9,      KC_F10,     FR_HASH, KC_F12, _______, _______,  _______,    KC_KP_1, KC_KP_2, KC_KP_3, _______, _______,
    _______, _______,    _______,    _______,                                        _______,    _______, KC_KP_0, KC_KP_DOT)
};
// clang-format on

// sync transport
typedef struct _sync_keycode_t {
    uint16_t keycode;
} sync_keycode_t;

// force rigth side to update
bool b_sync_need_send = false;

// last keycode typed
sync_keycode_t last_keycode;

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    // vertical orientation
    return OLED_ROTATION_270;
}

void render(gui_state_t t) {
    // logo
    render_logo(t);

#if IS_LEFT
    // left side
    render_layer_frame(t);
    render_gears();

    decay_scope();
    render_scope(t);
#endif

#if IS_RIGHT
    // right side
    render_circle(t);
#endif
}

void update(uint16_t keycode) {
#if IS_LEFT
    update_scope();
#endif

#if IS_RIGHT
    update_circle(keycode);
#endif
}

void reset(void) {
#if IS_LEFT
    reset_scope();
#endif

#if IS_RIGHT
    reset_ring();
#endif
}

void set_wackingup_mode_clean(void) {
    oled_clear();
    reset();
}

bool oled_task_user(void) {
    gui_state_t t = get_gui_state();

    // in sleep mode => turn display off
    if (t == _SLEEP) {
        oled_off();
        return false;
    }

    // not in sleep mode => screen is on
    oled_on();

#ifdef WITH_BOOT
    // in booting mode => display booting animation
    if (t == _BOOTING) {
        bool boot_finished = render_boot();
        if (boot_finished) {
            // end of the boot : wacking up
            set_wackingup_mode_clean();
            update_gui_state();
        }
        return false;
    }
#endif

    // in halting mode => display booting animation
    if (t == _HALTING) {
        render_halt();
        return false;
    }

    render(t);
    return false;
}

void process_key(uint16_t keycode) {
    // update screen with the new key
    update(keycode);

    gui_state_t t = get_gui_state();

    if (t == _IDLE) {
        // wake up animation
        reset();
    }

    if (t == _BOOTING || t == _HALTING) {
        // cancel booting or halting : waking_up
        set_wackingup_mode_clean();
    }

    if (t == _SLEEP) {
        // boot sequence
        set_wackingup_mode_clean();
        reset_boot();
    }

    update_gui_state();
}

void user_sync_a_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const sync_keycode_t* m2s = (const sync_keycode_t*)in_data;
    // get the last char typed on left side and update the right side
    process_key(m2s->keycode);
}

void keyboard_post_init_user(void) {
    // callback for tranport sync data
    transaction_register_rpc(USER_SYNC_A, user_sync_a_slave_handler);
}

void housekeeping_task_user(void) {
    // only for master side
    if (!is_keyboard_master()) return;

    // only if a new char was typed
    if (!b_sync_need_send) return;

    // send the char to the slave side : sync is done
    if (transaction_rpc_send(USER_SYNC_A, sizeof(last_keycode), &last_keycode)) {
        b_sync_need_send = false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
        // master : store keycode to sent to the other side to be process_key
        last_keycode.keycode = keycode;
        b_sync_need_send     = true;

        // gui process the input
        process_key(keycode);
    }
    return true;
}

#if IS_LEFT
layer_state_t layer_state_set_user(layer_state_t state) {
    // update the frame with the layer name
    update_layer_frame(state);
    return state;
}
#endif
