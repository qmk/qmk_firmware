#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [0] = LAYOUT_ortho_3x12(KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_NUHS, LSFT_T(KC_NUBS), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT),
        [1] = LAYOUT_ortho_3x12(KC_GRV, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
        [2] = LAYOUT_ortho_3x12(KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
        [3] = LAYOUT_ortho_3x12(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};

bool my_lalt_flag = false;

enum combos { 
  Q_W_ESC,
  A_S_TAB,
  LBRC_RBRC_BSPC,
  QUOT_NUHS_ENT,
  LSFT_Z_LCTL,
  SLSH_RSFT_RCTL,
  C_V_LALT,
  M_COMM_RALT,
  Z_X_LGUI,
  DOT_SLSH_RGUI,
  V_B_TT,
  N_M_TT,
  B_N_LT
};

enum custom_keycodes {
  KC_SHFT_ESC
};

const uint16_t PROGMEM q_w_esc_combo[] = { KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM a_s_tab_combo[] = { KC_A, KC_S, COMBO_END};
const uint16_t PROGMEM lbrc_rbrc_bspc_combo[] = { KC_LBRC, KC_RBRC, COMBO_END};
const uint16_t PROGMEM quot_nuhs_ent_combo[] = { KC_QUOT, KC_NUHS, COMBO_END};
const uint16_t PROGMEM lsft_z_lctl_combo[] = { LSFT_T(KC_NUBS), KC_Z, COMBO_END}; 
const uint16_t PROGMEM slsh_rsft_rctl_combo[] = { KC_SLSH, KC_RSFT, COMBO_END};
const uint16_t PROGMEM c_v_lalt_combo[] = { KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM m_comm_ralt_combo[] = { KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM z_x_lgui_combo[] = { KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM dot_slsh_rgui_combo[] = { KC_DOT, KC_SLSH, COMBO_END};
const uint16_t PROGMEM v_b_tt_combo[] = { KC_V, KC_B, COMBO_END};
const uint16_t PROGMEM n_m_tt_combo[] = { KC_N, KC_M, COMBO_END};
const uint16_t PROGMEM b_n_lt_combo[] = { KC_B, KC_N, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [Q_W_ESC] = COMBO(q_w_esc_combo, KC_SHFT_ESC),
  [A_S_TAB] = COMBO_ACTION(a_s_tab_combo),
  [LBRC_RBRC_BSPC] = COMBO_ACTION(lbrc_rbrc_bspc_combo),
  [QUOT_NUHS_ENT] = COMBO(quot_nuhs_ent_combo, KC_ENT),
  [LSFT_Z_LCTL] = COMBO(lsft_z_lctl_combo, KC_LCTL), 
  [SLSH_RSFT_RCTL] = COMBO(slsh_rsft_rctl_combo, KC_RCTL),
  [C_V_LALT] = COMBO_ACTION(c_v_lalt_combo),
  [M_COMM_RALT] = COMBO_ACTION(m_comm_ralt_combo),
  [Z_X_LGUI] = COMBO(z_x_lgui_combo, KC_LGUI),
  [DOT_SLSH_RGUI] = COMBO(dot_slsh_rgui_combo, KC_RGUI),
  [V_B_TT] = COMBO_ACTION(v_b_tt_combo),
  [N_M_TT] = COMBO_ACTION(n_m_tt_combo),
  [B_N_LT] = COMBO_ACTION(b_n_lt_combo) 
};

int COMBO_LEN = sizeof(key_combos)/sizeof(key_combos[0]);

static uint16_t key_timer;
/*
static bool spc_pressed;
*/
static bool layer2tapped = false;
static bool layer3tapped = false;

void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {
    case Q_W_ESC:
      if (pressed) {
        if (IS_LAYER_ON(1)) {
          register_code16(KC_GRV);
        } else {
          register_code16(KC_ESC);
        }
      } else {
        if (IS_LAYER_ON(1)) {
          unregister_code16(KC_GRV);
        } else {
          unregister_code16(KC_ESC);
        }
      }
      break;
    case A_S_TAB:
      if (pressed) {
        if (my_lalt_flag) {
          register_code16(LALT(KC_TAB));
        } else {
          register_code16(KC_TAB);
        }
      } else {
        if (my_lalt_flag) {
          unregister_code16(LALT(KC_TAB));
        } else {
          unregister_code16(KC_TAB);
        }
      }
      break;
    case LBRC_RBRC_BSPC:
      if (pressed) {
        if (IS_LAYER_ON(1)) {
          register_code16(KC_DEL);
        } else {
          register_code16(KC_BSPC);
        }
      } else {
        if (IS_LAYER_ON(1)) {
          unregister_code16(KC_DEL);
        } else {
          unregister_code16(KC_BSPC);
        }
      }
      break;
    case C_V_LALT:
      if (pressed && !my_lalt_flag) {
        my_lalt_flag=true;
        register_mods(MOD_BIT(KC_LALT));
      } else if (!pressed && my_lalt_flag) {
        my_lalt_flag=false;
        unregister_mods(MOD_BIT(KC_LALT));
      }
      break;
    case M_COMM_RALT:
      if (pressed) {
        register_mods(MOD_BIT(KC_RALT));
      } else {
        unregister_mods(MOD_BIT(KC_RALT));
      }
      break;
    case V_B_TT:
      if (pressed) {
        key_timer = timer_read();
	if (!layer_state_is(2)) {
          layer_on(2);
	}
      } else {
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
	  if (layer2tapped) {
            layer_off(2);
	    layer2tapped = false;
	  } else {
	    layer2tapped = true;
	  }
	} else if (timer_elapsed(key_timer) >= TAPPING_TERM && layer_state_is(2)) {
          layer_off(2);
	}
      }
      break;
    case N_M_TT:
      if (pressed) {
        key_timer = timer_read();
	if (!layer_state_is(3)) {
          layer_on(3);
	}
      } else {
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
	  if (layer3tapped) {
            layer_off(3);
	    layer3tapped = false;
	  } else {
	    layer3tapped = true;
	  }
	} else if (timer_elapsed(key_timer) >= TAPPING_TERM && layer_state_is(3)) {
          layer_off(3);
	}
      }
      break;
    case B_N_LT:
      if (pressed) {
        key_timer = timer_read();
        layer_on(1);
/*
        if (spc_pressed) {
          tap_code(KC_SPC);
        } else {
          layer_on(1);
          spc_pressed = 0;
        }
*/
      } else {
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          tap_code(KC_SPC);
/*
          spc_pressed = 1;
        } else {
          spc_pressed = 0;
*/
	}
        layer_off(1);
      }
      break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_SHFT_ESC:
      if (record->event.pressed) {
        if (IS_LAYER_ON(1)) {
          register_code16(KC_GRV);
        } else {
          register_code16(KC_ESC);
        }
      } else {
        if (IS_LAYER_ON(1)) {
          unregister_code16(KC_GRV);
        } else {
          unregister_code16(KC_ESC);
        }
      }
      return false;
      break;
  }
  return true;
}
