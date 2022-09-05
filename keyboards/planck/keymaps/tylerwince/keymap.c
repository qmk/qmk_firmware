#include QMK_KEYBOARD_H
#include "muse.h"

enum planck_keycodes {
  RGB_SLD = SAFE_RANGE,
  TOGGLE_LAYER_COLOR,
};

enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
  _LAYER4,
};

//Tap Dance Declarations
enum {
  TD_SEMI_COLON,
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SEMI_COLON] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_planck_grid(
            /* _BASE
             * ,-----------------------------------------------------------------------------------.
             * | Tab  |   '  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  |   /  |
             * |------+------+------+------+------+-------------+------+------+------+------+------|
             * |CtlEsc|   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  | Bksp |
             * |------+------+------+------+------+------|------+------+------+------+------+------|
             * |      |   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
             * |------+------+------+------+------+------+------+------+------+------+------+------|
             * |      | Ctrl | Alt  | GUI  |LOWER | Shift/Space | RAISE|      |      |      |      |
             * `-----------------------------------------------------------------------------------'
             */
          KC_TAB,            KC_QUOTE,          KC_COMMA, KC_DOT,  KC_P,  KC_Y,             KC_F,  KC_G,  KC_C,    KC_R,    KC_L,    KC_SLASH,
          LCTL_T(KC_ESCAPE), KC_A,              KC_O,     KC_E,    KC_U,  KC_I,             KC_D,  KC_H,  KC_T,    KC_N,    KC_S,    KC_BSPACE,
          _______,           TD(TD_SEMI_COLON), KC_Q,     KC_J,    KC_K,  KC_X,             KC_B,  KC_M,  KC_W,    KC_V,    KC_Z,    KC_ENTER,
          _______,           KC_LCTRL,          KC_LALT,  KC_LGUI, LOWER, LSFT_T(KC_SPACE), KC_NO, RAISE, _______, _______, _______, _______
          ),

  [_LOWER] = LAYOUT_planck_grid(
            /* _LOWER
             * ,-----------------------------------------------------------------------------------.
             * |  `   |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   \  |
             * |------+------+------+------+------+-------------+------+------+------+------+------|
             * |  ~   |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |   |  |
             * |------+------+------+------+------+------|------+------+------+------+------+------|
             * |      |      |      |      |      |      |      |   _  |   +  |   {  |   }  |Delete|
             * |------+------+------+------+------+------+------+------+------+------+------+------|
             * |      | Ctrl | Alt  | GUI  |LOWER | Shift/Space | RAISE|      |   [  |   ]  |      |
             * `-----------------------------------------------------------------------------------'
             */
          KC_GRAVE, KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,        KC_0,        KC_BSLASH,
          KC_TILD,  KC_EXLM,  KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN,     KC_RPRN,     KC_PIPE,
          _______,  _______,  _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR,     KC_RCBR,     KC_DELETE,
          _______,  KC_LCTRL, KC_LALT, KC_LGUI, _______, _______, KC_NO,   _______, _______, KC_LBRACKET, KC_RBRACKET, _______
          ),

  [_RAISE] = LAYOUT_planck_grid(
            /* _RAISE
             * ,-----------------------------------------------------------------------------------.
             * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      |      |      |      |RIGHT |      |
             * |------+------+------+------+------+-------------+------+------+------+------+------|
             * |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      | LEFT |      |      |      |Delete|
             * |------+------+------+------+------+------|------+------+------+------+------+------|
             * |      |      |      | DOWN |  UP  |      |      |   -  |   =  |      |      |      |
             * |------+------+------+------+------+------+------+------+------+------+------+------|
             * |THINGS|1PASS |      |      |LOWER | Shift/Space | RAISE|      |      |      |      |
             * `-----------------------------------------------------------------------------------'
             */

          KC_F1,          KC_F2,           KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, _______,  _______,  _______, KC_RIGHT, _______,
          KC_F7,          KC_F8,           KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_LEFT,  _______,  _______, _______,  KC_DELETE,
          _______,        _______,         _______, KC_DOWN, KC_UP,   _______, _______, KC_MINUS, KC_EQUAL, _______, _______,  _______,
          LALT(KC_SPACE), LGUI(KC_BSLASH), _______, _______, _______, _______, KC_NO,   _______,  _______,  _______, _______,  _______
          ),

  [_ADJUST] = LAYOUT_planck_grid(
            /* _LOWER
             * ,-----------------------------------------------------------------------------------.
             * |Reset |      |      |      |      |WIN-TL|WIN-TR|      |      |      |WIN-R |      |
             * |------+------+------+------+------+-------------+------+------+------+------+------|
             * |      |      |      |      |      |WIN-BL|WIN-BR|WIN-L |      |      |      |      |
             * |------+------+------+------+------+------|------+------+------+------+------+------|
             * |      |      |      |WIN-B |WIN-T |      |      |      |      |      |      |      |
             * |------+------+------+------+------+------+------+------+------+------+------+------|
             * | BASE |LAYER4|      |      |LOWER | Shift/Space | RAISE|VOL-DN| BR-DN|BR-UP |VOL-UP|
             * `-----------------------------------------------------------------------------------'
             */

          QK_BOOT, _______, _______, _______,          _______,          LALT(LCTL(KC_7)), LALT(LCTL(KC_8)), _______,          _______,           _______, LALT(LCTL(KC_L)), _______,
          _______, _______, _______, _______,          _______,          LALT(LCTL(KC_U)), LALT(LCTL(KC_I)), LALT(LCTL(KC_H)), _______,           _______, _______,          _______,
          _______, _______, _______, LALT(LCTL(KC_J)), LALT(LCTL(KC_K)), _______,          _______,          _______,          _______,           _______, _______,          LALT(LCTL(KC_ENTER)),
          TO(0),   TO(4),   _______, _______,          _______,          _______,          KC_NO,            _______,          KC_AUDIO_VOL_DOWN, KC_F14,  KC_F15,           KC_AUDIO_VOL_UP
          ),

  [_LAYER4] = LAYOUT_planck_grid(
            /* _LOWER
             * ,-----------------------------------------------------------------------------------.
             * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   '  |
             * |------+------+------+------+------+-------------+------+------+------+------+------|
             * |CtlEsc|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | Bksp |
             * |------+------+------+------+------+------|------+------+------+------+------+------|
             * |      |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
             * |------+------+------+------+------+------+------+------+------+------+------+------|
             * |      | Ctrl | Alt  | GUI  |LOWER | Shift/Space | RAISE|      |      |      |      |
             * `-----------------------------------------------------------------------------------'
             */

          KC_TAB,            KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,             KC_Y,  KC_U,  KC_I,     KC_O,    KC_P,      KC_QUOTE,
          LCTL_T(KC_ESCAPE), KC_A,    KC_S,    KC_D,    KC_F,  KC_G,             KC_H,  KC_J,  KC_K,     KC_L,    KC_SCOLON, KC_BSPACE,
          _______,           KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,             KC_N,  KC_M,  KC_COMMA, KC_DOT,  KC_SLASH,  KC_ENTER,
          _______,           KC_LCTL, KC_LALT, KC_LGUI, LOWER, LSFT_T(KC_SPACE), KC_NO, RAISE, _______,  _______, _______,   _______
          ),

};

extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;
bool disable_layer_color = 0;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [0] = { {32,255,234}, {32,255,234}, {12,225,241}, {12,225,241}, {0,204,255}, {0,204,255}, {169,120,255}, {169,120,255}, {169,120,255}, {146,224,255}, {146,224,255}, {146,224,255},
            {32,255,234}, {32,255,234}, {12,225,241}, {12,225,241}, {0,204,255}, {0,204,255}, {169,120,255}, {169,120,255}, {169,120,255}, {146,224,255}, {146,224,255}, {146,224,255},
            {32,255,234}, {32,255,234}, {12,225,241}, {12,225,241}, {0,204,255}, {0,204,255}, {169,120,255}, {169,120,255}, {169,120,255}, {146,224,255}, {146,224,255}, {146,224,255},
            {32,255,234}, {32,255,234}, {12,225,241}, {12,225,241}, {0,204,255}, {0,0,0},     {169,120,255}, {169,120,255}, {146,224,255}, {146,224,255}, {146,224,255} },

    [1] = { {0,204,255}, {0,204,255}, {0,204,255}, {0,204,255}, {0,204,255}, {0,204,255}, {0,204,255}, {0,204,255}, {0,204,255}, {0,204,255}, {0,204,255}, {0,204,255},
            {0,204,255}, {0,204,255}, {0,204,255}, {0,204,255}, {0,204,255}, {0,204,255}, {0,204,255}, {0,204,255}, {0,204,255}, {0,204,255}, {0,204,255}, {0,204,255},
            {0,0,0},     {0,0,0},     {0,0,0},     {0,0,0},     {0,0,0},     {0,0,0},     {0,0,0},     {0,204,255}, {0,204,255}, {0,204,255}, {0,204,255}, {0,204,255},
            {0,0,0},     {0,204,255}, {0,204,255}, {0,204,255}, {0,204,255}, {0,0,0},     {0,0,0},     {0,0,0},     {0,204,255}, {0,204,255}, {0,0,0} },

    [2] = { {169,120,255}, {169,120,255}, {169,120,255}, {169,120,255}, {169,120,255}, {169,120,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {169,120,255}, {0,0,0},
            {169,120,255}, {169,120,255}, {169,120,255}, {169,120,255}, {169,120,255}, {169,120,255}, {0,0,0}, {169,120,255}, {0,0,0}, {0,0,0}, {0,0,0}, {169,120,255},
            {0,0,0}, {0,0,0}, {0,0,0}, {169,120,255}, {169,120,255}, {0,0,0}, {0,0,0}, {169,120,255}, {169,120,255}, {0,0,0}, {0,0,0}, {0,0,0},
            {169,120,255}, {169,120,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {169,120,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [4] = { {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
  if (g_suspend_state || disable_layer_color) { return; }
  switch (get_highest_layer(layer_state)) {
    case 0:
      set_layer_color(0);
      break;
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 4:
      set_layer_color(4);
      break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
    case RGB_TOG:
  if (record->event.pressed) {
    if (rgb_matrix_config.val) {
      rgb_matrix_sethsv(rgb_matrix_config.hue, rgb_matrix_config.sat, 0);
    } else {
      rgb_matrix_sethsv(rgb_matrix_config.hue, rgb_matrix_config.sat, 255);
    }
  }
  return false;
    case TOGGLE_LAYER_COLOR:
      if (record->event.pressed) {
        disable_layer_color ^= 1;
      }
      return false;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (muse_mode) {
        if (IS_LAYER_ON(_RAISE)) {
            if (clockwise) {
                muse_offset++;
            } else {
                muse_offset--;
            }
        } else {
            if (clockwise) {
                muse_tempo+=1;
            } else {
                muse_tempo-=1;
            }
        }
    } else {
        if (clockwise) {
        #ifdef MOUSEKEY_ENABLE
            tap_code(KC_MS_WH_DOWN);
        #else
            tap_code(KC_PGDN);
        #endif
        } else {
        #ifdef MOUSEKEY_ENABLE
            tap_code(KC_MS_WH_UP);
        #else
            tap_code(KC_PGUP);
        #endif
        }
    }
    return true;
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
    case RAISE:
    case LOWER:
        return false;
    default:
        return true;
    }
}
layer_state_t layer_state_set_user(layer_state_t state) {
    palClearPad(GPIOB, 8);
    palClearPad(GPIOB, 9);
    uint8_t layer = get_highest_layer(state);
    switch (layer) {
        case _LOWER:
            palSetPad(GPIOB, 9);
            break;
        case _RAISE:
            palSetPad(GPIOB, 8);
            break;
        case _ADJUST:
            palSetPad(GPIOB, 9);
            palSetPad(GPIOB, 8);
            break;
        default:
            break;
    }
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
