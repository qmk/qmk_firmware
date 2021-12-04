
// mon clavier en dvorak
#include QMK_KEYBOARD_H
#include "keymap_french.h"

#include "gui_state.h"
#include "boot.h"

#include "layer_frame.h"
#include "burst.h"
#include "fast_random.h"

#include "ring.h"

#include "navi_logo.h"

#include "transactions.h"
#include "rgblight.h"



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* QWERTY
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  DEL |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  ^   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |RShift|
     * |------+------+------+------+------+------|  "     |    |  )  |------+------+------+------+------+------|
     * |LCTRL |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |  $   |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *                   | LAlt |  rai  | Space | LOWER /  /       \Enter \ | BackSP | ]  | RGUI |
     *                   |      |      |      |/       /         \      \ |      |      |      |
     *                   `----------------------------'           '------''--------------------'
     */

    //[_QWERTY] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DELETE, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, FR_CIRC, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_RSFT, KC_LCTRL, KC_Z, KC_X, KC_C, KC_V, KC_B, S(KC_Z), FR_RPRN, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_QUOT, KC_LALT, TT(_RAISE), KC_SPC, TT(_LOWER), KC_ENT, KC_BSPC, KC_RBRC, KC_RGUI),

    [_QWERTY] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DELETE, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, FR_CIRC, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_RSFT, KC_LCTRL, KC_Z, KC_X, KC_C, KC_V, KC_B, S(KC_Z), FR_RPRN, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_QUOT, KC_LALT, TT(_RAISE), KC_SPC, TT(_LOWER), KC_ENT, KC_BSPC, KC_RBRC, KC_RGUI),

    /* LOWER      ESC
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |  ESC |  F1   |  F2  |  F3  |  F4   |  F5  |                        F6   |  F7    |  F8  |  F9  |  F10  |  DEL    |      |               w
     * |------+------+------+------+--------+------|                    |------+------+------+------+------+------|
     * |  F10 |  F11  |  F12  | DEL | paste | copy |                    |  finde  |  F8  |  print  | redo  | w  | home  |
     * |------+------+------+------+--------+------|                    |------+------+------+------+------+------|
     * |      |  all  |   @   | SAV | undo  |BackSP  |-------.    ,-------|   left  |   down  |   up  |   right  |   )  |   end  |
     * |------+------+------+------+--------+--------|   [   enter    |    ]  |------+------+------+------+------+------|
     * |      |  F11  |  F10  |  F5 |  TAB   |  cut   |-------|    |-------|  b    |   _  |   +  |   {  |   }  |   |  |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *                   | LAlt | LGUI |LOWER | /       /       \Enter \  |RAISE | MENU | RGUI |
     *                   |      |      |      |/       /         \      \ |      |      |      |
     *                   `----------------------------'           '------''--------------------'
     */
    [_LOWER] = LAYOUT(KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_DELETE, RESET, KC_F11, KC_F12,

                      KC_DELETE, RCTL(FR_V), RCTL(FR_C), RCTL(FR_F), KC_F8, KC_PSCR, RCTL(FR_Y), RCTL(KC_RIGHT), KC_HOME, _______, RCTL(FR_A), KC_AT, RCTL(FR_S), RCTL(FR_Z), KC_BSPC, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_RPRN, KC_END, _______, KC_F11, KC_F10, KC_F5, LALT(KC_TAB), RCTL(FR_X), KC_ENT, _______, RCTL(KC_LEFT), KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, _______, TT(_RAISE), _______, _______, _______, _______, KC_APP, _______),
    /* RAISE
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |      |      |      |      |      |                    |      |     |   /   | etoile |   - | rgb toggle
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |   `  |   1  |   2  |   3  |   [  |   ]  |                    |   ^  |   7  |   8  |   9  |   plus  |  rgb mod    |
     * |------+------+------+------+------+------|                    |------+------+------+-------+------+------|
     * |      |  @   |  |   |  &   |  €   |  #  |-------.    ,-------|   $   |   4  |   5  |   6  |Right |  rgb hui    |
     * |------+------+------+------+------+------|       |    |    ]  |------+------+------+------+------+------|
     * |  F7  |  F8  |  F9  | F10  |  #   | F12  |-------|    |-------|   +  |   1  |   2  |   3  |   ]  |    rgb hui breathe  |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |   0  |  .    |
     *                   |      |      |      |/       /         \      \ |      |      |      |
     *                   `----------------------------'           '------''--------------------'
     */

    [_RAISE] = LAYOUT(_______, _______, _______, _______, _______, _______, _______, _______, KC_PSLS, KC_PAST, KC_PMNS, RGB_TOG, KC_GRV, KC_1, KC_2, KC_3, FR_LBRC, FR_RBRC, FR_EQL, KC_KP_7, KC_KP_8, KC_KP_9, KC_PPLS, RGB_MOD, _______, FR_AT, FR_PIPE, ALGR(KC_1), FR_EURO, FR_HASH, S(FR_EQL), KC_KP_4, KC_KP_5, KC_KP_6, KC_RGHT, RGB_HUI, KC_F7, KC_F8, KC_F9, KC_F10, FR_HASH, KC_F12, _______, _______, KC_PLUS, KC_KP_1, KC_KP_2, KC_KP_3, KC_RBRC, RGB_MODE_BREATHE, _______, _______, _______, _______, _______, _______, KC_KP_0, KC_KP_DOT)};


// sync transport
typedef struct _sync_keycode_t {
    uint16_t keycode;
    bool     need_blink;
} sync_keycode_t;

sync_keycode_t last_keycode;
bool           b_sync_need_send = false;

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void render(gui_state_t t) {
    // logo
    render_logo(t);

// left side
#    if IS_LEFT
    render_layer_frame(t);
    render_gears();

    decay_scope();
    render_scope(t);
#    endif

// right side
#    if IS_RIGHT
    render_circle(t);
#    endif
}

void update(uint16_t keycode) {
#    if IS_LEFT
    update_scope(keycode);
#    endif

#    if IS_RIGHT
    update_circle(keycode);
#    endif
}


void reset(void) {
#    if IS_LEFT
    reset_scope();
#    endif

#    if IS_RIGHT
    reset_ring();
#    endif
}

#    define ANIM_BLINK_FRAME_DURATION 100
uint32_t anim_blink_timer = 0;

void blink_underglow(void) {
    int led_index = (fastrand() % 12);
    sethsv(HSV_WHITE, (LED_TYPE*)&led[led_index]);  // led 0
    // sethsv(HSV_RED,   (LED_TYPE *)&led[1]); // led 1
    // sethsv(HSV_GREEN, (LED_TYPE *)&led[2]); // led 2
    rgblight_set();
    anim_blink_timer = timer_read32();
}

void oled_task_user(void) {
    gui_state_t t = get_gui_state();

    // in sleep mode => turn display off
    if (t == _SLEEP) {
        oled_off();
        return;
    }

    oled_on();

    // in booting mode => display booting animation
    if (t == _BOOTING) {
        render_boot();
        return;
    }

    // in halting mode => display booting animation
    if (t == _HALTING) {
        render_halt();
        return;
    }

    render(t);

    if (timer_elapsed32(anim_blink_timer) > ANIM_BLINK_FRAME_DURATION) {
        rgblight_reload_from_eeprom();
    }
}



void process_key(uint16_t keycode, bool need_blink) {
    // update screen with the new key
    update(keycode);

    if (need_blink) {
        blink_underglow();
    }

    gui_state_t t = get_gui_state();

    if (t == _IDLE) {
        // wake up animation
        reset();
    }

    if (t == _BOOTING) {
        // cancel booting
        oled_clear();
        reset();
    }

    if (t == _HALTING) {
        // cancel halting : waking_up
        oled_clear();
        reset();
    }

    if (t == _SLEEP) {
        // boot sequence
        reset();
        reset_boot();
        oled_clear();
    }

    update_gui_state();
}

void user_sync_a_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const sync_keycode_t* m2s = (const sync_keycode_t*)in_data;
    process_key(m2s->keycode, m2s->need_blink);
}

void keyboard_post_init_user(void) { transaction_register_rpc(USER_SYNC_A, user_sync_a_slave_handler); }

void housekeeping_task_user(void) {
    if (!is_keyboard_master()) return;
    if (!b_sync_need_send) return;

    if (transaction_rpc_send(USER_SYNC_A, sizeof(last_keycode), &last_keycode)) {
        b_sync_need_send = false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
        // no action if slave
        // if (!is_keyboard_master()) {
        //     return true;
        // }

        // blink on correct side
        bool input_from_master_side = record->event.key.row < 5;
        bool need_blink_slave       = !input_from_master_side;

        // master : store keycode to sent to the other side to be process_key
        last_keycode.keycode    = keycode;
        last_keycode.need_blink = need_blink_slave;
        b_sync_need_send        = true;

        // gui process the input
        process_key(keycode, !need_blink_slave);
    }
    return true;
}

#if IS_LEFT
layer_state_t layer_state_set_user(layer_state_t state) {
    update_layer_frame(state);
    return state;
}
#endif
