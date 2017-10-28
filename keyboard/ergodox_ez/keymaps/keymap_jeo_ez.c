/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Jeo layout for ErgoDox EZ. Optimised for OS X.                            *
 *                                                                           *
 * v1.0.0                                                                    *
 *                                                                           *
 * Joe Cridge, 2015.                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "ergodox_ez.h"
#include "action_layer.h"
#include "debug.h"

/**
 * Keyboard layers
 */
#define  BASE  0  /* qgmlwy...                 */
#define  CAPS  1  /* QGMLWY...                 */
#define  SYMB  2  /* Neo symbol layer          */
#define  FPAD  3  /* Function and numpad layer */
#define  WASD  4  /* Standard QWERTY layout    */
#define  LOCK  5  /* Kitten-proof layer        */

/**
 * Custom macros
 */
#define  MHEX  0  /* Sends "0x" */
#define  MBIN  1  /* Sends "0b" */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = KEYMAP(
    /**
     * BASE: Left Hand
     *
     *        ,--------------------------------------------------.
     *        |Activity|1     |2     |3     |4     |5     |Pause |
     *        |--------+------+------+------+------+-------------|
     *        |Tab     |q     |g     |m     |l     |w     |Volume|
     *        |--------+------+------+------+------+------|Up    |
     *        |Symbol  |d     |s     |t     |n     |r     |------|
     *        |--------+------+------+------+------+------|Volume|
     *        |Upper   |z     |x     |c     |v     |j     |Down  |
     *        `--------+------+------+------+------+-------------'
     *          |QWERTY|Left  |Right |Up    |Down  |
     *          `----------------------------------'
     *                                                    ,-------------.
     *                                                    |Prev  |Next  |
     *                                             ,------|------|------|
     *                                             |Cmd   |Ctrl  |Mute  |
     *                                             |      |      |------|
     *                                             |      |      |Alt   |
     *                                             `--------------------'
     */
     KC_F16,    KC_1,     KC_2,     KC_3,   KC_4,     KC_5,     KC_MPLY,
     KC_TAB,    KC_Q,     KC_G,     KC_M,   KC_L,     KC_W,     KC_VOLU,
     MO(SYMB),  KC_D,     KC_S,     KC_T,   KC_N,     KC_R,
     MO(CAPS),  KC_Z,     KC_X,     KC_C,   KC_V,     KC_J,     KC_VOLD,
     TG(WASD),  KC_LEFT,  KC_RGHT,  KC_UP,  KC_DOWN,

                                                      KC_MPRV,  KC_MNXT,
                                                                KC_MUTE,
                                            KC_LGUI,  KC_LCTL,  KC_LALT,

    /**
     * BASE: Right Hand
     *
     *               ,--------------------------------------------------.
     *               |Prefs |6     |7     |8     |9     |0     |Search  |
     *               |------+------+------+------+------+------+--------|
     *               |Page  |y     |f     |u     |b     |BkSpce|Escape  |
     *               |Up    |------+------+------+------+------+--------|
     *               |------|i     |a     |e     |o     |h     |Enter   |
     *               |Page  |------+------+------+------+------+--------|
     *               |Down  |k     |p     |,     |.     |/     |Upper   |
     *               `-------------+------+------+------+------+--------'
     *                             |Down  |Up    |Right |Left  |Save  |
     *                             `----------------------------------'
     *        ,-------------.
     *        |Term  |Editor|
     *        |------+------+------.
     *        |Delete|Symbol|Space |
     *        |------|      |      |
     *        |Fn    |      |      |
     *        `--------------------'
     *
     */
     KC_F17,      KC_6,      KC_7,     KC_8,     KC_9,      KC_0,      KC_F18,
     KC_PGUP,     KC_Y,      KC_F,     KC_U,     KC_B,      KC_BSPC,   KC_ESC,
                  KC_I,      KC_A,     KC_E,     KC_O,      KC_H,      KC_ENT,
     KC_PGDN,     KC_K,      KC_P,     KC_COMM,  KC_DOT,    KC_SLSH,   MO(CAPS),
                             KC_DOWN,  KC_UP,    KC_RIGHT,  KC_LEFT,   KC_F19,

     KC_F20,      KC_F21,
     KC_DELT,
     TG(FPAD),    MO(SYMB),  KC_SPC
  ),

  [CAPS] = KEYMAP(
    /**
     * CAPS: Left Hand
     *
     * Blank keys are transparent (i.e. fall back to BASE).
     *
     *        ,--------------------------------------------------.
     *        |        |      |      |      |      |      |      |
     *        |--------+------+------+------+------+-------------|
     *        |TAB     |Q     |G     |M     |L     |W     |      |
     *        |--------+------+------+------+------+------|      |
     *        |        |D     |S     |T     |N     |R     |------|
     *        |--------+------+------+------+------+------|      |
     *        |        |Z     |X     |C     |V     |J     |      |
     *        `--------+------+------+------+------+-------------'
     *          |LOCK  |      |      |      |      |
     *          `----------------------------------'
     *                                                    ,-------------.
     *                                                    |      |      |
     *                                             ,------|------|------|
     *                                             |CMD   |CTRL  |      |
     *                                             |      |      |------|
     *                                             |      |      |ALT   |
     *                                             `--------------------'
     */
     KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,     KC_TRNS,
     S(KC_TAB),  S(KC_Q),  S(KC_G),  S(KC_M),  S(KC_L),    S(KC_W),     KC_TRNS,
     KC_TRNS,    S(KC_D),  S(KC_S),  S(KC_T),  S(KC_N),    S(KC_R),
     KC_TRNS,    S(KC_Z),  S(KC_X),  S(KC_C),  S(KC_V),    S(KC_J),     KC_TRNS,
     TG(LOCK),   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,

                                                           KC_TRNS,     KC_TRNS,
                                                                        KC_TRNS,
                                               (KC_LGUI),  S(KC_LCTL),  S(KC_LALT),

    /**
     * CAPS: Right Hand
     *
     * Blank keys are transparent (i.e. fall back to BASE).
     *
     *               ,--------------------------------------------------.
     *               |      |      |      |      |      |      |        |
     *               |------+------+------+------+------+------+--------|
     *               |      |Y     |F     |U     |B     |      |        |
     *               |      |------+------+------+------+------+--------|
     *               |------|I     |A     |E     |O     |H     |ENTER   |
     *               |      |------+------+------+------+------+--------|
     *               |      |K     |P     |EmDash|MidDot|?     |        |
     *               `-------------+------+------+------+------+--------'
     *                             |      |      |      |      |SAVE  |
     *                             `----------------------------------'
     *        ,-------------.
     *        |      |      |
     *        |------+------+------.
     *        |      |      |SPACE |
     *        |------|      |      |
     *        |      |      |      |
     *        `--------------------'
     *
     */
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,
     KC_TRNS,  S(KC_Y),  S(KC_F),  S(KC_U),     S(KC_B),     KC_TRNS,     KC_TRNS,
               S(KC_I),  S(KC_A),  S(KC_E),     S(KC_O),     S(KC_H),     S(KC_ENT),
     KC_TRNS,  S(KC_K),  S(KC_P),  UC(0x2014),  UC(0x00B7),  S(KC_SLSH),  KC_TRNS,
                         KC_TRNS,  KC_TRNS,     KC_TRNS,     KC_TRNS,     S(KC_F19),

     KC_TRNS,  KC_TRNS,
     KC_TRNS,
     KC_TRNS,  KC_TRNS,  S(KC_SPC)
  ),

  [SYMB] = KEYMAP(
    /**
     * SYMB: Left Hand
     *
     * Blank keys are transparent. Hashed keys are disabled.
     *
     *        ,--------------------------------------------------.
     *        |        | #### |@     |GBP   |EUR   | #### |      |
     *        |--------+------+------+------+------+-------------|
     *        |        |...   |_     |[     |]     |^     |      |
     *        |--------+------+------+------+------+------|      |
     *        |        |\     |/     |{     |}     |*     |------|
     *        |--------+------+------+------+------+------|      |
     *        |        |#     |$     ||     |~     |`     |      |
     *        `--------+------+------+------+------+-------------'
     *          | #### |      |      |      |      |
     *          `----------------------------------'
     *                                                    ,-------------.
     *                                                    |      |      |
     *                                             ,------|------|------|
     *                                             |      |      |      |
     *                                             |      |      |------|
     *                                             |      |      |      |
     *                                             `--------------------'
     */
     KC_TRNS,  KC_NO,       KC_AT,    UC(0x00A3),  UC(0x20AC),  KC_NO,    KC_TRNS,
     KC_TRNS,  UC(0x2026),  KC_UNDS,  KC_LBRC,     KC_RBRC,     KC_CIRC,  KC_TRNS,
     KC_TRNS,  KC_BSLS,     KC_SLSH,  KC_LCBR,     KC_RCBR,     KC_ASTR,
     KC_TRNS,  KC_HASH,     KC_DLR,   KC_PIPE,     KC_TILD,     KC_GRV,   KC_TRNS,
     KC_NO,    KC_TRNS,     KC_TRNS,  KC_TRNS,     KC_TRNS,

                                                                KC_TRNS,  KC_TRNS,
                                                                          KC_TRNS,
                                                  KC_TRNS,      KC_TRNS,  KC_TRNS,

    /**
     * SYMB: Right Hand
     *
     * Blank keys are transparent. Hashed keys are disabled.
     *
     *               ,--------------------------------------------------.
     *               |      | #### |LDQUO |RDQUO |LSQUO |LDQUO |        |
     *               |------+------+------+------+------+------+--------|
     *               |      |!     |<     |>     |=     |&     |        |
     *               |      |------+------+------+------+------+--------|
     *               |------|?     |(     |)     |-     |:     |        |
     *               |      |------+------+------+------+------+--------|
     *               |      |+     |%     |"     |'     |;     |        |
     *               `-------------+------+------+------+------+--------'
     *                             |      |      |      |      |      |
     *                             `----------------------------------'
     *        ,-------------.
     *        |      |      |
     *        |------+------+------.
     *        |      |      |      |
     *        |------|      |      |
     *        |      |      |      |
     *        `--------------------'
     *
     */
     KC_TRNS,  KC_NO,       UC(0x201C),  UC(0x201D),  UC(0x2018),  UC(0x2019),  KC_TRNS,
     KC_TRNS,  KC_EXLM,     S(KC_COMM),  S(KC_DOT),   KC_EQL,      KC_AMPR,     KC_TRNS,
               S(KC_SLSH),  KC_LPRN,     KC_RPRN,     KC_MINS,     KC_COLN,     KC_TRNS,
     KC_TRNS,  KC_PLUS,     KC_PERC,     S(KC_QUOT),  KC_QUOT,     KC_SCLN,     KC_TRNS,
                            KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,

     KC_TRNS,  KC_TRNS,
     KC_TRNS,
     KC_TRNS,  KC_TRNS,     KC_TRNS
  ),

  [FPAD] = KEYMAP(
    /**
     * FPAD: Left Hand
     *
     * This half-layer is designed to function as an independent navigation pad.
     *
     * Blank keys are transparent. Hashed keys are disabled.
     *
     *        ,--------------------------------------------------.
     *        |Escape  |F1    |F2    |F3    |F4    |F5    |      |
     *        |--------+------+------+------+------+-------------|
     *        |Tab     |PgUp  |BackSp|Up    |Delete|PgDn  |      |
     *        |--------+------+------+------+------+------|      |
     *        |Enter   |Home  |Left  |Down  |Right |End   |------|
     *        |--------+------+------+------+------+------|      |
     *        |TAB     |Close |Back  |NewTab|Fwd   |NewWin|      |
     *        `--------+------+------+------+------+-------------'
     *          |LOCK  | #### | #### | #### | #### |
     *          `----------------------------------'
     *                                                    ,-------------.
     *                                                    |      |      |
     *                                             ,------|------|------|
     *                                             |      |      |      |
     *                                             |      |      |------|
     *                                             |      |      |      |
     *                                             `--------------------'
     */
     KC_ESC,     KC_F1,       KC_F2,    KC_F3,       KC_F4,    KC_F5,       KC_TRNS,
     KC_TAB,     KC_PGUP,     KC_BSPC,  KC_UP,       KC_DELT,  KC_PGDN,     KC_TRNS,
     KC_ENT,     KC_HOME,     KC_LEFT,  KC_DOWN,     KC_RGHT,  KC_END,
     S(KC_TAB),  LGUI(KC_W),  KC_WBAK,  LGUI(KC_T),  KC_WFWD,  LGUI(KC_N),  KC_TRNS,
     TG(LOCK),   KC_NO,       KC_NO,    KC_NO,       KC_NO,

                                                               KC_TRNS,     KC_TRNS,
                                                                            KC_TRNS,
                                                     KC_TRNS,  KC_TRNS,     KC_TRNS,

    /**
     * FPAD: Right Hand
     *
     * This half-layer is designed to function as an independent keypad for
     * calculator and hex input.
     *
     * Blank keys are transparent. Hashed keys are disabled.
     *
     *               ,--------------------------------------------------.
     *               |:     |F6    |F7    |F8    |F9    |F10   |/       |
     *               |------+------+------+------+------+------+--------|
     *               |0x    |A     |7     |8     |9     |D     |*       |
     *               |      |------+------+------+------+------+--------|
     *               |------|B     |4     |5     |6     |E     |-       |
     *               |0b    |------+------+------+------+------+--------|
     *               |      |C     |1     |2     |3     |F     |+       |
     *               `-------------+------+------+------+------+--------'
     *                             |#     |0     |.     |e     |,     |
     *                             `----------------------------------'
     *        ,-------------.
     *        |Left  |Right |
     *        |------+------+------.
     *        |BackSp|Escape|Enter |
     *        |------|      |      |
     *        |      |      |      |
     *        `--------------------'
     *
     */
     KC_COLN,  KC_F6,    KC_F7,    KC_F8,  KC_F9,    KC_F10,   KC_PSLS,
     M(MHEX),  S(KC_A),  KC_P7,    KC_P8,  KC_P9,    S(KC_D),  KC_PAST,
               S(KC_B),  KC_P4,    KC_P5,  KC_P6,    S(KC_E),  KC_PMNS,
     M(MBIN),  S(KC_C),  KC_P1,    KC_P2,  KC_P3,    S(KC_F),  KC_PPLS,
                         KC_HASH,  KC_P0,  KC_PDOT,  KC_E,     KC_PCMM,

     KC_LEFT,  KC_RGHT,
     KC_BSPC,
     KC_TRNS,  KC_ESC,   KC_PENT
  ),

  [WASD] = KEYMAP(
    /**
     * WASD: Left Hand
     *
     * Blank keys are transparent.
     *
     *        ,--------------------------------------------------.
     *        |Escape  |1    !|2    @|3    #|4    $|5    %|Pause |
     *        |--------+------+------+------+------+-------------|
     *        |Tab     |Q     |W     |E     |R     |T     |Volume|
     *        |--------+------+------+------+------+------|Up    |
     *        |CapsLock|A     |S     |D     |F     |G     |------|
     *        |--------+------+------+------+------+------|Volume|
     *        |Shift   |Z     |X     |C     |V     |B     |Down  |
     *        `--------+------+------+------+------+-------------'
     *          |      |Ctrl  |Alt   |Cmd   |Space |
     *          `----------------------------------'
     *                                                    ,-------------.
     *                                                    |Prev  |Next  |
     *                                             ,------|------|------|
     *                                             |Home  |End   |Mute  |
     *                                             |      |      |------|
     *                                             |      |      |Menu  |
     *                                             `--------------------'
     */
    KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_MPLY,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_VOLU,
    KC_LCAP,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_VOLD,
    KC_TRNS,  KC_LCTL,  KC_LALT,  KC_LGUI,  KC_SPC,

                                                      KC_MPRV,  KC_MNXT,
                                                                KC_MUTE,
                                            KC_HOME,  KC_END,   KC_MENU,

    /**
     * WASD: Right Hand
     *
     *               ,--------------------------------------------------.
     *               |`    ~|6    ^|7    &|8    *|9    (|0    )|BckSpace|
     *               |------+------+------+------+------+------+--------|
     *               |Page  |Y     |U     |I     |O     |P     |\      ||
     *               |Up    |------+------+------+------+------+--------|
     *               |------|H     |J     |K     |L     |;    :|Enter   |
     *               |Page  |------+------+------+------+------+--------|
     *               |Down  |N     |M     |,    <|.    >|/    ?|Shift   |
     *               `-------------+------+------+------+------+--------'
     *                             |-    _|=    +|[    {|]    }|'    "|
     *                             `----------------------------------'
     *        ,-------------.
     *        |Insert|Up    |
     *        |------+------+------.
     *        |Left  |Down  |Right |
     *        |------|      |      |
     *        |Delete|      |      |
     *        `--------------------'
     *
     */
    KC_GRV,   KC_6,     KC_7,     KC_8,     KC_9,     KC_0,      KC_BSPC,
    KC_PGUP,  KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,      KC_BSLS,
              KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,   KC_ENT,
    KC_PGDN,  KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,   KC_RSFT,
                        KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,   KC_QUOT,

    KC_INS,   KC_UP,
    KC_LEFT,
    KC_DELT,  KC_DOWN,  KC_RGHT
  ),

  [LOCK] = KEYMAP(
    /**
     * LOCK: Left Hand
     *
     * Hashed keys are disabled.
     *
     *        ,--------------------------------------------------.
     *        | ###### | #### | #### | #### | #### | #### | #### |
     *        |--------+------+------+------+------+-------------|
     *        | ###### | #### | #### | #### | #### | #### | #### |
     *        |--------+------+------+------+------+------| #### |
     *        | ###### | #### | #### | #### | #### | #### |------|
     *        |--------+------+------+------+------+------| #### |
     *        | ###### | #### | #### | #### | #### | #### | #### |
     *        `--------+------+------+------+------+-------------'
     *          |LOCK  | #### | #### | #### | #### |
     *          `----------------------------------'
     *                                                    ,-------------.
     *                                                    | #### | #### |
     *                                             ,------|------|------|
     *                                             | #### | #### | #### |
     *                                             | #### | #### |------|
     *                                             | #### | #### | #### |
     *                                             `--------------------'
     */
     KC_NO,    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
     KC_NO,    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
     KC_NO,    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
     KC_NO,    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
     TG(LOCK), KC_NO,  KC_NO,  KC_NO,  KC_NO,

                                               KC_NO,  KC_NO,
                                                       KC_NO,
                                       KC_NO,  KC_NO,  KC_NO,

    /**
     * LOCK: Right Hand
     *
     * Blank keys are transparent.
     *
     *               ,--------------------------------------------------.
     *               | #### | #### | #### | #### | #### | #### | ###### |
     *               |------+------+------+------+------+------+--------|
     *               | #### | #### | #### | #### | #### | #### | ###### |
     *               | #### |------+------+------+------+------+--------|
     *               |------| #### | #### | #### | #### | #### | ###### |
     *               | #### |------+------+------+------+------+--------|
     *               | #### | #### | #### | #### | #### | #### | ###### |
     *               `-------------+------+------+------+------+--------'
     *                             | #### | #### | #### | #### | #### |
     *                             `----------------------------------'
     *        ,-------------.
     *        | #### | #### |
     *        |------+------+------.
     *        | #### | #### | #### |
     *        |------| #### | #### |
     *        | #### | #### | #### |
     *        `--------------------'
     *
     */
     KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
     KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
             KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
     KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
                     KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,

     KC_NO,  KC_NO,
     KC_NO,
     KC_NO,  KC_NO,  KC_NO
  ),
};

const uint16_t PROGMEM fn_actions[] = { };

const macro_t *
action_get_macro (keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch (id)
    {
    case MHEX:
      if (record->event.pressed)
        return MACRO(I(1), T(0), T(X), END);  /* Sends "0x" */
      break;
    case MBIN:
      if (record->event.pressed)
        return MACRO(I(1), T(0), T(B), END);  /* Sends "0b" */
      break;
    }
  return MACRO_NONE;
};

/**
 * Run once on initialisation
 */
void *
matrix_init_user (void)
{
  /* Do nothing */
};

/**
 * Run constantly as a background loop
 */
void *
matrix_scan_user (void)
{
  uint8_t layer = biton32 (layer_state);

  /**
   * Turn off all LEDs
   */
  ergodox_board_led_off ();    /* LED on Teensy board           */
  ergodox_right_led_1_off ();  /* Left (red) indicator LED      */
  ergodox_right_led_2_off ();  /* Middle (green) indicator LED  */
  ergodox_right_led_3_off ();  /* Right (blue) indicator LED    */

  /**
   * Turn back on the relevant ones
   */
  switch (layer)
    {
    case FPAD:
      ergodox_right_led_3_on ();
      break;
    case WASD:
      ergodox_right_led_2_on ();
      break;
    case LOCK:
      ergodox_right_led_1_on ();
    default:
      /* Do nothing */
      break;
    }
};
