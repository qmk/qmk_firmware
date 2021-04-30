#include QMK_KEYBOARD_H

enum layers {
    _DVORAK,
    _QWERTY,
    _CODE,
};

// work in progress simulation of kakoune behavior
bool kak_mode = false;

enum tapdances {
    _LCTLGUI,
};

enum keycodes {
    KC_KAK = SAFE_RANGE,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [_LCTLGUI] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_LGUI),
};

// Layers
#define KC_DVORK DF(_DVORAK)
#define KC_QWRTY DF(_QWERTY)
#define KC_CODE MO(_CODE)

// Modifiers
#define KC_COPY LCTL(KC_C)
#define KC_PASTE LCTL(KC_V)

// Tapdances
#define KC_LCG TD(_LCTLGUI)

// Misc
#define KC_ KC_TRNS
#define KC_RESET RESET

// Used to create a keymap using only KC_ prefixed keys
#ifndef LAYOUT_kc
#define LAYOUT_kc( \
    L00, L01, L02, L03, L04, L05,           R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15,           R10, R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24, L25,           R20, R21, R22, R23, R24, R25, \
    L30, L31, L32, L33, L34, L35, LT4, RT4, R30, R31, R32, R33, R34, R35, \
                        LT1, LT2, LT3, RT3, RT2, RT1 \
    ) \
    LAYOUT( \
        KC_##L00, KC_##L01, KC_##L02, KC_##L03, KC_##L04, KC_##L05,                     KC_##R00, KC_##R01, KC_##R02, KC_##R03, KC_##R04, KC_##R05, \
        KC_##L10, KC_##L11, KC_##L12, KC_##L13, KC_##L14, KC_##L15,                     KC_##R10, KC_##R11, KC_##R12, KC_##R13, KC_##R14, KC_##R15, \
        KC_##L20, KC_##L21, KC_##L22, KC_##L23, KC_##L24, KC_##L25,                     KC_##R20, KC_##R21, KC_##R22, KC_##R23, KC_##R24, KC_##R25, \
        KC_##L30, KC_##L31, KC_##L32, KC_##L33, KC_##L34, KC_##L35, KC_##LT4, KC_##RT4, KC_##R30, KC_##R31, KC_##R32, KC_##R33, KC_##R34, KC_##R35, \
                                                KC_##LT1, KC_##LT2, KC_##LT3, KC_##RT3, KC_##RT2, KC_##RT1 \
    )
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DVORAK] = LAYOUT_kc(
//  ┌─────┬─────┬─────┬─────┬─────┬─────┐              ┌─────┬─────┬─────┬─────┬─────┬─────┐
     PSCR ,  1  ,  2  ,  3  ,  4  ,  5  ,                 6  ,  7  ,  8  ,  9  ,  0  ,QWRTY,
//  ├─────┼─────┼─────┼─────┼─────┼─────┤              ├─────┼─────┼─────┼─────┼─────┼─────┤
      TAB ,QUOTE,COMMA, DOT ,  P  ,  Y  ,                 F  ,  G  ,  C  ,  R  ,  L  ,SLASH,
//  ├─────┼─────┼─────┼─────┼─────┼─────┤              ├─────┼─────┼─────┼─────┼─────┼─────┤
      ESC ,  A  ,  O  ,  E  ,  U  ,  I  ,                 D  ,  H  ,  T  ,  N  ,  S  ,MINUS,
//  ├─────┼─────┼─────┼─────┼─────┼─────┬─────┐  ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┤
     LGUI ,SCLN ,  Q  ,  J  ,  K  ,  X  ,PGUP ,   PGDN ,  B  ,  M  ,  W  ,  V  ,  Z  , ENT ,
//  └─────┴─────┴─────┴─────┼─────┴─────┴─────┼  ┼─────┴─────┴─────┼─────┴─────┴─────┴─────┘
                              LCG , LALT, LSFT,   BSPC , SPC ,CODE
//                          └─────┴─────┴─────┘  └─────┴─────┴─────┘
  ),

  [_QWERTY] = LAYOUT_kc(
//  ┌─────┬─────┬─────┬─────┬─────┬─────┐              ┌─────┬─────┬─────┬─────┬─────┬─────┐
          ,     ,     ,     ,     ,     ,                    ,     ,     ,     ,     ,DVORK,
//  ├─────┼─────┼─────┼─────┼─────┼─────┤              ├─────┼─────┼─────┼─────┼─────┼─────┤
          ,  Q  ,  W  ,  E  ,  R  ,  T  ,                 Y  ,  U  ,  I  ,  O  ,  P  ,BSLS ,
//  ├─────┼─────┼─────┼─────┼─────┼─────┤              ├─────┼─────┼─────┼─────┼─────┼─────┤
          ,  A  ,  S  ,  D  ,  F  ,  G  ,                 H  ,  J  ,  K  ,  L  ,SCLN ,QUOTE,
//  ├─────┼─────┼─────┼─────┼─────┼─────┬─────┐  ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┤
          ,  Z  ,  X  ,  C  ,  V  ,  B  ,     ,        ,  N  ,  M  ,COMMA, DOT ,SLASH,     ,
//  └─────┴─────┴─────┴─────┼─────┴─────┴─────┼  ┼─────┴─────┴─────┼─────┴─────┴─────┴─────┘
                                  ,     ,     ,        ,     ,
//                          └─────┴─────┴─────┘  └─────┴─────┴─────┘
  ),


  [_CODE] = LAYOUT_kc(
//  ┌─────┬─────┬─────┬─────┬─────┬─────┐              ┌─────┬─────┬─────┬─────┬─────┬─────┐
      F12 , F1  , F2  , F3  , F4  , F5  ,                F6  , F7  , F8  , F9  , F10 , F11 ,
//  ├─────┼─────┼─────┼─────┼─────┼─────┤              ├─────┼─────┼─────┼─────┼─────┼─────┤
          , LT  ,LCBR ,LBRC ,LPRN ,AMPR ,                AT  ,MINUS,SLASH, DLR ,EXLM ,BSLS ,
//  ├─────┼─────┼─────┼─────┼─────┼─────┤              ├─────┼─────┼─────┼─────┼─────┼─────┤
     GRAVE, GT  ,RCBR ,RBRC ,RPRN ,PIPE ,               CIRC ,PLUS ,ASTR ,PERC , UP  , EQL ,
//  ├─────┼─────┼─────┼─────┼─────┼─────┬─────┐  ┌─────┬─────┼─────┼─────┼─────┼─────┼─────┤
     RESET,     ,     ,     ,     ,     ,HOME ,    END , KAK ,COPY ,PASTE,LEFT ,DOWN ,RIGHT,
//  └─────┴─────┴─────┴─────┼─────┴─────┴─────┼  ┼─────┴─────┴─────┼─────┴─────┴─────┴─────┘
                                  ,     ,     ,    DEL ,     ,
//                          └─────┴─────┴─────┘  └─────┴─────┴─────┘
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_KAK: {
            if (record->event.pressed) {
                kak_mode = !kak_mode;
                return false;
            }
        } break;
    }

    if (kak_mode) {
        switch (keycode) {
            case KC_ESC: {
                if (record->event.pressed) {
                    kak_mode = false;
                    return false;
                }
            } break;
            case KC_I: {
                if (record->event.pressed) {
                    kak_mode = false;
                    tap_code(KC_LEFT);
                    return false;
                }
            } break;
            case KC_A: {
                if (record->event.pressed) {
                    kak_mode = false;
                    tap_code(KC_RIGHT);
                    return false;
                }
            } break;
            case KC_W: {
                if (record->event.pressed) {
                    uint8_t mods = get_mods();
                    if ((mods & MOD_MASK_SHIFT) == 0)
                        tap_code(KC_RIGHT);
                    set_mods(MOD_MASK_CS);
                    tap_code(KC_RIGHT);
                    set_mods(mods);
                    return false;
                }
            } break;
            case KC_B: {
                if (record->event.pressed) {
                    uint8_t mods = get_mods();
                    if ((mods & MOD_MASK_SHIFT) == 0)
                        tap_code(KC_LEFT);
                    set_mods(MOD_MASK_CS);
                    tap_code(KC_LEFT);
                    set_mods(mods);
                    return false;
                }
            } break;
            case KC_H: {
                if (record->event.pressed) {
                    if ((get_mods() & MOD_MASK_ALT) == 0)
                        tap_code(KC_LEFT);
                    else
                        tap_code(KC_HOME);
                    return false;
                }
            } break;
            case KC_J: {
                if (record->event.pressed) {
                    tap_code(KC_DOWN);
                    return false;
                }
            } break;
            case KC_K: {
                if (record->event.pressed) {
                    tap_code(KC_UP);
                    return false;
                }
            } break;
            case KC_L: {
                if (record->event.pressed) {
                    if ((get_mods() & MOD_MASK_ALT) == 0)
                        tap_code(KC_RIGHT);
                    else
                        tap_code(KC_END);
                    return false;
                }
            } break;
            case KC_X: {
                if (record->event.pressed) {
                    uint8_t mods = get_mods();
                    tap_code(KC_HOME);
                    set_mods(MOD_MASK_SHIFT);
                    tap_code(KC_END);
                    set_mods(mods);
                    return false;
                }
            } break;
            case KC_Y: {
                if (record->event.pressed) {
                    tap_code16(KC_COPY);
                    return false;
                }
            } break;
            case KC_D: {
                if (record->event.pressed) {
                    tap_code16(KC_COPY);
                    tap_code(KC_BSPC);
                    return false;
                }
            } break;
            case KC_C: {
                if (record->event.pressed) {
                    tap_code(KC_BSPC);
                    kak_mode = false;
                    return false;
                }
            } break;
            case KC_P: {
                if (record->event.pressed) {
                    if ((get_mods() & MOD_MASK_SHIFT) == 0)
                        tap_code(KC_RIGHT);
                    else
                        tap_code(KC_LEFT);
                    tap_code16(KC_PSTE);
                    return false;
                }
            } break;
            case KC_R: {
                if (record->event.pressed) {
                    tap_code16(KC_PSTE);
                    return false;
                }
            } break;
            case KC_U: {
                if (record->event.pressed) {
                    if ((get_mods() & MOD_MASK_SHIFT) == 0)
                        tap_code16(LCTL(KC_Z));
                    else
                        tap_code16(LCTL(KC_Y));
                    return false;
                }
            } break;
        }
    }
    return true;
}
