#include QMK_KEYBOARD_H

#define HOME G(KC_LEFT)
#define END G(KC_RGHT)
#define FWD G(KC_RBRC)
#define BACK G(KC_LBRC)
#define TABL G(S(KC_LBRC))
#define TABR G(S(KC_RBRC))
#define SPCL A(G(KC_LEFT))
#define SPCR A(G(KC_RGHT))
#define LA_SYM MO(SYM)
#define LA_NAV MO(NAV)

enum layers {
    DEF,
    SYM,
    NAV,
    NUM,
};

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,

    SW_WIN,  // Switch to next window         (cmd-tab)
    SW_LANG, // Switch to next input language (ctl-spc)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_callum(
        // Left hand
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,
        KC_A,    KC_R,    KC_S,    KC_T,    KC_D,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
                                   LA_NAV,  KC_LSFT,

        // Right hand
        KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
        KC_H,    KC_N,    KC_E,    KC_I,    KC_O,
        KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
        KC_SPC,  LA_SYM
    ),

    [SYM] = LAYOUT_callum(
        // Left hand
        KC_ESC,  KC_LBRC, KC_LCBR, KC_LPRN, KC_TILD,
        KC_MINS, KC_ASTR, KC_EQL,  KC_UNDS, KC_DLR,
        KC_PLUS, KC_PIPE, KC_AT,   KC_BSLS, KC_PERC,
                                   _______, _______,

        // Right hand
        KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC, KC_GRV,
        KC_HASH, OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT,
        XXXXXXX, KC_AMPR, KC_SCLN, KC_COLN, KC_EXLM,
        _______, _______
    ),

    [NAV] = LAYOUT_callum(
        // Left hand
        KC_TAB,  SW_WIN,  TABL,    TABR,    KC_VOLU,
        OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  KC_VOLD,
        SPCL,    SPCR,    BACK,    FWD,     KC_MPLY,
                                   _______, _______,

        // Right hand
        RESET,   HOME,    KC_UP,   END,     KC_DEL,
        KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC,
        XXXXXXX, KC_PGDN, KC_PGUP, SW_LANG, KC_ENT,
        _______, _______
    ),

    [NUM] = LAYOUT_callum(
        // Left hand
        KC_7,    KC_5,    KC_3,    KC_1,    KC_9,
        OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  KC_F11,
        KC_F7,   KC_F5,   KC_F3,   KC_F1,   KC_F9,
                                   _______, _______,

        // Right hand
        KC_8,    KC_0,    KC_2,    KC_4,    KC_6,
        KC_F10,  OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT,
        KC_F8,   KC_F12,  KC_F2,   KC_F4,   KC_F6,
        _______, _______
    ),
};

// Implements cmd-tab like behaviour on a single key. On first tap of trigger
// cmdish is held and tabish is tapped -- cmdish then remains held until some
// other key is hit or released. For example:
//
//     trigger, trigger, a -> cmd down, tab, tab, cmd up, a
//     nav down, trigger, nav up -> nav down, cmd down, tab, cmd up, nav up
//
// This behaviour is useful for more than just cmd-tab, hence: cmdish, tabish.
void update_switcher(
    bool *active,
    uint16_t cmdish,
    uint16_t tabish,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            if (!*active) {
                *active = true;
                register_code(cmdish);
            }
            register_code(tabish);
        } else {
            unregister_code(tabish);
            // Don't unregister cmdish until some other key is hit or released.
        }
    } else if (*active) {
        unregister_code(cmdish);
        *active = false;
    }
}

bool is_layer(uint16_t keycode) {
    return keycode == LA_SYM || keycode == LA_NAV;
}

bool is_mod(uint16_t keycode) {
    return keycode == KC_LSFT || keycode == OS_SHFT ||
        keycode == OS_CTRL || keycode == OS_ALT || keycode == OS_CMD;
}

typedef enum {
    up_unqueued,
    up_queued,
    down_unused,
    down_used,
} oneshot_state;

// Custom oneshot mod implementation that doesn't rely on timers. If a mod is
// used while it is held it will be unregistered on keyup as normal, otherwise
// it will be queued and only released after the next non-mod keyup.
//
// Queued mods can be carried to lower layers but not to higher layers. Given
// higher layers all have the full complement of modifier keys we never need to
// carry a queued mod to a higher layer, so tapping a layer key becomes a
// convenient way to cancel queued mods.
void update_oneshot(
    oneshot_state *state,
    uint16_t mod,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (*state == up_unqueued) {
                register_code(mod);
            }
            *state = down_unused;
        } else {
            // Trigger keyup
            switch (*state) {
            case down_unused:
                // If we didn't use the mod while trigger was held, queue it.
                *state = up_queued;
                break;
            case down_used:
                // If we did use the mod while trigger was held, unregister it.
                *state = up_unqueued;
                unregister_code(mod);
                break;
            default:
                break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (is_layer(keycode) && *state != up_unqueued) {
                // Cancel oneshot on layer keydown, there's no reason to carry
                // mods to a higher layer so this is a convenient way of
                // clearing unused oneshots.
                *state = up_unqueued;
                unregister_code(mod);
            }
        } else {
            if (!is_layer(keycode) && !is_mod(keycode)) {
                // On non-layer, non-mod keyup, consider the oneshot used.
                // Don't touch the oneshot state on layer or mod keyup, so that
                // they stack with other mods, and can be carried to lower
                // layers.
                switch (*state) {
                case down_unused:
                    *state = down_used;
                    break;
                case up_queued:
                    *state = up_unqueued;
                    unregister_code(mod);
                    break;
                default:
                    break;
                }
            }
        }
    }
}

bool swin_active = false;
bool slan_active = false;

oneshot_state osft_state = up_unqueued;
oneshot_state octl_state = up_unqueued;
oneshot_state oalt_state = up_unqueued;
oneshot_state ocmd_state = up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_switcher(&swin_active, KC_LGUI, KC_TAB, SW_WIN, keycode, record);
    update_switcher(&slan_active, KC_LCTL, KC_SPC, SW_LANG, keycode, record);

    update_oneshot(&osft_state, KC_LSFT, OS_SHFT, keycode, record);
    update_oneshot(&octl_state, KC_LCTL, OS_CTRL, keycode, record);
    update_oneshot(&oalt_state, KC_LALT, OS_ALT, keycode, record);
    update_oneshot(&ocmd_state, KC_LCMD, OS_CMD, keycode, record);

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, NUM);
}
