# The default keymap for YD3xn15mx

```
  [_ZOOM_M] = LAYOUT(
                                    KC_MPLY,
                             KC_MPRV,    KC_MNXT,
                  SCMD(KC_V),                      SCMD(KC_A),
            KC_PGUP,    KC_PGDN,             KC_VOLD,    KC_VOLU,

   KC_ESC      , LCMD(KC_U)    , SCMD(KC_W)    , SCMD(KC_D)    , KC_ENT    ,
   TT(_ADJUST) , SCMD(KC_H)    , SCMD(KC_N)    , SCMD(KC_T)    , SCMD(KC_M),
   TT(_RGB___) , SCMD(KC_A)    , SCMD(KC_V)    , SCMD(KC_S)    , LCMD(KC_W)
   ),

  [_ZOOM_W] = LAYOUT(
                                    KC_MPLY,
                             KC_MPRV,    KC_MNXT,
                  LALT(KC_V),                      LALT(KC_A),
            KC_PGUP,    KC_PGDN,             KC_VOLD,    KC_VOLU,

   KC_ESC      , LALT(KC_U)    , LALT(KC_F1)   , LALT(KC_F2)   , KC_ENT       ,
   TT(_ADJUST) , LALT(KC_H)    , LALT(KC_N)    , LALT(KC_T)    , C(A(S(KC_H))),
   TT(_RGB___) , LALT(KC_A)    , LALT(KC_V)    , LALT(KC_S)    , LALT(KC_F4)
   ),

  [_RGB___] = LAYOUT(
                                    KC_MPLY,
                             KC_MPRV,    KC_MNXT,
                 KC_MSTP,                          KC_MUTE,
           KC_PGUP,    KC_PGDN,              KC_VOLD,    KC_VOLU,

   ______      , RGB_M_P       , RGB_M_B       , RGB_M_R       , RGB_MOD     ,
   TT(_ADJUST) , RGB_M_SW      , RGB_M_SN      , RGB_M_TW      , RGB_RMOD    ,
   MO(_RGB___) , RGB_M_X       , RGB_M_K       , RGB_M_G       , RGB_M_T
  ),

  [_ADJUST] = LAYOUT(
                                    KC_MPLY,
                             KC_VOLD,    KC_VOLU,
                 KC_MSTP,                          KC_MUTE,
           KC_PGUP,    KC_PGDN,              KC_VOLD,    KC_VOLU,

   RESET       , ZOOM_W        , RGB_SAI       , RGB_VAI       , RGB_MOD     ,
   ______      , ZOOM_M        , RGB_SAD       , RGB_VAD       , RGB_RMOD    ,
   ______      , ______        , RGB_HUD       , RGB_HUI       , RGB_TOG
  ),
```

There are ripples with encoders.  You might need to replace those encoders.
As of Feb 14th 2022, I'm still waiting for my new encoders but will update the result once I replace those.
