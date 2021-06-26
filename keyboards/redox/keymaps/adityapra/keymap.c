#include QMK_KEYBOARD_H

#define GUI_TAB_TIMER_WAIT_MS 500

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DVORAK 0
#define _NUM 1
#define _SYMB 2

#define LCTL_ESC MT(MOD_LCTL, KC_ESC)
#define LALT_DWN MT(MOD_LALT, KC_DOWN)
#define LGUI_UP MT(MOD_LGUI, KC_UP)
#define RGUI_LFT MT(MOD_RGUI, KC_LEFT)
#define RALT_RGT MT(MOD_RALT, KC_RGHT)
#define BSPC_SYMB LT(_SYMB, KC_BSPC)
#define ENT_NUM LT(_NUM, KC_ENT)
#define LSFT_TAB MT(MOD_LSFT, KC_TAB)
#define RSFT_ESC MT(MOD_RSFT, KC_ESC)

enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  NUM,
  SYMB,
  GUI_TAB,
  MACOS_CPY,
  MACOS_PST,
  MACOS_CWD,
  TMUX_VI,
};

// Shortcut to make keymap more readable

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_DVORAK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_QUOT ,KC_COMM ,KC_DOT  ,KC_P    ,KC_Y    ,_______ ,                          _______ ,KC_F    ,KC_G    ,KC_C    ,KC_R    ,KC_L    ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_A    ,KC_O    ,KC_E    ,KC_U    ,KC_I    ,_______ ,                          _______ ,KC_D    ,KC_H    ,KC_T    ,KC_N    ,KC_S    ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_SLSH ,KC_Q    ,KC_J    ,KC_K    ,KC_X    ,_______ ,_______ ,        _______ ,_______ ,KC_B    ,KC_M    ,KC_W    ,KC_V    ,KC_Z    ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,LALT_DWN,LGUI_UP ,     KC_SPC   ,   LCTL_ESC,LSFT_TAB,        RSFT_ESC, ENT_NUM,   BSPC_SYMB,    RGUI_LFT ,RALT_RGT,_______ ,_______ 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_NUM] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_LBRC ,KC_7    ,KC_8    ,KC_9    ,KC_RBRC ,_______ ,                          _______ ,TMUX_VI ,_______ ,MACOS_CPY,_______,_______,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_SCLN ,KC_4    ,KC_5    ,KC_6    ,KC_EQL  ,_______ ,                          _______ ,_______ ,GUI_TAB ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_GRV  ,KC_1    ,KC_2    ,KC_3    ,KC_BSLS ,_______ ,_______ ,         _______ ,_______ ,_______ ,MACOS_CWD,_______,MACOS_PST,_______, _______,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     KC_0    ,    KC_MINS ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______ 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_SYMB] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_LCBR ,KC_AMPR ,KC_ASTR , KC_LPRN,KC_RCBR ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_COLN ,KC_DOLLAR,KC_PERC,KC_CIRC ,KC_PLUS ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_TILD ,KC_EXLM ,KC_AT   ,KC_HASH ,KC_PIPE ,_______ ,_______ ,        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     KC_RPRN ,    KC_UNDS ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______ 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  )
};


uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case BSPC_SYMB:
        return 110;
      case ENT_NUM:
        return 110;
      default:
        return TAPPING_TERM;
    }
}

bool is_gui_tab_active = false;
uint16_t gui_tab_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case GUI_TAB:
      if (record->event.pressed) {
        if (!is_gui_tab_active) {
          is_gui_tab_active = true;
          register_code(KC_LGUI);
        }
        gui_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
    case MACOS_CPY:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI("c"));
      }
      break;
    case MACOS_PST:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI("v"));
      }
      break;
    case MACOS_CWD:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI("`"));
      }
      break;
    case TMUX_VI:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("a")"[");
      }
      break;
  }
  return true;
}

void matrix_scan_user(void) {
  if (is_gui_tab_active) {
    if (timer_elapsed(gui_tab_timer) > GUI_TAB_TIMER_WAIT_MS) {
      unregister_code(KC_LGUI);
      is_gui_tab_active = false;
    }
  }
}
