#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "keymap_bepo.h"
#include "keymap_german.h"

#define BASE    0 // dvorak layout (default)
#define AUX     1 // auxiliary keys

#define BEPO 2 // default layer
#define FNAV 3 // function / navigation keys
#define NUM 4 // numeric keypad keys
#define MSE 5 // mouse keys
#define SYMB 6 // mouse keys
#define MDIA 7 // mouse keys

#define KP_00 0
#define CA_Fx 1

// MACROS
/* #define OBRACE 0 // key { or shift */
/* #define CBRACE 1 // key } or shift */
/* #define OBRACK 2 // key [ or left alt */
/* #define CBRACK 3 // key ] or left alt */
/* #define CAPS   4 // caps lock */

// LEDS
#define USB_LED_NUM_LOCK    0
#define USB_LED_CAPS_LOCK   1
#define USB_LED_SCROLL_LOCK 2
#define USB_LED_COMPOSE     3
#define USB_LED_KANA        4

// TIMERS
#define KEY_TAP_FAST 85
#define KEY_TAP_SLOW 95

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap 0: Base layer
   *
   * ,--------------------------------------------------.                                  ,--------------------------------------------------.
   * |   $    |   "  |   <  |   >  |   (  |   )  |Delete|                                  |ScroLo|   @  |   +  |   -  |   /  |   *  |   =    |
   * |--------+------+------+------+------+-------------|                                  |------+------+------+------+------+------+--------|
   * |   %    |   B  |E_ACUT|   P  |   O  |E_GRAV|Backsp|                                  |CapsLo|   ^  |   V  |   D  |   L  |   J  |   Z    |
   * |--------+------+------+------+------+------|  ace |                                  |      |------+------+------+------+------+--------|
   * |   W    |   A  |   U  |   I  |   E  |   ,  |------|                                  |------|   C  |   T  |   S  |   R  |   N  |   M    |
   * |--------+------+------+------+------+------|  Tab |                                  | NumLo|------+------+------+------+------+--------|
   * | E_CIRC |A_GRAV|   Y  |   X  |   .  |   K  |      |                                  |      |   '  |   Q  |   G  |   H  |   F  | C_CEDIL|
   * `--------+------+------+------+------+-------------,-------------.      ,-------------`-------------+------+------+------+------+--------'
   *   |QWERTY|      |LSuper| LCtrl|  LAlt|             |Escape| L_Mse|      |      |Insert|             | AltGr| RCtrl|RSuper|PrntSc| Pause|
   *   `----------------------------------'      ,------|------|------|      |------+------+------.      `----------------------------------'
   *                                             |      |      | L_Num|      | CA_Fx|      |      |
   *                                             | Space|LShift|------|      |------|RShift|Enter |
   *                                             |      |      |L_FNav|      |L_FNav|      |      |
   *                                             `--------------------'      `--------------------'
   */
  [BEPO] = KEYMAP(
                  // Left hand
                  BP_DOLLAR,	BP_DQOT,	BP_LGIL,	BP_RGIL,	BP_LPRN,	BP_RPRN,	KC_DEL,
                  BP_PERCENT,	BP_B,		BP_E_ACUTE,	BP_P,		BP_O,		BP_E_GRAVE,	KC_BSPC,
                  BP_W,		BP_A,		BP_U,		BP_I,		BP_E,		BP_COMMA,
                  BP_ECRC,	BP_A_GRAVE,	BP_Y,		BP_X,		BP_DOT,		BP_K,		KC_TAB,
                  TG(QWER),	KC_NO,		KC_LGUI,	KC_LCTL,	KC_LALT,
                  KC_ESC,		MO(MSE),
                  MO(NUM),
                  KC_SPC,		KC_LSHIFT,	MO(FNAV),
                  // Right hand
                  KC_SLCK,	BP_AT,		BP_PLUS,	BP_MINUS,	BP_SLASH,	BP_ASTR,	BP_EQUAL,
                  KC_CAPSLOCK,	BP_DCRC,	BP_V,		BP_D,		BP_L,		BP_J,		BP_Z,
                  BP_C,		BP_T,		BP_S,		BP_R,		BP_N,		BP_M,
                  KC_NUMLOCK,	BP_APOS,	BP_Q,		BP_G,		BP_H,		BP_F,		BP_CCED,
                  BP_ALGR,	KC_RCTL,	KC_RGUI,	KC_PSCREEN,	KC_PAUSE,
                  KC_NO,		KC_INS,
                  M(CA_Fx),
                  MO(FNAV),	KC_RSHIFT,	KC_ENTER),

  /* Keymap 4: function / navigation layer
   *
   * ,--------------------------------------------------.                                  ,--------------------------------------------------.
   * |        |  F1  |  F2  |  F3  |  F4  |  F5  |VolMut|                                  |      |  F6  |  F7  |  F8  |  F9  |  F10 |        |
   * |--------+------+------+------+------+-------------|                                  |------+------+------+------+------+------+--------|
   * |        |      |      |      |      |      |VolDwn|                                  |      | PgUp | Home |  Up  |  End |  F11 |        |
   * |--------+------+------+------+------+------|      |                                  |      |------+------+------+------+------+--------|
   * |        |      |      |      |      |      |------|                                  |------| PgDn | Left | Down | Right|  F12 |        |
   * |--------+------+------+------+------+------| VolUp|                                  |      |------+------+------+------+------+--------|
   * |        | Undo |  Cut | Copy | Paste|      |      |                                  |      |      |      |      |      |      |        |
   * `--------+------+------+------+------+-------------,-------------.      ,-------------`-------------+------+------+------+------+--------'
   *   |      |      |      |      |      |             |      |      |      |      |      |             |      |      |      |      |      |
   *   `----------------------------------'      ,------|------|------|      |------+------+------.      `----------------------------------'
   *                                             |      |      |      |      |      |      |      |
   *                                             |      |      |------|      |------|      |      |
   *                                             |      |      |      |      |      |      |      |
   *                                             `--------------------'      `--------------------'
   */
  [FNAV] = KEYMAP(
                  // Left hand
                  KC_NO,		KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,		KC_MUTE,
                  KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_VOLU,
                  KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
                  KC_NO,		KC_UNDO,	KC_CUT,		KC_COPY,	KC_PASTE,	KC_NO,		KC_VOLD,
                  KC_NO,		KC_NO,		KC_TRNS,	KC_TRNS,	KC_TRNS,
                  KC_NO,		KC_NO,
                  KC_NO,
                  KC_NO,		KC_TRNS,	KC_TRNS,
                  // Right hand
                  KC_NO,		KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_NO,
                  KC_NO,		KC_PGUP,	KC_HOME,	KC_UP,		KC_END,		KC_F11,		KC_NO,
                  KC_PGDOWN,	KC_LEFT,	KC_DOWN,	KC_RIGHT,	KC_F12,		KC_NO,
                  KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
                  KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_NO,		KC_NO,
                  KC_NO,		KC_NO,
                  KC_TRNS,
                  KC_TRNS,	KC_TRNS,	KC_NO),
  /* Keymap 5: numeric layer, sends keypad codes
   *
   * ,--------------------------------------------------.                                  ,--------------------------------------------------.
   * |        |      |      |      |      |      |      |                                  |      |      |   +  |   -  |   /  |   *  |        |
   * |--------+------+------+------+------+-------------|                                  |------+------+------+------+------+------+--------|
   * |        |      |      |      |      |      |      |                                  |      |      |   7  |   8  |   9  |      |        |
   * |--------+------+------+------+------+------|      |                                  |      |------+------+------+------+------+--------|
   * |        |      |      |      |      |      |------|                                  |------|      |   4  |   5  |   6  |      |        |
   * |--------+------+------+------+------+------|      |                                  |      |------+------+------+------+------+--------|
   * |        |      |      |      |      |      |      |                                  |      |      |   1  |   2  |   3  |      |        |
   * `--------+------+------+------+------+-------------,-------------.      ,-------------`-------------+------+------+------+------+--------'
   *   |      |      |      |      |      |             |      |      |      |      |      |             |   0  |  00  |   .  |      |      |
   *   `----------------------------------'      ,------|------|------|      |------+------+------.      `----------------------------------'
   *                                             |      |      |      |      |      |      |      |
   *                                             |      |      |------|      |------|      | Enter|
   *                                             |      |      |      |      |      |      |      |
   *                                             `--------------------'      `--------------------'
   */
  [NUM] = KEYMAP(
                 // Left hand
                 KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
                 KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
                 KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
                 KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
                 KC_NO,		KC_NO,		KC_TRNS,	KC_TRNS,	KC_TRNS,
                 KC_NO,		KC_NO,
                 KC_TRNS,
                 KC_NO,		KC_TRNS,	KC_NO,
                 // Right hand
                 KC_NO,		KC_NO,		KC_KP_PLUS,	KC_KP_MINUS,	KC_KP_SLASH,	KC_KP_ASTERISK,	KC_NO,
                 KC_NO,		KC_NO,		KC_KP_7,	KC_KP_8,	KC_KP_9,	KC_NO,		KC_NO,
                 KC_NO,		KC_KP_4,	KC_KP_5,	KC_KP_6,	KC_NO,		KC_NO,
                 KC_NO,		KC_NO,		KC_KP_1,	KC_KP_2,	KC_KP_3,	KC_NO,		KC_NO,
                 KC_KP_0,	M(KP_00),	KC_KP_COMMA,	KC_NO,		KC_NO,
                 KC_NO,		KC_NO,
                 KC_NO,
                 KC_NO,		KC_TRNS,	KC_KP_ENTER),
  /* Keymap 6: mouse layer
   *
   * ,--------------------------------------------------.                                  ,--------------------------------------------------.
   * |        |      |      |      |      |      |      |                                  |      |      |      |      |      |      |        |
   * |--------+------+------+------+------+-------------|                                  |------+------+------+------+------+------+--------|
   * |        |      |      |      |      |      |      |                                  |      |      |LClick|  Up  |RClick| WhUp |        |
   * |--------+------+------+------+------+------|      |                                  |      |------+------+------+------+------+--------|
   * |        |      |      |      |      |      |------|                                  |------|      | Left | Down | Right|WhDown|        |
   * |--------+------+------+------+------+------|      |                                  |      |------+------+------+------+------+--------|
   * |        |      |      |      |      |      |      |                                  |      |      |      |      |      |      |        |
   * `--------+------+------+------+------+-------------,-------------.      ,-------------`-------------+------+------+------+------+--------'
   *   |      |      |      |      |      |             |      |      |      |      |      |             |      |      |      |      |      |
   *   `----------------------------------'      ,------|------|------|      |------+------+------.      `----------------------------------'
   *                                             |      |      |      |      |      |      |      |
   *                                             |      |      |------|      |------|      |      |
   *                                             |      |      |      |      |      |      |      |
   *                                             `--------------------'      `--------------------'
   */
  [MSE] = KEYMAP(
                 // Left hand
                 KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
                 KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
                 KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
                 KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
                 KC_NO,		KC_NO,		KC_TRNS,	KC_TRNS,	KC_TRNS,
                 KC_NO,		KC_TRNS,
                 KC_NO,
                 KC_NO,		KC_TRNS,	KC_NO,
                 // Right hand
                 KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
                 KC_NO,		KC_NO,		KC_MS_BTN1,	KC_MS_UP,	KC_MS_BTN2,	KC_MS_WH_UP,	KC_NO,
                 KC_NO,		KC_MS_LEFT,	KC_MS_DOWN,	KC_MS_RIGHT,	KC_MS_WH_DOWN,	KC_NO,
                 KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
                 KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_NO,		KC_NO,
                 KC_NO,		KC_NO,
                 KC_NO,
                 KC_NO,		KC_TRNS,	KC_NO)

  /* Keymap 0: Base layer
   * Keys with double values (like Esc/Ctrl) correspond to the 'tapped' key and the 'held' key, respectively
   *
   * ,--------------------------------------------------.           ,--------------------------------------------------.
   * |        |   1  |   2  |   3  |   4  |   5  |  Esc |           |  Esc |   6  |   7  |   8  |   9  |   0  | = / +  |
   * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
   * |   ~    |" / ' |, / < |. / > |   P  |   Y  |   [  |           |   ]  |   F  |   G  |   C  |   H  |   L  | / / ?  |
   * |--------+------+------+------+------+------|   {  |           |   }  |------+------+------+------+------+--------|
   * |  Tab   |   A  |   O  |   E  |U/LSft| I/L1 |------|           |------|  D/L1|R/RSft|   T  |   N  |   S  | - / _  |
   * |--------+------+------+------+------+------| LGUI |           | LGUI |------+------+------+------+------+--------|
   * | {/LSft |; / : |   Q  |   J  |   K  |   X  |      |           |      |   B  |   M  |   W  |   V  |   Z  | }/RSft |
   * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
   *   |      |      |      |      | ~L1  |                                       | ~L1  |      |      | \ / ||        |
   *   `----------------------------------'                                       `----------------------------------'
   *                                        ,-------------.       ,-------------.
   *                                        | HOME |  END |       | LEFT | RIGHT|
   *                                 ,------|------|------|       |------+--------+------.
   *                                 | BSPC |  DEL | PGUP |       |  UP  | SPACE  |RETURN|
   *                                 |  /   |  /   |------|       |------|   /    |  /   |
   *                                 | LCTL | LALT |PGDWN |       | DOWN | LALT   | LCTL |
   *                                 `--------------------'       `----------------------'
   *
   */
  [BASE] = KEYMAP(
                  // left hand
                  KC_NO,          KC_1,     KC_2,   KC_3,   KC_4,          KC_5,           KC_ESC,
                  KC_TILD,        KC_QUOTE, KC_COMM,KC_DOT, KC_P,          KC_Y,           KC_LBRACKET,
                  KC_TAB,         KC_A,     KC_O,   KC_E,   SFT_T(KC_U),   LT(AUX, KC_I),
                  SFT_T(KC_LBRC), KC_SCLN,  KC_Q,   KC_J,   KC_K,          KC_X,           KC_LGUI,
                  KC_NO,          KC_NO,    KC_NO,  KC_NO,  MO(AUX),
                  KC_HOME, KC_END,
                  KC_PGUP,
                  CTL_T(KC_BSPC), ALT_T(KC_DEL), KC_PGDN,
                  // right hand
                  KC_ESC,          KC_6,           KC_7,         KC_8,   KC_9,   KC_0,   KC_EQL,
                  KC_RBRACKET,     KC_F,           KC_G,         KC_C,   KC_R,   KC_L,   KC_SLASH,
                  LT(AUX, KC_D),  SFT_T(KC_H),  KC_T,   KC_N,   KC_S,   KC_MINUS,
                  KC_LGUI,         KC_B,           KC_M,         KC_W,   KC_V,   KC_Z,   SFT_T(KC_RBRC),
                  MO(AUX), KC_NO,   KC_NO,  KC_BSLASH, KC_NO,
                  KC_LEFT, KC_RIGHT,
                  KC_UP,
                  KC_DOWN, ALT_T(KC_ENT), CTL_T(KC_SPC)
                  ),
  /* Keymap 1: Aux layer
   *
   * ,--------------------------------------------------.           ,--------------------------------------------------.
   * |  VolUp |      |      |      |      |      | SLEEP            | PWR  |      |      |      |      |      |        |
   * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
   * |  VolDn |  F1  |  F2  |  F3  |  F4  |      |      |           |      |      |   7  |   8  |   9  |   *  |        |
   * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   * |        |  F5  |  F6  |  F7  |  F8  | TRANS|------|           |------|TRANS |   4  |   5  |   6  |   +  |        |
   * |--------+------+------+------+------+------|      |           |PSCR  |------+------+------+------+------+--------|
   * |  TRANS |  F9  |  F10 |  F11 |  F12 |      |      |           |      |      |   1  |   2  |   3  |   /  |  TRANS |
   * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
   *   |CTRL-S|CTRL-Z|CTRL-X|CTRL-C| TRANS|                                       | TRANS|    . |   0  |   =  |      |
   *   `----------------------------------'                                       `----------------------------------'
   *                                        ,-------------.       ,-------------.
   *                                        | TRANS| TRANS|       | TRANS| TRANS|
   *                                 ,------|------|------|       |------+------+------.
   *                                 |      |      | TRANS|       | TRANS|      |      |
   *                                 |TRANS |TRANS |------|       |------| TRANS| TRANS|
   *                                 |      |      | TRANS|       | TRANS|      |      |
   *                                 `--------------------'       `--------------------'
   */
  [AUX] = KEYMAP(
                 // left hand
                 KC_VOLU, KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_SLEP,
                 KC_VOLD, KC_F1, KC_F2,  KC_F3,  KC_F4,  KC_NO,   KC_NO,
                 KC_NO  , KC_F5, KC_F6,  KC_F7,  KC_F8,  KC_TRNS,
                 KC_TRNS, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO,   KC_NO,
                 LCTL(KC_S), LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), KC_TRNS,
                 KC_TRNS  , KC_TRNS,
                 KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS,
                 // right hand
                 KC_PWR,  KC_NO,   KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,
                 KC_NO,   KC_NO,   KC_7,   KC_8,   KC_9,    KC_PAST, KC_NO,
                 KC_TRNS, KC_4,   KC_5,   KC_6,    KC_PPLS, KC_NO,
                 KC_PSCR, KC_NO,   KC_1,   KC_2,   KC_3,    KC_PSLS, KC_TRNS,
                 KC_TRNS,KC_DOT, KC_0,    KC_PEQL, KC_NO,
                 KC_TRNS  , KC_TRNS,
                 KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS
                 ),
  /* Keymap 1: Symbol Layer
   *
   * ,--------------------------------------------------.           ,--------------------------------------------------.
   * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
   * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
   * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
   * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   * |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
   * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
   * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
   *   |      |      |      |      |      |                                       |      |    . |   0  |   =  |      |
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
  [SYMB] = KEYMAP(
                  // left hand
                  KC_TRNS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
                  KC_TRNS,DE_EXLM,DE_AT,  DE_LCBR,DE_RCBR,DE_PIPE,KC_TRNS,
                  KC_TRNS,DE_HASH,DE_DLR, DE_LPRN,DE_RPRN,DE_GRV,
                  KC_TRNS,DE_PERC,DE_CIRC,DE_LBRC,DE_RBRC,DE_TILD,KC_TRNS,
                  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                  KC_TRNS,KC_TRNS,
                  KC_TRNS,
                  KC_TRNS,KC_TRNS,KC_TRNS,
                  // right hand
                  KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
                  KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    DE_ASTR, KC_F12,
                  KC_DOWN, KC_4,   KC_5,    KC_6,    DE_PLUS, KC_TRNS,
                  KC_TRNS, DE_AMPR, KC_1,   KC_2,    KC_3,    DE_BSLS, KC_TRNS,
                  KC_TRNS,KC_DOT,  KC_0,    DE_EQL,  KC_TRNS,
                  KC_TRNS, KC_TRNS,
                  KC_TRNS,
                  KC_TRNS, KC_TRNS, KC_TRNS
                  ),
  /* Keymap 2: Media and mouse keys
   *
   * ,--------------------------------------------------.           ,--------------------------------------------------.
   * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
   * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
   * |        |      | Lclk | MsUp | Rclk |      |      |           |      |      |VolDwn| Mute |VolUp |      |   F12  |
   * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   * |        | Btn4 |MsLeft|MsDown|MsRght| Btn5 |------|           |------|      | Prev | Stop | Play | Next |        |
   * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   * |        |WhRght|WhDown| WhUp |WhLeft|WhClk |      |           |      |BwSrch|BwBack|BwHome|BwRefr|BwFwd |        |
   * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
   *   |      |      |MsAcl0|MsAcl1|MsAcl2|                                       |      |      |      |      |      |
   *   `----------------------------------'                                       `----------------------------------'
   *                                        ,-------------.       ,-------------.
   *                                        |      |      |       |      |      |
   *                                 ,------|------|------|       |------+------+------.
   *                                 |      |      |      |       |      |Brwser|Brwser|
   *                                 | Lclk | Rclk |------|       |------|Back  |Forwd |
   *                                 |      |      |      |       |      |      |      |
   *                                 `--------------------'       `--------------------'
   */
  // MEDIA AND MOUSE
  [MDIA] = KEYMAP(
                  KC_TRNS, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_TRNS,
                  KC_TRNS, KC_TRNS, KC_BTN1, KC_MS_U, KC_BTN2, KC_TRNS, KC_TRNS,
                  KC_TRNS, KC_BTN4, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN5,
                  KC_TRNS, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_BTN3, KC_TRNS,
                  KC_TRNS, KC_TRNS, KC_ACL0, KC_ACL1, KC_ACL2,
                  KC_TRNS, KC_TRNS,
                  KC_TRNS,
                  KC_BTN1, KC_BTN2, KC_TRNS,
                  // right hand
                  KC_TRNS, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11,
                  KC_TRNS, KC_TRNS, KC_VOLD, KC_MUTE, KC_VOLU, KC_TRNS, KC_F12,
                  KC_TRNS, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, KC_TRNS,
                  KC_TRNS, KC_WSCH, KC_WBAK, KC_WHOM, KC_WREF, KC_WFWD, KC_TRNS,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                  KC_TRNS, KC_TRNS,
                  KC_TRNS,
                  KC_TRNS, KC_WBAK, KC_WFWD
                  ),
};



const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(AUX)                // FN1 - Momentary Layer 1 (Aux)
  [2] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
  case 0:
    if (record->event.pressed) {
      register_code(KC_RSFT);
    } else {
      unregister_code(KC_RSFT);
    }
    break;
  case KP_00:
    if (record->event.pressed) {
      return MACRO( T(KP_0), D(KP_0), END );
    } else {
      return MACRO( U(KP_0), END );
    }
    break;
  case CA_Fx:
    if (record->event.pressed) {
      layer_on(FNAV);
      return MACRO( D(LALT), D(LCTL), END );
    } else {
      layer_off(FNAV);
      return MACRO( U(LCTL), U(LALT), END );
    }
    break;
  }
  return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

  uint8_t layer = biton32(layer_state);

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
  case SYMB:
    ergodox_right_led_1_on();
    break;
  case MDIA:
    ergodox_right_led_2_on();
    break;
  default:
    ergodox_board_led_off();
    break;
  default:
    // none
    break;
  }
}
