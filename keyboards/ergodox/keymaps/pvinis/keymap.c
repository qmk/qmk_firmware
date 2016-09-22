// pvinis' ergodox keymap

#include "ergodox.h"
#include "mousekey.h"

// easier name for left ctrl-alt-gui
#define ALLM(kc) LCAG(kc)

// layers
enum {
  BASE = 0,
  BEGIN,
  QWERTY,
  CARPALX,
  SYSCTL,
};

// extra keys
enum {
  NONE = 0,

  // mouse
  MS_UL, // up   left
  MS_UR, // up   right
  MS_DL, // down left
  MS_DR, // down right

  // tap dance
  TD_FLSH, // flash keyboard
};

// application selection
// this is sending ctrl-alt-gui-<key>, and this is picked up by hammerspoon
#define AP_SLCK ALLM(KC_S)
#define AP_XCOD ALLM(KC_X)
#define AP_MSGR ALLM(KC_M)

// keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* BASE
 * the base of the keyboard.
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |4x FLASH|      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |BEGIN |QWERTY|       |SYSCTL|      |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |CARPAL|       |Slack |        |      |
 *                                 |Backsp|LShift|------|       |------| Enter  |Space |
 *                                 |      |      |SYSCTL|       |Msngr |        |      |
 *                                 `--------------------'       `----------------------'
 */
[BASE] = KEYMAP(
 TD(TD_FLSH)    ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO    ,KC_NO
,KC_NO          ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO    ,KC_NO
,KC_NO          ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO
,KC_NO          ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO    ,KC_NO
,KC_NO          ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO

                                                          ,TG(BEGIN)  ,TG(QWERTY)
                                                                      ,TG(CARPALX)
                                                  ,KC_BSPC  ,KC_LSFT  ,TG(SYSCTL)

                ,KC_NO    ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO    ,KC_NO
                ,KC_NO    ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO    ,KC_NO
                          ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO    ,KC_NO
                ,KC_NO    ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO    ,KC_NO
                                  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO    ,KC_NO

   ,TG(SYSCTL)  ,KC_NO
   ,AP_SLCK
   ,AP_MSGR     ,KC_ENT  ,KC_SPC
),

/* BEGIN
 * a beginner's keymap i currently use.
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |   1  |   2  |   3  |   4  |   5  |   6  |           |   6  |   7  |   8  |   9  |   0  |   -  |   =    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |   [  |           |   ]  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |Esc/Ctrl|   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  | Enter  |
 * |--------+------+------+------+------+------|   (  |           |   )  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |   `  |  Cmd |      | Cmd  |                                       |      |      |      |   '  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 |      |      |------|       |------|        |      |
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
[BEGIN] = KEYMAP(
 KC_TRNS          ,KC_1    ,KC_2     ,KC_3     ,KC_4      ,KC_5    ,KC_6
,KC_TAB           ,KC_Q    ,KC_W     ,KC_E     ,KC_R      ,KC_T    ,KC_LBRC
,CTL_T(KC_ESC)    ,KC_A    ,KC_S     ,KC_D     ,KC_F      ,KC_G
,KC_LSFT          ,KC_Z    ,KC_X     ,KC_C     ,KC_V      ,KC_B    ,KC_LPRN
,KC_TRNS          ,KC_GRV  ,KC_LGUI  ,KC_LEFT  ,KC_RIGHT

                                                                   ,KC_TRNS  ,KC_TRNS
                                                                             ,KC_TRNS
                                                         ,KC_TRNS  ,KC_TRNS  ,KC_TRNS

                ,KC_6       ,KC_7  ,KC_8   ,KC_9     ,KC_0     ,KC_MINS    ,KC_EQL
                ,KC_RBRC    ,KC_Y  ,KC_U   ,KC_I     ,KC_O     ,KC_P       ,KC_BSLS
                            ,KC_H  ,KC_J   ,KC_K     ,KC_L     ,KC_SCLN    ,KC_ENT
                ,KC_RPRN    ,KC_N  ,KC_M   ,KC_COMM  ,KC_DOT   ,KC_SLSH    ,KC_RSFT
                                   ,KC_UP  ,KC_DOWN  ,KC_TRNS  ,KC_QUOT    ,KC_TRNS

      ,KC_TRNS  ,KC_TRNS
      ,KC_TRNS
      ,KC_TRNS  ,KC_TRNS  ,KC_TRNS
),

/* QWERTY
 * the default qwerty keymap. not really used, but i'll keep it here for now.
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 |      |      |------|       |------|        |      |
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
[QWERTY] = KEYMAP(
 KC_TRNS    ,KC_1     ,KC_2     ,KC_3     ,KC_4     ,KC_5    ,KC_TRNS
,KC_TRNS    ,KC_Q     ,KC_W     ,KC_E     ,KC_R     ,KC_T    ,KC_TRNS
,KC_TRNS    ,KC_A     ,KC_S     ,KC_D     ,KC_F     ,KC_G
,KC_TRNS    ,KC_Z     ,KC_X     ,KC_C     ,KC_V     ,KC_B    ,KC_TRNS
,KC_TRNS    ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS

                                                             ,KC_TRNS  ,KC_TRNS
                                                                       ,KC_TRNS
                                                   ,KC_TRNS  ,KC_TRNS  ,KC_TRNS

                ,KC_TRNS    ,KC_6  ,KC_7     ,KC_8     ,KC_9     ,KC_0       ,KC_TRNS
                ,KC_TRNS    ,KC_Y  ,KC_U     ,KC_I     ,KC_O     ,KC_P       ,KC_TRNS
                            ,KC_H  ,KC_J     ,KC_K     ,KC_L     ,KC_SCLN    ,KC_TRNS
                ,KC_TRNS    ,KC_N  ,KC_M     ,KC_COMM  ,KC_DOT   ,KC_SLSH    ,KC_TRNS
                                   ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS    ,KC_TRNS

      ,KC_TRNS  ,KC_TRNS
      ,KC_TRNS
      ,KC_TRNS  ,KC_TRNS  ,KC_TRNS
),

/* CARPALX
 * the keymap i would like to transition to.
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |   1  |   2  |   3  |   4  |   5  |      |           | RIGHT|   6  |   7  |   8  |   9  |   0  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   Q  |   G  |   M  |   L  |   W  |      |           |  L1  |   Y  |   F  |   U  |   B  |   ;  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   D  |   S  |   T  |   N  |   R  |------|           |------|   I  |   A  |   E  |   O  |   H  |        |
 * |--------+------+------+------+------+------|      |           | Meh  |------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   J  |      |           |      |   K  |   P  |   ,  |   .  |   /  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |  Up  |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[CARPALX] = KEYMAP(
 KC_TRNS    ,KC_1     ,KC_2     ,KC_3     ,KC_4     ,KC_5    ,KC_TRNS
,KC_TRNS    ,KC_Q     ,KC_G     ,KC_M     ,KC_L     ,KC_W    ,KC_TRNS
,KC_TRNS    ,KC_D     ,KC_S     ,KC_T     ,KC_N     ,KC_R
,KC_TRNS    ,KC_Z     ,KC_X     ,KC_C     ,KC_V     ,KC_J    ,KC_TRNS
,KC_TRNS    ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS

                                                             ,KC_TRNS  ,KC_TRNS
                                                                       ,KC_TRNS
                                                   ,KC_TRNS  ,KC_TRNS  ,KC_TRNS

                ,KC_TRNS    ,KC_6  ,KC_7     ,KC_8     ,KC_9     ,KC_0       ,KC_TRNS
                ,KC_TRNS    ,KC_Y  ,KC_F     ,KC_U     ,KC_B     ,KC_SCLN    ,KC_TRNS
                            ,KC_I  ,KC_A     ,KC_E     ,KC_O     ,KC_H       ,KC_TRNS
                ,KC_TRNS    ,KC_K  ,KC_P     ,KC_COMM  ,KC_DOT   ,KC_SLSH    ,KC_TRNS
                                   ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS    ,KC_TRNS

      ,KC_TRNS  ,KC_TRNS
      ,KC_TRNS
      ,KC_TRNS  ,KC_TRNS  ,KC_TRNS
),


/* SYSCTL
 * a keymap to control my system.
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      | Mute |VolDn |VolUp |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |MsUpL | MsUp |MsUpR |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |MsLeft| MsDn |MsRght|      | Lock   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |MsDnL | MsDn |      |      | Sleep  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      | Power|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |MidClk|
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |Left  |Right |
 *                                 |      |      |------|       |------| Click| Click|
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[SYSCTL] = KEYMAP(
 KC_TRNS    ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO    ,KC_NO
,KC_NO      ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO    ,KC_NO
,KC_NO      ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO
,KC_NO      ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO    ,KC_NO
,KC_NO      ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO

                                                      ,KC_NO  ,KC_NO
                                                              ,KC_NO
                                              ,KC_NO  ,KC_NO  ,KC_NO

       /*,KC_POP*/,KC_NO    ,KC_NO  ,KC_NO  ,KC_MUTE  ,KC_VOLD  ,KC_VOLU    ,KC_NO
      /*,KC_PTRN*/,KC_NO    ,KC_NO  ,KC_NO  ,KC_NO    ,KC_NO    ,KC_NO      ,KC_NO
                            ,KC_NO  ,KC_NO  ,KC_NO    ,KC_NO    ,KC_NO      ,LCTL(LSFT(KC_PWR))
                  ,KC_NO    ,KC_NO  ,KC_NO  ,KC_NO    ,KC_NO    ,KC_NO      ,KC_SLEP
                                    ,KC_NO  ,KC_NO    ,KC_NO    ,KC_NO      ,KC_PWR

          ,KC_NO  ,KC_NO
          ,KC_NO
          ,KC_NO  ,KC_NO  ,KC_NO
),

/* TEMPLATE
 * keymap template with transparent and non-transparent keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 |      |      |------|       |------|        |      |
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
/*
[TEMPLATE] = KEYMAP(
 KC_TRNS    ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS    ,KC_TRNS
,KC_TRNS    ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS    ,KC_TRNS
,KC_TRNS    ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS
,KC_TRNS    ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS    ,KC_TRNS
,KC_TRNS    ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS

                                                                ,KC_TRNS  ,KC_TRNS
                                                                          ,KC_TRNS
                                                      ,KC_TRNS  ,KC_TRNS  ,KC_TRNS

                ,KC_TRNS    ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS    ,KC_TRNS
                ,KC_TRNS    ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS    ,KC_TRNS
                            ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS    ,KC_TRNS
                ,KC_TRNS    ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS    ,KC_TRNS
                                      ,KC_TRNS  ,KC_TRNS  ,KC_TRNS  ,KC_TRNS    ,KC_TRNS

      ,KC_TRNS  ,KC_TRNS
      ,KC_TRNS
      ,KC_TRNS  ,KC_TRNS  ,KC_TRNS
),
[TEMPLATE] = KEYMAP(
 KC_NO    ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO    ,KC_NO
,KC_NO    ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO    ,KC_NO
,KC_NO    ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO
,KC_NO    ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO    ,KC_NO
,KC_NO    ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO

                                                    ,KC_NO  ,KC_NO
                                                            ,KC_NO
                                            ,KC_NO  ,KC_NO  ,KC_NO

                ,KC_NO    ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO    ,KC_NO
                ,KC_NO    ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO    ,KC_NO
                          ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO    ,KC_NO
                ,KC_NO    ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO    ,KC_NO
                                  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO    ,KC_NO

        ,KC_NO  ,KC_NO
        ,KC_NO
        ,KC_NO  ,KC_NO  ,KC_NO
),
*/
};

// keyboard initialization
void matrix_init_user() {
  ergodox_led_all_on();
  for (int i = LED_BRIGHTNESS_HI; i > LED_BRIGHTNESS_LO; i--) {
    ergodox_led_all_set(i);
    wait_ms(5);
  }
  wait_ms(1000);
  for (int i = LED_BRIGHTNESS_LO; i > 0; i--) {
    ergodox_led_all_set(i);
    wait_ms(10);
  }
  ergodox_led_all_off();
}

// extra keys
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch (id) {

    // mouse
  case MS_UL:
    if (record->event.pressed) {
      mousekey_on(KC_MS_UP);
      mousekey_on(KC_MS_LEFT);
    } else {
      mousekey_off(KC_MS_UP);
      mousekey_off(KC_MS_LEFT);
    }
    break;
  case MS_UR:
    if (record->event.pressed) {
      mousekey_on(KC_MS_UP);
      mousekey_on(KC_MS_RIGHT);
    } else {
      mousekey_off(KC_MS_UP);
      mousekey_off(KC_MS_RIGHT);
    }
    break;
  case MS_DL:
    if (record->event.pressed) {
      mousekey_on(KC_MS_DOWN);
      mousekey_on(KC_MS_LEFT);
    } else {
      mousekey_off(KC_MS_DOWN);
      mousekey_off(KC_MS_LEFT);
    }
    break;
  case MS_DR:
    if (record->event.pressed) {
      mousekey_on(KC_MS_DOWN);
      mousekey_on(KC_MS_RIGHT);
    } else {
      mousekey_off(KC_MS_DOWN);
      mousekey_off(KC_MS_RIGHT);
    }
    break;
  }
  return MACRO_NONE;
}

// tap dances

// flash keyboard on 4x tap, with leds
void flash_each_tap(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    ergodox_right_led_3_on();
    break;
  case 2:
    ergodox_right_led_2_on();
    break;
  case 3:
    ergodox_right_led_1_on();
    break;
  case 4:
    ergodox_right_led_3_off();
    wait_ms(50);
    ergodox_right_led_2_off();
    wait_ms(50);
    ergodox_right_led_1_off();
    break;
  }
}

void flash_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 4) {
    reset_keyboard();
    reset_tap_dance(state);
  }
}

void flash_dance_reset(qk_tap_dance_state_t *state, void *user_data) {
  ergodox_right_led_1_off();
  wait_ms(50);
  ergodox_right_led_2_off();
  wait_ms(50);
  ergodox_right_led_3_off();
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_FLSH] = ACTION_TAP_DANCE_FN_ADVANCED( flash_each_tap, flash_dance_finished, flash_dance_reset ),
};
