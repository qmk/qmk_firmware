static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Keymap: Default Layer in QWERTY
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |   ~    |   1  |   2  |   3  |   4  |   5  |   \  |           |   -  |   6  |   7  |   8  |   9  |   0  |   =    |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * | Tab    |   Q  |   W  |   E  |   R  |   T  | ~L5  |           | ~L6  |   Y  |   U  |   I  |   O  |   P  |   [    |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * | Tab/Shf|   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
     * |--------+------+------+------+------+------|  L0  |           | ~L7  |------+------+------+------+------+--------|
     * | LCtrl  |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  |   ]    |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   | ~L5  | ~L2  | Caps | LAlt | LGui |                                       |  Lft |  Up  |  Dn  | Rght | ~L6  |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        | +L2  | Home |       | PgUp | Del  |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |  End |       | PgDn |      |      |
     *                                 | BkSp |  ESC |------|       |------| Enter| Space|
     *                                 |      |      |  Spc |       | Ins  |      |      |
     *                                 `--------------------'       `--------------------'
     *
     *
     *
     ****************************************************************************************************
     *
     * Under XOrg, I use my own mapping from QWERTY to "Workman for Programmers"
     * See XOrg files in ./addons/ subdirectory.
     *
     * I have to do so, because of two things:
     * 1) my native language is Russian, and XOrg keymap for it is based on QWERTY layout
     * 2) I want to have non-standart shifted keys, like $ (as normal) and @ (as shifted), or _ and -
     *
     * And even if (2) could be solved using FN* keys (but there is limit in firmware for only 32 such
     * keys), then (1) can't be solved at firmware level at all.
     *
     * So, I have to stick with QWERTY as my main layout + my own XOrg keyboard layout for English.
     * But sometimes I have to input something when XOrg is not active - for example, in Linux console,
     * or in firmware console (while debugging firmware), or when keyboard is connected to not my computer.
     *
     * For such cases I have Layer1 :)
     * // hint: switch to Layer1 is only at Layer6
     *
     ****************************************************************************************************
     *
     *
     *
     * Keymap: Default Layer in Workman
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |  ~     |   ;  |   !  |   #  |   {  |   }  |   '  |           |   ^  |   [  |   ]  |   *  |   (  |   )  |   =    |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * | Tab    |   Q  |   D  |   R  |   W  |   B  |  NO  |           | ~L7  |   J  |   F  |   U  |   P  |   $  |   :    |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * | Tab/Shf|   A  |   S  |   H  |   T  |   G  |------|           |------|   Y  |   N  |   E  |   O  |   I  |   -    |
     * |--------+------+------+------+------+------| Home |           | End  |------+------+------+------+------+--------|
     * | LCtrl  |   Z  |   X  |   M  |   C  |   V  |      |           |      |   K  |   L  |   ,  |   .  |   /  |   |    |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   | ~L5  | ~L2  | Caps | LAlt | LGui |                                       |  Lft |  Up  |  Dn  | Rght | ~L6  |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |  L0  |  +L2 |       | PgUp | Del  |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |  NO  |       | PgDn |      |      |
     *                                 | BkSp |  ESC |------|       |------| Enter| Space|
     *                                 |      |      |  Spc |       | Ins  |      |      |
     *                                 `--------------------'       `--------------------'
     *
     * Keymap: Default Layer in Workman / with Shift
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |  `     |   1  |   2  |   3  |   4  |   5  |   "  |           |   \  |   6  |   7  |   8  |   9  |   0  |   +    |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * | Tab    |   Q  |   D  |   R  |   W  |   B  |  NO  |           | ~L7  |   J  |   F  |   U  |   P  |   @  |   %    |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * | Tab/Shf|   A  |   S  |   H  |   T  |   G  |------|           |------|   Y  |   N  |   E  |   O  |   I  |   _    |
     * |--------+------+------+------+------+------| Home |           | End  |------+------+------+------+------+--------|
     * | LCtrl  |   Z  |   X  |   M  |   C  |   V  |      |           |      |   K  |   L  |   ,  |   .  |   /  |   &    |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   | ~L5  | ~L2  | Caps | LAlt | LGui |                                       |  Lft |  Up  |  Dn  | Rght | ~L6  |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |  L0  |  +L2 |       | PgUp | Del  |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |  NO  |       | PgDn |      |      |
     *                                 | BkSp |  ESC |------|       |------| Enter| Space|
     *                                 |      |      |  Spc |       | Ins  |      |      |
     *                                 `--------------------'       `--------------------'
     *
     */

    KEYMAP(  // Layer0: default, leftled:none
        // left hand
        GRV, 1,   2,   3,   4,   5,   BSLS,
        FN2, Q,   W,   E,   R,   T,   FN23,
        FN11,FN28,FN29,FN30,FN31,G,
        FN12,FN24,FN25,FN26,FN27,B,   HOME,
        FN21,FN20,CAPS,FN13,FN14,
                                      FN17,FN19,
                                           NO,
                                 FN5, FN6, FN7,
        // right hand
             MINS,6,   7,   8,   9,   0,   EQL,
             FN23,Y,   U,   I,   O,   P,   LBRC,
                  H,   J,   K,   L,   SCLN,FN15,
             END, N,   M,   COMM,DOT, SLSH,FN16,
                       LEFT,UP,  DOWN,RGHT,FN22,
        PGUP,DEL,
        PGDN,
        FN8, FN9, FN10
    ),

    KEYMAP(  // Layer1: Workman layout, leftled:all
        // left hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,Q,   D,   R,   W,   B,   TRNS,
        TRNS,A,   S,   H,   T,   G,
        TRNS,Z,   X,   M,   C,   V,   TRNS,
        TRNS,TRNS,FN17,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,J,   F,   U,   P,   4,   TRNS,
                  Y,   N,   E,   O,   I,   TRNS,
             TRNS,K,   L,   TRNS,TRNS,TRNS,TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),

    KEYMAP(  // Layer2: numpad, leftled:mid/blue
        // left hand
        TRNS,NO,  NO,  NO,  NO,  PAUS,PSCR,
        TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
        TRNS,NO,  NO,  NO,  TRNS,NO,
        TRNS,NO,  NO,  NO,  TRNS,NO,  TRNS,
        TRNS,TRNS,FN17,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             SLCK,NLCK,PSLS,PAST,PAST,PMNS,BSPC,
             TRNS,NO,  P7,  P8,  P9,  PMNS,PGUP,
                  NO,  P4,  P5,  P6,  PPLS,PGDN,
             TRNS,NO,  P1,  P2,  P3,  PPLS,PENT,
                       P0,  PDOT,SLSH,PENT,PENT,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),

    KEYMAP(  // Layer3: F-keys + PgUp/PgDn on right hand, leftled:bot/green
        // left hand
        TRNS,NO,  NO,  NO,  NO,  NO,  NO,
        TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
        TRNS,NO,  TRNS,NO,  NO,  NO,
        TRNS,NO,  TRNS,NO,  NO,  NO,  TRNS,
        TRNS,TRNS,TRNS,LALT,LGUI,
                                      TRNS,TRNS,
                                           TRNS,
                                 LCTL,LSFT,TRNS,
        // right hand
             NO,  NO,  NO,  NO,  NO,  NO,  TRNS,
             TRNS,NO,  F1,  F2,  F3,  F4,  PGUP,
                  NO,  F5,  F6,  F7,  F8,  PGDN,
             TRNS,NO,  F9,  F10, F11, F12, APP,
                       RGUI,RALT,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,RSFT,RCTL
    ),

    KEYMAP(  // Layer4: unconvenient keys on right hand, leftled:top/white
        // left hand
        TRNS,NO,  NO,  NO,  NO,  NO,  NO,
        TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
        TRNS,TRNS,NO,  NO,  NO,  NO,
        TRNS,TRNS,NO,  NO,  NO,  NO,  TRNS,
        TRNS,TRNS,TRNS,LALT,LGUI,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,

        /* in Workman right hand will be:
                { } ( ) +
              ^ ! ?     =
              ' ! $ " ; \
              # [ < > ] \
        */

        // right hand
             NO,  NO,  4,   5,   9,   0,   PPLS,
             TRNS,MINS,2,   FN5, 9,   0,   EQL,
                  BSLS,2,   P,   FN1, 1,   FN2,
             TRNS,3,   6,   FN3, FN4, 7,   FN2,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),

    KEYMAP(  // Layer5: F-keys instead of numbers, leftled:top/white
        // left hand
        TRNS,F1,  F2,  F3,  F4,  F5,  F6,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             F7,  F8,  F9,  F10, F11, F12, TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),

    KEYMAP(  // Layer6: F-keys + utils(Teensy, Workman-layer switch), leftled:top/white+onboard
        // left hand
        TRNS,F1,  F2,  F3,  F4,  F5,  F6,
        FN0, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        FN18,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             F7,  F8,  F9,  F10, F11, F12, TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,FN0,
                  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),

    //
    // rarely used
    //

    KEYMAP(  // Layer7: F-keys only, leftled:top/white
        // left hand
        FN0, NO,  NO,  NO,  NO,  NO,  NO,
        FN1, F13, F14, F15, F16, NO,  TRNS,
        TRNS,F17, F18, F19, F20, NO,
        TRNS,F21, F22, F23, F24, NO,  TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             NO,  NO,  NO,  NO,  NO,  NO,  TRNS,
             TRNS,NO,  F1,  F2,  F3,  F4,  TRNS,
                  NO,  F5,  F6,  F7,  F8,  TRNS,
             TRNS,NO,  F9,  F10, F11, F12, TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        SLEP,TRNS,TRNS
    ),

    KEYMAP(  // Layer8: mouse and navigation, leftled:mid/blue+bot/green
        // left hand
        TRNS,NO,  NO,  NO,  NO,  NO,  NO,
        TRNS,NO,  NO,  NO,  ACL0,NO,  TRNS,
        TRNS,NO,  NO,  TRNS,ACL1,NO,
        TRNS,NO,  NO,  TRNS,ACL2,NO,  TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,

        // right hand
             F16, MPLY,MPRV,MNXT,VOLD,VOLU,MUTE,
             F14, BTN2,WH_L,WH_U,WH_D,WH_R,PGUP,
                  BTN1,MS_L,MS_U,MS_D,MS_R,PGDN,
             F15, BTN3,HOME,END, DEL, INS, NO,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),

    KEYMAP(  // Layer9: application-specific shortcuts (mostly browser), leftled:top/white+bot/green
        // left hand
        TRNS,NO,  NO,  NO,  NO,  NO,  NO,
        TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
        TRNS,NO,  NO,  NO,  NO,  NO,
        TRNS,NO,  NO,  NO,  TRNS,NO,  TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             NO,  NO,  NO,  NO,  NO,  NO,  TRNS,
             TRNS,NO,  FN12,FN13,FN14,FN15,FN10,
                  FN1, FN2, FN3, FN4, FN5, FN11,
             TRNS,TRNS,FN6, FN7, FN8, FN9, FN0,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),

/*
    // templates to copy from

    KEYMAP(  // LayerN: transparent on edges + hard-defined thumb keys, all others are empty
        // left hand
        TRNS,NO,  NO,  NO,  NO,  NO,  NO,
        TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
        TRNS,NO,  NO,  NO,  NO,  NO,
        TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
        TRNS,TRNS,TRNS,LALT,LGUI,
                                      TRNS,TRNS,
                                           TRNS,
                                 LCTL,LSFT,TRNS,
        // right hand
             NO,  NO,  NO,  NO,  NO,  NO,  TRNS,
             TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
                  NO,  NO,  NO,  NO,  NO,  TRNS,
             TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
                       RGUI,RALT,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,RSFT,RCTL
    ),
    KEYMAP(  // LayerN: fully transparent
        // left hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),
*/

};

/* id for user defined functions & macros */
enum function_id {
    TEENSY_KEY,
    CUSTOM_KEY,
    L_CTRL_ALT_ENT,
    R_CTRL_ALT_ENT,
};

enum macro_id {
    XMONAD_RESET,
    PASSWORD1,
    PASSWORD2,
    PASSWORD3,
};

/*
 * Fn action definition
 */
static const uint16_t PROGMEM fn_actions[] = {
    [0] =   ACTION_FUNCTION(TEENSY_KEY),                    // FN0  - Teensy key

    [1] =   ACTION_MODS_KEY(MOD_LSFT, KC_BSLS),             // FN1  = Shifted BackSlash // " in Workman
    [2] =   ACTION_MODS_KEY(MOD_LSFT, KC_MINS),             // FN2  = Shifted Minus     // \ in Workman
    [3] =   ACTION_MODS_KEY(MOD_LSFT, KC_COMM),             // FN3  = Shifted comma     // < in Workman
    [4] =   ACTION_MODS_KEY(MOD_LSFT, KC_DOT),              // FN4  = Shifted dot       // > in Workman

    [5] =   ACTION_MODS_TAP_KEY(MOD_LCTL, KC_BSPC),         // FN5  = LShift with tap BackSpace
    [6] =   ACTION_MODS_TAP_KEY(MOD_LSFT, KC_DEL),          // FN6  = LCtrl  with tap Delete
    [7] =   ACTION_MODS_TAP_KEY(MOD_LALT, KC_ESC),          // FN7  = LAlt   with tap Escape
    [8] =   ACTION_MODS_TAP_KEY(MOD_RALT, KC_INS),          // FN8  = RAlt   with tap Ins
    [9] =   ACTION_MODS_TAP_KEY(MOD_RSFT, KC_ENT),          // FN9  = RShift with tap Enter
    [10] =  ACTION_MODS_TAP_KEY(MOD_RCTL, KC_SPC),          // FN10 = RCtrl  with tap Space

    [11] =  ACTION_MODS_TAP_KEY(MOD_LSFT, KC_TAB),          // FN11 = LShift with tap Tab
    [12] =  ACTION_MODS_TAP_KEY(MOD_LCTL, KC_GRV),          // FN12 = LCtrl  with tap Tilda
    [13] =  ACTION_MODS_TAP_KEY(MOD_LALT, KC_SPC),          // FN13 = LAlt   with tap Space
    [14] =  ACTION_MODS_TAP_KEY(MOD_LGUI, KC_ESC),          // FN14 = LGui   with tap Escape
    [15] =  ACTION_MODS_TAP_KEY(MOD_RSFT, KC_QUOT),         // FN15 = RShift with tap quotes
    [16] =  ACTION_MODS_TAP_KEY(MOD_RCTL, KC_RBRC),         // FN16 = RCtrl  with tap ]

    [17] =  ACTION_LAYER_SET(0, ON_BOTH),                   // FN17 - set Layer0
    [18] =  ACTION_LAYER_SET(1, ON_BOTH),                   // FN18 - set Layer1, to use Workman layout at firmware level
    [19] =  ACTION_LAYER_SET(2, ON_BOTH),                   // FN19 - set Layer2, to use with Numpad keys

    [21] =  ACTION_FUNCTION_TAP(L_CTRL_ALT_ENT),            // FN21 - momentary Layer5+CTRL+ALT on Enter, to use with F* keys on top row
    [22] =  ACTION_FUNCTION_TAP(R_CTRL_ALT_ENT),            // FN22 - momentary Layer6+CTRL+ALT on Enter, to use with F* keys on top row + utils

    [28] =  ACTION_LAYER_TAP_KEY(4, KC_A),                  // FN28 = momentary Layer4 on A key, to use with unconvenient keys
    [29] =  ACTION_LAYER_TAP_KEY(3, KC_S),                  // FN29 = momentary Layer3 on S key, to use with F* keys
    [30] =  ACTION_LAYER_TAP_KEY(8, KC_D),                  // FN30 = momentary Layer8 on D key, to use with mouse and navigation keys
    [31] =  ACTION_LAYER_TAP_KEY(2, KC_F),                  // FN31 = momentary Layer2 on F key, to use with Numpad keys

    // i'd like to remove this - will try to get used to live without this and convert them to usual keys
    [20] =  ACTION_LAYER_MOMENTARY(2),                      // FN20 - momentary Layer2, to use with Numpad keys
// or
//  [20] =  ACTION_FUNCTION_TAP(CUSTOM_KEY),                // FN20 - use custom key, with tapping support

    [23] =  ACTION_LAYER_TAP_KEY(7, KC_BSLS),               // FN23 - momentary Layer7 on ' , to use with F* keys (F1-F24)

    [24] =  ACTION_LAYER_TAP_KEY(4, KC_Z),                  // FN24 = momentary Layer4 on Z key, to use with unconvenient keys
    [25] =  ACTION_LAYER_TAP_KEY(3, KC_X),                  // FN25 = momentary Layer3 on X key, to use with F* keys
    [26] =  ACTION_LAYER_TAP_KEY(8, KC_C),                  // FN26 = momentary Layer8 on C key, to use with mouse and navigation keys
    [27] =  ACTION_LAYER_TAP_KEY(9, KC_V),                  // FN27 = momentary Layer9 on V key, to use with application-specific shortcuts
};

static const uint16_t PROGMEM fn_actions_4[] = {
    [1]  =  ACTION_MODS_KEY(MOD_LSFT, KC_BSLS),             // FN1  = Shifted BackSlash // " in Workman
    [2]  =  ACTION_MODS_KEY(MOD_LSFT, KC_MINS),             // FN2  = Shifted Minus     // \ in Workman
    [3]  =  ACTION_MODS_KEY(MOD_LSFT, KC_COMM),             // FN3  = Shifted comma     // < in Workman
    [4]  =  ACTION_MODS_KEY(MOD_LSFT, KC_DOT),              // FN4  = Shifted dot       // > in Workman
    [5]  =  ACTION_MODS_KEY(MOD_LSFT, KC_SLSH),             // FN5  = Shifted slash     // ? in Workman
};

static const uint16_t PROGMEM fn_actions_7[] = {
    [0]  =  ACTION_MACRO(XMONAD_RESET),                     // FN0  = xmonad-reanimator
    [1]  =  ACTION_MACRO(PASSWORD1),                        // FN1  = default password
    [2]  =  ACTION_MACRO(PASSWORD1),                        // FN2  = other password
    [3]  =  ACTION_MACRO(PASSWORD1),                        // FN3  = mega password
};

static const uint16_t PROGMEM fn_actions_9[] = {
    [0]  =  ACTION_MODS_KEY(MOD_LCTL,          KC_P0),      // FN0  = Ctrl+0
    [1]  =  ACTION_MODS_KEY(MOD_LALT,          KC_P1),      // FN1  = Alt+1
    [2]  =  ACTION_MODS_KEY(MOD_LALT,          KC_P2),      // FN2  = Alt+2
    [3]  =  ACTION_MODS_KEY(MOD_LALT,          KC_P3),      // FN3  = Alt+3
    [4]  =  ACTION_MODS_KEY(MOD_LALT,          KC_P4),      // FN4  = Alt+4
    [5]  =  ACTION_MODS_KEY(MOD_LALT,          KC_P5),      // FN5  = Alt+5
    [6]  =  ACTION_MODS_KEY(MOD_LALT,          KC_P6),      // FN6  = Alt+6
    [7]  =  ACTION_MODS_KEY(MOD_LALT,          KC_P7),      // FN7  = Alt+7
    [8]  =  ACTION_MODS_KEY(MOD_LALT,          KC_P8),      // FN8  = Alt+8
    [9]  =  ACTION_MODS_KEY(MOD_LALT,          KC_P9),      // FN9  = Alt+9
    [10] =  ACTION_MODS_KEY(MOD_LCTL|MOD_LSFT, KC_TAB),     // FN10 = Ctrl+Shift+Tab
    [11] =  ACTION_MODS_KEY(MOD_LCTL,          KC_TAB),     // FN11 = Ctrl+Tab
    [12] =  ACTION_MODS_KEY(MOD_LCTL|MOD_LSFT, KC_PGUP),    // FN12 = Ctrl+Shift+PgUp
    [13] =  ACTION_MODS_KEY(MOD_LCTL|MOD_LSFT, KC_PGDN),    // FN13 = Ctrl+Shift+PgDn
    [14] =  ACTION_MODS_KEY(MOD_LCTL,          KC_PMNS),    // FN14 = Ctrl+Pad Minus
    [15] =  ACTION_MODS_KEY(MOD_LCTL,          KC_PPLS),    // FN15 = Ctrl+Pad Plus
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    // print("action_function called\n");
    // print("id  = "); phex(id); print("\n");
    // print("opt = "); phex(opt); print("\n");

    if (id == TEENSY_KEY) {
        clear_keyboard();
        print("\n\nJump to bootloader... ");
        _delay_ms(50);
        bootloader_jump(); // should not return
        print("not supported.\n");
    }

    if (id == L_CTRL_ALT_ENT || id == R_CTRL_ALT_ENT) {
        if (record->tap.count == 0 || record->tap.interrupted) {
            uint8_t weak_mods;
            uint8_t layer;

            if (id == L_CTRL_ALT_ENT) {
                weak_mods = MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT);
                layer     = 5;
            } else {
                weak_mods = MOD_BIT(KC_RCTL) | MOD_BIT(KC_RALT);
                layer     = 6;
            }

            if (record->event.pressed) {
                layer_on(layer);
                add_weak_mods(weak_mods);
            } else {
                del_weak_mods(weak_mods);
                layer_off(layer);
            }
        } else {
            if (record->event.pressed) {
                add_key(KC_ENT);
                send_keyboard_report();
            } else {
                del_key(KC_ENT);
                send_keyboard_report();
            }
        }
    }


/*
 * just an example of custom key implementation
 * not really needed with custom keymap_fn_to_action(),
 * because it will allow you to have 32 FN** keys on EACH layer
 */

/*
    keyevent_t event = record->event;

    if (id == CUSTOM_KEY) {
        uint8_t layer = biton32(layer_state);
        uint8_t col = event.key.col;
        uint8_t row = event.key.row;
        uint8_t handled = 0;

        if (event.pressed) {
            if (layer == XXX && col == XXX && row == XXX) {
                    action_macro_play(
                        MACRO(
                            ...........
                        END)
                    );
                    handled++;
                }
            }
        }

        if (!handled) {
            print("custom key not handled");
            print(": layer "); pdec(layer);
            print(", col "); pdec(col);
            print(", row "); pdec(row);
            print("\n");
        }
    }
*/

}

#include "keymap_passwords.h"
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (record->event.pressed) {
        switch (id) {
            case XMONAD_RESET:  return MACRO_XMONAD_RESET;
            case PASSWORD1:     return MACRO_PASSWORD1;
        }
    }
    return MACRO_NONE;
}

#define FN_ACTIONS_SIZE     (sizeof(fn_actions)   / sizeof(fn_actions[0]))
#define FN_ACTIONS_4_SIZE   (sizeof(fn_actions_4) / sizeof(fn_actions_4[0]))
#define FN_ACTIONS_7_SIZE   (sizeof(fn_actions_7) / sizeof(fn_actions_7[0]))
#define FN_ACTIONS_9_SIZE   (sizeof(fn_actions_9) / sizeof(fn_actions_9[0]))

/*
 * translates Fn keycode to action
 * for some layers, use different translation table
 */
action_t keymap_fn_to_action(uint8_t keycode)
{
    uint8_t layer = biton32(layer_state);

    action_t action;
    action.code = ACTION_NO;

    if (layer == 4 && FN_INDEX(keycode) < FN_ACTIONS_4_SIZE) {
        action.code = pgm_read_word(&fn_actions_4[FN_INDEX(keycode)]);
    }

    if (layer == 7 && FN_INDEX(keycode) < FN_ACTIONS_7_SIZE) {
        action.code = pgm_read_word(&fn_actions_7[FN_INDEX(keycode)]);
    }

    if (layer == 9 && FN_INDEX(keycode) < FN_ACTIONS_9_SIZE) {
        action.code = pgm_read_word(&fn_actions_9[FN_INDEX(keycode)]);
    }

    // by default, use fn_actions from default layer 0
    // this is needed to get mapping for same key, that was used switch to some layer,
    // to have possibility to switch layers back
    if (action.code == ACTION_NO && FN_INDEX(keycode) < FN_ACTIONS_SIZE) {
        action.code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]);
    }

    return action;
}

