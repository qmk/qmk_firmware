/* Copyright 2020 tominabox1
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _NUM_SYM,
    _NAV
};

#define KC_NUM_SPC LT(_NUM_SYM, KC_SPC)
#define KC_GA LGUI_T(KC_A)
#define KC_AS LALT_T(KC_S)
#define KC_CD LCTL_T(KC_D)
#define KC_SF LSFT_T(KC_F)
#define KC_SJ RSFT_T(KC_J)
#define KC_CK RCTL_T(KC_K)
#define KC_AL RALT_T(KC_L)
#define KC_GSCLN RGUI_T(KC_SCLN)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,  KC_MPLY,  KC_Y,   KC_U,    KC_I,   KC_O,     KC_P,
   KC_GA,  KC_AS,  KC_CD,  KC_SF,   KC_G,            KC_H,  KC_SJ,   KC_CK,  KC_AL, KC_GSCLN,
    KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,            KC_N,   KC_M, KC_COMM, KC_DOT,  KC_SLSH,
                         KC_LCTL, KC_ENT,            KC_NUM_SPC, MO(_NAV)
  ),

  [_NUM_SYM] = LAYOUT(
        KC_1,  KC_2,     KC_3,     KC_4,      KC_5,  KC_TRNS,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,
    KC_EXLM,  KC_AT,  KC_HASH,   KC_DLR,   KC_PERC,            KC_CIRC,  KC_AMPR,  KC_ASTR, KC_EQUAL,  KC_MINS,
    KC_BSLS,KC_LCBR,  KC_LBRC,  KC_LPRN,   KC_UNDS,            KC_RPRN,  KC_RBRC,  KC_RCBR,   KC_DOT,   KC_GRV,
                                KC_CAPS,   KC_TRNS,            KC_TRNS,  KC_TRNS
  ),

  [_NAV] = LAYOUT(
      QK_BOOT,  _______,  AG_NORM,  AG_SWAP,  DB_TOGG, KC_TRNS,   KC_GRV,  KC_PGDN,    KC_UP,  KC_PGUP,  KC_SCLN,
    RGB_TOG,  RGB_HUI,  RGB_SAI,  RGB_VAI,  KC_NO,           KC_HOME,  KC_LEFT,  KC_DOWN,  KC_RGHT,   KC_END,
    RGB_MOD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  KC_NO,           KC_MINS,    KC_INT1,  KC_COMM,   KC_DOT,  KC_BSLS,
                                  KC_TRNS,KC_TRNS,           KC_TRNS,  KC_TRNS
  )
};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] =  {ENCODER_CCW_CW(KC_MNXT, KC_MPRV) },
    [_NUM_SYM] = { ENCODER_CCW_CW(KC_WH_D, KC_WH_U) },
    [_NAV] = { ENCODER_CCW_CW(KC_PGDN, KC_PGUP) }
};
#endif

#ifdef COMBO_ENABLE
enum combo_events {
    COMBO_BSPC,
    COMBO_NUMBAK,
    COMBO_TAB,
    COMBO_ESC,
    COMBO_DEL,
};

const uint16_t PROGMEM combo_bspc[]   = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM combo_numbak[] = {KC_0, KC_9, COMBO_END};
const uint16_t PROGMEM combo_tab[]    = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM combo_esc[]    = {KC_E, KC_W, COMBO_END};
const uint16_t PROGMEM combo_del[]    = {KC_MINS, KC_EQL, COMBO_END};

combo_t key_combos[] = {
    [COMBO_BSPC] = COMBO(combo_bspc, KC_BSPC),
    [COMBO_NUMBAK] = COMBO(combo_numbak, KC_BSPC),
    [COMBO_TAB] = COMBO(combo_tab, KC_TAB),
    [COMBO_ESC] = COMBO(combo_esc, KC_ESC),
    [COMBO_DEL] = COMBO(combo_del, KC_DEL)
};
#endif

#ifdef OLED_ENABLE

// Add additional layer names here if desired. Only first 5 characters will be copied to display.
const char PROGMEM layer_base[]    = "BASE";
const char PROGMEM layer_num_sym[] = " SYM";
const char PROGMEM layer_nav[]     = " NAV";
// Add layer name variables to array here. Make sure these are in order.
const char* const PROGMEM layer_names[] = {
    layer_base,
    layer_num_sym,
    layer_nav
};

static char oled_layer_buf[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static layer_state_t top_layer_cache;

/* BEGIN STANDARD QMK FUNCTIONS */
bool oled_task_user(void) {
    oled_write_raw_P(lechiffre_logo, sizeof(lechiffre_logo));
    // Renders the current keyboard state (layer, lock, caps, scroll, etc);
    oled_set_cursor(0, 3);
    oled_write_P(oled_section_break, false);
    render_layer_status(oled_layer_buf);
    oled_write_P(oled_section_break, false);
    render_mod_status(get_mods() | get_oneshot_mods());
    oled_write_P(oled_section_break, false);
    render_keylock_status(host_keyboard_led_state());
    oled_write_P(oled_section_break, false);
    render_keylogger_status();

    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
        add_keylog(keycode, record);
    }

    return true;
}

// If we don't force an update during initialization, the layer name buffer will start out blank.
layer_state_t default_layer_state_set_user(layer_state_t state) {
    update_layer_namebuf(get_highest_layer(state), true);
    return state;
}
layer_state_t layer_state_set_user(layer_state_t state) {
    update_layer_namebuf(get_highest_layer(state | default_layer_state), false);
    return state;
}

/* END STANDARD QMK FUNCTIONS */
/* BEGIN CUSTOM HELPER FUNCTION FOR OLED */
// Avoid excessive copying by only updating the layer name buffer when the layer changes
void update_layer_namebuf(layer_state_t layer, bool force_update) {
    if (force_update || layer != top_layer_cache) {
        top_layer_cache = layer;
        if (layer < ARRAY_SIZE(layer_names)) {
            memcpy_P(oled_layer_buf, pgm_read_ptr(&layer_names[layer]), ARRAY_SIZE(oled_layer_buf) - 1);
        } else {
            memcpy(oled_layer_buf, get_u8_str(layer, ' '), ARRAY_SIZE(oled_layer_buf) - 1);
        }
    }
}
#endif
