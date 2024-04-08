#include QMK_KEYBOARD_H

#include "oneshot.h"
#include "swapper.h"

#define FWD G(KC_RBRC) // possibly remove
#define BACK G(KC_LBRC) // possibly remove

#define TAB_L C(S(KC_TAB))
#define TAB_R C(KC_TAB)

#define DESK_L C(G(KC_LEFT))
#define DESK_R C(G(KC_RGHT))

#define MS_UP KC_MS_UP
#define MS_DOWN KC_MS_DOWN
#define MS_LEFT KC_MS_LEFT
#define MS_RGHT KC_MS_RIGHT
#define MS_WHDN KC_MS_WH_DOWN
#define MS_WHUP KC_MS_WH_UP
#define MS_BTN1 KC_MS_BTN1
#define MS_BTN2 KC_MS_BTN2
#define MS_ACL0 KC_MS_ACCEL0
#define MS_ACL1 KC_MS_ACCEL1
#define MS_ACL2 KC_MS_ACCEL2

#define PLAY KC_MEDIA_PLAY_PAUSE
#define STOP KC_MEDIA_STOP
#define PREV KC_MEDIA_PREV_TRACK
#define NEXT KC_MEDIA_NEXT_TRACK
#define VOL_DN KC_AUDIO_VOL_DOWN
#define VOL_UP KC_AUDIO_VOL_UP
#define MUTE KC_AUDIO_MUTE
#define BRI_DN KC_BRIGHTNESS_DOWN
#define BRI_UP KC_BRIGHTNESS_UP

#define LA_SYM MO(_SYM)
#define LA_NAV MO(_NAV)
#define LA_MOU DF(_MOU)
#define LA_MED DF(_MED)
#define LA_DEF DF(_DEF)

enum layers {
    _DEF,
    _SYM,
    _NAV,
    _NUM,
    _MED,
    _MOU,    
};

enum keycodes {
    // Custom oneshot mod implementation with no timers (oneshot.c)
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_GUI,
    // Custom swapper implementation (swapper.c)
    SW_WIN, // Switch to next window         (alt-tab)
    SW_TAB, // Switch to next tab            (ctrl-tab)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEF] = LAYOUT_split_3x5_3(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                          KC_BSPC, KC_LSFT, LA_NAV,  LA_SYM,  KC_SPC,  KC_ENT
    ),

    [_SYM] = LAYOUT_split_3x5_3(
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,                                           
        KC_TILD, KC_GRV,  KC_QUOT, KC_DQUO, KC_PMNS, KC_PLUS, OS_SHFT, OS_CTRL, OS_ALT,  OS_GUI,
        KC_BSLS, KC_PIPE, LA_MED,  XXXXXXX, KC_UNDS, KC_EQL,  KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC,
                          _______, _______, _______, _______, _______, _______
    ),

    [_NAV] = LAYOUT_split_3x5_3(
        SW_WIN,  SW_TAB,  TAB_L,   TAB_R,   KC_ESC,  KC_ESC,  KC_HOME, KC_END, KC_BSPC, KC_DEL,
        OS_GUI,  OS_ALT,  OS_CTRL, OS_SHFT, KC_ENT,  KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT, KC_ENT,
        DESK_L,  DESK_R,  LA_MOU,  KC_PSCR, KC_TAB,  KC_TAB,  KC_PGDN, KC_PGUP,XXXXXXX, KC_CAPS,
                          _______, _______, _______, _______, _______, _______
    ),

    [_NUM] = LAYOUT_split_3x5_3(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        OS_GUI,  OS_ALT,  OS_CTRL, OS_SHFT, KC_F11,  KC_F12,  OS_SHFT, OS_CTRL, OS_ALT,  OS_G
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
                          _______, _______, _______, _______, _______, _______
    ),

    [_MED] = LAYOUT_split_3x5_3(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        BRI_DN,  BRI_UP,  VOL_DN,  VOL_UP,  MUTE,    PREV,    PLAY,    STOP,    NEXT,    XXXXXXX,
        XXXXXXX, XXXXXXX, KC_SLEP, KC_WAKE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	                      _______, _______, LA_DEF, LA_DEF, _______, _______
    ),

    [_MOU] = LAYOUT_split_3x5_3(
        XXXXXXX, XXXXXXX, MS_UP,   XXXXXXX, KC_ESC,  KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  
	    XXXXXXX, MS_LEFT, MS_DOWN, MS_RGHT, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ENT,     
        XXXXXXX, MS_BTN2, MS_WHUP, MS_WHDN, XXXXXXX, MS_BTN1, MS_ACL0, MS_ACL1, MS_ACL2, XXXXXXX, 
                          _______, _______, LA_DEF,  LA_DEF, _______, _______
    )      
};


bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
    case KC_LSFT:
    case OS_SHFT:    
    case OS_CTRL:
    case OS_ALT:
    case OS_GUI:
        return true;
    default:
        return false;
    }
}

bool sw_win_active = false;
bool sw_tab_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_gui_state = os_up_unqueued;

// called during key processing before the actual key event is handled allowing us to override key behavior
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(
        &sw_win_active, KC_LALT, KC_TAB, SW_WIN, OS_SHFT,
        keycode, record
    );
    update_swapper(
        &sw_tab_active, KC_LCTL, KC_TAB, SW_TAB, OS_SHFT,
        keycode, record
    );

    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_gui_state, KC_LGUI, OS_GUI,
        keycode, record
    );

    return true;
}

// activate the _NUM layer when the _SYM and _NAV layers are active
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYM, _NAV, _NUM);
}
