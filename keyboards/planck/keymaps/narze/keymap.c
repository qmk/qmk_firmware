#include QMK_KEYBOARD_H
#include "narze.h"
#ifdef AUDIO_ENABLE
    #include "audio.h"
#endif
#include "keymap_colemak.h"

extern keymap_config_t keymap_config;

enum planck_layers {
    _QWERTY,
    _COLEMAK,
    _QWOC,
    _LOWER,
    _RAISE,
    _PLOVER,
    _SUPERDUPER,
    _DEV,
    _MOUSE,
    _ADJUST
};

enum planck_keycodes {
    QWERTY = SAFE_RANGE,
    COLEMAK,
    QWOC,
    PLOVER,
    SUPERDUPER,
    DEV,
    MOUSE,
    LOWER,
    RAISE,
    BACKLIT,
    EXT_PLV,
    SDTOGG, // Toggle SuperDuper
    GUI_UNDS,
    LSFT_LPRN,
};

enum process_combo_event {
    CB_SUPERDUPER,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | F19  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Hp/Ec|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Sft/(| Z/Dv |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  | SD-/ |Sft/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Rse/[| Ctrl | Alt  | GUI/_|Lower |    Space    | Raise| Bksp | Alt  | Ctrl | Low/]|
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_F19,
    HPR_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    LSFT_LPRN, LT(_DEV, KC_Z),   KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  LT(_SUPERDUPER, KC_SLSH), SFT_ENT,
    LT(_RAISE, KC_LBRC), KC_LCTL, KC_LALT, GUI_UNDS, LOWER,   KC_SPC,  KC_SPC, RAISE,   KC_BSPC, ALT_COLN, KC_RCTL,   LT(_LOWER, KC_RBRC)
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  |  -   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Hp/Ec|   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Sft/(| Z/Dv |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  | SD-/ |Sft/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI/_|Lower |    Space    | Raise| Bksp | Alt  | Ctrl | Low/]|
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,    KC_MINS,
    HPR_ESC, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,       KC_QUOT,
    LSFT_LPRN, LT(_DEV, KC_Z),   KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  LT(_SUPERDUPER, KC_SLSH), SFT_ENT,
    LT(_RAISE, KC_LBRC), KC_LCTL, KC_LALT, GUI_UNDS, LOWER,   KC_SPC,  KC_SPC, RAISE,   KC_BSPC, ALT_COLN, KC_RCTL,   LT(_LOWER, KC_RBRC)
),

/* Qwerty on software Colemak : Useful for gaming with qwerty keymaps! */
[_QWOC] = LAYOUT_planck_grid(
    KC_TAB,  CM_Q,    CM_W,    CM_E,    CM_R,    CM_T,    CM_Y,    CM_U,    CM_I,    CM_O,    CM_P,    KC_MINS,
    HPR_ESC, CM_A,    CM_S,    CM_D,    CM_F,    CM_G,    CM_H,    CM_J,    CM_K,    CM_L,    CM_SCLN, KC_QUOT,
    LSFT_LPRN, LT(_DEV, KC_Z),   CM_X,    CM_C,    CM_V,    CM_B,    CM_N,    CM_M,    CM_COMM, CM_DOT,  LT(_SUPERDUPER, CM_SLSH), SFT_ENT,
    LT(_RAISE, KC_LBRC), KC_LCTL, KC_LALT, GUI_UNDS, LOWER,   KC_SPC,  KC_SPC, RAISE,   KC_BSPC, ALT_COLN, KC_RCTL,   LT(_LOWER, KC_RBRC)
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |      |      |     |Sft/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,S(KC_NUHS),_______,_______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |      |      |     |Sft/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_TILD, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |TogOut|   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_PLOVER] = LAYOUT_planck_grid(
    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   ,
    XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX
),

/* SuperDuper : https://gist.github.com/narze/861e2167784842d38771
 * /-----------------------------------------------------------------------------------\
 * |      |      |      |      |      |      |      |      |  T←  |  T→  |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Alt  | [SuperDuper]| Bksp | Gui  |  ←   |  ↓   |   ↑  |  →   | Del  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |   Shift     |      |      |      |      |      |
 * \-----------------------------------------------------------------------------------/
 */
[_SUPERDUPER] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, S(LGUI(KC_LBRC)), S(LGUI(KC_RBRC)), _______, _______,
    _______, KC_LALT, _______, _______, KC_BSPC, KC_LGUI, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_DEL, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, KC_LSFT, KC_LSFT, _______, _______, _______, _______, _______
),

/* Dev Layer
 * /-----------------------------------------------------------------------------------\
 * |      |      |      |      |      |      |      |   -  |   +  |   (  |   )  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |   _  |   [  |   ]  |   {  |   }  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |   =  |   |  |   <  |   >  |   ?  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * \-----------------------------------------------------------------------------------/
 */
[_DEV] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, KC_MINS, S(KC_EQL), S(KC_9), S(KC_0), _______,
    _______, _______, _______, _______, _______, _______, S(KC_MINS), KC_LBRC, KC_RBRC, S(KC_LBRC), S(KC_RBRC), _______,
    _______, _______, _______, _______, _______, _______,  KC_EQL, S(KC_BSLASH), S(KC_COMM), S(KC_DOT), S(KC_SLSH), _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Mouse
 * /-----------------------------------------------------------------------------------\
 * |      |      |  S↑  |  M↑  |  S↓  |      |      |      |  S↑  |  S↓  |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |  M←  |  M↓  |  M→  |      |  M←  |  M↓  |  M↑  |  M→  |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |[Mouse|      |      |      |  M3  |  M3  |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |  M2  |  LeftClick  |  M2  |      |      |      |      |
 * \-----------------------------------------------------------------------------------/
 */
[_MOUSE] = LAYOUT_planck_grid(
    _______, _______, KC_WH_U, KC_MS_U, KC_WH_D, _______, _______, _______, KC_WH_U, KC_WH_D, _______, _______,
    _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______,
    _______, _______, _______, _______, _______, KC_BTN3, KC_BTN3, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, KC_BTN2, KC_BTN1, KC_BTN1, KC_BTN2, _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|QwOnCo|Plover|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|SDtogg|      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
    _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, QWOC,    PLOVER,  _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  SDTOGG,  _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, BACKLIT
)

};

#ifdef AUDIO_ENABLE
    float tone_plover[][2]     = SONG(PLOVER_SOUND);
    float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
    float tone_coin[][2]       = SONG(VIOLIN_SOUND);
    float tone_goodbye[][2]    = SONG(GOODBYE_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);

                set_superduper_key_combo_layer(_QWERTY);
            }
            return false;

        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);

                set_superduper_key_combo_layer(_COLEMAK);
            }
            return false;

        case QWOC:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWOC);

                set_superduper_key_combo_layer(_QWOC);
            }
            return false;

        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;

        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;

        case BACKLIT:
            if (record->event.pressed) {
                register_code(KC_RSFT);
                #ifdef BACKLIGHT_ENABLE
                    backlight_step();
                #endif
            } else {
                unregister_code(KC_RSFT);
            }
            return false;

        case PLOVER:
            if (record->event.pressed) {
                #ifdef AUDIO_ENABLE
                    stop_all_notes();
                    PLAY_SONG(tone_plover);
                #endif
                layer_off(_RAISE);
                layer_off(_LOWER);
                layer_off(_ADJUST);
                layer_on(_PLOVER);
                if (!eeconfig_is_enabled()) {
                        eeconfig_init();
                }
                keymap_config.raw = eeconfig_read_keymap();
                keymap_config.nkro = 1;
                eeconfig_update_keymap(keymap_config.raw);
            }
            return false;

        case EXT_PLV:
            if (record->event.pressed) {
                #ifdef AUDIO_ENABLE
                    PLAY_SONG(tone_plover_gb);
                #endif
                layer_off(_PLOVER);
            }
            return false;

        case SDTOGG:
            if (record->event.pressed) {
                bool enabled = toggle_superduper_mode();

                #ifdef AUDIO_ENABLE
                    if (enabled) {
                        PLAY_SONG(tone_coin);
                    } else {
                        PLAY_SONG(tone_goodbye);
                    }
                #endif
            }
            return false;

        // Macros

        // 1. Hold for LGUI, tap for Underscore
        case GUI_UNDS:
            perform_space_cadet(record, keycode, KC_LGUI, KC_LSFT, KC_MINS);
            return false;

        // 2. Hold for LSHIFT, tap for Parens open
        case LSFT_LPRN:
            perform_space_cadet(record, keycode, KC_LSFT, KC_LSFT, KC_9);
            return false;

        default:
            return true;
    }
    return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
}

void matrix_setup(void) {
    set_superduper_key_combos();
}

void matrix_scan_user(void) {
}

void process_combo_event(uint16_t combo_index, bool pressed) {
    if (pressed) {
        switch(combo_index) {
            case CB_SUPERDUPER:
                layer_on(_SUPERDUPER);
                break;
        }
    } else {
        layer_off(_SUPERDUPER);
        unregister_mods(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT)); // Sometimes mods are held, unregister them
    }
}
