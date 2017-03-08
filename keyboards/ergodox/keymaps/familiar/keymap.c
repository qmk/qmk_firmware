#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default layer
#define ARRW 1 // function, media, arrow keys
#define NUMP 2 // numpad
#define INTL 3 // international symbols

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Tap Dance Codes
enum {
    SLASH,
    WHACK,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
/* layer 0 : default
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | `      |   1  |   2  |   3  |   4  |   5  |   6  |           |  7   |   8  |   9  |   0  |   -  |   =  | BCKSPC |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | TAB    |   Q  |   W  |   E  |   R  |   T  | HOME |           | PGUP |   Y  |   U  |   I  |   O  |   P  | DELETE |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | NOOP   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |  ENTER |
 * |--------+------+------+------+------+------|  END |           | PGDN |------+------+------+------+------+--------|
 * | (/LSFT |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |  UP  | )/RSFT |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 * | LCTRL  | LGUI | MENU |   '  | NOOP |                                       |   [  |   ]  | LEFT | DOWN |  RIGHT |
 * `------------------------------------'                                       `------------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |PRTSCR| ESC  |       | VOL- | VOL+ |
 *                                 ,------|------|------|       |------+------+------.
 *                                 | ALT/ |SLASH/| NUMLK|       | MUTE |WHACK/| ALT/ |
 *                                 | SPC  |MO(1)/|------|       |------|MO(1)/| SPC  |
 *                                 |      |TG(1) | LAY3 |       | LAY2 |TG(1) |      |
 *                                 `--------------------'       `--------------------'
 */
[BASE] = KEYMAP(
        // left hand
        KC_GRV,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,
        KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_HOME,
        XXXXXXX,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,
        KC_LSPO,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_END,
        KC_LCTL,    KC_LGUI,    KC_MENU,    KC_QUOT,    XXXXXXX,
                                                                    KC_INS,     KC_ESC,
                                                                                KC_NLCK,
                                                    ALT_T(KC_SPC),  TD(SLASH),  TG(INTL),
        // right hand
            KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,    KC_EQL,     KC_BSPC,
            KC_PGUP,    KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_DEL,
                        KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_ENTER,
            KC_PGDN,    KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_UP,      KC_RSPC,
                                    KC_LBRC,    KC_RBRC,    KC_LEFT,    KC_DOWN,    KC_RGHT,
            KC_VOLD,    KC_VOLU,
            KC_MUTE,
            TG(NUMP),   TD(WHACK),   ALT_T(KC_SPC)
    ),

/* layer 1 : functions and arrows
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  | F10  | F11  | F12  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |  UP  |      |      |      |           |      |      |      |      |      |      | INSERT |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      | LEFT | DOWN |RIGHT |      |------|           |------| LEFT | DOWN |  UP  | RIGHT|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |M_PREV|M_STOP|M_PLPS|M_NEXT|      |      |           |      |      |      |      |      | PGUP |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 * |        |      |      |      |      |                                       |      |      | HOME | PGDN |    END |
 * `------------------------------------'                                       `------------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |SYSREQ| PAUSE|       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | SCRLK|       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[ARRW] = KEYMAP(
        // left hand
        _______,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,
        _______,    _______,    _______,    KC_UP,      _______,    _______,    _______,
        _______,    _______,    KC_LEFT,    KC_DOWN,    KC_RGHT,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,
                                                                    KC_SYSREQ,  KC_PAUSE,
                                                                                KC_SLCK,
                                                    _______,        _______,    _______,
        // right hand
            KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     _______,
            _______,    _______,    _______,    _______,    _______,    _______,    KC_INS,
                        KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    _______,    _______,
            _______,    _______,    _______,    _______,    _______,    KC_PGUP,    _______,
                                    _______,    _______,    KC_HOME,    KC_PGDN,    KC_END,
            _______,    _______,
            _______,
            _______,    _______,    _______
    ),

/* layer 2 : numberpad
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 * |        |      |      |      |      |                                       |      |      |      |      |        |
 * `------------------------------------'                                       `------------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[NUMP] = KEYMAP(
        // left hand
        _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,
                                            _______,    _______,
                                                        _______,
                            _______,        _______,    _______,
        // right hand
            _______,    _______,    _______,    _______,    _______,    _______,    _______,
            _______,    _______,    _______,    _______,    _______,    _______,    _______,
                        _______,    _______,    _______,    _______,    _______,    _______,
            _______,    _______,    _______,    _______,    _______,    _______,    _______,
                                    _______,    _______,    _______,    _______,    _______,
            _______,    _______,
            _______,
            _______,    _______,    _______
    ),

/* layer 3: International symbols, etc
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 * |        |      |      |      |      |                                       |      |      |      |      |        |
 * `------------------------------------'                                       `------------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[INTL] = KEYMAP(
        // left hand
        _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,
                                            _______,    _______,
                                                        _______,
                            _______,        _______,    _______,
        // right hand
            _______,    _______,    _______,    _______,    _______,    _______,     _______,
            _______,    _______,    _______,    _______,    _______,    _______,    _______,
                        _______,    _______,    _______,    _______,    _______,    _______,
            _______,    _______,    _______,    _______,    _______,    _______,    _______,
                                    _______,    _______,    _______,    _______,    _______,
            _______,    _______,
            _______,
            _______,    _______,    _______
    ),
};

// See https://github.com/algernon/ergodox-layout/blob/master/keymap.c
// When holding the SLASH or WHACK key, the ARRW layer activates while the key is held.
// Tapping the key produces the / or \ key. Double-tapping it toggles the ARRW layer
// on until a third tap.

typedef struct {
    bool layer_toggle;
    bool sticky;
} td_ta_state_t;

static void slash_finished (qk_tap_dance_state_t *state, void *user_data) {
    td_ta_state_t *td_ta = (td_ta_state_t *) user_data;

    if (td_ta->sticky) {
        td_ta->sticky = false;
        td_ta->layer_toggle = false;
        layer_off (ARRW);
        return;
    }

    if (state->count == 1 && !state->pressed) {
        register_code (KC_SLSH);
        td_ta->sticky = false;
        td_ta->layer_toggle = false;
    } else {
        td_ta->layer_toggle = true;
        layer_on (ARRW);
        td_ta->sticky = (state->count == 2);
    }
}

static void slash_reset (qk_tap_dance_state_t *state, void *user_data) {
    td_ta_state_t *td_ta = (td_ta_state_t *) user_data;

    if (!td_ta->layer_toggle)
        unregister_code (KC_SLSH);
    if (!td_ta->sticky)
        layer_off (ARRW);
}

static void whack_finished (qk_tap_dance_state_t *state, void *user_data) {
    td_ta_state_t *td_ta = (td_ta_state_t *) user_data;

    if (td_ta->sticky) {
        td_ta->sticky = false;
        td_ta->layer_toggle = false;
        layer_off (ARRW);
        return;
    }

    if (state->count == 1 && !state->pressed) {
        register_code (KC_BSLS);
        td_ta->sticky = false;
        td_ta->layer_toggle = false;
    } else {
        td_ta->layer_toggle = true;
        layer_on (ARRW);
        td_ta->sticky = (state->count == 2);
    }
}

static void whack_reset (qk_tap_dance_state_t *state, void *user_data) {
    td_ta_state_t *td_ta = (td_ta_state_t *) user_data;

    if (!td_ta->layer_toggle)
        unregister_code (KC_BSLS);
    if (!td_ta->sticky)
        layer_off (ARRW);
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [SLASH] = {
        .fn = { NULL, slash_finished, slash_reset },
        .user_data = (void *)&((td_ta_state_t) { false, false })
    },
    [WHACK] = {
        .fn = { NULL, whack_finished, whack_reset },
        .user_data = (void *)&((td_ta_state_t) { false, false })
    }
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        case 3:
            ergodox_right_led_3_on();
            break;
        default:
            // none
            break;
    }

};
