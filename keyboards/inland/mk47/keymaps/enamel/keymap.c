#include QMK_KEYBOARD_H

#include "oneshot.h"
#include "swapper.h"

#define HOME G(KC_UP)
#define END G(KC_DOWN)
#define BACK G(KC_LBRC)
#define FORWD G(KC_RBRC)
#define TABL G(S(KC_LBRC))
#define TABR G(S(KC_RBRC))
#define DEL_WRD_F A(KC_DEL)
#define DEL_WORD A(KC_BSPC)
#define DEL_LINE G(KC_BSPC)
#define SPOTL G(KC_SPC)
#define LA_SYM OSL(SYM)
#define LA_NAV LT(NAV, KC_SPC)
#define LA_R_NAV LT(NAV_RIGHT, KC_TAB)
#define LA_NAV_REV LT(NAV_REV, KC_PAST)
#define LA_SYM_REV OSL(SYM_REV)
#define LA_MEDIA OSL(MED)
#define LA_NUM MO(NUM)
#define UNDO G(KC_Z)
#define REDO LSFT(G(KC_Z))

enum layers {
    DEF,
    SYM,
    NAV,
    NAV_RIGHT,
    MED,
    NAV_REV,
    SYM_REV,
    NUM,
};

enum custom_keycodes {
    REPEAT = SAFE_RANGE,
    SELWORD,
};

enum tap_dance_indexes {
    TD_SEARCH,
};

enum combo_events {
    // Left Side Press
    COMBO_SHIFT_LEFT,
    COMBO_TAB,
    COMBO_UNDO,
    COMBO_REDO,
    LA_COMBO_NAV_TO_SYM,

    // Right Side Press
    COMBO_SHIFT_RIGHT,
    COMBO_ENTER,
    LA_COMBO_SYM_TO_NAV,
    COMBO_BSPC,
    COMBO_DELETE,
    COMBO_DELETE_LINE,

    // Both Side Press
    COMBO_CAPS_WORD,
    COMBO_SHIFT_DUAL_OSL,

    // Total Combo Count. Always last.
    COMBO_COUNT,
};

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,

    SW_WIN,  // Switch to next window         (cmd-tab)
};

// Left Side
const uint16_t PROGMEM shift_left_combo[] = {KC_A, KC_R, KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_A, KC_R, KC_S, COMBO_END};
const uint16_t PROGMEM undo_combo[] = {KC_X, KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM redo_combo[] = {KC_Z, KC_X, KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM nav_to_sym_combo[] = {KC_TAB, LA_SYM, COMBO_END};

// Right Side
const uint16_t PROGMEM shift_right_combo[] = {KC_N, KC_E, KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM enter_combo[] = {KC_N, KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM sym_to_nav_combo[] = {KC_ASTR, LA_NAV, COMBO_END};
const uint16_t PROGMEM bspc_combo[] = {KC_E, KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM delete_combo[] = {KC_L, KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM delete_line_combo[] = {KC_L, KC_U, KC_Y, KC_QUOT, COMBO_END};

// Both Sides
const uint16_t PROGMEM caps_word_combo[] = {KC_T, KC_N, COMBO_END};
const uint16_t PROGMEM shift_dual_osl_combo[] = {KC_S, KC_E, COMBO_END};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*  DEFAULT LAYER
 * ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
 * |       |       |       |       |       |       |       |       |       |       |       |       |
 * |   Q   |   W   |   F   |   P   |   B   |       |       |   J   |   L   |   U   |   Y   |   ?   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       |       |       |       |       |       |
 * |   A   |   R   |   S   |   T   |   G   |       |       |   M   |   N   |   E   |   I   |   O   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       |       |       |   <   |   >   |   ?   |
 * |   Z   |   X   |   C   |   D   |   V   |       |       |   K   |   H   |   ,   |   .   |   /   |
 * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |               |       |       |       |       |       |
 * |       |       |  REP  |  NAV  | SHFT  |     SOTLT     |NAV-TAB|  SYM  | MEDIA |       |SEARCH |
 * `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------'
*/

[DEF] = LAYOUT(
    KC_Q,      KC_W,      KC_F,     KC_P,    KC_B,    XXXXXXX, XXXXXXX,  KC_J,      KC_L,    KC_U,      KC_Y,       KC_QUES,
    KC_A,      KC_R,      KC_S,     KC_T,    KC_G,    XXXXXXX, XXXXXXX,  KC_M,      KC_N,    KC_E,      KC_I,       KC_O,
    KC_Z,      KC_X,      KC_C,     KC_D,    KC_V,    XXXXXXX, XXXXXXX,  KC_K,      KC_H,    KC_SLSH,   KC_COMM,    KC_DOT,
    KC_MCTL,   XXXXXXX,  QK_REP,   LA_NAV,  OS_SHFT,       SPOTL,       LA_R_NAV,  LA_SYM,  LA_MEDIA,  XXXXXXX,  TD(TD_SEARCH)
),

/*  SYMBOLS LAYER
* ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
* |       |       |       |       |       |       |       |       |       |       |       |       |
* |   \   |   [   |   (   |   {   |  ESC  |       |       |   ^   |   }   |   )   |   ]   |   "   |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |       |       |       |       |
* |   !   |   '   |   :   |   _   |   ~   |       |       |   #   |  CMD  |  ALT  |  CTRL |  SHFT |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |       |       |       |       |
* |   $   |   &   |   +   |   -   |   %   |       |       |   |   |   @   |   ;   |   =   |   *   |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |  HOLD |       |       |       |
* |       |       |  REP  |  NAV  |  SHFT |     SPOTL     |NAV-TAB|  SYM  | MEDIA |       |       |
* `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------'
*/

[SYM] = LAYOUT(
    KC_BSLS,  KC_LBRC,  KC_LPRN,  KC_LCBR,   KC_ESC,   XXXXXXX, XXXXXXX,  KC_CIRC,  KC_RCBR,  KC_RPRN,  KC_RBRC,   KC_DQT,
    KC_EXLM,  KC_QUOT,  KC_COLN,  KC_UNDS,   KC_TILD,  XXXXXXX, XXXXXXX,  KC_HASH,  OS_CMD,   OS_ALT,   OS_CTRL,   OS_SHFT,
    KC_DLR,   KC_AMPR,  KC_PLUS,  KC_MINS,   KC_PERC,  XXXXXXX, XXXXXXX,  KC_PIPE,  KC_AT,    KC_SCLN,  KC_EQL,    LA_NAV_REV,
    XXXXXXX,  XXXXXXX,  _______,  _______,   KC_BSPC,        SPOTL,       _______,  _______,  _______,  XXXXXXX,   XXXXXXX
),
/*  NAVIGATION LAYER
* ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
* |       |       |       |       |       |       |       |       |       |       |       |       |
* |  ESC  | SW WIN| TABL  | TABR  |       |       | BOOT  |       |  HOME |   UP  |  END  |  DELW |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |       |       |       |       |
* | SHIFT |  CTRL |  ALT  |  CMD  |       |       |       | BACK  | LEFT  | DOWN  | RIGHT |  BSPC |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |       |       |       |       |
* |       |       |       |  TAB  |       |       |       | FORWD | PG UP | PG DN |  SPC  |  ENT  |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       | HOLD  |       |       |       |OR HOLD|       |       |       |       |
* |       |       |  REP  |  NAV  | SHFT  |     SPOTL     |NAV-TAB|  SYM  | MEDIA |       |       |
* `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------'
*/

[NAV] = LAYOUT(
    KC_ESC,    SW_WIN,   TABL,     TABR,     XXXXXXX,  XXXXXXX, QK_BOOT,  XXXXXXX,  HOME,     KC_UP,     END,       DEL_WORD,
    OS_SHFT,   OS_CTRL,  OS_ALT,   OS_CMD,   XXXXXXX,  XXXXXXX, XXXXXXX,  BACK,     KC_LEFT,  KC_DOWN,   KC_RGHT,   KC_BSPC,
    LA_SYM_REV,    XXXXXXX,  XXXXXXX,  KC_TAB,   XXXXXXX,  XXXXXXX, XXXXXXX,  FORWD,    KC_PGUP,  KC_PGDN,   KC_SPC,    KC_ENT,
    XXXXXXX,   XXXXXXX,  _______,  _______,  _______,        SPOTL,       KC_SPC,   _______,  _______,   XXXXXXX,   XXXXXXX
),

/*  NAVIGATION RIGHT LAYER
* ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
* |       |       |       |       |       |       |       |       |       |       |       |       |
* |  ESC  | SW WIN| TABL  | TABR  |       |       | BOOT  |       |  HOME |   UP  |  END  |  DELW |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |       |       |       |       |
* | SHIFT |  CTRL |  ALT  |  CMD  |       |       |       | BACK  | LEFT  | DOWN  | RIGHT |  BSPC |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |       |       |       |       |
* |       |       |       |  TAB  |       |       |       | FORWD | PG UP | PG DN |  SPC  |  ENT  |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       | HOLD  |       |       |       |OR HOLD|       |       |       |       |
* |       |       |  REP  |  NAV  | SHFT  |     SPOTL     |NAV-TAB|  SYM  | MEDIA |       |       |
* `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------'
*/

[NAV_RIGHT] = LAYOUT(
    KC_ESC,      SW_WIN,   TABL,     TABR,     XXXXXXX,  XXXXXXX, QK_BOOT,  XXXXXXX,  HOME,     KC_UP,     END,       DEL_WORD,
    OS_SHFT,     OS_CTRL,  OS_ALT,   OS_CMD,   XXXXXXX,  XXXXXXX, XXXXXXX,  BACK,     KC_LEFT,  KC_DOWN,   KC_RGHT,   KC_BSPC,
    LA_SYM_REV,  XXXXXXX,  XXXXXXX,  KC_TAB,   XXXXXXX,  XXXXXXX, XXXXXXX,  FORWD,    KC_PGUP,  KC_PGDN,   KC_SPC,    KC_ENT,
    XXXXXXX,     XXXXXXX,  _______,  _______,  _______,        SPOTL,       _______,  _______,  _______,   XXXXXXX,   XXXXXXX
),

/*  MEDIA LAYER
* ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
* |       |       |       |       |       |       |       |       |       |       |       |       |
* | Hue-  | Hue+  | Efct- | Efct+ |       |       |       |       | Vol-  |       | Vol-  |       |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |       |       |       |       |
* | RGBM- | RGBM+ | Lum-  | Lum+  |       |       |       | Slow  |  <--  | Play  |  -->  | Fast  |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |       |       |       |       |
* | Sat-  | Sat+  |       | RGB~  |       |       |       |       | Prev  |       | Next  | Mute  |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |       | HOLD  |       |       |
* |       |       |  REP  |  NAV  | SHFT  |     SPOTL     |NAV-TAB|  SYM  | MEDIA |       |       |
* `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------'
*/

[MED] = LAYOUT(
    RGB_HUD,   RGB_HUI,   RGB_SPD,   RGB_SPI,   XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX,     KC_VOLD,  XXXXXXX,  KC_VOLU,  XXXXXXX,
    RGB_RMOD,  RGB_MOD,   RGB_VAD,   RGB_VAI,   XXXXXXX,  XXXXXXX, XXXXXXX,  LSFT(KC_LT), KC_LEFT,  KC_MPLY,  KC_RGHT,  LSFT(KC_GT),
    RGB_SAD,   RGB_SAI,   XXXXXXX,   RGB_TOG,   XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX,     KC_MPRV,  XXXXXXX,  KC_MNXT,  KC_MUTE,
    XXXXXXX,   XXXXXXX,   _______,   _______,   _______,        SPOTL,       _______,     _______,  _______,  XXXXXXX,  XXXXXXX
),

/*  NAVIGATION REVERSE LAYER
* ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
* |       |       |       |       |       |       |       |       |       |       |       |       |
* |  DELW |  END  |   UP  | HOME  |       |       | BOOT  |       |  SWIN |  ESC  | TABR  | TABL  |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |       |       |       |       |
* |  BSPC | RIGHT | DOWN  | LEFT  |       |       | BACK  |       |  CMD  |  ALT  | CTRL  | SHFT  |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |       |       |       |       |
* |  ENT  |  SPC  | PGDN  | PGUP  |       |       | FORWD |       |  TAB  |       |       |       |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       | HOLD  |       |       |       |OR HOLD|       |       |       |       |
* |       |       |  REP  |  NAV  | SHFT  |     SPOTL     |NAV-TAB|  SYM  | MEDIA |       |       |
* `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------'
*/

[NAV_REV] = LAYOUT(
    DEL_WORD,  END,       KC_UP,     HOME,     XXXXXXX,  XXXXXXX, QK_BOOT,  XXXXXXX,  SW_WIN,   KC_ESC,    TABR,     TABL,
    KC_BSPC,   KC_RGHT,   KC_DOWN,   KC_LEFT,  XXXXXXX,  XXXXXXX, BACK,     XXXXXXX,  OS_CMD,   OS_ALT,    OS_CTRL,   OS_SHFT,
    KC_ENT,    KC_SPC,    KC_PGDN,   KC_PGUP,  XXXXXXX,  XXXXXXX, FORWD,    XXXXXXX,  KC_TAB,   XXXXXXX,   XXXXXXX,   XXXXXXX,
    XXXXXXX,   XXXXXXX,   _______,   _______,  _______,        SPOTL,       _______,  _______,  _______,   XXXXXXX,   XXXXXXX
),

/*  SYMBOLS REVERSE LAYER
* ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
* |       |       |       |       |       |       |       |       |       |       |       |       |
* |   "   |   ]   |   )   |   }   |   ^   |       |       |  ESC  |   {   |   (   |   [   |   \   |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |       |       |       |       |
* |       |       | FLDel | FDel  |   #   |       |       |   ~   |   _   |   :   |   '   |   !   |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |       |       |       |       |
* |   *   |   =   |   ;   |   @   |   |   |       |       |   %   |   -   |   +   |   &   |   $   |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |  HOLD |       |       |       |
* |       |       |  REP  |  NAV  |  SHFT |     SPOTL     |NAV-TAB|  SYM  | MEDIA |       |       |
* `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------'
*/

[SYM_REV] = LAYOUT(
    KC_DQT,   KC_RBRC,  KC_RPRN,   KC_RCBR,  KC_CIRC,  XXXXXXX, XXXXXXX,  KC_ESC,   KC_LCBR,  KC_LPRN,  KC_LBRC,  KC_BSLS,
    XXXXXXX,  XXXXXXX,  DEL_WRD_F, KC_DEL,   KC_HASH,  XXXXXXX, XXXXXXX,  KC_TILD,  KC_UNDS,  KC_COLN,  KC_QUOT,  KC_EXLM,
    XXXXXXX,  KC_EQL,   KC_SCLN,   KC_AT,    KC_PIPE,  XXXXXXX, XXXXXXX,  KC_PERC,  KC_MINS,  KC_PLUS,  KC_AMPR,  KC_DLR,
    XXXXXXX,  XXXXXXX,  _______,   _______,  _______,        SPOTL,       _______,  _______,  _______,  XXXXXXX,  XXXXXXX
),

/*  NUM LAYER
* ,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
* |       |       |       |       |       |       |       |       |       |       |       |       |
* |  FN6  |  FN7  |  FN8  |  FN9  | FN10  |       |       |   ,   |   7   |   8   |   9   |   $   |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |       |       |       |       |
* |  FN1  |  FN2  |  FN3  |  FN4  |  FN5  |       |       |   0   |   4   |   5   |   6   |  BSPC |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       |       |       |       |       |       |       |       |       |       |
* |  TAB  |       | SHIFT |  SPC  |       |       |       |   .   |   1   |   2   |   3   |  ENT  |
* |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
* |       |       |       | HOLD  |       |       |       | HOLD  |       |       |       |       |
* |       |       |  REP  |  NAV  | SHFT  |     SPOTL     |NAV-TAB|   0   | MEDIA |       |       |
* `-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------'
*/

[NUM] = LAYOUT(
    KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,   XXXXXXX, XXXXXXX,  KC_COMM,   KC_7,   KC_8,      KC_9,     KC_DLR,
    KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,    XXXXXXX, XXXXXXX,  KC_0,      KC_4,   KC_5,      KC_6,     KC_BSPC,
    KC_TAB,    XXXXXXX,   KC_LSFT,   KC_SPC,    XXXXXXX,  XXXXXXX, XXXXXXX,  KC_DOT,    KC_1,   KC_2,      KC_3,     KC_ENT,
    XXXXXXX,   XXXXXXX,   _______,   _______,   _______,       SW_WIN,       _______,   KC_0,   _______,   XXXXXXX,  XXXXXXX
),
};

    // Tap Dance Definitions
    void tap_dance_search(tap_dance_state_t *state, void *user_data) {
            if (state->count == 1) {
                    // Open new tab an start search with "reddit"
                    SEND_STRING(SS_LCTL("t"));
                    SEND_STRING("reddit ");
            } else if (state->count == 2) {
                    // Send the URL for Gmail and press Enter
                    SEND_STRING(SS_LCTL("t"));
                    SEND_STRING("https://mail.google.com\n");
            } else if (state->count == 3) {
                    // add archive string to cursor location for free articles
                    SEND_STRING("archive.is/");
            }
    }

    tap_dance_action_t tap_dance_actions[] = {
            [TD_SEARCH] = ACTION_TAP_DANCE_FN(tap_dance_search),
    };

    // Callum One-Shot Modifiers
    bool is_oneshot_cancel_key(uint16_t keycode) {
            switch (keycode) {
            // Cancel unused modifiers by tapping nav or sym.
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
            case OS_CMD:
                    return true;
            default:
                    return false;
            }
    }

    oneshot_state os_shft_state = os_up_unqueued;
    oneshot_state os_ctrl_state = os_up_unqueued;
    oneshot_state os_alt_state = os_up_unqueued;
    oneshot_state os_cmd_state = os_up_unqueued;

    bool sw_win_active = false;

    bool process_oneshot(uint16_t keycode, keyrecord_t *record) {
        update_oneshot(&os_shft_state, KC_LSFT, OS_SHFT, keycode, record);
        update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTRL, keycode, record);
        update_oneshot(&os_alt_state, KC_LALT, OS_ALT, keycode, record);
        update_oneshot(&os_cmd_state, KC_LCMD, OS_CMD, keycode, record);
        return true;
    }

    bool process_update_sw_win(uint16_t keycode, keyrecord_t *record) {
        update_swapper(&sw_win_active, KC_LGUI, KC_TAB, SW_WIN, keycode, record);
        return true;
    }

    bool process_record_user(uint16_t keycode, keyrecord_t *record) {
        if (!process_oneshot(keycode, record)) return false;
        if (!process_update_sw_win(keycode, record)) return false;

        // switch (keycode) {
        //     case LA_NAV:
        //     if (record->event.pressed) {
        //         layer_on(NAV);
        //         update_tri_layer(NAV, SYM_REV, NUM);
        //     } else {
        //         layer_off(NAV);
        //         update_tri_layer(NAV, SYM_REV, NUM);
        //     }
        //     return false;
        //     // case SYM:
        //     // if (record->event.pressed) {
        //     //     layer_on(SYM);
        //     //     update_tri_layer(SYM, NAV, NUM);
        //     // } else {
        //     //     layer_off(SYM);
        //     //     update_tri_layer(SYM, NAV, NUM);
        //     // }
        //     // return false;
        //     }

        return true;
    }

    // OS Detection
    os_variant_t detected_host_os_kb(void) {
        os_variant_t detected_os = detected_host_os();
        if (!process_detected_host_os_user(detected_os)) {
            return OS_UNSURE;
        }
        switch (detected_os) {
            case OS_MACOS:
                return OS_MACOS;
                break;
            case OS_IOS:
                return OS_IOS;
                break;
            case OS_WINDOWS:
                return OS_WINDOWS;
                break;
            case OS_LINUX:
                return OS_LINUX;
                break;
            case OS_UNSURE:
                return OS_UNSURE;
                break;
        }

        return detected_os;
    }

    bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
        if (rgb_matrix_indicators_advanced_user(led_min, led_max) != true) {
            return false;
        }

        // switch (detected_host_os_kb()) {
        //     case OS_MACOS:
        //         rgb_matrix_set_color_all(RGB_WHITE);
        //         break;
        //     case OS_IOS:
        //         rgb_matrix_set_color_all(RGB_WHITE);
        //         break;
        //     case OS_WINDOWS:
        //         rgb_matrix_set_color_all(RGB_BLUE);
        //         break;
        //     case OS_LINUX:
        //         rgb_matrix_set_color_all(RGB_GREEN);
        //         break;
        //     case OS_UNSURE:
        //         rgb_matrix_set_color_all(RGB_RED);
        //         break;
        // }

        return true;
    }

    void process_combo_event(uint16_t combo_index, bool pressed) {

        switch(combo_index) {
            case COMBO_SHIFT_LEFT:
                if (pressed) {
                    layer_on(1);
                } else {
                    layer_off(1);
                }
                break;
        }

        switch(combo_index) {
            case LA_COMBO_NAV_TO_SYM:
                if (pressed) {
                    layer_on(3);
                } else {
                    layer_off(3);
                }
                break;
        }

        switch(combo_index) {
            case LA_COMBO_SYM_TO_NAV:
                if (pressed) {
                    layer_on(3);
                } else {
                    layer_off(3);
                }
                break;
        }

        switch(combo_index) {
            case COMBO_ENTER:
                if (pressed) {
                    layer_on(3);
                } else {
                    layer_off(3);
                }
                break;
        }
    }

    layer_state_t layer_state_set_user(layer_state_t state) {

        // Just prioritizes the reverse layers over the normal layers when pinky thumb combo is active. Not sure if both are needed.
        return update_tri_layer_state(state, SYM_REV, NAV, NUM);
        // return update_tri_layer_state(state, NAV, SYM_REV, NUM);


        // // Maintains the numpad layer while holding pinky thumb combo. You have to release the thumb and maintain the pinky to switch to the reverse layers.
        // // Also, the order of the next two lines is affecting which thumb pinky combo can be used to access the numpad layer. both sides do not need to do this though
        // // as the numpad is preferred on the right side for now.
        // // this is stopping from letting the numpad work on dual thumb press
        // // Maybe I can use the same logic as the reverse layers to prioritize the numpad layer over the reverse layers
        // return update_tri_layer_state(state, SYM, NAV_REV, NUM_TWO);

        // return update_tri_layer_state(state, NAV, SYM_REV, NUM);
        // // return update_tri_layer_state(state, SYM, NAV_RIGHT, NUM);

        // switch (get_highest) {

        // }

    }

    combo_t key_combos[COMBO_COUNT] = {
        // Left Side
        [COMBO_SHIFT_LEFT] = COMBO(shift_left_combo, OS_SHFT),
        [COMBO_TAB] = COMBO(tab_combo, KC_TAB),
        [COMBO_UNDO] = COMBO(undo_combo, UNDO),
        [COMBO_REDO] = COMBO(redo_combo, REDO),
        [LA_COMBO_NAV_TO_SYM] = COMBO(nav_to_sym_combo, LA_NAV),

        // Right Side
        [COMBO_SHIFT_RIGHT] = COMBO(shift_right_combo, OS_SHFT),
        [COMBO_ENTER] = COMBO(enter_combo, KC_ENT),
        [LA_COMBO_SYM_TO_NAV] = COMBO(sym_to_nav_combo, LA_SYM),
        [COMBO_BSPC] = COMBO(bspc_combo, KC_BSPC),
        [COMBO_DELETE] = COMBO(delete_combo, DEL_WORD),
        [COMBO_DELETE_LINE] = COMBO(delete_line_combo, DEL_LINE),

        // Both Sides
        [COMBO_CAPS_WORD] = COMBO(caps_word_combo, CW_TOGG),
        [COMBO_SHIFT_DUAL_OSL] = COMBO(shift_dual_osl_combo, OS_SHFT),
    };
