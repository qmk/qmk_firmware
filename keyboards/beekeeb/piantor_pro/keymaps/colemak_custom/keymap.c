// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Colemak layout for Piantor Pro 36-key (3x5 + 3 thumb keys)
// Layout visualization:
//      ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
//      │ Q │ W │ F │ P │ G │       │ J │ L │ U │ Y │ ; │
//      ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
//      │ A │ R │ S │ T │ D │       │ H │ N │ E │ I │ O │
//      ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
//      │ Z │ X │ C │ V │ B │       │ K │ M │ , │ . │ / │
//      └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
//                ┌───┐                   ┌───┐
//                │GUI├───┐           ┌───┤Alt│
//                └───┤Bsp├───┐   ┌───┤Ent├───┘
//                    └───┤   │   │   ├───┘
//                        └───┘   └───┘

enum layer_names {
    _BASE,  // Main layer (Colemak)
    _CODE,   // Code layer
    _NUM  // Numbers layer
};

enum combo_events {
    LANG_SWITCH_COMBO,
};

const uint16_t PROGMEM lang_switch_combo[] = {TO(_NUM), TO(_CODE), COMBO_END};

combo_t key_combos[] = {
    [LANG_SWITCH_COMBO] = COMBO_ACTION(lang_switch_combo),
};

// Tap dance definitions (only for keys that can't use mod-tap or layer-tap)
enum {
    TD_F_UNDS,      // F: tap = F, hold = underscore
    TD_P_CMD_SLASH, // P: tap = P, hold = Command + /
    TD_G_TAB,       // G: tap = G, hold = Tab
    TD_J_ESC,       // J: tap = J, hold = Escape
    TD_U_UNDS,      // U: tap = U, hold = dash
    TD_Z_CMD,       // Z: tap = Z, hold = Command + Z (undo)
    TD_X_CMD,       // X: tap = X, hold = Command + X (cut)
    TD_C_CMD,       // C: tap = C, hold = Command + C (copy)
    TD_V_CMD,       // V: tap = V, hold = Command + V (paste)
    TD_M_EXLM,      // M: tap = M, hold = exclamation
    TD_SLASH_UNDS,  // /: tap = /, hold = underscore
    TD_LT_QMARK,    // <: tap = <, hold = ?
    TD_Q_TILD,      // Q: tap = Q, hold = ~
    TD_SPC_COLN,    // Space: tap = Space, hold = :
    TD_DOT_EQL,     // Period: tap = period, hold = equals
    TD_PERC_TILD,   // %: tap = %, hold = ~
    TD_UNDS_CAPS,   // _: tap = _, hold = CapsLock
    TD_DLR_CTRL_SPC, // $: tap = $, hold = Ctrl + Space
    TD_ENT_DOWN,     // Enter: tap = Enter, hold = Down Arrow
};

void dance_f_unds_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        // Key is being held - output underscore
        register_code16(KC_UNDS);
    } else {
        // Key was tapped - output F
        register_code16(KC_F);
    }
}

void dance_f_unds_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code16(KC_UNDS);
    unregister_code16(KC_F);
}

void dance_p_cmd_slash_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        // Key is being held - output Command + /
        register_code(KC_LGUI);
        register_code(KC_SLSH);
    } else {
        // Key was tapped - output P
        register_code16(KC_P);
    }
}

void dance_p_cmd_slash_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_SLSH);
    unregister_code(KC_LGUI);
    unregister_code16(KC_P);
}

void dance_g_tab_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        // Key is being held - output Tab
        register_code16(KC_TAB);
    } else {
        // Key was tapped - output G
        register_code16(KC_G);
    }
}

void dance_g_tab_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code16(KC_TAB);
    unregister_code16(KC_G);
}

void dance_j_esc_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        register_code16(KC_ESC);
    } else {
        register_code16(KC_J);
    }
}

void dance_j_esc_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code16(KC_ESC);
    unregister_code16(KC_J);
}

void dance_u_unds_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        register_code16(KC_MINS);
    } else {
        register_code16(KC_U);
    }
}

void dance_u_unds_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code16(KC_MINS);
    unregister_code16(KC_U);
}

void dance_z_cmd_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        register_code(KC_LGUI);
        register_code(KC_Z);
    } else {
        register_code16(KC_Z);
    }
}

void dance_z_cmd_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_Z);
    unregister_code(KC_LGUI);
    unregister_code16(KC_Z);
}

void dance_x_cmd_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        register_code(KC_LGUI);
        register_code(KC_X);
    } else {
        register_code16(KC_X);
    }
}

void dance_x_cmd_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_X);
    unregister_code(KC_LGUI);
    unregister_code16(KC_X);
}

void dance_c_cmd_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        register_code(KC_LGUI);
        register_code(KC_C);
    } else {
        register_code16(KC_C);
    }
}

void dance_c_cmd_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_C);
    unregister_code(KC_LGUI);
    unregister_code16(KC_C);
}

void dance_v_cmd_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        register_code(KC_LGUI);
        register_code(KC_V);
    } else {
        register_code16(KC_V);
    }
}

void dance_v_cmd_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_V);
    unregister_code(KC_LGUI);
    unregister_code16(KC_V);
}

void dance_m_exlm_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        register_code16(KC_EXLM);
    } else {
        register_code16(KC_M);
    }
}

void dance_m_exlm_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code16(KC_EXLM);
    unregister_code16(KC_M);
}

void dance_slash_unds_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        register_code16(KC_UNDS);
    } else {
        register_code16(KC_SLSH);
    }
}

void dance_slash_unds_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code16(KC_UNDS);
    unregister_code16(KC_SLSH);
}

void dance_lt_qmark_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        // Hold = ?
        register_code(KC_LSFT);
        register_code(KC_SLSH);
    } else {
        // Tap = <
        register_code(KC_LSFT);
        register_code(KC_COMM);
    }
}

void dance_lt_qmark_reset(tap_dance_state_t *state, void *user_data) {
    // Always release every keycode this dance can register.
    // `state->pressed` is not reliable here for selecting the branch on reset.
    unregister_code(KC_SLSH);
    unregister_code(KC_COMM);
    unregister_code(KC_LSFT);
}

void dance_q_tild_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        register_code16(KC_TILD);
    } else {
        register_code16(KC_Q);
    }
}

void dance_q_tild_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code16(KC_TILD);
    unregister_code16(KC_Q);
}

void dance_spc_coln_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        register_code16(KC_COLN);
    } else {
        register_code16(KC_SPC);
    }
}

void dance_spc_coln_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code16(KC_COLN);
    unregister_code16(KC_SPC);
}

void dance_dot_eql_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        register_code16(KC_EQL);
    } else {
        register_code16(KC_DOT);
    }
}

void dance_dot_eql_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code16(KC_EQL);
    unregister_code16(KC_DOT);
}

void dance_perc_tild_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        register_code16(KC_TILD);
    } else {
        register_code16(KC_PERC);
    }
}

void dance_perc_tild_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code16(KC_TILD);
    unregister_code16(KC_PERC);
}

void dance_unds_caps_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        register_code(KC_CAPS);
    } else {
        register_code16(KC_UNDS);
    }
}

void dance_unds_caps_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_CAPS);
    unregister_code16(KC_UNDS);
}

void dance_dlr_ctrl_spc_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        // Hold = Ctrl + Space
        register_code(KC_LCTL);
        register_code(KC_SPC);
    } else {
        // Tap = $
        register_code16(KC_DLR);
    }
}

void dance_dlr_ctrl_spc_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_SPC);
    unregister_code(KC_LCTL);
    unregister_code16(KC_DLR);
}

void dance_ent_down_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        register_code16(KC_DOWN);
    } else {
        register_code16(KC_ENT);
    }
}

void dance_ent_down_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code16(KC_DOWN);
    unregister_code16(KC_ENT);
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_F_UNDS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_f_unds_finished, dance_f_unds_reset),
    [TD_P_CMD_SLASH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_p_cmd_slash_finished, dance_p_cmd_slash_reset),
    [TD_G_TAB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_g_tab_finished, dance_g_tab_reset),
    [TD_J_ESC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_j_esc_finished, dance_j_esc_reset),
    [TD_U_UNDS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_u_unds_finished, dance_u_unds_reset),
    [TD_Z_CMD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_z_cmd_finished, dance_z_cmd_reset),
    [TD_X_CMD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_x_cmd_finished, dance_x_cmd_reset),
    [TD_C_CMD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_c_cmd_finished, dance_c_cmd_reset),
    [TD_V_CMD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_v_cmd_finished, dance_v_cmd_reset),
    [TD_M_EXLM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_m_exlm_finished, dance_m_exlm_reset),
    [TD_SLASH_UNDS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_slash_unds_finished, dance_slash_unds_reset),
    [TD_LT_QMARK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_lt_qmark_finished, dance_lt_qmark_reset),
    [TD_Q_TILD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_q_tild_finished, dance_q_tild_reset),
    [TD_SPC_COLN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_spc_coln_finished, dance_spc_coln_reset),
    [TD_DOT_EQL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_dot_eql_finished, dance_dot_eql_reset),
    [TD_PERC_TILD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_perc_tild_finished, dance_perc_tild_reset),
    [TD_UNDS_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_unds_caps_finished, dance_unds_caps_reset),
    [TD_DLR_CTRL_SPC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_dlr_ctrl_spc_finished, dance_dlr_ctrl_spc_reset),
    [TD_ENT_DOWN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_ent_down_finished, dance_ent_down_reset),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    if (!pressed) {
        return;
    }

    switch (combo_index) {
        case LANG_SWITCH_COMBO:
            // Fire a language-switch HID key (Globe/Fn-like behavior on many macOS setups).
            tap_code(KC_LNG2);
            break;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Base Layer - Colemak
     */
    [_BASE] = LAYOUT_split_3x5_3(
        TD(TD_Q_TILD),    KC_W,    TD(TD_F_UNDS),    TD(TD_P_CMD_SLASH),    TD(TD_G_TAB),                               TD(TD_J_ESC),   KC_L,    TD(TD_U_UNDS),    KC_Y,    S(KC_DOT),
        LCTL_T(KC_A),    LALT_T(KC_R),    LGUI_T(KC_S),    LSFT_T(KC_T),   LT(_CODE, KC_D),                              LT(_CODE, KC_H),   RSFT_T(KC_N),    RGUI_T(KC_E),    RALT_T(KC_I),    RCTL_T(KC_O),
        TD(TD_Z_CMD),    TD(TD_X_CMD),    TD(TD_C_CMD),    TD(TD_V_CMD),    LT(_NUM, KC_B),                               LT(_NUM, KC_K),    TD(TD_M_EXLM),    KC_BSPC, TD(TD_SLASH_UNDS),  TD(TD_LT_QMARK),
                                   TO(_NUM), TD(TD_SPC_COLN), TD(TD_ENT_DOWN),         MEH_T(KC_COMM), TD(TD_DOT_EQL), TO(_CODE)
    ),

        /*
     * Code Layer
     */
    [_CODE] = LAYOUT_split_3x5_3(
        KC_HASH, KC_AT,   KC_DLR,  KC_LPRN, KC_MINS,                            KC_PLUS, KC_RPRN, KC_AMPR, KC_BSLS, KC_DEL,
        KC_DQUO, KC_QUOT, KC_PIPE, KC_LCBR, _______,                            _______, KC_RCBR, KC_SCLN, KC_SLSH, KC_GRV,
        TD(TD_PERC_TILD), KC_CIRC, KC_LBRC, KC_LT,   _______,                            _______, KC_GT,   KC_RBRC, KC_ASTR, TD(TD_UNDS_CAPS),
                                   TO(_BASE), _______, _______,         _______,   _______, TO(_BASE)
    ),

    /*
     * Numbers Layer
     */
    [_NUM] = LAYOUT_split_3x5_3(
        KC_MUTE, KC_VOLD, KC_VOLU, KC_UP,   KC_LEFT,                            KC_RGHT, KC_P7,   KC_P8,   KC_P9,   KC_PERC,
        KC_MPRV, KC_MPLY, KC_MNXT, KC_DOWN, _______,                             _______ , KC_P4,   KC_P5,   KC_P6,   KC_P0,
        TD(TD_Z_CMD), TD(TD_X_CMD), TD(TD_C_CMD), TD(TD_V_CMD), _______,                            _______, KC_P1,   KC_P2,   KC_P3,   TD(TD_DLR_CTRL_SPC),
                                   TO(_BASE), KC_MINS, KC_PLUS,        KC_SLSH, KC_ASTR, TO(_BASE)
    )

};

// Optional: Enable per-key RGB lighting if your keyboard supports it
// #ifdef RGBLIGHT_ENABLE
// const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//     {0, 1, HSV_RED}
// );
// const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYER_LIST(
//     my_capslock_layer
// );
// #endif

