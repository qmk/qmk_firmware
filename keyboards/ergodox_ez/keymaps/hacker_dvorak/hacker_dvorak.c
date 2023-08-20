// Keyboard keymap:
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DVORAK] = LAYOUT_ergodox(

        // HACKER DVORAK left hand

         //------------------------+-------------------------+-------------------------+-------------------------+-------------------------+-------------------------+------------------------//
        //  ESCAPE                 |                         |                         |                         |                         |                         |     START RECORDING     //
        //                         |                         |                         |                         |                         |                         |                         //
                   KC_ESC,                 TD(GRV_TILD),             TD(AT_DLR),              TD(LCBR_LABK),            TD(LPRN_LBRC),            TD(EXLM_QUES),           DM_REC1,            //
        //                         |                       ~ |                       $ |                       < |                       [ |                       ? |                         //
        //                         |            TAP DANCE: ` |            TAP DANCE: @              TAP DANCE: { |            TAP DANCE: ( |            TAP DANCE: ! |     DYNAMIC MARCO 1     //
         //------------------------+-------------------------+-------------------------+-------------------------+-------------------------+-------------------------+------------------------//
        //  TAB                    |      MOD TAP: ALT+SHIFT |       MOD TAP: CTRL+ALT |     MOD TAP: CTRL+SHIFT | P                       | Y                       |                         //
        //                         |                         |                         |                         |                         |                         |                         //
                   KC_TAB,                TD(NONE_LEAD),            TD(QUOT_DQUO),           TD(DOT_COMM),               LCG_T(KC_P),              LAG_T(KC_Y),            DM_PLY1,            //
        //                         |                    LEAD |                       " |                       , |                         |                         |                         //
        //                         |         TAP DANCE: NONE |            TAP DANCE: ' |            TAP DANCE: . |       MOD TAP: CTRL+GUI |        MOD TAP: ALT+GUI |                         //
         //------------------------+-------------------------+-------------------------+-------------------------+-------------------------+-------------------------|   PLAY DYNAMIC MACRO 1  //
        //                         |            MOD TAP: ALT |           MOD TAP: CTRL |        LAYER TAP: SHIFT | M TAP DANCE: ARROWS/GUI |      MOD TAP: SHIFT+GUI |                         //
        //                         |                         |                         |                         |                       Ü |                         |                         //
                TD(EQL_PLUS),             LALT_T(KC_A),             LCTL_T(KC_O),             LSFT_T(KC_E),            TD(U_ARR_GUI),             SGUI_T(KC_I),      //-----------------------//
        //                       + |                       Á |                       Ó |                       É |                       Ú |                       Í |                         //
        //            TAP DANCE: = |            TAP DANCE: A |            TAP DANCE: O |            TAP DANCE: E |            TAP DANCE: U |            TAP DANCE: I |                         //
         //------------------------+-------------------------+-------------------------+-------------------------+-------------------------+-------------------------|  META                   //
        //          STOP RECORDING |  MOD TAP: GUI+SHIFT+ALT | Q                       | J                       | K                       | X                       |                         //
        //                         |                         |                         |                         |                         |                         |                         //
                DM_RSTP,                  TD(SCLN_COLN),            LCAG_T(KC_Q),             TD(J_MED_MEH),            TD(K_NUM_HYP),            LCSG_T(KC_X),                KC_LGUI,        //
        //                         |                       : |                         |                         |                         |                         |                         //
        //           DYNAMIC MACRO |            TAP DANCE: ; |      MOD TAP: SHIFT+GUI |  M TAP DANCE: MEDIA/MEH |  M TAP DANCE: ATM/HYPER |  MOD TAP: CTL+SHIFT+GUI |                         //
         //------------------------+-------------------------+-------------------------+-------------------------+-------------------------+-------------------------+------------------------//
        //         LAYERS SWITCHER | APPLICATION MENU        |                         |                         |                        //
        //                         |                         |                         |                         |                  SCROLL //
                 TG(LAYERS),                 KC_APP,                  KC_NUM,                   KC_SCRL,                   KC_CAPS,        //
        //                         |                         |                         |                         |                  NUM    //
        //            LAYER TOGGLE |                         |                         |                         |       TAP DANCE: CAPS   //
         //------------------------+-------------------------+-------------------------+-------------------------+------------------------//

                                                                                                               // HACKER DVORAK left thumb

                                                                                                                                           //------------------------+------------------------//
                                                                                                                                          // MOUSE WHEEL LEFT        | MOUSE WHEEL RIGHT       //
                                                                                                                                          //                         |                         //
                                                                                                                                                     KC_WH_L,                  KC_WH_R,        //
                                                                                                                                          //                         |                         //
                                                                                                                                           //                        |                         //
                                                                                                                //-------------------------+-------------------------+------------------------//
                                                                                                               //                          |                         | HOME                    //
                                                                                                               //                          |                         |                         //
                                                                                                                /*  SPACE                   |  BACKSPACE             */         KC_HOME,       //
                                                                                                               //                          |                         |                         //
                                                                                                               //                          |                         |                         //
                                                                                                                           KC_SPC,                   KC_BSPC,        //-----------------------//
                                                                                                               //                          |                         | END                     //
                                                                                                               //                          |                         |                         //
                                                                                                               /*                          |                        */         KC_END,         //
                                                                                                               //                          |                         |                         //
                                                                                                               //                          |                         |                         //
                                                                                                                //-------------------------+-------------------------+------------------------//

        // HACKER DVORAK right hand

         //------------------------+-------------------------+-------------------------+-------------------------+-------------------------+-------------------------+------------------------//
        //                         |                         |                         |                         |                         |                         |                         //
        //                         |                         |                         |                         |                         |                         |                         //
                DM_REC2,                   TD(APMR_PIPE),            TD(RPRN_RBRC),            TD(RCBR_RABK),            TD(HASH_PERC),            TD(ASTR_CIRC),               XXXXXXX,        //
        //                         |                         |                         |                         |                         |                         |                         //
        //                         |                         |                         |                         |                         |                         |                         //
         //------------------------+-------------------------+-------------------------+-------------------------+-------------------------+-------------------------+------------------------//
        //                         |                         |                         |                         |                         |                         |                         //
        //                         |                         |                         |                         |                         |                         |                         //
                DM_PLY2,                   LAG_T(KC_F),              LCG_T(KC_G),             C_S_T(KC_C),                LCA_T(KC_R),             LAS_T(KC_L),             TD(SLSH_BSLS),     //
        //                         |                         |                         |                         |                         |                         |                         //
        //                         |                         |                         |                         |                         |                         |                         //
        //                         |-------------------------+-------------------------+-------------------------+-------------------------+-------------------------+------------------------//
        //                         |                         |                         |                         |                         |                         |                         //
        //                         |                         |                         |                         |                         |                         |                         //
        /*-----------------------*/        SGUI_T(KC_D),            TD(H_MOU_GUI),            LSFT_T(KC_T),               LCTL_T(KC_N),            LALT_T(KC_S),            TD(MINS_UNDS),     //
        //                         |                         |                         |                         |                         |                         |                         //
        //                         |                         |                         |                         |                         |                         |                         //
        //                         |-------------------------+-------------------------+-------------------------+-------------------------+-------------------------+------------------------//
        //                         |                         |                         |                         |                         |                         |                         //
        //                         |                         |                         |                         |                         |                         |                         //
                   KC_LGUI,                LCSG_T(KC_B),            TD(M_CHO_HYP),            TD(W_MED_MEH),            LCAG_T(KC_V),             LASG_T(KC_Z),                COMPOSE,        //
        //                         |                         |                         |                         |                         |                         |                         //
        //                         |                         |                         |                         |                         |                         | ⎄                      //
         //------------------------+-------------------------+-------------------------+-------------------------+-------------------------+-------------------------+------------------------//
                                                             //                        |                         |                         |                         |                         //
                                                            //                         |                         |                         |                         |                         //
                                                                      KC_LEFT,                   KC_UP,                    KC_DOWN,                 KC_RGHT,                  KC_SYRQ,         //
                                                            //                         |                         |                         |                         |                         //
                                                            //                         |                         |                         |                         |                         //
                                                             //------------------------+-------------------------+-------------------------+-------------------------+------------------------//

        // HACKER DVORAK right thumb

         //------------------------+------------------------//
        //                         |                         //
        //                         |                         //
                   KC_WH_U,                  KC_WH_D,        //
        //                         |                         //
        //                         |                         //
         //------------------------+-------------------------+------------------------//
        //                         |                         |                         //
        //                         |                         |                         //
                   KC_PGUP,        //                        |                         //
        //                         |                         |                         //
        //                         |                         |                         //
         //------------------------|                         |                         //
        //                         |                         |                         //
        //                         |                         |                         //
                  KC_PGDN,                   KC_DEL,                   KC_ENT          //
        //                         |                         |                         //
        //                         |                         |                         //
         //------------------------+-------------------------+------------------------//

    ),

    [PLOVER] = LAYOUT_ergodox(
        // left hand
        XXXXXXX,    XXXXXXX,       KC_MS_BTN2, KC_MS_UP,   KC_MS_BTN1,  KC_MS_BTN3, GUI_T(KC_NO),
        KC_ESC,     KC_MS_BTN4,    KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_MS_BTN5, PV_NUM,
        KC_TAB,     PV_LS,         PV_LT,      PV_LP,      PV_LH,       PV_STAR,
        KC_CAPS,    PV_LS,         PV_LK,      PV_LW,      PV_LR,       PV_STAR,    PV_STAR,
        XXXXXXX, TG(LAYERS), PV_NUM,     PV_NUM,     PV_NUM,

        // left thumb
              KC_SPACE, KC_BSPC,
                        KC_HOME,
        PV_A, PV_O,     KC_END,

        // right hand
        KC_MS_ACCEL2, KC_MS_ACCEL1,  KC_MS_ACCEL0, KC_UP,   KC_APPLICATION, XXXXXXX,        KC_MS_WH_UP,
        PV_NUM,       KC_MS_WH_LEFT, KC_LEFT,      KC_DOWN, KC_RIGHT,       KC_MS_WH_RIGHT, KC_MS_WH_DOWN,
                      PV_STAR,       PV_RF,        PV_RP,   PV_RL,          PV_RT,          PV_RD,
        PV_STAR,      PV_STAR,       PV_RR,        PV_RB,   PV_RG,          PV_RS,          PV_RZ,
                                     PV_NUM,       PV_NUM,  PV_NUM,         PV_NUM,         XXXXXXX,

        // right thumb
        KC_DELETE, KC_ENTER,
        KC_PGUP,
        KC_PGDN, PV_E,     PV_U
    ),

    [GAMING] = LAYOUT_ergodox(
        // left hand
        KC_ESCAPE,            GUI_T(KC_MINS), KC_I,     KC_O,   KC_P,   ALGR_T(KC_EQL), KC_T,
        KC_TAB,               KC_LALT,        KC_Q,     KC_W,   KC_E,   ALL_T(KC_R),    KC_G,
        LT(MOUSE, KC_GRV), KC_LCTL,        KC_A,     KC_S,   KC_D,   MEH_T(KC_F),
        KC_BSLS,              KC_LSFT,      KC_Z,     KC_X,   KC_C,   SCMD_T(KC_V),   KC_M,
        XXXXXXX,           TG(LAYERS),  KC_COMM, KC_DOT, KC_LBRC,

        // left thumb
                   MO(MEDIA_FN), KC_NUM,
                                 KC_SCLN,
         KC_SPACE, KC_ENTER,     KC_BSPC,

        // right hand
        KC_QUOT,       KC_Y,       KC_K,        KC_U,        KC_KP_7, KC_KP_8,  KC_KP_9,
        KC_MS_WH_UP,   KC_H,       KC_J,        KC_L,        KC_KP_4, KC_KP_2,  KC_KP_6,
                       KC_B,       KC_MS_UP,    KC_N,        KC_KP_1, KC_KP_5,  KC_KP_3,
        KC_MS_WH_DOWN, KC_MS_LEFT, KC_MS_DOWN,  KC_MS_RIGHT, KC_UP,   KC_KP_0,  KC_SLASH,
                                   KC_RBRC,     KC_LEFT,     KC_DOWN, KC_RIGHT, XXXXXXX,

        // right thumb
        KC_MS_BTN5, MO(CHORD),
        KC_MS_BTN4,
        KC_MS_BTN3, KC_MS_BTN2,   KC_MS_BTN1
    ),

    [ARROWS] = LAYOUT_ergodox(
        // left hand
        XXXXXXX, XXXXXXX,       XXXXXXX,      XXXXXXX,      XXXXXXX,    XXXXXXX, XXXXXXX,
        XXXXXXX, SCMD_T(KC_NO), MEH_T(KC_NO), ALL_T(KC_NO), XXXXXXX,    XXXXXXX, XXXXXXX,
        XXXXXXX, KC_LCTL,       KC_LSFT,      XXXXXXX,      _______,    XXXXXXX,
        XXXXXXX, KC_RALT,       KC_LALT,      GUI_T(KC_NO), XXXXXXX,    XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,       XXXXXXX,      XXXXXXX,      XXXXXXX,

        // left thumb
                  XXXXXXX,   XXXXXXX,
                             KC_HOME,
        KC_SPACE, KC_BSPC,   KC_END,

        // right hand
        LGUI(KC_X), XXXXXXX,       LCTL(KC_X), KC_MS_WH_UP,   XXXXXXX,       XXXXXXX,        XXXXXXX,
        LGUI(KC_C), XXXXXXX,       LCTL(KC_C), KC_UP,         SCTL(KC_C),    LCTL(KC_Z),     LGUI(KC_Z),
                    KC_MS_WH_LEFT, KC_LEFT,    KC_DOWN,       KC_RIGHT,      KC_MS_WH_RIGHT, KC_APPLICATION,
        LGUI(KC_V), XXXXXXX,       LCTL(KC_V), KC_MS_WH_DOWN, SCTL(KC_V),    LCTL(KC_Y),     SGUI(KC_Z),
        XXXXXXX,    XXXXXXX,       XXXXXXX,    XXXXXXX,       KC_SCRL,

        // right thumb
        XXXXXXX,   XXXXXXX,
        KC_PGUP,
        KC_PGDN, KC_DELETE, KC_ENTER
    ),

    [MOUSE] = LAYOUT_ergodox(
        // left hand
        XXXXXXX,       XXXXXXX,       XXXXXXX,    KC_MS_WH_UP,   LCTL(KC_X),  XXXXXXX,        LGUI(KC_X),
        LGUI(KC_Z),    LCTL(KC_Z),    SCTL(KC_C), KC_MS_UP,      LCTL(KC_C),  KC_MS_BTN4,     LGUI(KC_C),
        KC_MS_BTN3,    KC_MS_WH_LEFT, KC_MS_LEFT, KC_MS_DOWN,    KC_MS_RIGHT, KC_MS_WH_RIGHT,
        LGUI(KC_Z),    LCTL(KC_Y),    SCTL(KC_V), KC_MS_WH_DOWN, LCTL(KC_V),  KC_MS_BTN5,     LGUI(KC_V),
        KC_SCRL,       XXXXXXX,       XXXXXXX,    XXXXXXX,       XXXXXXX,

        // left thumb
                    XXXXXXX,    XXXXXXX,
                                XXXXXXX,
        KC_MS_BTN1, KC_MS_BTN2, XXXXXXX,

        // right hand
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,      XXXXXXX,       XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, ALL_T(KC_NO), MEH_T(KC_NO), SCMD_T(KC_NO), XXXXXXX,
                 XXXXXXX, _______, KC_MS_ACCEL1, KC_LSFT,      KC_LCTL,       KC_MS_ACCEL2,
        XXXXXXX, XXXXXXX, XXXXXXX, GUI_T(KC_NO), KC_LALT,      KC_RALT,       XXXXXXX,
                          XXXXXXX, XXXXXXX,      XXXXXXX,      XXXXXXX,       XXXXXXX,

        // right thumb
        XXXXXXX, XXXXXXX,
        XXXXXXX,
        XXXXXXX, XXXXXXX, KC_MS_ACCEL0
    ),

    [NUMPAD] = LAYOUT_ergodox(
        // left hand
        XXXXXXX, XXXXXXX,  XXXXXXX,      XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,  GUI_T(KC_NO), XXXXXXX, ALL_T(KC_NO),  XXXXXXX, XXXXXXX,
        _______, KC_LCTL,  KC_LSFT,      _______, MEH_T(KC_NO),  XXXXXXX,
        XXXXXXX, KC_RALT,  KC_LALT,      XXXXXXX, SCMD_T(KC_NO), XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,  XXXXXXX,      XXXXXXX, XXXXXXX,

        // left thumb
                  XXXXXXX,   XXXXXXX,
                             KC_HOME,
        KC_SPACE, KC_BSPC,   KC_END,

        // right hand
        KC_X, KC_A, KC_B,   KC_C, KC_D,     KC_E,    KC_F,
        KC_O, KC_I, KC_1,   KC_2, KC_3,     KC_SLSH, KC_PERC,
              KC_M, KC_4,   KC_5, KC_6,     KC_PLUS, KC_MINS,
        KC_L, KC_J, KC_7,   KC_8, KC_9,     KC_ASTR, KC_CIRC,
                    KC_DOT, KC_0, KC_COMM, KC_UNDS,  KC_BSLS,

        // right thumb
        XXXXXXX,   XXXXXXX,
        KC_PGUP,
        KC_PGDN, KC_DELETE, KC_ENTER
    ),

    [LAYERS] = LAYOUT_ergodox(
        // left hand
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX,

        // left thumb
                 XXXXXXX, XXXXXXX,
                          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,

        // right hand
        XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX, XXXXXXX,
                 XXXXXXX, TO(DVORAK), TO(PLOVER), TO(GAMING), XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX, XXXXXXX,
                          XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX, XXXXXXX,

        // right thumb
        XXXXXXX, XXXXXXX,
        XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [MEDIA_FN] = LAYOUT_ergodox(
        // left hand
        KC_VOLD,   KC_MUTE, RGB_TOG,    XXXXXXX, KC_MAIL,      KC_FIND, KC_WWW_REFRESH,
        KC_MPRV, KC_F9,         KC_F7,      KC_F5,   KC_F3,        KC_F1,   KC_WWW_HOME,
        KC_PAUS,            KC_F19,        KC_F17,     KC_F15,  KC_F13,       KC_F11,
        RGB_HUD,             XXXXXXX,       XXXXXXX,    _______, KC_F23,       KC_F21,  KC_WWW_BACK,
        RGB_VAD,             KC_CAPS,       KC_PSCR,    XXXXXXX, MO(FIRMWARE),

        // left thumb
                 _______, XXXXXXX,
                          XXXXXXX,
        XXXXXXX, XXXXXXX, KC_MEDIA_EJECT,

        // right hand
        KC_WWW_FAVORITES, KC_MYCM, KC_CALC,   XXXXXXX, RGB_MOD,         RGB_M_P,        KC_VOLU,
        KC_WWW_SEARCH,    KC_F2,          KC_F4,           KC_F6,   KC_F8,           KC_F10,         KC_MNXT,
                          KC_F12,         KC_F14,          KC_F16,  KC_F18,          KC_F20,         KC_MPLY,
        KC_WWW_FORWARD,   KC_F22,         KC_F24,          _______, XXXXXXX,         XXXXXXX,        RGB_HUI,
                                          KC_PWR, XXXXXXX, KC_SLEP, KC_WAKE, RGB_VAI,

        // right thumb
        XXXXXXX,   XXXXXXX,
        XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [CHORD] = LAYOUT_ergodox(
        // left hand
        XXXXXXX, HYPR(KC_F1),  HYPR(KC_F2),  HYPR(KC_F3),  HYPR(KC_F4),  HYPR(KC_F5),  XXXXXXX,
        XXXXXXX, HYPR(KC_F6),  HYPR(KC_F7),  HYPR(KC_F8),  HYPR(KC_F9),  HYPR(KC_F10), XXXXXXX,
        XXXXXXX, HYPR(KC_F11), HYPR(KC_F12), HYPR(KC_F13), HYPR(KC_F14), HYPR(KC_F15),
        XXXXXXX, HYPR(KC_F16), HYPR(KC_F17), HYPR(KC_F18), HYPR(KC_F19), HYPR(KC_F20), XXXXXXX,
        XXXXXXX, HYPR(KC_F21), HYPR(KC_F22), HYPR(KC_F23), HYPR(KC_F24),

        // left thumb
                 XXXXXXX, XXXXXXX,
                          XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,

        // right hand
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                 XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,

        // right thumb
        XXXXXXX, _______,
        XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [FIRMWARE] = LAYOUT_ergodox(

        // left hand
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,

        // left thumb
               XXXXXXX, XXXXXXX,
                        XXXXXXX,
        QK_BOOT, XXXXXXX, XXXXXXX,

        // right hand
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,

        // right thumb
        XXXXXXX, XXXXXXX,
        XXXXXXX,
        XXXXXXX, XXXXXXX, EE_CLR
    )
};
