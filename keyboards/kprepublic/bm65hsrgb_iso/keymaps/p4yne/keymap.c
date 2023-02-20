/* Copyright 2019 ashlar 2021 peepeetee, deadolus 2022 p4yne
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
#include "custom_keymap.h"
#include "sendstring_german.h"

#ifdef TAP_DANCE_ENABLE
enum {
  TD_HOME_END,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  // tap once for home, twice for end
  [TD_HOME_END] = ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_END)
};
#endif

// Custom layer types
enum layertypes {
  LYR_SOLID, // fullsize coloring
  LYR_TRANS, // used keys in layer color, lower layer shines through on unused keys
  LYR_BLACK  // only used key in layer color
};

// Defines names for use in layer keycodes and the keymap
enum layers {
  _LVL0_,
  _LVL1_,
  _LVL2_,
  _LVL3_,
  _LVL4_,
  _LVL5_,
  _LVL6_,
  _LVL7_
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
     * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│Hom│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │     │PgU│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐ Ent├───┤
     * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ # │    │PgD│
     * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
     * │Shft│ \ │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ Shift│ ↑ │End│
     * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
     * │Ctrl│GUI │Alt │                        │ Alt│Ctrl│ │ ← │ ↓ │ → │
     * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
     */
#ifdef TAP_DANCE_ENABLE
/* 0: ISO qwertz, SPACECADET and TAPDANCE */
/*  [_LVL0_] = LAYOUT_65_iso_blocker(
      KC_ESC,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,      KC_MINS,  KC_EQL, KC_BSPC, KC_DEL,
      KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      KC_LBRC, KC_RBRC,          TD(TD_HOME_END),
      KC_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,   KC_QUOT, KC_NUHS, KC_ENT,  KC_PGUP,
      SC_LSPO, KC_NUBS,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,    KC_SLSH, SC_RSPC, KC_UP,   KC_PGDN,
      KC_LCTL, KC_LGUI, SC_LAPO,                    KC_SPC,                               SC_RAPC, MO(_LVL1_),         KC_LEFT, KC_DOWN, KC_RGHT
      ),
 */
/* 0: ISO DE qwertz, SPACECADET and TAPDANCE */
  [_LVL0_] = LAYOUT_65_iso_blocker(
      KC_ESC,     DE_1,    DE_2,    DE_3,    DE_4,    DE_5,    DE_6,    DE_7,    DE_8,    DE_9,    DE_0,      DE_SS,   DE_ACUT, KC_BSPC, KC_DEL,
      KC_TAB,     DE_Q,    DE_W,    DE_E,    DE_R,    DE_T,    DE_Z,    DE_U,    DE_I,    DE_O,    DE_P,      DE_UDIA, DE_PLUS,          TD(TD_HOME_END),
      KC_CAPS,    DE_A,    DE_S,    DE_D,    DE_F,    DE_G,    DE_H,    DE_J,    DE_K,    DE_L,    DE_ODIA,   DE_ADIA, DE_HASH, KC_ENT,  KC_PGUP,
      SC_LSPO, DE_LABK,    DE_Y,    DE_X,    DE_C,    DE_V,    DE_B,    DE_N,    DE_M,    DE_COMM, DE_DOT,    DE_MINS, SC_RSPC, KC_UP,   KC_PGDN,
      KC_LCTL, KC_LGUI, SC_LAPO,                    KC_SPC,                               SC_RAPC, MO(_LVL1_),         KC_LEFT, KC_DOWN, KC_RGHT
      ),
#else
  /* 0: ISO qwertz, SPACECADET but no TAPDANCE */
  [_LVL0_] = LAYOUT_65_iso_blocker(
      KC_ESC,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,      KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
      KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      KC_LBRC, KC_RBRC, KC_ENT,  KC_HOME,
      KC_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,   KC_QUOT, KC_NUHS,          KC_PGUP,
      SC_LSPO, KC_NUBS,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,    KC_SLSH, SC_RSPC, KC_UP,   KC_PGDN,
      KC_LCTL, KC_LGUI, SC_LAPO,                    KC_SPC,                               SC_RAPC, MO(_LVL1_),         KC_LEFT, KC_DOWN, KC_RGHT
      ),
#endif
  /* 1: Function key, multimedia control, layer switching board and LEADER */
  [_LVL1_] = LAYOUT_65_iso_blocker(
      KC_GRV,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     _______,    LGUI(KC_END),
      S(KC_GRV), _______,    _______,    _______,    _______,    _______,    _______,    _______, _______, _______, _______, _______, _______,                LGUI(KC_PAUSE),
      QK_BOOT,     TO(_LVL2_), TO(_LVL3_), TO(_LVL4_), TO(_LVL5_), TO(_LVL6_), TO(_LVL7_), _______, _______, _______, KC_BRIU, _______, KC_MUTE,    TO(_LVL0_), KC_VOLU,
      _______,   _______,    _______,    _______,    _______,    _______,    _______,    _______, _______, _______, KC_BRID, _______, S(KC_MUTE), KC_MPLY,    KC_VOLD,
      _______,   _______,    _______,                            QK_LEAD,                                  _______, _______,          KC_MPRV,    KC_MSTP,    KC_MNXT
      ),
  /* 2: Mouse layer and virtual/multiple desktop navigation */
  [_LVL2_] = LAYOUT_65_iso_blocker(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,      _______,
      _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______, _______, KC_PGDN, KC_PGUP, KC_PSCR, KC_WH_U, _______, _______,                    _______,
      _______, _______, KC_BTN1, KC_BTN2, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_WH_D, _______, _______,      TO(_LVL0_),   _______,
      _______, _______, _______, _______, _______, _______, _______, KC_HOME,  KC_END, _______, _______, _______, _______,      LCA(KC_UP),   LCA(KC_E),
      _______, _______, _______,                   _______,                            _______, _______,          LCA(KC_LEFT), LCA(KC_DOWN), LCA(KC_RGHT)
      ),
#ifdef DYNAMIC_MACRO_ENABLE
  /* 3: Dynamic macro, NUMPAD and settings */
  [_LVL3_] = LAYOUT_65_iso_blocker(
      _______, DM_PLY1, DM_PLY2, _______, _______,  _______, _______, _______, _______, KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS, _______,    _______,
      _______, DM_REC1, DM_REC2, _______, RGB_MOD,  RGB_HUI, RGB_SAI, RGB_VAI, _______, KC_P7,   KC_P8,   KC_P9,   KC_PMNS,             _______,
      _______, _______, _______, _______, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, TO(_LVL0_), _______,
      _______, _______, _______, _______, _______,  _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______,    _______,
      _______, _______, _______,                    RGB_TOG,                            KC_0,    KC_PCMM,          _______, _______,    _______
      ),
#else
  /* 3: NUMPAD and settings */
  [_LVL3_] = LAYOUT_65_iso_blocker(
      _______, _______, _______, _______, _______,  _______, _______, _______, _______, KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS, _______,    _______,
      _______, _______, _______, _______, RGB_MOD,  RGB_HUI, RGB_SAI, RGB_VAI, _______, KC_P7,   KC_P8,   KC_P9,   KC_PMNS,             _______,
      _______, _______, _______, _______, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, TO(_LVL0_), _______,
      _______, _______, _______, _______, _______,  _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______,    _______,
      _______, _______, _______,                    RGB_TOG,                            KC_0,    KC_PCMM,          _______, _______,    _______
      ),
#endif
  /* Gaming layer no TAPDANCE no SPACECADET simple QWERTZ layout for custom coloring */
  [_LVL4_] = LAYOUT_65_iso_blocker(
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,      KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      KC_LBRC, KC_RBRC,          KC_HOME,
      KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,   KC_QUOT, KC_NUHS, KC_ENT,  KC_PGUP,
      KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,    KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN,
      KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, TO(_LVL0_),         KC_LEFT, KC_DOWN, KC_RGHT
      ),
  /* 5: ISO qwerty DE 2 US Base Layer */
  [_LVL5_] = LAYOUT_65_iso_blocker(
      KC_ESC,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,       DE_MINS, DE_EQL,     KC_BSPC, KC_DEL,
      KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    DE_Y,    KC_U,    KC_I,    KC_O,    KC_P,       DE_LBRC, DE_RBRC,             KC_HOME,
      KC_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    DE_SCLN,    DE_QUOT, DE_BSLS,    KC_ENT,  KC_PGUP,
      MO(_LVL6_), DE_GRV,  DE_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    DE_COMM, DE_DOT,     DE_SLSH, MO(_LVL6_), KC_UP,   KC_PGDN,
      KC_LCTL,    KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, TO(_LVL0_),          KC_LEFT,    KC_DOWN, KC_RGHT
      ),
  /* 6: ISO qwerty DE 2 US Shifted Layer */
  [_LVL6_] = LAYOUT_65_iso_blocker(
      _______, DE_EXLM, DE_AT,   DE_HASH, DE_DLR,  DE_PERC, DE_CIRC, DE_AMPR, DE_ASTR, DE_LPRN, DE_RPRN,    DE_UNDS, DE_PLUS, _______, _______,
      _______, S(KC_Q), S(KC_W), S(KC_E), S(KC_R), S(KC_T), S(DE_Y), S(KC_U), S(KC_I), S(KC_O), S(KC_P),    DE_LCBR, DE_RCBR,          KC_END,
      KC_CAPS, S(KC_A), S(KC_S), S(KC_D), S(KC_F), S(KC_G), S(KC_H), S(KC_J), S(KC_K), S(KC_L), DE_COLN,    DE_DQUO, DE_PIPE, _______, _______,
      KC_LSFT, DE_TILD, S(DE_Z), S(KC_X), S(KC_C), S(KC_V), S(KC_B), S(KC_N), S(KC_M), DE_LABK, DE_RABK,    DE_QUES, KC_RSFT, _______, _______,
      _______, _______, _______,                   _______,                            _______, TO(_LVL0_),          _______, _______, _______
      ),
/* Led Type Lighting Layer functionally equivalent to _LVL0_ / layer 0 */
#ifdef TAP_DANCE_ENABLE
  /* 7: ISO DE qwertz, SPACECADET and TAPDANCE */
  [_LVL7_] = LAYOUT_65_iso_blocker(
      KC_ESC,     DE_1,    DE_2,    DE_3,    DE_4,    DE_5,    DE_6,    DE_7,    DE_8,    DE_9,    DE_0,      DE_SS,   DE_ACUT, KC_BSPC, KC_DEL,
      KC_TAB,     DE_Q,    DE_W,    DE_E,    DE_R,    DE_T,    DE_Z,    DE_U,    DE_I,    DE_O,    DE_P,      DE_UDIA, DE_PLUS,          TD(TD_HOME_END),
      KC_CAPS,    DE_A,    DE_S,    DE_D,    DE_F,    DE_G,    DE_H,    DE_J,    DE_K,    DE_L,    DE_ODIA,   DE_ADIA, DE_HASH, KC_ENT,  KC_PGUP,
      SC_LSPO, DE_LABK,    DE_Y,    DE_X,    DE_C,    DE_V,    DE_B,    DE_N,    DE_M,    DE_COMM, DE_DOT,    DE_MINS, SC_RSPC, KC_UP,   KC_PGDN,
      KC_LCTL, KC_LGUI, SC_LAPO,                    KC_SPC,                               SC_RAPC, TO(_LVL0_),         KC_LEFT, KC_DOWN, KC_RGHT
      ),
#else
  /* 7: ISO qwertz, SPACECADET but no TAPDANCE */
  [_LVL7_] = LAYOUT_65_iso_blocker(
      KC_ESC,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,      KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
      KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      KC_LBRC, KC_RBRC,          KC_HOME,
      KC_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,   KC_QUOT, KC_NUHS, KC_ENT,  KC_PGUP,
      SC_LSPO, KC_NUBS,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,    KC_SLSH, SC_RSPC, KC_UP,   KC_PGDN,
      KC_LCTL, KC_LGUI, SC_LAPO,                    KC_SPC,                               SC_RAPC, TO(_LVL0_),         KC_LEFT, KC_DOWN, KC_RGHT
      ),
#endif


  /*template
    [_UL] = LAYOUT_65_iso_blocker(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TO(0),   _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,                   _______,                            _______, _______,          _______, _______, _______
    )
    */
};


// layer color and type
const uint8_t PROGMEM ledmap[][4] = {
  // LEDs off on Layer 0
  //[_LVL0_] = {{0, 0, 0},       LYR_SOLID},
  [_LVL0_] = {C_HSV_WINERED,   LYR_SOLID},
  [_LVL1_] = {HSV_RED,         LYR_TRANS},
  [_LVL2_] = {HSV_MAGENTA,     LYR_BLACK},
  [_LVL3_] = {HSV_PURPLE,      LYR_BLACK},
  [_LVL4_] = {C_HSV_DARKGOLD,  LYR_SOLID},
  [_LVL5_] = {C_HSV_DARKBLUE,  LYR_SOLID},
  [_LVL6_] = {HSV_BLUE,        LYR_TRANS},
  [_LVL7_] = {C_HSV_WINERED,   LYR_SOLID}
};


void keyboard_post_init_user(void) {
  // Call the post init code.
#ifdef CONSOLE_ENABLE
  debug_enable=true;
  debug_matrix=true;
#endif
  //rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
  //rgb_matrix_set_flags(LED_FLAG_NONE);
  rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
  //rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
  //rgb_matrix_sethsv(HSV_OFF);
  //rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
  //rgb_matrix_sethsv_noeeprom(HSV_OFF);
  //rgb_matrix_set_color_all(RGB_BLACK);
  rgb_matrix_enable();
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    // useful for getting matrix right
    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %u, time: %u, interrupt: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif

    switch (keycode) {
      case RGB_TOG:
        if (record->event.pressed) {
          switch (rgb_matrix_get_flags()) {
            case LED_FLAG_ALL: {
               rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
               rgb_matrix_set_color_all(RGB_BLACK);
            }
            break;
            case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
               rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
               rgb_matrix_set_color_all(RGB_BLACK);
            }
            break;
            case LED_FLAG_UNDERGLOW: {
               rgb_matrix_set_flags(LED_FLAG_NONE);
               rgb_matrix_disable_noeeprom();
            }
            break;
            default: {
               rgb_matrix_set_flags(LED_FLAG_ALL);
               rgb_matrix_enable_noeeprom();
            }
            break;
          }
        }
        return false;
      default:
        return true; // Process all other keycodes normally
  }
}


void set_led_color_by_hsv(int ledkey, uint8_t h_in, uint8_t s_in, uint8_t v_in){
    HSV hsv = { .h = h_in, .s = s_in, .v = v_in};
    RGB rgb = hsv_to_rgb(hsv);
    float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
    rgb_matrix_set_color(ledkey, f * rgb.r, f * rgb.g, f * rgb.b);
}

void set_led_color_by_layer(int layer, int ledkey){
    set_led_color_by_hsv(ledkey, pgm_read_byte(&ledmap[layer][0]),
                              pgm_read_byte(&ledmap[layer][1]),
                              pgm_read_byte(&ledmap[layer][2]));
}

void set_ledkey_by_layer_type(int layer, int ledkey, uint16_t key){
    if (rgb_matrix_get_flags() != LED_FLAG_ALL){
        if ( key == KC_TRNS ) {
            if ((pgm_read_byte(&ledmap[layer][3]) == LYR_TRANS) && (layer > 0)){
                // this key is transparent and the layer below does something
                // - light it up in  (lower) layer-1 specific color
                set_led_color_by_layer(layer-1, ledkey);
            }
            if (pgm_read_byte(&ledmap[layer][3]) == LYR_BLACK){
                // this key is transparent but the lower layer is not intended
                // to be used, it still works but not intended; type BLACK
                set_led_color_by_hsv(ledkey, HSV_BLACK);
            }
        } else {
            // this key does something - light it up in layer specific color
            // regular key and SOLID or BLACK as layer type
            set_led_color_by_layer(layer, ledkey);
        }
    }
}

void set_caps_lock(int layer) {
    int caps_lock_led = 30;
    led_t host_leds = host_keyboard_led_state();
    if (host_leds.caps_lock) {
        set_led_color_by_hsv(caps_lock_led, HSV_WHITE);
    } else {
        // if capslock is not pressed don't clear it,
        // it might be used for displaying led pattern
        if((rgb_matrix_get_flags() != LED_FLAG_ALL)) {
            // or to keep the correct lighting on for the layer that use all keys
            // on all other layers turn the led off, so only switch it of when
            // layer is BLACK
            if(pgm_read_byte(&ledmap[layer][3]) == LYR_BLACK){
              set_led_color_by_hsv(caps_lock_led, HSV_BLACK);
            }
        }
    }
}

void set_layer_color(int layer) {
    // key specific lighting
    int ledkey=0;
    for (int keyindex=0; keyindex<MATRIX_COLS*MATRIX_ROWS;keyindex++) {
        uint8_t row = keyindex/MATRIX_COLS;
        uint8_t col = (keyindex-(keyindex/MATRIX_COLS)*MATRIX_COLS);
        uint16_t key=pgm_read_word(&keymaps[layer][row][col]);

        // continue if this is not a valid key
        if (key==KC_NO) { continue; }

        // handle layer specific coloring
        set_ledkey_by_layer_type(layer, ledkey, key);
        /* === below this function add custom overriding ledkey lighting === */

        // gaming layer with highlighted keys
        //if (IS_LAYER_ON(_LVL4_)) {
        if (layer == _LVL4_) {
            if((key==KC_W) || (key==KC_A) || (key==KC_S) || (key==KC_D)) {
                set_led_color_by_hsv(ledkey, HSV_GOLD);
            }
            if((key==KC_R) || (key==KC_SPC) || (key==KC_LSFT) || (key==KC_LCTL)) {
                set_led_color_by_hsv(ledkey, HSV_GOLDENROD);
            }
        }

        // color testing layer
        /*if (layer == _LVL7_) {
        switch (ledkey) {
          case 16: {
                set_led_color_by_hsv(ledkey, HSV_AZURE);
              }
              break;
          case 17: {
                set_led_color_by_hsv(ledkey, HSV_BLUE);
              }
              break;
          case 18: {
                set_led_color_by_hsv(ledkey, HSV_CHARTREUSE);
              }
              break;
          case 19: {
                set_led_color_by_hsv(ledkey, HSV_CORAL);
              }
              break;
          case 20: {
                set_led_color_by_hsv(ledkey, HSV_CYAN);
              }
              break;
          case 21: {
                set_led_color_by_hsv(ledkey, HSV_GOLD);
              }
              break;
          case 22: {
                set_led_color_by_hsv(ledkey, HSV_GOLDENROD);
              }
              break;
          case 23: {
                set_led_color_by_hsv(ledkey, HSV_MAGENTA);
              }
              break;
          case 24: {
                set_led_color_by_hsv(ledkey, HSV_ORANGE);
              }
              break;
          case 25: {
                set_led_color_by_hsv(ledkey, HSV_PINK);
              }
              break;
          case 26: {
                set_led_color_by_hsv(ledkey, HSV_RED);
              }
              break;
          case 27: {
                set_led_color_by_hsv(ledkey, HSV_SPRINGGREEN);
              }
              break;
          case 32: {
                set_led_color_by_hsv(ledkey, HSV_MAGENTA);
              }
              break;
          case 33: {
                set_led_color_by_hsv(ledkey, HSV_TEAL);
              }
              break;
          case 34: {
                set_led_color_by_hsv(ledkey, HSV_TURQUOISE);
              }
              break;
          case 35: {
                set_led_color_by_hsv(ledkey, HSV_WHITE);
              }
              break;
          case 36: {
                set_led_color_by_hsv(ledkey, HSV_YELLOW);
              }
              break;
          case 37: {
                set_led_color_by_hsv(ledkey, HSV_PURPLE);
              }
              break;
          case 38: {
                set_led_color_by_hsv(ledkey, HSV_GREEN);
              }
              break;
          default: {
              }
              break;
            }
        }*/
        ledkey++;
    }
    // non key specific lighting instead led flag based
    if (layer == _LVL7_){
        for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; ++i) {
            if (HAS_ANY_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
                set_led_color_by_hsv(i, C_HSV_DARKGOLD);
            }
            if (HAS_ANY_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
                set_led_color_by_hsv(i, HSV_BLACK);
            }
            if (HAS_ANY_FLAGS(g_led_config.flags[i], LED_FLAG_KEYLIGHT)) {
                set_led_color_by_layer(layer, i);
            }
        }
    }

    return;
}

bool rgb_matrix_indicators_user(void) {
    int layer = get_highest_layer(layer_state);
    set_layer_color(layer);
    set_caps_lock(layer);
    return false;
}

#ifdef LEADER_ENABLE
LEADER_EXTERNS();

void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_ONE_KEY(KC_F) {
          // Anything you can do in a macro.
          SEND_STRING("QMK is awesome.");
        }
        SEQ_TWO_KEYS(KC_D, KC_D) {
          SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
        }
        SEQ_TWO_KEYS(KC_S, KC_S) {
          SEND_STRING(SS_LCTL("v"));
        }
        SEQ_THREE_KEYS(KC_D, KC_D, KC_S) {
          SEND_STRING("https://start.duckduckgo.com\n");
        }
    }
}
#endif
