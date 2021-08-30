#include QMK_KEYBOARD_H
//#define SWE_AA LALT(KC_A)
#ifndef VIMMOD_H
#define VIMMOD_H

#define LAY_1 MO(_L1)
#define LAY_2 MO(_L2)
#define LAY_3 MO(_L3)
#define ESC_L1 LT(_L1, KC_ESC)
#define L1_EQL LT(_L1, KC_EQL)
#define MIN_L2 LT(_L2, KC_MINUS)
#define SFT_ENT RSFT_T(KC_ENTER)
#define GUITAB LGUI(KC_TAB)
//#define ALT_AA RALT_T(SWE_AA)

#define L_SHIFT_HELD (get_mods() & (MOD_BIT(KC_LSFT)))
#define R_SHIFT_HELD (get_mods() & (MOD_BIT(KC_RSFT)))
#define SHIFT_HELD (L_SHIFT_HELD || R_SHIFT_HELD)
#define L_CTRL_HELD (get_mods() & (MOD_BIT(KC_LCTRL)))
#define R_CTRL_HELD (get_mods() & (MOD_BIT(KC_RCTRL)))
#define CTRL_HELD (L_CTRL_HELD || R_CTRL_HELD)
#define L_GUI_HELD (get_mods() & (MOD_BIT(KC_LGUI)))
#define R_GUI_HELD (get_mods() & (MOD_BIT(KC_RGUI)))
#define GUI_HELD (L_GUI_HELD || R_GUI_HELD)

#define TAPPING_TERM 250

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  VIM_ESC = SAFE_RANGE,
  SWE_AA,
  SWE_AE,
  SWE_OE,
  ALT_AA,
  HAPPY,
  SAD,
  TONGUE
};

bool handle_vim_mode(uint16_t keycode, keyrecord_t *record, uint8_t vim_layer_no);
void mod_type(uint16_t modcode, uint16_t keycode);
#endif
