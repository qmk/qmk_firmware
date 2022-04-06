#include "nathancooke7.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_charybdis_3x5(
    KC_Q   , KC_W  , KC_E    , KC_R    , KC_T       ,                    KC_Y      , KC_U      , KC_I      , KC_O   , KC_P     ,
    KC_CA  , KC_AS , KC_GD   , KC_SF   , KC_G       ,                    KC_H      , KC_SJ     , KC_GK     , KC_AL  , KC_CSCLN ,
    NAV_Z  , MOU_X , KC_C    , KC_V    , KC_B       ,                    KC_N      , KC_M      , KC_COMM   , KC_DOT , SYM_SLSH ,
                     SYM_ENT , KC_NO   , BACK_WORDS ,                    MISC_DEL , NAV_SPACE
  ),

  [_MISC] = LAYOUT_charybdis_3x5(
    _______  , _______ , DESKTOP  , _______ , _______  ,                 _______  , _______  , _______ , _______  , RESET    ,
    AM_LEFT  , DESK_L  , MISSION  , DESK_R  , AM_RITE  ,                 AM_CYCLE , AM_1     , AM_2    , AM_CCW   , _______  ,
    KC_LCTRL , _______ , _______  , _______ , _______  ,                 _______  , MS_BACK  , MS_FORE , TAB_BACK , TAB_FORE ,
                         MUTE_MIC , KC_NO   , MUTE_CAM ,                 _______  , RAZ_HAND
  ),

  [_MOUSE] = LAYOUT_charybdis_3x5(
    _______ , _______ , _______ , _______ , _______ ,                    _______ , _______ , _______ , _______ , _______ ,
    _______ , _______ , _______ , _______ , L_CLICK ,                    _______ , _______ , _______ , _______ , _______ ,
    _______ , _______ , SNIPING , DRGSCRL , R_CLICK ,                    _______ , _______ , _______ , _______ , _______ ,
                        _______ , KC_NO   , _______ ,                    _______ , _______
  ),

  [_NAV] = LAYOUT_charybdis_3x5(
    _______ , KC_F6   , ALT_U   , _______ , _______ ,                    GUI_L      , KC_HOME , KC_END     , GUI_R , _______ ,
    _______ , WEB_B   , ALT_D   , WEB_F   , _______ ,                    LEFT       , KC_DOWN , KC_UP      , RIGHT , _______ ,
    _______ , _______ , _______ , _______ , _______ ,                    ALT_L      , _______ , _______    , ALT_R , _______ ,
                        _______ , KC_NO   , _______ ,                    SCREEN_CAP , _______
  ),

  [_SYMBOLS] = LAYOUT_charybdis_3x5(
    _______ , _______ , _______  , _______  , _______ ,                   _______ , KC_7 , KC_8   , KC_9 , KC_EQL  ,
    _______ , _______ , KC_GRAVE , KC_TILDE , _______ ,                   _______ , KC_4 , KC_5   , KC_6 , KC_COLN ,
    KC_LSFT , CUT     , COPY     , PASTE    , _______ ,                   KC_RSFT , KC_1 , KC_2   , KC_3 , KC_BSLS ,
                        _______  , KC_NO    , _______ ,                   KC_DOT  , KC_0
  ),

  [_WORDS] = LAYOUT_charybdis_3x5(
    KC_SECRET_1 , KC_SECRET_2 , _______ , _______ , _______ ,             _______ , _______ , _______ , _______ , SARCASM ,
    _______     , _______     , _______ , CAPS    , _______ ,             _______ , _______ , _______ , _______ , _______ ,
    _______     , _______     , _______ , _______ , _______ ,             _______ , _______ , _______ , _______ , _______ ,
                                _______ , KC_NO   , _______ ,             _______ , _______
  ),

  /* [_TEMPLATE] = LAYOUT_charybdis_3x5( */
  /*   _______ , _______ , _______ , _______ , _______ ,                    _______ , _______ , _______ , _______ , _______ , */
  /*   _______ , _______ , _______ , _______ , _______ ,                    _______ , _______ , _______ , _______ , _______ , */
  /*   _______ , _______ , _______ , _______ , _______ ,                    _______ , _______ , _______ , _______ , _______ , */
  /*                       _______ , KC_NO   , _______ ,                    _______ , _______ */
  /* ), */
};
