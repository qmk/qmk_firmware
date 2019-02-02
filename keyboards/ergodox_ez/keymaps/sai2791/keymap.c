#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_german.h"
#include "keymap_nordic.h"

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  RGB_SLD,

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | TO(3)|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L1  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L2|  LGui  |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv/L1|  '"  |AltShf| Left | Right|                                       |  Up  | Down |   [  |   ]  | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
  [0] = LAYOUT_ergodox(
                      KC_EQUAL,KC_1,KC_2,KC_3,KC_4,KC_5,KC_LEFT,
                      KC_DELETE,KC_Q,KC_W,KC_E,KC_R,KC_T,TG(1),
                      KC_BSPACE,KC_A,KC_S,KC_D,KC_F,KC_G,
                      KC_LSHIFT,CTL_T(KC_Z),KC_X,KC_C,KC_V,KC_B,KC_HYPR,
                      LT(1,KC_GRAVE),KC_QUOTE,LALT(KC_LSHIFT),KC_LEFT,KC_RIGHT,
                                                      ALT_T(KC_APPLICATION),KC_LGUI,
                                                      KC_HOME,
                                                      KC_SPACE,KC_BSPACE,KC_END,

                      TO(3),KC_6,KC_7,KC_8,KC_9,KC_0,KC_MINUS,
                      TG(1),KC_Y,KC_U,KC_I,KC_O,KC_P,KC_BSLASH,
                      KC_H,KC_J,KC_K,KC_L,LT(2,KC_SCOLON),GUI_T(KC_QUOTE),
                      KC_MEH,KC_N,KC_M,KC_COMMA,KC_DOT,RCTL_T(KC_SLASH),KC_RSHIFT,
                      KC_UP,KC_DOWN,KC_LBRACKET,KC_RBRACKET,MO(1),
                                                        KC_LCTRL,CTL_T(KC_ESCAPE),
                                                        KC_PGUP,
                                                        KC_PGDOWN,KC_TAB,KC_ENTER),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ESC   |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  | LockScr|
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |desk_l|desk_r|                                       |   0  |      |   .  |   =  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
  [1] = LAYOUT_ergodox(
                                           KC_ESCAPE,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_TRANSPARENT,
                                           KC_TRANSPARENT,KC_EXLM,KC_AT,KC_LCBR,KC_RCBR,KC_PIPE,KC_TRANSPARENT,
                                           KC_TRANSPARENT,KC_HASH,KC_DLR,KC_LPRN,KC_RPRN,KC_GRAVE,
                                           KC_TRANSPARENT,KC_PERC,KC_CIRC,KC_LBRACKET,KC_RBRACKET,KC_TILD,KC_TRANSPARENT,
                                           KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,DESK_L,DESK_R,
                                                                                RGB_MOD,KC_TRANSPARENT,
                                                                                KC_TRANSPARENT,
                                                                                RGB_VAD,RGB_VAI,KC_TRANSPARENT,

                                           KC_TRANSPARENT,KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,
                                           KC_TRANSPARENT,KC_UP,KC_7,KC_8,KC_9,KC_ASTR,KC_F12,
                                           KC_DOWN,KC_4,KC_5,KC_6,KC_TRANSPARENT,KC_TRANSPARENT,
                                           KC_TRANSPARENT,KC_AMPR,KC_1,KC_2,KC_3,KC_BSLASH,KC_LOCKSCR,
                                           KC_0,KC_NO,KC_DOT,KC_EQUAL,KC_TRANSPARENT,
                                                                                RGB_TOG,RGB_SLD,
                                                                                KC_TRANSPARENT,
                                                                                KC_TRANSPARENT,RGB_HUD,RGB_HUI),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | BRGTUP |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | BRGTDW |      |      | MsUp |      |      |      |           |      |      |      |      |      | Play |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      | //// |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
  [2] = LAYOUT_ergodox(
                      KC_BRIU,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
                      KC_BRID,KC_TRANSPARENT,KC_TRANSPARENT,KC_MS_UP,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
                      KC_TRANSPARENT,KC_TRANSPARENT,KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT,KC_TRANSPARENT,
                      KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
                      KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MS_BTN1,KC_MS_BTN2,
                                                           KC_TRANSPARENT,KC_TRANSPARENT,
                                                           KC_TRANSPARENT,
                                                           KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,

                      KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,MT(MOD_HYPR, KC_RIGHT),
                      KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MEDIA_PLAY_PAUSE,MT(MOD_MEH, KC_RIGHT),
                      KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
                      KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_TRANSPARENT,KC_TRANSPARENT,
                      KC_AUDIO_VOL_UP,KC_AUDIO_VOL_DOWN,KC_AUDIO_MUTE,KC_TRANSPARENT,KC_TRANSPARENT,
                                                           KC_TRANSPARENT,KC_TRANSPARENT,
                                                           KC_TRANSPARENT,
                                                           KC_TRANSPARENT,KC_TRANSPARENT,KC_WWW_BACK),
/* Keymap 2: World of Warcraft
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ESC   |  F6  |  F7  |  ]   |  F9  |  =   |  T   |           |  L0  |      |      |      |      |      |  C/F1  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   3    |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |      |      |      |      |  =   |  C/F2  |
 * |--------+------+------+------+------+------|  Y   |           |      |------+------+------+------+------+--------|
 * |  TAB   |  1   |   2  |   4  |   5  |   6  |------|           |------|      |      |      |      |      |  C/F3  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | SPACE  |      |      |      |   8  |   9  |  7   |           |      |      |      | Prev | Next |      |  C/F4  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LCTL |  B   |      |      |      |                                       |VolUp |VolDn | Mute |      | A/F2 |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | F10  | F12  |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | A/F2 |       |      |      |      |
 *                                 | F11  |  F8  |------|       |------|      |      |
 *                                 |      |      |  0   |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// World of Warcraft
  [3] = LAYOUT_ergodox(
                      KC_ESCAPE,KC_F6,KC_F7,KC_RBRACKET,KC_F9,KC_EQUAL,KC_T,
                      KC_3,KC_1,KC_F2,KC_F3,KC_F4,KC_F5,KC_Y,
                      KC_TAB,KC_F1,KC_2,KC_4,KC_5,KC_6,
                      KC_SPACE,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_8,KC_9,KC_7,
                      KC_LCTRL,KC_TRANSPARENT,KC_B,KC_TRANSPARENT,KC_TRANSPARENT,
                                                           KC_F10,KC_F12,
                                                           LALT(KC_F1),
                                                           KC_F11,KC_F8,KC_0,

                      TO(0),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,LCTL(KC_F1),
                      KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_EQUAL,LCTL(KC_F2),
                      KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,LCTL(KC_F3),
                      KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,LCTL(KC_F4),
                      KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,LALT(KC_F2),
                                                           KC_TRANSPARENT,KC_TRANSPARENT,
                                                           KC_TRANSPARENT,
                                                           KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

};

rgb_config_t rgb_matrix_config;

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [1] = { {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228}, {163,228,228} },

    [2] = { {154,234,246}, {154,234,246}, {154,234,246}, {154,234,246}, {154,234,246}, {154,234,246}, {154,234,246}, {154,234,246}, {154,234,246}, {85,203,158}, {154,234,246}, {154,234,246}, {154,234,246}, {154,234,246}, {154,234,246}, {154,234,246}, {154,234,246}, {85,203,158}, {85,203,158}, {154,234,246}, {243,222,234}, {243,222,234}, {243,222,234}, {154,234,246}, {154,234,246}, {154,234,246}, {154,234,246}, {154,234,246}, {154,234,246}, {154,234,246}, {154,234,246}, {243,222,234}, {154,234,246}, {154,234,246}, {154,234,246}, {243,222,234}, {243,222,234}, {243,222,234}, {154,234,246}, {154,234,246}, {154,234,246}, {154,234,246}, {154,234,246}, {154,234,246}, {85,203,158}, {85,203,158}, {154,234,246}, {154,234,246} },

    [3] = { {172,249,254}, {172,249,254}, {172,249,254}, {172,249,254}, {172,249,254}, {172,249,254}, {172,249,254}, {172,249,254}, {172,249,254}, {85,203,158}, {172,249,254}, {172,249,254}, {172,249,254}, {172,249,254}, {172,249,254}, {172,249,254}, {172,249,254}, {172,249,254}, {172,249,254}, {172,249,254}, {172,249,254}, {172,249,254}, {172,249,254}, {172,249,254}, {85,203,158}, {172,249,254}, {85,203,158}, {32,176,255}, {32,176,255}, {32,176,255}, {32,176,255}, {32,176,255}, {85,203,158}, {32,176,255}, {10,225,255}, {10,225,255}, {10,225,255}, {172,249,254}, {32,176,255}, {243,222,234}, {243,222,234}, {172,249,254}, {172,249,254}, {172,249,254}, {172,249,254}, {172,249,254}, {85,203,158}, {172,249,254} },

};

void matrix_init_user(void) {
  rgb_matrix_config.raw = eeprom_read_dword(EECONFIG_RGB_MATRIX);
}

void set_leds_color( int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    uint8_t val = pgm_read_byte(&ledmap[layer][i][2]);
    // if the brightness of the led is set to 0 in the map,
    // the value is not overriden with global controls, allowing the led
    // to appear turned off
    HSV hsv = { .h = pgm_read_byte(&ledmap[layer][i][0]), .s = pgm_read_byte(&ledmap[layer][i][1]), .v = val == 0 ? 0 : rgb_matrix_config.val};
    RGB rgb = hsv_to_rgb( hsv );
    rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
  }
}

void rgb_matrix_indicators_user(void) {
  uint32_t mode = rgblight_get_mode();
  if(mode == 1) {
    uint8_t layer = biton32(layer_state);
    switch (layer) {
      case 1:
        set_leds_color(1);
        break;
      case 2:
        set_leds_color(2);
        break;
      case 3:
        set_leds_color(3);
        break;
    }
  }
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
      break;
  }
  return true;
}

uint32_t layer_state_set_user(uint32_t state) {

    uint8_t layer = biton32(state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      case 1:
        ergodox_right_led_1_on();
        break;
      case 2:
        ergodox_right_led_2_on();
        break;
      case 3:
        ergodox_right_led_3_on();
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      default:
        break;
    }
    return state;

};
