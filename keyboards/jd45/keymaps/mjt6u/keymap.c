#include QMK_KEYBOARD_H

enum jd45_layers
{
    _QWERTY,
    _QWERTYNUMMODS,
    _NUMSYM,
    _FUNCTION,
    _NUMPAD,
    _FKEYNUMPAD,
    _ADJUST
};

enum jd45_keycodes
{
    NUMSYM = SAFE_RANGE,
    MACSLEEP,
    USEFNMODS,
    USENUMMODS,
    DYNAMIC_MACRO_RANGE,
};

#include "dynamic_macro.h"

#define LONGPRESS_DELAY 150
#define LAYER_TOGGLE_DELAY 900

#define __MOD__ KC_TRNS
#define F_FNSPC LT(_NUMSYM, KC_SPC)
#define F_NUMSPC LT(_NUMPAD, KC_SPC)
#define F_FNTAB LT(_FUNCTION, KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
    F_FNTAB,       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,          KC_MINS,     KC_BSPC,              \
    CTL_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,                    LT(_ADJUST, KC_QUOT), \
    KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                    SFT_T(KC_ENT),        \
    XXXXXXX,       KC_LALT, KC_LGUI, XXXXXXX,          XXXXXXX,          F_FNSPC,          XXXXXXX, MO(_FUNCTION), MO(_ADJUST), XXXXXXX               \
  ),

  [_QWERTYNUMMODS] = LAYOUT( \
    F_FNTAB,       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,     KC_I,    KC_O,    KC_P,            KC_MINS,     KC_BSPC,              \
    CTL_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,     KC_K,    KC_L,    KC_SCLN,                      LT(_ADJUST, KC_QUOT), \
    KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,     KC_COMM, KC_DOT,  KC_SLSH,                      SFT_T(KC_ENT),        \
    XXXXXXX,       KC_LALT, KC_LGUI, XXXXXXX,          XXXXXXX,          F_NUMSPC,          XXXXXXX, MO(_FKEYNUMPAD), MO(_ADJUST), XXXXXXX               \
  ),

  [_NUMSYM] = LAYOUT( \
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, KC_DEL,  \
    __MOD__, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,          _______, \
    _______, _______, _______, _______, _______, KC_SPC,  KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,          _______, \
    XXXXXXX, __MOD__, __MOD__, XXXXXXX,          XXXXXXX,          _______,          XXXXXXX, __MOD__, __MOD__, XXXXXXX  \
  ),

  [_FUNCTION] = LAYOUT( \
    __MOD__, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
    __MOD__, _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______,          _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, \
    XXXXXXX, __MOD__, __MOD__, XXXXXXX,          XXXXXXX,          _______,          XXXXXXX, __MOD__, __MOD__, XXXXXXX  \
  ),

  [_NUMPAD] = LAYOUT( \
    KC_GRV,  _______, KC_UP,   _______, KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_PSCR, KC_LBRC, KC_RBRC, \
    _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_4,    KC_5,    KC_6,    KC_INS,  KC_HOME, KC_PGUP, _______,          _______, \
    _______, _______, _______, _______, KC_1,    KC_2,    KC_3,    KC_DEL,  KC_END,  KC_PGDN, _______,          _______, \
    XXXXXXX, _______, _______, XXXXXXX,          XXXXXXX,          _______,          XXXXXXX, __MOD__, __MOD__, XXXXXXX  \
  ),

  [_FKEYNUMPAD] = LAYOUT( \
    _______, _______, KC_VOLU, _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, _______, _______, \
    _______, KC_MPRV, KC_VOLD, KC_MNXT, KC_F4,   KC_F5,   KC_F6,   KC_J,    KC_K,    KC_L,    KC_SCLN,          _______, \
    _______, _______, _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_MUTE, KC_MPRV, KC_MNXT, KC_MSTP,          _______, \
    XXXXXXX, _______, _______, XXXXXXX,          XXXXXXX,          _______,          XXXXXXX, __MOD__, __MOD__, XXXXXXX  \
  ),

  [_ADJUST] = LAYOUT( \
    _______, QK_BOOT, _______, _______, _______,   _______, _______,    DYN_REC_START1,  DYN_REC_START2,  _______,  KC_PSCR, _______, _______, \
    _______, _______, _______, _______, USEFNMODS, _______, _______,    DYN_MACRO_PLAY1, DYN_MACRO_PLAY2, MACSLEEP, _______,          _______, \
    _______, _______, _______, _______, _______,   _______, USENUMMODS, _______,         _______,         _______,  _______,          _______, \
    XXXXXXX, _______, _______, XXXXXXX,            XXXXXXX,             _______,                          XXXXXXX, __MOD__,  __MOD__, XXXXXXX  \
  )
};

void persistent_default_layer_set(uint16_t default_layer)
{
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

static bool singular_key = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    uint16_t macro_kc = (keycode == MO(_ADJUST) ? DYN_REC_STOP : keycode);
    if (!process_record_dynamic_macro(macro_kc, record))
    {
        return false;
    }
    println(" ");
    print("process record");

    switch (keycode)
    {
    case MACSLEEP:
        if (record->event.pressed)
        {
            // ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT, KC_PWR);
            register_code(KC_RSFT);
            register_code(KC_RCTL);
            register_code(KC_PWR);
            unregister_code(KC_PWR);
            unregister_code(KC_RCTL);
            unregister_code(KC_RSFT);
        }
        return false;
        break;
    case USEFNMODS:
        if (record->event.pressed)
        {
            persistent_default_layer_set(1UL << _QWERTY);
#ifdef AUDIO_ENABLE
            PLAY_SONG(tone_fnpc);
#endif
            print("Space-FN");
        }
        return false;
        break;
    case USENUMMODS:
        if (record->event.pressed)
        {
            persistent_default_layer_set(1UL << _QWERTYNUMMODS);
#ifdef AUDIO_ENABLE
            PLAY_SONG(tone_fnmac);
#endif
            print("Space-Numpad");
        }
        return false;
        break;
    default:
        singular_key = false;
        break;
    }

    return true;
};

void matrix_init_user(void)
{
#ifdef AUDIO_ENABLE
    startup_user();
#endif
    // debug_enable = true;
}
