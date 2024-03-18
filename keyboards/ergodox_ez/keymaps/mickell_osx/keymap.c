#include QMK_KEYBOARD_H
#include "version.h"
#include "i18n.h"

enum custom_keycodes {
  RGB_SLD = SAFE_RANGE,
  HSV_86_255_128,
  HSV_172_255_255,
  HSV_27_255_255,
  BRIGHT_TOGGLE,
  VOL_TOGGLE,
  ST_MACRO_0, // macro for cmd + c
  ST_MACRO_1, // macro for cmd + v
  ST_MACRO_2, // macro for "435-"
  ST_MACRO_3, // macro for "kellchidester@gmail.com"
  ST_MACRO_4, // macro for cmd + p
  ST_MACRO_5, // macro for "Mickell Morris"
  ST_MACRO_6, // macro for "morris.mickell@gmail.com"
  ST_MACRO_7, // macro for cmd + z
  CMD_SHIFT,
  MAC_SPOTLIGHT,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌────────────┬────────────┬────────────┬──────┬──────┬───────────┬───────────────┐           ┌────────────┬──────────┬─────┬──────┬───────────────┬────────────┬────────────┐
//    │    esc     │     1      │     2      │  3   │  4   │     5     │       [       │           │     ]      │    6     │  7  │  8   │       9       │     0      │     `      │
//    ├────────────┼────────────┼────────────┼──────┼──────┼───────────┼───────────────┤           ├────────────┼──────────┼─────┼──────┼───────────────┼────────────┼────────────┤
//    │    tab     │     q      │     w      │  e   │  r   │     t     │ BRIGHT_TOGGLE │           │     '      │    y     │  u  │  i   │       o       │     p      │     \      │
//    ├────────────┼────────────┼────────────┼──────┼──────┼───────────┼───────────────┘           └────────────┼──────────┼─────┼──────┼───────────────┼────────────┼────────────┤
//    │    caps    │     a      │     s      │  d   │  f   │     g     │                                        │    h     │  j  │  k   │       l       │  LT(2, ;)  │     -      │
//    ├────────────┼────────────┼────────────┼──────┼──────┼───────────┼───────────────┐           ┌────────────┼──────────┼─────┼──────┼───────────────┼────────────┼────────────┤
//    │ left_SHIFT │     z      │     x      │  c   │  v   │     b     │  VOL_TOGGLE   │           │     =      │    n     │  m  │  ,   │       .       │     /      │ rght_SHIFT │
//    ├────────────┼────────────┼────────────┼──────┼──────┼───────────┴───────────────┘           └────────────┴──────────┼─────┼──────┼───────────────┼────────────┼────────────┤
//    │   TG(1)    │ ST_MACRO_0 │ ST_MACRO_1 │ left │ rght │                                                               │ up  │ down │ MAC_SPOTLIGHT │ ST_MACRO_7 │ ST_MACRO_4 │
//    └────────────┴────────────┴────────────┴──────┴──────┼───────────┬───────────────┐           ┌────────────┬──────────┼─────┴──────┴───────────────┴────────────┴────────────┘
//                                                         │ left_GUI  │   left_CTRL   │           │ rght_CTRL  │ rght_GUI │
//                                                         └───────────┼───────────────┤           ├────────────┼──────────┘
//                                                                     │  ST_MACRO_2   │           │ ST_MACRO_5 │
//                                                  ┌──────┬───────────┼───────────────┤           ├────────────┼──────────┬─────┐
//                                                  │ bspc │ CMD_SHIFT │  ST_MACRO_3   │           │ ST_MACRO_6 │   ent    │ spc │
//                                                  └──────┴───────────┴───────────────┘           └────────────┴──────────┴─────┘
[0] = LAYOUT_ergodox_pretty(
  KC_ESCAPE     , KC_1       , KC_2       , KC_3    , KC_4     , KC_5        , KC_LBRC       ,             KC_RBRC       , KC_6         , KC_7     , KC_8     , KC_9          , KC_0           , KC_GRAVE      ,
  KC_TAB        , KC_Q       , KC_W       , KC_E    , KC_R     , KC_T        , BRIGHT_TOGGLE ,             KC_QUOTE      , KC_Y         , KC_U     , KC_I     , KC_O          , KC_P           , KC_BSLS       ,
  KC_CAPS       , KC_A       , KC_S       , KC_D    , KC_F     , KC_G        ,                                             KC_H         , KC_J     , KC_K     , KC_L          , LT(2, KC_SCLN) , KC_MINUS      ,
  KC_LEFT_SHIFT , KC_Z       , KC_X       , KC_C    , KC_V     , KC_B        , VOL_TOGGLE    ,             KC_EQUAL      , KC_N         , KC_M     , KC_COMMA , KC_DOT        , KC_SLASH       , KC_RIGHT_SHIFT,
  TG(1)         , ST_MACRO_0 , ST_MACRO_1 , KC_LEFT , KC_RIGHT ,                                                                          KC_UP    , KC_DOWN  , MAC_SPOTLIGHT , ST_MACRO_7     , ST_MACRO_4    ,
                                                                 KC_LEFT_GUI , KC_LEFT_CTRL  ,             KC_RIGHT_CTRL , KC_RIGHT_GUI                                                                        ,
                                                                               ST_MACRO_2    ,             ST_MACRO_5                                                                                          ,
                                                      KC_BSPC  , CMD_SHIFT   , ST_MACRO_3    ,             ST_MACRO_6    , KC_ENTER     , KC_SPACE
),

//    ┌─────────────┬────┬─────────────┬─────────────┬─────────────┬──────────────────┬────────────────┐           ┌────────────────────┬─────────┬─────────────┬────┬────┬─────┬─────────────┐
//    │     esc     │ f1 │     f2      │     f3      │     f4      │        f5        │  tRANSPARENT   │           │    tRANSPARENT     │   f6    │     f7      │ f8 │ f9 │ f10 │     f11     │
//    ├─────────────┼────┼─────────────┼─────────────┼─────────────┼──────────────────┼────────────────┤           ├────────────────────┼─────────┼─────────────┼────┼────┼─────┼─────────────┤
//    │ tRANSPARENT │ !  │      @      │      {      │      }      │        |         │  tRANSPARENT   │           │    tRANSPARENT     │   up    │      7      │ 8  │ 9  │  *  │     f12     │
//    ├─────────────┼────┼─────────────┼─────────────┼─────────────┼──────────────────┼────────────────┘           └────────────────────┼─────────┼─────────────┼────┼────┼─────┼─────────────┤
//    │ tRANSPARENT │ #  │      $      │      (      │      )      │        `         │                                                 │  down   │      4      │ 5  │ 6  │  +  │ tRANSPARENT │
//    ├─────────────┼────┼─────────────┼─────────────┼─────────────┼──────────────────┼────────────────┐           ┌────────────────────┼─────────┼─────────────┼────┼────┼─────┼─────────────┤
//    │ tRANSPARENT │ %  │      ^      │      [      │      ]      │        ~         │  tRANSPARENT   │           │    tRANSPARENT     │    &    │      1      │ 2  │ 3  │  \  │ tRANSPARENT │
//    ├─────────────┼────┼─────────────┼─────────────┼─────────────┼──────────────────┴────────────────┘           └────────────────────┴─────────┼─────────────┼────┼────┼─────┼─────────────┤
//    │ tRANSPARENT │ =  │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │                                                                              │ tRANSPARENT │ .  │ 0  │  =  │ tRANSPARENT │
//    └─────────────┴────┴─────────────┴─────────────┴─────────────┼──────────────────┬────────────────┐           ┌────────────────────┬─────────┼─────────────┴────┴────┴─────┴─────────────┘
//                                                                 │ RGB_MODE_FORWARD │    RGB_VAI     │           │      RGB_TOG       │ RGB_SLD │
//                                                                 └──────────────────┼────────────────┤           ├────────────────────┼─────────┘
//                                                                                    │ HSV_86_255_128 │           │ TOGGLE_LAYER_COLOR │
//                                                   ┌─────────────┬──────────────────┼────────────────┤           ├────────────────────┼─────────┬─────────────┐
//                                                   │   RGB_VAD   │ HSV_172_255_255  │ HSV_27_255_255 │           │    tRANSPARENT     │ RGB_HUD │   RGB_HUI   │
//                                                   └─────────────┴──────────────────┴────────────────┘           └────────────────────┴─────────┴─────────────┘
[1] = LAYOUT_ergodox_pretty(
  KC_ESCAPE      , KC_F1    , KC_F2          , KC_F3          , KC_F4          , KC_F5            , KC_TRANSPARENT ,             KC_TRANSPARENT     , KC_F6   , KC_F7          , KC_F8  , KC_F9 , KC_F10   , KC_F11        ,
  KC_TRANSPARENT , KC_EXLM  , KC_AT          , KC_LCBR        , KC_RCBR        , KC_PIPE          , KC_TRANSPARENT ,             KC_TRANSPARENT     , KC_UP   , KC_7           , KC_8   , KC_9  , KC_ASTR  , KC_F12        ,
  KC_TRANSPARENT , KC_HASH  , KC_DLR         , KC_LPRN        , KC_RPRN        , KC_GRAVE         ,                                                   KC_DOWN , KC_4           , KC_5   , KC_6  , KC_PLUS  , KC_TRANSPARENT,
  KC_TRANSPARENT , KC_PERC  , KC_CIRC        , KC_LBRC        , KC_RBRC        , KC_TILD          , KC_TRANSPARENT ,             KC_TRANSPARENT     , KC_AMPR , KC_1           , KC_2   , KC_3  , KC_BSLS  , KC_TRANSPARENT,
  KC_TRANSPARENT , KC_EQUAL , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,                                                                                KC_TRANSPARENT , KC_DOT , KC_0  , KC_EQUAL , KC_TRANSPARENT,
                                                                                 RGB_MODE_FORWARD , RGB_VAI        ,             RGB_TOG            , RGB_SLD                                                              ,
                                                                                                    HSV_86_255_128 ,             TOGGLE_LAYER_COLOR                                                                        ,
                                                                RGB_VAD        , HSV_172_255_255  , HSV_27_255_255 ,             KC_TRANSPARENT     , RGB_HUD , RGB_HUI
),

//    ┌─────────────┬─────────────┬─────────────┬─────────────┬─────────────┬─────────────┬─────────────┐           ┌─────────────┬─────────────┬─────────────┬─────────────┬─────────────┬─────────────┬─────────────┐
//    │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │           │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │   QK_BOOT   │
//    ├─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┤           ├─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┤
//    │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │    ms_u     │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │           │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │
//    ├─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┘           └─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┤
//    │ tRANSPARENT │ tRANSPARENT │    ms_l     │    ms_d     │    ms_r     │ tRANSPARENT │                                       │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │    mply     │
//    ├─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┐           ┌─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┤
//    │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │           │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │    mprv     │    mnxt     │ tRANSPARENT │ tRANSPARENT │
//    ├─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┴─────────────┘           └─────────────┴─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┤
//    │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │    btn1     │    btn2     │                                                                   │    volu     │    vold     │    mute     │ tRANSPARENT │ tRANSPARENT │
//    └─────────────┴─────────────┴─────────────┴─────────────┴─────────────┼─────────────┬─────────────┐           ┌─────────────┬─────────────┼─────────────┴─────────────┴─────────────┴─────────────┴─────────────┘
//                                                                          │ tRANSPARENT │ tRANSPARENT │           │ tRANSPARENT │ tRANSPARENT │
//                                                                          └─────────────┼─────────────┤           ├─────────────┼─────────────┘
//                                                                                        │ tRANSPARENT │           │ tRANSPARENT │
//                                                            ┌─────────────┬─────────────┼─────────────┤           ├─────────────┼─────────────┬─────────────┐
//                                                            │ tRANSPARENT │ tRANSPARENT │ tRANSPARENT │           │ tRANSPARENT │ tRANSPARENT │  www_back   │
//                                                            └─────────────┴─────────────┴─────────────┘           └─────────────┴─────────────┴─────────────┘
[2] = LAYOUT_ergodox_pretty(
  KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,             KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT  , KC_TRANSPARENT      , KC_TRANSPARENT      , KC_TRANSPARENT , QK_BOOT            ,
  KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_MS_UP       , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,             KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT  , KC_TRANSPARENT      , KC_TRANSPARENT      , KC_TRANSPARENT , KC_TRANSPARENT     ,
  KC_TRANSPARENT , KC_TRANSPARENT , KC_MS_LEFT     , KC_MS_DOWN     , KC_MS_RIGHT    , KC_TRANSPARENT ,                                               KC_TRANSPARENT , KC_TRANSPARENT  , KC_TRANSPARENT      , KC_TRANSPARENT      , KC_TRANSPARENT , KC_MEDIA_PLAY_PAUSE,
  KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,             KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT  , KC_MEDIA_PREV_TRACK , KC_MEDIA_NEXT_TRACK , KC_TRANSPARENT , KC_TRANSPARENT     ,
  KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_MS_BTN1     , KC_MS_BTN2     ,                                                                                 KC_AUDIO_VOL_UP , KC_AUDIO_VOL_DOWN   , KC_AUDIO_MUTE       , KC_TRANSPARENT , KC_TRANSPARENT     ,
                                                                                       KC_TRANSPARENT , KC_TRANSPARENT ,             KC_TRANSPARENT , KC_TRANSPARENT                                                                                                     ,
                                                                                                        KC_TRANSPARENT ,             KC_TRANSPARENT                                                                                                                      ,
                                                                      KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,             KC_TRANSPARENT , KC_TRANSPARENT , KC_WWW_BACK
)
};



uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  mod_state = get_mods();

  switch (keycode) {
    case BRIGHT_TOGGLE:
        if (record->event.pressed) {
            // Detect the activation of either shift keys
            if (mod_state & MOD_MASK_SHIFT) {
              // First temporarily canceling both shifts so that shift isn't applied to the keycodes
              del_mods(MOD_MASK_SHIFT);
              // this is brightness down because shift is being held
              register_code(KC_BRMD);

              // re apply shift
              set_mods(mod_state);
            } else {
              // this is brightness up
              register_code(KC_PAUS);
            }
        } else {
            // keyup event
                // First temporarily canceling both shifts so that shift isn't applied to the keycodes
                del_mods(MOD_MASK_SHIFT);
                // unregister brightness up and down, it seems fine to unregister both
                unregister_code(KC_SCRL);
                unregister_code(KC_PAUS);
                set_mods(mod_state);
        }
    break;

    case VOL_TOGGLE:
        if (record->event.pressed) {
            // Detect the activation of either shift keys
            if (mod_state & MOD_MASK_SHIFT) {
              // volume down because shift is being held
              register_code(KC_KB_VOLUME_DOWN);
            } else {
              // volume up
              register_code(KC_KB_VOLUME_UP);
            }
        } else {
                unregister_code(KC_KB_VOLUME_DOWN);
                unregister_code(KC_KB_VOLUME_UP);
        }
    break;

    case CMD_SHIFT:
        if(record->event.pressed){
            //keydown event
            register_code(KC_LGUI);
            register_code(KC_LSFT);
        } else {
            //keyup event
            unregister_code(KC_LGUI);
            unregister_code(KC_LSFT);
        }
      break;

    case ST_MACRO_0:
    if (record->event.pressed) {
      SEND_STRING(SS_LGUI(SS_TAP(X_C)));
    }
    break;

    case ST_MACRO_1:
    if (record->event.pressed) {
      SEND_STRING(SS_LGUI(SS_TAP(X_V)));
    }
    break;

    case ST_MACRO_2:
    if (record->event.pressed) {
      SEND_STRING("(435)773-8590");
    }
    break;

    case ST_MACRO_3:
    if (record->event.pressed) {
      SEND_STRING("kellchidester@gmail.com");
    }
    break;

    case ST_MACRO_4:
    if (record->event.pressed) {
      SEND_STRING(SS_LGUI(SS_TAP(X_P)));
    }
    break;

    case ST_MACRO_5:
    if (record->event.pressed) {
      SEND_STRING("Mickell Morris");
    }
    break;

    case ST_MACRO_6:
    if (record->event.pressed) {
      SEND_STRING("morris.mickell@gmail.com");
    }
    break;

    case ST_MACRO_7:
    if (record->event.pressed) {
      SEND_STRING(SS_LGUI(SS_TAP(X_Z)));
    }
    break;

    case MAC_SPOTLIGHT:
      HCS(0x221);

    // case RGB_SLD:
    //   if (record->event.pressed) {
    //     rgblight_mode(1);
    //   }
    //   return false;
    // case HSV_86_255_128:
    //   if (record->event.pressed) {
    //     rgblight_mode(1);
    //     rgblight_sethsv(86,255,128);
    //   }
    //   return false;
    // case HSV_172_255_255:
    //   if (record->event.pressed) {
    //     rgblight_mode(1);
    //     rgblight_sethsv(172,255,255);
    //   }
    //   return false;
    // case HSV_27_255_255:
    //   if (record->event.pressed) {
    //     rgblight_mode(1);
    //     rgblight_sethsv(27,255,255);
    //   }
    //   return false;
  }
  return true;
}

uint8_t layer_state_set_user(uint8_t state) {
    uint8_t layer = biton(state);
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



