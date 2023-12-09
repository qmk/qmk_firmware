// Layout picture at http://www.keyboard-layout-editor.com/#/gists/125febfad6960add078e6f14256539b6

#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
#include "audio.h"
#endif
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY  0
#define _NUMPAD  1
#define _LOCKED  2
#define _RAISE   3
#define _LOWER   4
#define _FUNCTN  5
#define _MEDIA   6
#define _ONESHOT 7

enum planck_keycodes {
    QWERTY = SAFE_RANGE,
    NUMPAD,
    RAISE,
    LOWER,
    MEDIA,
    ONESHOT,
    DYNAMIC_MACRO_RANGE
};

#include "dynamic_macro.h"

// Key code names
#define SFT_ENT  MT(MOD_RSFT, KC_ENT)    // Tap for enter, hold for right shift
#define LOCK     TG(_LOCKED)
#define KC_PSTE  KC_PASTE
#define ZOOM_IN  LCTL(KC_EQL)
#define ZOOM_OUT LCTL(KC_MINS)
#define ZOOM_NML LCTL(KC_0)

#ifdef TAP_DANCE_ENABLE
#define SFT_CAP  TD(0)  // Left shift, double tap for caps
#endif
#ifndef TAP_DANCE_ENABLE
#define SFT_CAP  KC_LSFT // Regular left shift
#endif

// Tap Dance Definitions
#ifdef TAP_DANCE_ENABLE
tap_dance_action_t tap_dance_actions[] = {
    [0]  = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS)
};
#endif

// Layout definitions
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | BKSP |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |   '  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |*Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  |SftEnt|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  | Mute | Lower|    Space    | Raise|   /  | Left | Down | Right|
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    SFT_CAP, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   SFT_ENT,
    KC_LCTL, KC_LGUI, KC_LALT, MEDIA,   LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT
),

/* NUMPAD
 * ,-----------------------------------------------------------------------------------.
 * |QWERTY| NULL |  Up  | NULL | NULL | NULL | NULL |   /  |   7  |   8  |   9  |   -  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Left | Down | Right| NULL | NULL | NULL |   *  |   4  |   5  |   6  |   +  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |NumLck| NULL | NULL | NULL | NULL | NULL |BckSp |   1  |   2  |   3  |  Ent |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |   0  |   .  |   ,  |   =  |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_planck_grid(
    QWERTY,  XXXXXXX,   KC_UP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSLS,  KC_P7,  KC_P8,   KC_P9,   KC_PMNS,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX, XXXXXXX, KC_PAST,  KC_P4,  KC_P5,   KC_P6,   KC_PPLS,
    _______, KC_NUM,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,  KC_P1,  KC_P2,   KC_P3,   KC_PENT,
    _______, _______, _______, _______, _______, _______, _______, _______,  KC_P0,  KC_PDOT, KC_PCMM, KC_PEQL
),

/* LOCK
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |      |      |      |      |      | Enter|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | NULL |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOCKED] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  KC_ENT,
    _______, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* RAISE
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F11 |  F12 |  F13 |  F14 |  F15 |      |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |LShift|  F16 |  F17 |  F18 |  F19 |  F20 |      |ISO # |ISO / | NULL | PgUp | Enter|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      | Home | PgDn |  End |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_GRV , KC_1,    KC_2,      KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
    KC_DEL , KC_F11,  KC_F12,   KC_F13,  KC_F14, KC_F15, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    KC_LSFT, KC_F16,  KC_F17,   KC_F18,  KC_F19, KC_F20, _______, KC_NUHS, KC_NUBS, XXXXXXX, KC_PGUP, KC_ENT,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_END
),

/* LOWER
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |      |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |LShift|  F6  |  F7  |  F8  |  F9  |  F10 |      |ISO ~ |ISO | | NULL | PgUp | Enter|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      | Home | PgDn |  End |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL ,
    KC_DEL , KC_F1,   KC_F2,   KC_F3,    KC_F4, KC_F5,   _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
    KC_LSFT, KC_F6,   KC_F7,   KC_F8,    KC_F9, KC_F10,  _______, S(KC_NUHS), S(KC_NUBS), XXXXXXX, KC_PGUP, KC_ENT ,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_END
),

/* MEDIA AND COMMANDS
 * ,-----------------------------------------------------------------------------------.
 * | NULL | NULL |WbHome| NULL | NULL | NULL |Again | NULL |Insert| NULL |PrntSc| NULL |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | NULL | NULL |WbSrch| NULL | Find | NULL | NULL | NULL | NULL | NULL |PlyMc1|PlyMc2|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |LShift| NULL | NULL | Calc | NULL | NULL | NULL | NULL |ZoomOu|ZoomIn| Prev |RecStp|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |ONESHT| NULL | NULL |      | Vol- |     Mute    | Vol+ |Zoom 0| Stop | Next | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_MEDIA] = LAYOUT_planck_grid(
	XXXXXXX, XXXXXXX, KC_WHOM, XXXXXXX, XXXXXXX, XXXXXXX, KC_AGAIN, XXXXXXX, KC_INS,   XXXXXXX, KC_PSCR, XXXXXXX,
	XXXXXXX, XXXXXXX, KC_WSCH, XXXXXXX, KC_FIND, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, DM_PLY1, DM_PLY2,
	KC_LSFT, XXXXXXX, XXXXXXX, KC_CALC, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, ZOOM_OUT, ZOOM_IN, KC_MPRV, DM_RSTP,
	ONESHOT, XXXXXXX, XXXXXXX, _______, KC_VOLD, KC_MUTE, KC_MUTE,  KC_VOLU, ZOOM_NML, KC_MSTP, KC_MNXT, KC_MPLY
),

/* ONESHOT
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |RecMc1|RecMc2|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ONESHOT] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, DM_REC1, DM_REC2,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* FUNCTIONS
 * ,-----------------------------------------------------------------------------------.
 * | SLEEP| NULL | NULL | NULL | NULL | NULL | NULL | NULL | NULL | NULL | NULL | POWER|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | WAKE | NULL | NULL | NULL | NULL | NULL | NULL | NULL | NULL | NULL | NULL | NULL |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | NULL | NULL | NULL |AudOff|MusOff|QWERTY|NUMPAD|Mus On|Aud On| NULL |Voice+|SysReq|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Reset| NULL | LOCK | NULL |      |     NULL    |      | NULL |AGNorm|Voice-|AGSwap|
 * `-----------------------------------------------------------------------------------'
 */
[_FUNCTN] = LAYOUT_planck_grid(
	KC_SLEP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PWR,
	KC_WAKE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
	XXXXXXX, XXXXXXX, XXXXXXX, AU_OFF,  MU_OFF,  QWERTY,  NUMPAD,  MU_ON,   AU_ON,   XXXXXXX, AU_NEXT, KC_SYRQ,
	QK_BOOT, XXXXXXX, LOCK,    XXXXXXX, _______, XXXXXXX, XXXXXXX, _______, XXXXXXX, AG_NORM, AU_PREV, AG_SWAP
)

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2] = SONG(QWERTY_SOUND);
float tone_numpad[][2] = SONG(NUM_LOCK_ON_SOUND);
float tone_oneshot[][2] = SONG(TERMINAL_SOUND);
float tone_dyn_macro_rec[][2] = SONG(SONIC_RING);
float tone_dyn_macro_stop[][2] = SONG(COIN_SOUND);
#endif

void press_key(uint16_t key) {
    register_code(key);
    unregister_code(key);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // uint16_t macro_kc = (keycode == ONESHOT ? DM_RSTP : keycode);
    if (!process_record_dynamic_macro(keycode, record)) {
        switch(keycode) {
          case QK_DYNAMIC_MACRO_RECORD_START_1:
          case QK_DYNAMIC_MACRO_RECORD_START_2:
#ifdef AUDIO_ENABLE
              PLAY_SONG(tone_dyn_macro_rec);
#endif
              break;
          case QK_DYNAMIC_MACRO_RECORD_STOP:
#ifdef AUDIO_ENABLE
              PLAY_SONG(tone_dyn_macro_stop);
#endif
              break;
        }
        return false;
    }
    switch (keycode) {
        case ONESHOT:
            if (record->event.pressed) {
                layer_on(_ONESHOT);
                set_oneshot_layer(_ONESHOT, ONESHOT_START);
                clear_oneshot_layer_state(ONESHOT_PRESSED);
#ifdef AUDIO_ENABLE
                PLAY_SONG(tone_oneshot);
#endif
            }
            return false;
            break;
        case QWERTY:
            if (record->event.pressed) {
                if (IS_LAYER_ON(_NUMPAD)) {
#ifdef AUDIO_ENABLE
                    PLAY_SONG(tone_qwerty);
#endif
                    layer_off(_NUMPAD);
                }
            }
            return false;
            break;
        case NUMPAD:
            if (record->event.pressed) {
                if (!IS_LAYER_ON(_NUMPAD)) {
#ifdef AUDIO_ENABLE
                    PLAY_SONG(tone_numpad);
#endif
                    layer_on(_NUMPAD);
                }
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_RAISE, _LOWER, _FUNCTN);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_RAISE, _LOWER, _FUNCTN);
            }
            return false;
            break;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_RAISE, _LOWER, _FUNCTN);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_RAISE, _LOWER, _FUNCTN);
            }
            return false;
            break;
        case MEDIA:
            if (record->event.pressed) {
                layer_on(_MEDIA);
            } else {
                layer_off(_MEDIA);
            }
            return false;
            break;
    }
    return true;
}
