#include "action_layer.h"
#include "action_util.h"
#include "debug.h"
#include "eeconfig.h"
#include "ergodox_ez.h"
#include "version.h"
#include "wait.h"

/* Aliases */
#define ____ KC_TRNS

/* Layers */
enum
{
  COLE = 0,
  LOWER, // right hand 10 key
  RAISE, // Function keys
  AUX,   // Things like rebooting the board to be flashed. NUM + RAISE
};

/* Macros */
enum
{
  NONE = 0,

  // OS Functions
  F_PASTE,

  // Config Macros
  CF_EPRM,
  CF_VERS,

  // RGB Macro
  RGB_ANI,
};

/* Tap Dancery */
enum
{
  TD_BTK,
  TD_TDE,
  TD_LPRN,
  TD_RPRN,
  TD_MIN,
  TD_USC,
  TD_COPY,
  TD_UNDO,
  TD_FIND,
};

/* OS Identifier */
enum
{
  OS_WIN = 0,
  OS_OSX,
  OS_LIN,
};

uint8_t os_type = OS_WIN;

static uint16_t rgb_timer;
bool time_travel = false;
bool skip_leds = false;

/* Keymaps */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

        /* Keymap 0: Colemak Layer
         *
         * ,-----------------------------------------------------.           ,-----------------------------------------------------.
         * |    Find   | 1  ! | 2  @ | 3  # | 4  $ | 5  % | Undo |           | VOLUP| 6  ^ | 7  & | 8  * | 9  ( | 0  ) |    ----   |
         * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
         * |-----------+------+------+------+------+------+------|           |------+------+------+------+------+------+-----------|
         * |  '  "  `  |   Q   |   W  |   F  |   P  |  G  | CCopy|           | VOLDN|   J  |   L  | U Ü  |   Y  | = +  |  ~  :  ;  |
         * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
         * | (  [  {   | A  Ä  |   R  | S  ß |   T  |  D  |------|           |------|   H  |   N  |   E  |   I  | O Ö   | )  ]  }  |
         * |-----------+------+------+------+------+------| Paste|           | MUTE |------+------+------+------+------+-----------|
         * |  -  ,  <  |  Z   |   X  |   C  |   V  |   B  |      |           |      |   K  |   M  |  / ? | \ |  |   ^  |  _  .  >  |
         * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
         *     |  AUX | RAISE | LOWER | LEAD | GUI  |                                      |  ESC | LOCK |   <  |   v  |   >   |
         *     `-----------------------------------'                                       `-----------------------------------'
         *                                         ,-------------.           ,-------------.
         *                                         | ALT  | CTRL |           | HOME |  END |
         *                                  ,------|------|------|           |------+------+------.
         *                                  |      |      | Del  |           | PGUP |      |      |
         *                                  | Space|Backsp|------|           |------| Enter| Shift|
         *                                  |      |      | Tab  |           | PGDN |      |      |
         *                                  `--------------------'           `--------------------'
         */

        [COLE] = KEYMAP(
            // Left Hand
            TD(TD_FIND), KC_1, KC_2, KC_3, KC_4, KC_5, TD(TD_UNDO),
            TD(TD_BTK), KC_Q, KC_W, KC_F, KC_P, KC_G, TD(TD_COPY),
            TD(TD_LPRN), KC_A, KC_R, KC_S, KC_T, KC_D,
            TD(TD_MIN), KC_Z, KC_X, KC_C, KC_V, KC_B, M(F_PASTE),
            TT(AUX), TT(RAISE), TT(LOWER), KC_LEAD, OSM(MOD_LGUI),
            OSM(MOD_LALT), OSM(MOD_LCTL),
            KC_DEL,
            KC_SPC, KC_BSPC, KC_TAB,

            // Right Hand
            KC_VOLU, KC_6, KC_7, KC_8, KC_9, KC_0, ____,
            KC_VOLD, KC_J, KC_L, KC_U, KC_Y, KC_MINS, TD(TD_TDE),
            KC_H, KC_N, KC_E, KC_I, KC_O, TD(TD_RPRN),
            KC_MUTE, KC_K, KC_M, KC_SLSH, KC_BSLS, KC_UP, TD(TD_USC),
            KC_ESC, LGUI(KC_L), KC_LEFT, KC_DOWN, KC_RGHT,
            KC_HOME, KC_END,
            KC_PGUP,
            KC_PGDOWN, KC_ENT, OSM(MOD_LSFT)),

        /* Keymap 2: LOWER Layer
         *
         * ,-----------------------------------------------------.           ,-----------------------------------------------------.
         * |   ----    | ---- | ---- | ---- | ---- | ---- |      |           |      |   (  |   )  |   ^  |   /  | ---- |           |
         * |           |      |      |      |      |      | ---- |           | ---- |      |      |      |      |      |   ----    |
         * |-----------+------+------+------+------+------+------|           |------+------+------+------+------+------+-----------|
         * |   ----    | ---- | ---- | ---- | ---- | ---- |      |           |      |   7  |   8  |   9  |   *  | ---- |   ----    |
         * |-----------+------+------+------+------+------| ---- |           | ---- |------+------+------+------+------+-----------|
         * |   ----    | ---- | ---- | ---- | ---- | ---- |------|           |------|   4  |   5  |   6  |   -  | ---- |   ----    |
         * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
         * |   ----    | ---- | ---- | ---- | ---- | ---- | ---- |           | ---- |   1  |   2  |   3  |   +  | ---- |   ----    |
         * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
         *     | ----  | ---- | ---- | ---- | ---- |                                       |   0  |   =  | ---- | ---- | ----  |
         *     `-----------------------------------'                                       `-------------------------------------'
         *                                         ,-------------.           ,-------------.
         *                                         | ---- | ---- |           | ---- | ---- |
         *                                  ,------|------|------|           |------+------+------.
         *                                  |      |      | ---- |           | ---- |      |      |
         *                                  | ---- | ---- |------|           |------| ---- | ---- |
         *                                  |      |      | ---- |           | ---- |      |      |
         *                                  `--------------------'           `--------------------'
         */
        [LOWER] = KEYMAP(
            // Left Hand
            ____, ____, ____, ____, ____, ____, ____,
            ____, ____, ____, ____, ____, ____, ____,
            ____, ____, ____, ____, ____, ____,
            ____, ____, ____, ____, ____, ____, ____,
            ____, ____, ____, ____, ____,
            ____, ____,
            ____,
            ____, ____, ____,

            // Right Hand
            ____, KC_LPRN, KC_RPRN, KC_CIRC, KC_PSLS, ____, ____,
            ____, KC_7, KC_8, KC_9, KC_PAST, ____, ____,
            KC_4, KC_5, KC_6, KC_PMNS, ____, ____,
            ____, KC_1, KC_2, KC_3, KC_PPLS, ____, ____,
            KC_0, KC_PEQL, ____, ____, ____,
            ____, ____,
            ____,
            ____, ____, ____),

        /* Keymap 3: RAISE Layer
         *
         * ,-----------------------------------------------------.           ,-----------------------------------------------------.
         * |    F1     |  F2  |  F3  |  F4  |  F5  |  F6  | ---- |           | ---- |   !  |   @  |   #  |   $  |   %  |   `  ~    |
         * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
         * |-----------+------+------+------+------+------+------|           |------+------+------+------+------+------+-----------|
         * |    F7     |  F8  |  F9  | F10  | F11  |  F12 | ---- |           | ---- |   ^  |   &  |   *  |   (  |   )  |   -  _    |
         * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
         * |   ----    | ---- | ---- | ---- | ---- | ---- |------|           |------|  [ { |  } ] | \  | |  ; : | '  " |   =  +    |
         * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
         * |   ----    | ---- | ---- | ---- | ---- | ---- | ---- |           | ---- | , <  |  > . | /  ? | ---- | ---- |   ----    |
         * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
         *     | ----  | ---- | ---- | ---- | ---- |                                       | ---- | ---- | ---- | ---- | ----  |
         *     `-----------------------------------'                                       `-----------------------------------'
         *                                         ,-------------.           ,-------------.
         *                                         | ---- | ---- |           | ---- | ---- |
         *                                  ,------|------|------|           |------+------+------.
         *                                  |      |      | ---- |           | ---- |      |      |
         *                                  | ---- | ---- |------|           |------| ---- | ---- |
         *                                  |      |      | ---- |           | ---- |      |      |
         *                                  `--------------------'           `--------------------'
         */
        [RAISE] = KEYMAP(
            // Left Hand
            KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, ____,
            KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, ____,
            ____, ____, ____, ____, ____, ____,
            ____, ____, ____, ____, ____, ____, ____,
            ____, ____, ____, ____, ____,
            ____, ____,
            ____,
            ____, ____, ____,

            // Right Hand
            ____, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_GRV,
            ____, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_MINS,
            KC_LBRC, KC_RBRC, KC_BSLS, KC_SCLN, KC_QUOT, KC_EQL,
            ____, KC_COMM, KC_DOT, KC_SLSH, ____, ____, ____,
            ____, ____, ____, ____, ____,
            ____, ____,
            ____,
            ____, ____, ____),

        /* Keymap 7: Configuration Layer
         *
         * ,-----------------------------------------------------.           ,-----------------------------------------------------.
         * |  EEPROM   | ---- | ---- | ---- | ---- | ---- | ---- |           | PWR  | ---- | ---- | ---- | ---- | ---- |           |
         * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |  VERSION  |
         * |-----------+------+------+------+------+------+------|           |------+------+------+------+------+------+-----------|
         * |   ----    | ---- | ---- | ---- | ---- | ---- |      |           |      | ---- | ---- | ---- | ---- | ---- |   ----    |
         * |-----------+------+------+------+------+------| ---- |           | SLP |------+------+------+------+------+-----------|
         * |   ----    | ---- | ---- | ---- | ---- | ---- |------|           |------| ---- | ---- | ---- | ---- | ---- |   ----    |
         * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
         * |   ----    | ---- | ---- | ---- | ---- | ---- | ---- |           | WAKE | ---- | ---- | ---- | ---- | ---- |   ----    |
         * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
         *     | ----  | ---- | ---- | ---- | ---- |                                       | ---- | ---- | ---- | ---- | ----  |
         *     `-----------------------------------'                                       `-----------------------------------'
         *                                         ,-------------.           ,-------------.
         *                                         | ---- | ---- |           | TOG  | ANI  |
         *                                  ,------|------|------|           |------+------+------.
         *                                  |      |      | ---- |           | VAI |      |      |
         *                                  | ---- | ---- |------|           |------| HUI  | HUID |
         *                                  |      |      | ---- |           | VAD |      |      |
         *                                  `--------------------'           `--------------------'
         */
        [AUX] = KEYMAP(
            // Left Hand
            M(CF_EPRM), ____, ____, ____, ____, ____, KC_PWR,
            ____, ____, ____, ____, ____, ____, KC_SLEP,
            ____, ____, ____, ____, ____, ____,
            ____, ____, ____, ____, ____, ____, KC_WAKE,
            ____, ____, ____, ____, ____,
            ____, ____,
            ____,
            ____, ____, ____,

            // Right Hand
            KC_PWR, ____, ____, ____, ____, ____, M(CF_VERS),
            KC_SLEP, ____, ____, ____, ____, ____, ____,
            ____, ____, ____, ____, ____, ____,
            KC_WAKE, ____, ____, ____, ____, ____, ____,
            ____, ____, ____, ____, ____,
            RGB_TOG, M(RGB_ANI),
            RGB_VAI,
            RGB_VAD, RGB_HUI, RGB_HUD),
};

void unredo(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LCTL);
    register_code(KC_Y);
    unregister_code(KC_Y);
    unregister_code(KC_LCTL);
  }
  else
  {
    register_code(KC_LCTL);
    register_code(KC_Z);
    unregister_code(KC_Z);
    unregister_code(KC_LCTL);
  }
  reset_tap_dance(state);
}

void ccopy(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LCTL);
    register_code(KC_X);
    unregister_code(KC_X);
    unregister_code(KC_LCTL);
  }
  else
  {
    register_code(KC_LCTL);
    register_code(KC_C);
    unregister_code(KC_C);
    unregister_code(KC_LCTL);
  }
  reset_tap_dance(state);
}

void findreplace(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LCTL);
    register_code(KC_H);
    unregister_code(KC_H);
    unregister_code(KC_LCTL);
  }
  else
  {
    register_code(KC_LCTL);
    register_code(KC_F);
    unregister_code(KC_F);
    unregister_code(KC_LCTL);
  }
  reset_tap_dance(state);
}

qk_tap_dance_action_t tap_dance_actions[] = {
        [TD_BTK] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_GRV),
        [TD_TDE] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_TILD),
        [TD_LPRN] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_LPRN),
        [TD_RPRN] = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_RPRN),
        [TD_MIN] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_MINS),
        [TD_USC] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_UNDS),
        [TD_COPY] = ACTION_TAP_DANCE_FN(ccopy),
        [TD_UNDO] = ACTION_TAP_DANCE_FN(unredo),
        [TD_FIND] = ACTION_TAP_DANCE_FN(findreplace)};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch (id)
  {
  case F_PASTE:
    if (record->event.pressed)
    {
      register_code(KC_LCTL);
      register_code(KC_V);
      unregister_code(KC_V);
      unregister_code(KC_LCTL);
    }
    break;
  case RGB_ANI:
    if (record->event.pressed)
    {
      rgb_timer = timer_read();
    }
    else
    {
      if (timer_elapsed(rgb_timer) > 300)
      {
        rgblight_mode(1);
      }
      else
      {
        rgblight_step();
      }
    }
  case CF_EPRM:
    if (record->event.pressed)
    {
      eeconfig_init();
    }
    return false;
    break;
  case CF_VERS:
    if (record->event.pressed)
    {
      SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
    }
    return false;
    break;
  }
  return MACRO_NONE;
};

/*
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{}
*/

void tap(uint16_t code)
{
  register_code(code);
  unregister_code(code);
}

LEADER_EXTERNS();
void matrix_scan_user(void)
{

  uint8_t layer = biton32(layer_state);

  if (keyboard_report->mods & MOD_BIT(KC_LSFT) ||
      ((get_oneshot_mods() & MOD_BIT(KC_LSFT)) &&
       !has_oneshot_mods_timed_out()))
  {
    ergodox_right_led_1_set(LED_BRIGHTNESS_HI);
    ergodox_right_led_1_on();
  }
  else if (layer == RAISE || layer == AUX)
  {
    ergodox_right_led_1_set(LED_BRIGHTNESS_LO);
    ergodox_right_led_1_on();
  }
  else
  {
    ergodox_right_led_1_off();
  }

  if (keyboard_report->mods & MOD_BIT(KC_LCTL) ||
      ((get_oneshot_mods() & MOD_BIT(KC_LCTL)) &&
       !has_oneshot_mods_timed_out()))
  {
    ergodox_right_led_2_set(LED_BRIGHTNESS_HI);
    ergodox_right_led_2_on();
  }
  else if (layer == LOWER || layer == AUX)
  {
    ergodox_right_led_2_set(LED_BRIGHTNESS_LO);
    ergodox_right_led_2_on();
  }
  else
  {
    ergodox_right_led_2_off();
  }

  if (keyboard_report->mods & MOD_BIT(KC_LALT) ||
      ((get_oneshot_mods() & MOD_BIT(KC_LALT)) &&
       !has_oneshot_mods_timed_out()))
  {
    ergodox_right_led_3_set(LED_BRIGHTNESS_HI);
    ergodox_right_led_3_on();
  }
  else if (layer == COLE || layer == AUX)
  {
    ergodox_right_led_3_set(LED_BRIGHTNESS_LO);
    ergodox_right_led_3_on();
  }
  else
  {
    ergodox_right_led_3_off();
  }

  LEADER_DICTIONARY()
  {
    leading = false;
    leader_end();

    SEQ_THREE_KEYS(KC_W, KC_I, KC_N) { os_type = OS_WIN; };
    SEQ_THREE_KEYS(KC_O, KC_S, KC_X) { os_type = OS_OSX; };
    SEQ_THREE_KEYS(KC_L, KC_I, KC_N) { os_type = OS_LIN; };

    SEQ_ONE_KEY(KC_A)
    {
      switch (os_type)
      {
      case OS_WIN:
        tap(KC_NLCK);
        register_code(KC_RALT);
        tap(KC_KP_0);
        tap(KC_KP_2);
        tap(KC_KP_2);
        tap(KC_KP_8);
        unregister_code(KC_RALT);
        tap(KC_NLCK);
        break;
      case OS_OSX:
        register_code(KC_RALT);
        register_code(KC_RSFT);
        register_code(KC_SCLN);
        unregister_code(KC_SCLN);
        unregister_code(KC_RSFT);
        unregister_code(KC_RALT);
        tap(KC_A);
        break;
      case OS_LIN:
        tap(KC_RALT);
        tap(KC_DQT);
        tap(KC_A);
        break;
      }
    }
    SEQ_TWO_KEYS(KC_A, KC_A)
    {
      switch (os_type)
      {
      case OS_WIN:
        tap(KC_NLCK);
        register_code(KC_RALT);
        tap(KC_KP_0);
        tap(KC_KP_1);
        tap(KC_KP_9);
        tap(KC_KP_6);
        unregister_code(KC_RALT);
        tap(KC_NLCK);
        break;
      case OS_OSX:
        register_code(KC_RALT);
        register_code(KC_RSFT);
        register_code(KC_SCLN);
        unregister_code(KC_SCLN);
        unregister_code(KC_RSFT);
        unregister_code(KC_RALT);
        register_code(KC_LSFT);
        register_code(KC_A);
        unregister_code(KC_A);
        unregister_code(KC_LSFT);
        break;
      case OS_LIN:
        tap(KC_RALT);
        tap(KC_DQT);
        register_code(KC_LSFT);
        register_code(KC_A);
        unregister_code(KC_A);
        unregister_code(KC_LSFT);
        break;
      }
    }
    SEQ_ONE_KEY(KC_O)
    {
      switch (os_type)
      {
      case OS_WIN:
        tap(KC_NLCK);
        register_code(KC_RALT);
        tap(KC_KP_0);
        tap(KC_KP_2);
        tap(KC_KP_4);
        tap(KC_KP_6);
        unregister_code(KC_RALT);
        tap(KC_NLCK);
        break;
      case OS_OSX:
        register_code(KC_RALT);
        register_code(KC_RSFT);
        register_code(KC_SCLN);
        unregister_code(KC_SCLN);
        unregister_code(KC_RSFT);
        unregister_code(KC_RALT);
        tap(KC_O);
        break;
      case OS_LIN:
        tap(KC_RALT);
        tap(KC_DQT);
        tap(KC_O);
        break;
      }
    }
    SEQ_TWO_KEYS(KC_O, KC_O)
    {
      switch (os_type)
      {
      case OS_WIN:
        tap(KC_NLCK);
        register_code(KC_RALT);
        tap(KC_KP_0);
        tap(KC_KP_2);
        tap(KC_KP_1);
        tap(KC_KP_4);
        unregister_code(KC_RALT);
        tap(KC_NLCK);
        break;
      case OS_OSX:
        register_code(KC_RALT);
        register_code(KC_RSFT);
        register_code(KC_SCLN);
        unregister_code(KC_SCLN);
        unregister_code(KC_RSFT);
        unregister_code(KC_RALT);
        tap(LSFT(KC_O));
        break;
      case OS_LIN:
        tap(KC_RALT);
        tap(KC_DQT);
        register_code(KC_LSFT);
        register_code(KC_O);
        unregister_code(KC_O);
        unregister_code(KC_LSFT);
        break;
      }
    }
    SEQ_ONE_KEY(KC_U)
    {
      switch (os_type)
      {
      case OS_WIN:
        tap(KC_NLCK);
        register_code(KC_RALT);
        tap(KC_KP_0);
        tap(KC_KP_2);
        tap(KC_KP_5);
        tap(KC_KP_2);
        unregister_code(KC_RALT);
        tap(KC_NLCK);
        break;
      case OS_OSX:
        register_code(KC_RALT);
        register_code(KC_RSFT);
        register_code(KC_SCLN);
        unregister_code(KC_SCLN);
        unregister_code(KC_RSFT);
        unregister_code(KC_RALT);
        tap(KC_U);
        break;
      case OS_LIN:
        tap(KC_RALT);
        tap(KC_DQT);
        tap(KC_U);
        break;
      }
    }
    SEQ_TWO_KEYS(KC_U, KC_U)
    {
      switch (os_type)
      {
      case OS_WIN:
        tap(KC_NLCK);
        register_code(KC_RALT);
        tap(KC_KP_0);
        tap(KC_KP_2);
        tap(KC_KP_2);
        tap(KC_KP_0);
        unregister_code(KC_RALT);
        tap(KC_NLCK);
        break;
      case OS_OSX:
        register_code(KC_RALT);
        register_code(KC_RSFT);
        register_code(KC_SCLN);
        unregister_code(KC_SCLN);
        unregister_code(KC_RSFT);
        unregister_code(KC_RALT);
        tap(LSFT(KC_U));
        break;
      case OS_LIN:
        tap(KC_RALT);
        tap(KC_DQT);
        register_code(KC_LSFT);
        register_code(KC_U);
        unregister_code(KC_U);
        unregister_code(KC_LSFT);
        break;
      }
    }
    SEQ_ONE_KEY(KC_S)
    {
      switch (os_type)
      {
      case OS_WIN:
        tap(KC_NLCK);
        register_code(KC_RALT);
        tap(KC_KP_0);
        tap(KC_KP_2);
        tap(KC_KP_2);
        tap(KC_KP_3);
        unregister_code(KC_RALT);
        tap(KC_NLCK);
        break;
      case OS_OSX:
        register_code(KC_RALT);
        tap(KC_S);
        unregister_code(KC_RALT);
        break;
      case OS_LIN:
        tap(KC_RALT);
        tap(KC_S);
        tap(KC_S);
        break;
      }
    }
  }
}

void matrix_init_user(void)
{

  ergodox_led_all_on();
  rgblight_init();
  rgblight_enable();
  rgblight_setrgb(255, 0, 0);
  for (int i = LED_BRIGHTNESS_HI; i > LED_BRIGHTNESS_LO; i--)
  {
    ergodox_led_all_set(i);
    wait_ms(5);
  }
  rgblight_setrgb(255, 255, 0);
  wait_ms(1000);
  for (int i = LED_BRIGHTNESS_LO; i > 0; i--)
  {
    ergodox_led_all_set(i);
    wait_ms(10);
  }
  rgblight_setrgb(0, 255, 255);
  ergodox_led_all_off();
  wait_ms(1000);

  rgblight_effect_knight(50);
}