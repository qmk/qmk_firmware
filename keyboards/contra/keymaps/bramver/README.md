# Contra layout

My current setup consists of a very simple base layer, numbers layer, mouse layer and emoji layer.
Still many options, but time will tell if changes are needed.

## Keymap

```
#define SP_MSE LT(_MOUSE, KC_SPC)


BASE layer
  { QK_GESC , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_BSPC }, 
  { KC_TAB  , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    , KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_ENT  }, 
  { KC_LSFT , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_QUOT }, 
  { KC_LCTL , KC_GRV  , KC_LALT , KC_LGUI , MO(1)   , SP_MSE  , SP_MSE  , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , MO(2)   },

LOWER layer
  { _______ , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_DEL  }, 
  { _______ , KC_F1   , KC_F2   , KC_F3   , KC_LBRC , KC_MINS , KC_EQL  , KC_RBRC , KC_F7   , KC_F8   , KC_F9   , _______ }, 
  { _______ , KC_F4   , KC_F5   , KC_F6   , KC_HOME , KC_BSLS , KC_MPLY , KC_END  , KC_F10  , KC_F11  , KC_F12  , _______ }, 
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ },

EMOJI layer
  { _______ , UM(CLAP) , UM(CUM)  , UM(BNIS) , UM(BUTT) , UM(CAR)  , UM(FIRE) , UM(REDB) , UM(MONY) , UM(HNDR) , UM(SOS)  , _______ },
  { _______ , UM(CELE) , UM(PRAY) , UM(NAIL) , UM(OK)   , UM(THNK) , UM(UNAM) , UM(HEYE) , UM(COOL) , UM(EYES) , UM(SMIR) , _______ },
  { _______ , UM(TRIU) , UM(SCRM) , UM(VOMI) , UM(DTIV) , UM(EXPL) , UM(HAIR) , UM(DANC) , UM(STRN) , UM(LEFT) , UM(RGHT) , _______ },
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ },

MOUSE layer
  { _______ , KC_WH_L , KC_BTN1 , KC_MS_U , KC_BTN2 , KC_WH_U , KC_WH_U , KC_BTN1 , KC_MS_U , KC_BTN2 , KC_WH_L , _______ },
  { _______ , KC_WH_R , KC_MS_L , KC_MS_D , KC_MS_R , KC_WH_D , KC_WH_D , KC_MS_L , KC_MS_D , KC_MS_R , KC_WH_R , _______ },
  { _______ , KC_VOLD , KC_VOLU , KC_MPRV , KC_MNXT , KC_MPLY , KC_MPLY , KC_MPRV , KC_MNXT , KC_VOLD , KC_VOLU , _______ },
  { _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ },
```