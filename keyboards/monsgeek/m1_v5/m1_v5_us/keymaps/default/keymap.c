// Copyright 2024 yangzheng20003 (@yangzheng20003)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "module.h"
#include "lowpower.h"
#include "wls/wls.h"
#include QMK_KEYBOARD_H

// Optional features - set to 1 to enable, 0 to disable
#ifndef ENABLE_WASD_DIRECTION_SWAP
#    define ENABLE_WASD_DIRECTION_SWAP 1
#endif

#ifndef ENABLE_KEEP_AWAKE
#    define ENABLE_KEEP_AWAKE 1
#endif

// clang-format off
enum layers {
    _BL = 0,  // Base Layer (Windows)
    _FL,      // Function Layer (Windows)
    _MBL,     // Base Layer (Mac)
    _MFL,     // Function Layer (Mac)
    _FBL      // FN+Shift Layer
};
// clang-format on

enum custom_keycodes {
    HS_DIR = SAFE_RANGE, // WASD <-> Arrow swap toggle
    HS_CT_A,             // Ctrl as Menu toggle
    BT_TEST,
    KEEP_AWAKE,
};

#define ______ HS_BLACK

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BL] = LAYOUT( /* Base */
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,   KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_HOME,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_PGUP,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,   KC_PGDN,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_END,
        KC_LCTL,  KC_LCMD,  KC_LALT,                      KC_SPC,                                 KC_RALT,  MO(_FL),  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [_FL] = LAYOUT( /* Function Layer */
        QK_BOOT,  KC_MYCM,  KC_MAIL,  KC_WSCH,  KC_WHOM,  KC_MSEL,  KC_MPLY,  KC_MPRV,  KC_MNXT,  _______,  _______,  _______,  _______,  RM_NEXT,  _______,
        EE_CLR,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RM_SPDD,  RM_SPDU,  _______,  _______,
        _______,  _______,  HS_DIR,   KC_BT1,   KC_BT2,   KC_BT3,   KC_2G4,   KC_USB,   KC_INS,   _______,  KC_PSCR,  _______,  _______,  _______,  _______,
        _______,  _______, _______,  _______,  _______,   _______,  _______,  KEEP_AWAKE, _______,  RM_TOGG,  _______,  _______,            _______,  _______,
        _______,            _______,  _______,  KC_CALC,  _______,  _______,  _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  MO(_FBL), RM_VALU,  _______,
        _______,   GU_TOGG,  _______,                     HS_BATQ,                                _______,  _______,  HS_CT_A,  RM_SATU,  RM_VALD,  RM_SATD),

    [_MBL] = LAYOUT( /* Base (Mac) */
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,   KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_HOME,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_PGUP,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,   KC_PGDN,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_END,
        KC_LCTL,  KC_LALT,  KC_LCMD,                      KC_SPC,                                 KC_RCMD,  MO(_MFL), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [_MFL] = LAYOUT( /* Function Layer (Mac) */
        _______,  KC_BRID,  KC_BRIU,  KC_MCTL,  HS_SIRI,  _______,  _______,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  RM_NEXT,  _______,
        EE_CLR,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RM_SPDD,  RM_SPDU,  _______,  _______,
        _______,  _______,  HS_DIR,   KC_BT1,   KC_BT2,   KC_BT3,   KC_2G4,   KC_USB,   KC_INS,   _______,  KC_PSCR,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  KEEP_AWAKE, _______,  RM_TOGG,  _______,  _______,            _______,  _______,
        _______,            _______,  _______,  KC_CALC,  _______,  _______,  _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  MO(_FBL), RM_VALU,  _______,
        _______,  _______,  _______,                      HS_BATQ,                                _______,  _______,  HS_CT_A,  RM_SATU,  RM_VALD,  RM_SATD),
    [_FBL] = LAYOUT( /* ? */
        QK_BOOT,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  BT_TEST,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,                      _______,                                _______,  _______,  _______,  _______,  _______,  _______)

};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] = {ENCODER_CCW_CW(_______, _______)},
    [2] = {ENCODER_CCW_CW(_______, _______)},
    [3] = {ENCODER_CCW_CW(_______, _______)},
    [4] = {ENCODER_CCW_CW(_______, _______)},
};
#endif
// clang-format on

typedef union {
    uint32_t raw;
    struct {
        uint8_t wasd_act_as_directional : 1;
        uint8_t ctrl_act_as_menu : 1;
    };
} eeconfig_user_t;
eeconfig_user_t user_confinfo;

void eeconfig_init_user(void) {
    user_confinfo.raw = eeconfig_read_user();
    if (!user_confinfo.raw) {
        user_confinfo.wasd_act_as_directional = 0;
        user_confinfo.ctrl_act_as_menu        = 0;
    }
}

// Blink function from keyboard
extern void hs_kb_blink(void);

#if ENABLE_KEEP_AWAKE
#    define KEEP_AWAKE_INTERVAL 5000
uint32_t keep_awake_timer;

uint32_t keep_awake_callback(uint32_t trigger_time, void *cb_arg) {
    static bool    status         = false;
    report_mouse_t current_report = {};
    if (status) {
        current_report.y = 1;
    } else {
        current_report.y = -1;
    }
    host_mouse_send(&current_report);
    lpwr_update_timestamp();

    // prevent timeout
    if (*md_getp_state() == MD_STATE_CONNECTED) {
        hs_rgb_blink_set_timer(timer_read32());
    }

    status = !status;
    return KEEP_AWAKE_INTERVAL;
}
#endif

void m1v5_bt_test(void);

static uint32_t ctrl_act_as_menu_callback(uint32_t trigger_time, void *cb_arg) {
    user_confinfo.ctrl_act_as_menu = !user_confinfo.ctrl_act_as_menu;
    hs_kb_blink();
    eeconfig_update_user(user_confinfo.raw);
    return 0;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case BT_TEST:
            if (record->event.pressed) {
                m1v5_bt_test();
            }
            return false;

#if ENABLE_WASD_DIRECTION_SWAP
        case KC_A: {
            if (user_confinfo.wasd_act_as_directional) {
                if (record->event.pressed) {
                    register_code16(KC_LEFT);
                } else {
                    unregister_code16(KC_LEFT);
                }
                return false;
            }
        } break;

        case KC_S: {
            if (user_confinfo.wasd_act_as_directional) {
                if (record->event.pressed) {
                    register_code16(KC_DOWN);
                } else {
                    unregister_code16(KC_DOWN);
                }
                return false;
            }
        } break;

        case KC_D: {
            if (user_confinfo.wasd_act_as_directional) {
                if (record->event.pressed) {
                    register_code16(KC_RGHT);
                } else {
                    unregister_code16(KC_RGHT);
                }
                return false;
            }
        } break;

        case KC_W: {
            if (user_confinfo.wasd_act_as_directional) {
                if (record->event.pressed) {
                    register_code16(KC_UP);
                } else {
                    unregister_code16(KC_UP);
                }
                return false;
            } else {
                return true;
            }
        } break;

        case KC_LEFT: {
            if (user_confinfo.wasd_act_as_directional) {
                if (record->event.pressed) {
                    register_code16(KC_A);
                } else {
                    unregister_code16(KC_A);
                }
                return false;
            }
        } break;

        case KC_DOWN: {
            if (user_confinfo.wasd_act_as_directional) {
                if (record->event.pressed) {
                    register_code16(KC_S);
                } else {
                    unregister_code16(KC_S);
                }
                return false;
            }
        } break;

        case KC_RGHT: {
            if (user_confinfo.wasd_act_as_directional) {
                if (record->event.pressed) {
                    register_code16(KC_D);
                } else {
                    unregister_code16(KC_D);
                }
                return false;
            }
        } break;

        case KC_UP: {
            if (user_confinfo.wasd_act_as_directional) {
                if (record->event.pressed) {
                    register_code16(KC_W);
                } else {
                    unregister_code16(KC_W);
                }
                return false;
            }
        } break;
#endif

        case KC_RCTL:
            if (user_confinfo.ctrl_act_as_menu) {
                if (record->event.pressed) {
                    register_code16(KC_APP);
                } else {
                    unregister_code16(KC_APP);
                }
                return false;
            }
            break;

#if ENABLE_WASD_DIRECTION_SWAP
        case HS_DIR:
            if (record->event.pressed) {
                user_confinfo.wasd_act_as_directional = !user_confinfo.wasd_act_as_directional;
                hs_kb_blink();
                eeconfig_update_user(user_confinfo.raw);
            }
            return false;
#endif

        case HS_CT_A: {
            static deferred_token delayed_exec = INVALID_DEFERRED_TOKEN;
            if (record->event.pressed) {
                delayed_exec = defer_exec(3000, ctrl_act_as_menu_callback, NULL);
            } else if (delayed_exec != INVALID_DEFERRED_TOKEN) {
                cancel_deferred_exec(delayed_exec);
                delayed_exec = INVALID_DEFERRED_TOKEN;
            }
            return false;
        }

#if ENABLE_KEEP_AWAKE
        case KEEP_AWAKE: {
            static deferred_token delayed_exec = INVALID_DEFERRED_TOKEN;
            if (record->event.pressed) {
                if (keep_awake_timer) {
                    cancel_deferred_exec(delayed_exec);
                    keep_awake_timer = 0;
                    delayed_exec     = INVALID_DEFERRED_TOKEN;
                    md_send_devctrl(MD_SND_CMD_DEVCTRL_SLEEP_BT_EN);
                    md_send_devctrl(MD_SND_CMD_DEVCTRL_SLEEP_2G4_EN);
                } else {
                    delayed_exec = defer_exec(KEEP_AWAKE_INTERVAL, keep_awake_callback, NULL);
                    if (delayed_exec != INVALID_DEFERRED_TOKEN) keep_awake_timer = timer_read();
                    md_send_devctrl(MD_SND_CMD_DEVCTRL_SLEEP_BT_DIS);
                    md_send_devctrl(MD_SND_CMD_DEVCTRL_SLEEP_2G4_DIS);
                }
            }
            return false;
        }
#endif
    }

    return true;
}

bool rgb_matrix_indicators_user(void) {
#if ENABLE_KEEP_AWAKE
    if (keep_awake_timer) {
        // Blink J key (index 59) when keep awake is active
        if (timer_elapsed(keep_awake_timer) / 500 % 2 == 0) {
            rgb_matrix_set_color(59, 0xFF, 0xFF, 0xFF);
        } else {
            rgb_matrix_set_color(59, 0x00, 0x00, 0x00);
        }
    }
#endif
    return true;
}
