#include QMK_KEYBOARD_H
uint16_t copy_paste_timer;
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif
char wpm_str[10];
uint16_t wpm_graph_timer = 0;
extern uint8_t is_master;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

enum {
  TD_ESC_CAPS,
};

enum custom_keycodes {
  CP_PST = SAFE_RANGE,
  QWERTY,
  LOWER,
  RAISE,
  UC_DISA,
  UC_FLIP,
  UC_SHRG,
  UC_TABL,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LSHESC|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|CP_PST |    |LEADKEY|------+------+------+------+------+------|
 * |LCTRL |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  | Enter|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGui | LAlt |LOWER | /Space  /       \Enter \  |RAISE |DMPLY1|DMPLY2|
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT( \
  KC_GRV,         KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,         KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,  \
  LSFT_T(KC_ESC), KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LCTRL,       KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  CP_PST,  KC_LEAD, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  \
                                    KC_LGUI, KC_LALT, MO(1), KC_SPC,  KC_ENT,  MO(2),  DM_PLY1, DM_PLY2 \
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      | FLIP | TABL | SHRG | DISA |      |                    |      |      |      |      |      | Bksp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  Tab | Home |  Up  | End  | PGUP |      |                    |      |      |      |      |      |  Del |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LSHESC| Left | Down |Right | PGDN |      |-------.    ,-------|      |   _  |   +  |  {   |   }  |  |   |
 * |------+------+------+------+------+------|  C_P  |    |       |------+------+------+------+------+------|
 * |LCTRL |      |      |      |      |      |-------|    |-------|      |ISO ~ |ISO | |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGui | LAlt |LOWER | /Space  /       \Enter \  | RAISE |      |      |
 *                   |      |      |      |/       /         \      \ |       |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_LOWER] = LAYOUT( \
  XXXXXXX, UC_FLIP, UC_TABL, UC_SHRG, UC_DISA, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
  _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
  _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, XXXXXXX,                   XXXXXXX,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX,S(KC_NUHS),S(KC_NUBS),_______,_______,_______, \
                            _______, _______,  _______, _______, _______, _______, XXXXXXX, XXXXXXX \
),

/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      | Bksp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  Tab |      |      |      |      |      |                    |      |      |      |      |      | Del  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LSHESC|  F1  |  F2  |  F3  |  F4  |  F5  |-------.    ,-------|  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|  C_P  |    |       |------+------+------+------+------+------|
 * |LCTRL|  F7  |  F8  |  F9  |  F10 |  F11 |-------|    |-------|  F12 | ISO # |ISO /|   {  |   }  | Enter|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGui | LAlt |LOWER | /Space  /       \DMRSTP\  | RAISE|DMREC1|DMREC2|
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_RAISE] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,                  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, _______,  _______, KC_F12,  KC_NUHS, KC_NUBS, _______, _______, _______, \
                             _______, _______, _______, _______, DM_RSTP,  _______, DM_REC1, DM_REC2\
)};


//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master()) {
    return OLED_ROTATION_270;  // flips the display 270 degrees if master
  }
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);

static uint8_t zero_bar_count = 0;
static uint8_t bar_count = 0;

static void render_wpm_graph(void) {
  uint8_t bar_height = 0;
  uint8_t bar_segment = 0;

  if (wpm_graph_timer == 0) {
    wpm_graph_timer = timer_read();
    return;
  }
  if(timer_elapsed(wpm_graph_timer) > 500) {
    wpm_graph_timer = timer_read();

    if(OLED_DISPLAY_HEIGHT == 64)
      bar_height = get_current_wpm() / 2;
    if(OLED_DISPLAY_HEIGHT == 32)
      bar_height = get_current_wpm() / 4;
    if(bar_height > OLED_DISPLAY_HEIGHT)
      bar_height = OLED_DISPLAY_HEIGHT;

    if(bar_height == 0) {
        // keep track of how many zero bars we have drawn.  If
        // there is a whole screen worth, turn the display off and 
        // wait until there is something to do
        if (zero_bar_count > OLED_DISPLAY_WIDTH) {
      oled_off();
      return;
        }
        zero_bar_count++;
    } else
        zero_bar_count=0;

    oled_pan(false);
    bar_count++;
    for (uint8_t i = (OLED_DISPLAY_HEIGHT / 8); i > 0; i--) {
        if (bar_height > 7) {
      if (i % 2 == 1 && bar_count % 3 == 0)
          bar_segment = 254;
      else
          bar_segment = 255;
      bar_height -= 8;
        } else {
      switch (bar_height) {
          case 0:
        bar_segment = 0;
        break;
          case 1:
        bar_segment = 128;
        break;
          case 2:
        bar_segment = 192;
        break;
          case 3:
        bar_segment = 224;
        break;
          case 4:
        bar_segment = 240;
        break;
          case 5:
        bar_segment = 248;
        break;
          case 6:
        bar_segment = 252;
        break;
          case 7:
        bar_segment = 254;
        break;
      }
      bar_height = 0;

      if (i % 2 == 1 && bar_count % 3 == 0)
          bar_segment++;
        }
        oled_write_raw_byte(bar_segment, (i-1) * OLED_DISPLAY_WIDTH);
    }
  }
}

void render_layer_state(void) {
  oled_write_ln_P(PSTR("LAYER"), false);
  oled_write_ln_P(PSTR("DFLT"), layer_state_is(_QWERTY));
  oled_write_ln_P(PSTR("RSE"), layer_state_is(_RAISE));
  oled_write_ln_P(PSTR("LWR"), layer_state_is(_LOWER));
}

void render_status_secondary(void) {
  render_layer_state();
  oled_write_ln_P(PSTR(""), false);
  oled_write_ln_P(PSTR(""), false);
  oled_write_ln_P(PSTR(""), false);
  oled_write_ln_P(PSTR(""), false);
  oled_write_ln_P(PSTR(""), false);
  oled_write_ln_P(PSTR(""), false);
  oled_write_ln_P(PSTR(""), false);
#ifdef WPM_ENABLE
  // Write WPM
  sprintf(wpm_str, "WPM: %03d", get_current_wpm());
  oled_write(wpm_str, false);
#endif
}

void oled_task_user(void) {
  if (!is_keyboard_master()) {
	  render_wpm_graph();
  } else {
    render_status_secondary();
  }
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CP_PST:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("c"));
      } else {
        SEND_STRING(SS_LCTL("v"));
      }
      break;
#ifdef UNICODE_ENABLE
    case UC_FLIP:  // (ノಠ痊ಠ)ノ彡┻━┻
        if (record->event.pressed) {
            send_unicode_string("(ノಠ痊ಠ)ノ彡┻━┻");
        }
        break;
    case UC_TABL:  // ┬─┬ノ( º _ ºノ)
        if (record->event.pressed) {
            send_unicode_string("┬─┬ノ( º _ ºノ)");
        }
        break;
    case UC_SHRG:  // ¯\_(ツ)_/¯
        if (record->event.pressed) {
            send_unicode_string("¯\\_(ツ)_/¯");
        }
        break;
    case UC_DISA:  // ಠ_ಠ
        if (record->event.pressed) {
            send_unicode_string("ಠ_ಠ");
        }
        break;
#endif
  }
  return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {
  uint8_t layer = biton32(layer_state);
  switch (layer) {
    case _LOWER:
      if (clockwise) {
        tap_code(KC_PGDN);
      } else {
        tap_code(KC_PGUP);
      }
      break;
    case _QWERTY:
      if (clockwise) {
        tap_code(KC_WH_D);
      } else {
        tap_code(KC_WH_U);
      }
      break;
    case _RAISE:
      if (clockwise) {
        tap_code(KC_VOLU);
      } else {
        tap_code(KC_VOLD);
      }
      break;
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
};

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();
    SEQ_TWO_KEYS(KC_W, KC_1) {
      SEND_STRING("https://www.google.com\n");
    }
    SEQ_TWO_KEYS(KC_T, KC_1) {
      SEND_STRING("!roll all\n");
    }
    SEQ_TWO_KEYS(KC_T, KC_2) {
      SEND_STRING("!slots 5000\n");
    }
    SEQ_TWO_KEYS(KC_T, KC_3) {
      SEND_STRING("!slots 10000\n");
    }
  }
}