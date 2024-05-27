#include QMK_KEYBOARD_H
#include "gw_oled.h"
#include "quantum.h"

// clang-format off

// template
/*  _______,       _______,       _______,      _______,       _______,       _______,              _______,       _______,       _______,      _______,       _______,       _______, */
// formatting macro:
// mk2kWjrf<t_ý>a`kWkvehyjPwkr <t_ý>aj

enum layers {
  _QWERTY,
  _SYM,
  _NAVSYS,
  _NUM,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_split_3x6_3(
    CW_TOGG,       KC_Q,          KC_W,         KC_E,          KC_R,          KC_T,                 KC_Y,          KC_U,          KC_I,         KC_O,          KC_P,          KC_DEL,
    KC_ENT,        KC_A,          LT(3, KC_S),  LALT_T(KC_D),  LT(2, KC_F),   KC_G,                 KC_H,          KC_J,          KC_K,         KC_L,          KC_SCLN,       C(G(KC_Q)),
    QK_REP,        KC_Z,          KC_X,         KC_C,          KC_V,          KC_B,                 KC_N,          KC_M,          KC_COMM,      KC_DOT,        KC_COLN,       KC_HYPR,
                                                CTL_T(KC_ESC), GUI_T(KC_SPC), SFT_T(KC_TAB),        TG(2),         SFT_T(KC_BSPC),OSL(1)
),

[_SYM] = LAYOUT_split_3x6_3(
    _______,       _______,       KC_LT,        KC_GT,         KC_ASTR,       KC_GRV,               _______,       KC_AMPR,       KC_LCBR,      KC_RCBR,       KC_PERC,       _______,
    _______,       KC_QUES,       KC_MINS,      KC_DQUO,       KC_QUOT,       KC_TILD,              KC_BSLS,       KC_PLUS,       KC_LPRN,      KC_RPRN,       KC_UNDS,       _______,
    _______,       KC_HASH,       _______,      KC_EQL,        KC_EXLM,       KC_CIRC,              KC_DLR,        KC_PIPE,       KC_LBRC,      KC_RBRC,       KC_AT,         _______,
                                                KC_SLSH,       _______,       _______,              _______,       _______,       _______
),

[_NAVSYS] = LAYOUT_split_3x6_3(
    QK_BOOT,       _______,       _______,      _______,       _______,       _______,              _______,       C(KC_TAB),     KC_TAB,       LSFT(KC_TAB),  C(S(KC_TAB)),  _______,
    _______,       KC_MUTE,       KC_VOLD,      KC_VOLU,       _______,       _______,              KC_LEFT,       KC_DOWN,       KC_UP,        KC_RGHT,       _______,       _______,
    _______,       _______,       KC_MPRV,      KC_MNXT,       _______,       _______,              _______,       _______,       C(KC_LEFT),   C(KC_RGHT),    _______,       _______,
                                                _______,       _______,       _______,              _______,       KC_ENT,        _______
),

[_NUM] = LAYOUT_split_3x6_3(
    _______,       _______,       _______,      _______,       _______,       _______,              _______,       KC_7,          KC_8,         KC_9,          _______,       _______,
    _______,       _______,       _______,      _______,       _______,       _______,              _______,       KC_4,          KC_5,         KC_6,          _______,       _______,
    _______,       _______,       _______,      _______,       _______,       _______,              _______,       KC_1,          KC_2,         KC_3,          _______,       _______,
                                                _______,       _______,       _______,              _______,       _______,       KC_0
)

};

// clang-format on

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {};
#endif

/* ****************** */
/* KEYCODE SECTION BEGIN */
/* ****************** */

// return true to immediately select the hold action when another key is pressed.
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SFT_T(KC_BSPC):
            return true;
        default:
            return false;
    }
}

/* ****************** */
/* KEYCODE SECTION BEGIN */
/* ****************** */

/* ****************** */
/* RGB SECTION BEGIN */
/* ****************** */

#ifdef RGB_MATRIX_ENABLE
#    define RGB_LIGHT_BLUE 0x4c, 0xa8, 0xfc
#    define BASE_COL RGB_LIGHT_BLUE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];
            if (!(index >= led_min && index < led_max && index != NO_LED)) {
                continue;
            }
            uint16_t kc = keymap_key_to_keycode(layer, (keypos_t){col, row});
            if (kc == KC_NO) {
                rgb_matrix_set_color(index, RGB_OFF);
                continue;
            }
            if (kc == KC_TRNS) {
                rgb_matrix_set_color(index, BASE_COL);
                continue;
            }
            switch (layer) {
                case _QWERTY:
                    rgb_matrix_set_color(index, BASE_COL);
                    break;
                case _SYM:
                    rgb_matrix_set_color(index, RGB_PURPLE);
                    break;
                case _NAVSYS:
                    rgb_matrix_set_color(index, RGB_RED);
                    break;
                case _NUM:
                    rgb_matrix_set_color(index, RGB_GREEN);
                    break;
                default:
                    rgb_matrix_set_color(index, BASE_COL);
            }
        }
    }
    return false;
}
#endif

/* ****************** */
/* RGB SECTION END */
/* ****************** */

/* ****************** */
/* OLED SECTION BEGIN */
/* ****************** */

#ifdef OLED_ENABLE

void write_downtaunt_anim(void);

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
#    ifdef MASTER_RIGHT
    if (is_keyboard_master()) {
        return OLED_ROTATION_180;
    }
#    else
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;
    }
#    endif
    return rotation;
}

void oled_render_boot(bool bootloader) {
    oled_clear();
    for (int i = 0; i < 16; i++) {
        oled_set_cursor(0, i);
        if (bootloader) {
            oled_write_P(PSTR("Awaiting New Firmware "), false);
        } else {
            oled_write_P(PSTR("Rebooting "), false);
        }
    }

    oled_render_dirty(true);
}

bool shutdown_user(bool jump_to_bootloader) {
    oled_render_boot(jump_to_bootloader);
    return true;
}

uint16_t timer            = 0;
uint8_t  downtaunt_toggle = 0;

bool oled_task_user() {
    if (!is_keyboard_left()) {
        oled_write_raw(logo, sizeof(logo));
        return false;
    }

    const uint16_t TOGGLE_GAP_MS = 1000;
    if (timer_elapsed(timer) > TOGGLE_GAP_MS) {
        // Reset timer.
        timer = timer_read();
        downtaunt_toggle ^= 1;
    }

    const uint16_t DOWNTAUNT_WAIT_MS = 20000;
    const uint8_t  cur_layer         = get_highest_layer(layer_state);
    if (last_matrix_activity_elapsed() > DOWNTAUNT_WAIT_MS && cur_layer == _QWERTY) {
        write_downtaunt_anim();
    } else {
        switch (cur_layer) {
            case _QWERTY:
                oled_write_raw(gw_idle, sizeof(gw_idle));
                break;
            case _SYM:
                oled_write_raw(gw_diver, sizeof(gw_diver));
                break;
            case _NAVSYS:
                oled_write_raw(gw_parachute, sizeof(gw_parachute));
                break;
            case _NUM:
                oled_write_raw(gw_key, sizeof(gw_key));
                break;
        }
    }

    return false;
}

void write_downtaunt_anim(void) {
    if (downtaunt_toggle) {
        oled_write_raw(gw_downtaunt_f1, sizeof(gw_idle));
    } else {
        oled_write_raw(gw_downtaunt_f2, sizeof(gw_idle));
    }
}

#endif
/* ****************** */
/* OLED SECTION END */
/* ****************** */
