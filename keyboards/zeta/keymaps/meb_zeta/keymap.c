 /*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "zeta.h"
#include QMK_KEYBOARD_H

enum layers {
    BASE,
    NAV_NUM,
    NUM_SYM_FN,
    APP_NAV,
    // MATH_SYMBOLS,
};

enum custom_keycodes {
    SELECT_LINE =  SAFE_RANGE,
    // NEXT_SENTENCE,
    // ARROW,
    STICKY_SYM,
    NEXT_VIEW,
    PREV_VIEW
};

// enum unicode_names {
//     CONJUNCTION   ,
//     DISJUNCTION   ,
//     INTERSECTION  ,
//     UNION         ,
//     SUBSET        ,
//     SUPERSET      ,
//     UNIVERSAL     ,
//     INFINITYSYM   ,
//     EXISTENTIAL   ,
//     DERIVATIVE    ,
//     FALSUM        ,
//     VERUM         ,
//     TURNSTILE     ,
//     ADJUNCTION    ,
//     UPARROW       ,
//     DOWNARROW     ,
//     LEFTARROW     ,
//     RIGHTARROW    ,
//     LRARROW       ,
//     BLQUADRANT    ,
//     TLQUADRANT    ,
//     NOTEQUAL      ,
//     APPROXIMATELY ,
//     STRONGEQUALITY,
//     LTEQUAL       ,
//     GTEQUAL       ,
// };

// const uint32_t unicode_map[] PROGMEM = {
//     [CONJUNCTION]   = 0x22C0,
//     [DISJUNCTION]   = 0x22C1,
//     [INTERSECTION]  = 0x2229,
//     [UNION]         = 0x222A,
//     [SUBSET]        = 0x2282,
//     [SUPERSET]      = 0x2283,
//     [UNIVERSAL]     = 0x2200,
//     [INFINITYSYM]   = 0x221E,
//     [EXISTENTIAL]   = 0x2203,
//     [DERIVATIVE]    = 0x2202,
//     [FALSUM]        = 0x22A5,
//     [VERUM]         = 0x22A4,
//     [TURNSTILE]     = 0x22A2,
//     [ADJUNCTION]    = 0x22A3,
//     [UPARROW]       = 0x2191,
//     [DOWNARROW]     = 0x2193,
//     [LEFTARROW]     = 0x2190,
//     [RIGHTARROW]    = 0x2192,
//     [LRARROW]       = 0x2194,
//     [BLQUADRANT]    = 0x23BE,
//     [TLQUADRANT]    = 0x23BF,
//     [NOTEQUAL]      = 0x2260,
//     [APPROXIMATELY] = 0x2245,
//     [STRONGEQUALITY]= 0x2261,
//     [LTEQUAL]       = 0x2264,
//     [GTEQUAL]       = 0x2265,
// };

// TAP DANCE SETUP------------------------------------------------------------------------------------------------------------------------------------------------

void td_music_fn(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_code16(KC_MPLY);
            break;
        case 2:
            tap_code16(KC_MNXT);
            break;
        case 3:
            tap_code16(KC_MPRV);}
}

void ctrl_left_home(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_code16(LCTL(KC_LEFT));
            break;
        case 2:
            tap_code(KC_HOME);
    }
}

void ctrl_right_end(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_code16(LCTL(KC_RIGHT));
            break;
        case 2:
            tap_code(KC_END);
    }
}

enum tap_dances {
    TD_MUSIC = 0,
    ND_LEFT,
    ND_RIGHT,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_MUSIC] = ACTION_TAP_DANCE_FN(td_music_fn),
    [ND_LEFT] = ACTION_TAP_DANCE_FN(ctrl_left_home),
    [ND_RIGHT] = ACTION_TAP_DANCE_FN(ctrl_right_end),
};
// CONVENIENCE MACROS---------------------------------------------------------------------------------------------------------------------------------------------

#define BASE_SPACE LT(NAV_NUM,KC_SPC)
#define NAV_NUM_SPACE LT(NUM_SYM_FN,KC_SPC)
#define ALT_DEL LALT_T(KC_DEL)
#define TAB_LEFT RCS(KC_TAB)
#define TAB_RIGHT LCTL(KC_TAB)
#define BACK LALT(KC_LEFT)
#define FORWARD LALT(KC_RIGHT)
#define ZOOM_OUT LCTL(KC_PMNS)
#define ZOOM_IN LCTL(KC_PPLS)
#define DESKTOP_LEFT LCTL(LGUI(KC_LEFT))
#define DESKTOP_RIGHT LCTL(LGUI(KC_RIGHT))
#define ALT_F4 LALT(KC_F4)
#define MUSIC TD(TD_MUSIC)
#define ND_LEFT TD(ND_LEFT)
#define ND_RIGHT TD(ND_RIGHT)
#define APPNAV_MO MO(APP_NAV)

// KEYMAP AND LAYERS----------------------------------------------------------------------------------------------------------------------------------------------

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_split_3x6_3( // Base QWERTY layer
        KC_ESC    , KC_Q      , KC_W      , KC_E      , KC_R      , KC_T         , KC_Y         , KC_U      , KC_I      , KC_O         , KC_P        , KC_BSPC      ,
        KC_TAB    , KC_A      , KC_S      , KC_D      , KC_F      , KC_G         , KC_H         , KC_J      , KC_K      , KC_L         , KC_QUOT     , KC_ENT       ,
        KC_LSFT   , KC_Z      , KC_X      , KC_C      , KC_V      , KC_B         , KC_N         , KC_M      , KC_COMM   , KC_DOT       , KC_SLSH     , KC_RSFT      ,
        KC_NO     , KC_NO     , KC_NO     , KC_LCTL   , ALT_DEL   , BASE_SPACE   , BASE_SPACE   , KC_RGUI   , STICKY_SYM, KC_NO        ,KC_NO        , KC_NO
    ),
    [NAV_NUM] = LAYOUT_split_3x6_3( // Left-side navigation, right-side numpad layer
        KC_GRV    , ND_LEFT   , KC_UP     , ND_RIGHT  , KC_PLUS   , KC_LPRN      , KC_RPRN      , KC_7      , KC_8      , KC_9         , KC_DEL      , KC_BSPC      ,
        KC_TAB    , KC_LEFT   , KC_DOWN   , KC_RIGHT  , KC_EQL    , KC_LCBR      , KC_RCBR      , KC_4      , KC_5      , KC_6         , KC_SCLN     , KC_ENT       ,
        KC_LSFT   , KC_PIPE   , KC_UNDS   , KC_COLN   , KC_MINS   , KC_LBRC      , KC_RBRC      , KC_1      , KC_2      , KC_3         , KC_BSLS     , KC_RSFT      ,
        KC_NO     , KC_NO     , KC_NO     , KC_TRNS   , KC_TRNS   , NAV_NUM_SPACE, NAV_NUM_SPACE, KC_0      , KC_TRNS   , KC_NO        ,KC_NO        , KC_NO
    ),
    [NUM_SYM_FN] = LAYOUT_split_3x6_3( // Top-row numbers, middle-row symbols, bottom row function keys layer
        KC_1      , KC_2      , KC_3      , KC_4      , KC_5      , KC_6         , KC_7         , KC_8      , KC_9      , KC_0         , KC_MINS     , KC_EQL       ,
        KC_EXLM   , KC_AT     , KC_HASH   , KC_DLR    , KC_PERC   , KC_CIRC      , KC_AMPR      , KC_ASTR   , KC_LPRN   , KC_RPRN      , KC_UNDS     , KC_PLUS      ,
        KC_F1     , KC_F2     , KC_F3     , KC_F4     , KC_F5     , KC_F6        , KC_F7        , KC_F8     , KC_F9     , KC_F10       , KC_F11      , KC_F12       ,
        KC_NO     , KC_NO     , KC_NO     , KC_CAPS   , KC_MPLY   , KC_TRNS      , KC_TRNS      , KC_MPRV   , KC_MNXT   , KC_NO        ,KC_NO        , KC_NO
    ),
    [APP_NAV] = LAYOUT_split_3x6_3( // Transparent left-side, application navigation right-side
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS      , TAB_LEFT     , TAB_RIGHT, KC_HOME    , KC_UP        , KC_END      , ALT_F4       ,
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS      , BACK         , FORWARD  , KC_LEFT    , KC_DOWN      , KC_RIGHT    , SELECT_LINE  ,
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS      , ZOOM_OUT     , ZOOM_IN  , NEXT_VIEW  , PREV_VIEW    , DESKTOP_LEFT, DESKTOP_RIGHT,
        KC_NO     , KC_NO     , KC_NO     , KC_TRNS   , KC_TRNS   , KC_TRNS      , KC_TRNS      , MUSIC    , KC_TRNS    , KC_NO        ,KC_NO        , KC_NO
    ),
    // [MATH_SYMBOLS] = LAYOUT_split_3x6_3( // Space Cadet symbols
    //     KC_TRNS, X(CONJUNCTION), X(DISJUNCTION), X(INTERSECTION), X(UNION)        , X(SUPERSET)      , X(SUPERSET) , X(UNIVERSAL), X(INFINITYSYM), X(EXISTENTIAL), X(DERIVATIVE), KC_TRNS,
    //     KC_TRNS, X(FALSUM)     , X(VERUM)      , X(TURNSTILE)   , X(ADJUNCTION)   , X(UPARROW)       , X(DOWNARROW), X(LEFTARROW), X(RIGHTARROW) , X(LRARROW)    , KC_TRNS      , KC_TRNS,
    //     KC_TRNS, X(BLQUADRANT) , X(TLQUADRANT) , X(NOTEQUAL)    , X(APPROXIMATELY), X(STRONGEQUALITY), X(LTEQUAL)  , X(GTEQUAL)  , KC_TRNS       , KC_TRNS       , KC_TRNS      , KC_TRNS,
    //     KC_NO  , KC_NO         , KC_NO         , KC_TRNS        , KC_TRNS         , KC_TRNS          , KC_TRNS     , KC_TRNS     , KC_TRNS       , KC_NO         ,KC_NO         , KC_NO
    // ),
};

// KEY LOGGER SETUP-----------------------------------------------------------------------------------------------------------------------------------------------

#define key_log_rows 4
#define key_log_cols 20

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
     25, ' ',  17,  26, ' ', '-', '=', '[', ']','\\',
    ' ', ';','\'', '`', ',', '.', '/', ' ', ' ', ' '
};

const char code_to_name_shifted[60] = {
    ' ', ' ', ' ', ' ', 'A', 'B', 'C', 'D', 'E', 'F',
    'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
    25, ' ',  17,  26, ' ', '_', '+', '{', '}', '|',
    ' ', ':', '\"', '~', '<', '>', '?', ' ', ' ', ' '
};

char key_log[key_log_rows][key_log_cols] = { // HARD-CODED TO MATCH OLED LANDSCAPE ROWS AND COLS
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
};

void send_key_log(void){
    SEND_STRING("\n<key_log: ");
    for(int i = 0; i < key_log_rows; i++){
        for(int j = 0; j < key_log_cols; j++){
            send_char(key_log[i][j]);
        }
    }

    SEND_STRING(">\n");
}

void log_key(uint16_t keycode, uint8_t mods, uint8_t oneshot_mods){
    char shifted_sym = ' ';

    if(!((mods | oneshot_mods) & (MOD_MASK_ALT || MOD_MASK_CTRL || MOD_MASK_GUI))) {
        if(
            keycode < 60       ||
            keycode == KC_EXLM ||
            keycode == KC_AT   ||
            keycode == KC_HASH ||
            keycode == KC_DLR  ||
            keycode == KC_PERC ||
            keycode == KC_CIRC ||
            keycode == KC_AMPR ||
            keycode == KC_ASTR ||
            keycode == KC_LPRN ||
            keycode == KC_RPRN ||
            keycode == KC_UNDS ||
            keycode == KC_PLUS ||
            keycode == KC_COLN ||
            keycode == KC_LCBR ||
            keycode == KC_RCBR ||
            keycode == KC_PIPE
        ){
            for(int i = 0; i < key_log_rows; i++){
                for(int j = 0; j < key_log_cols; j++){
                    if(i == key_log_rows - 1 && j == key_log_cols - 1){
                        if(keycode < 60){
                            if(
                                ((mods | oneshot_mods) & MOD_MASK_SHIFT) ||
                                (keycode >= 4 && keycode <= 29 && host_keyboard_led_state().caps_lock)
                            ){
                                key_log[i][j] = code_to_name_shifted[keycode];
                            } else {
                                key_log[i][j] = code_to_name[keycode];
                            }
                        } else {
                            switch (keycode){
                                case KC_EXLM:
                                    shifted_sym = '!';
                                    break;
                                case KC_AT:
                                    shifted_sym = '@';
                                    break;
                                case KC_HASH:
                                    shifted_sym = '#';
                                    break;
                                case KC_DLR:
                                    shifted_sym = '$';
                                    break;
                                case KC_PERC:
                                    shifted_sym = '%';
                                    break;
                                case KC_CIRC:
                                    shifted_sym = '^';
                                    break;
                                case KC_AMPR:
                                    shifted_sym = '&';
                                    break;
                                case KC_ASTR:
                                    shifted_sym = '*';
                                    break;
                                case KC_LPRN:
                                    shifted_sym = '(';
                                    break;
                                case KC_RPRN:
                                    shifted_sym = ')';
                                    break;
                                case KC_UNDS:
                                    shifted_sym = '_';
                                    break;
                                case KC_PLUS:
                                    shifted_sym = '+';
                                    break;
                                case KC_COLN:
                                    shifted_sym = ':';
                                    break;
                                case KC_LCBR:
                                    shifted_sym = '{';
                                    break;
                                case KC_RCBR:
                                    shifted_sym = '}';
                                    break;
                                case KC_PIPE:
                                    shifted_sym = '|';
                            }

                            if(shifted_sym != ' '){
                                key_log[i][j] = shifted_sym;
                            }
                        }
                    } else {
                        key_log[i][j] = key_log[i][j+1];
                    }
                }
            }
        }
    }
};

void remove_space(void) {
    bool found_space = false;
    for(int i = key_log_rows - 1; i >= 0; i--){
        for(int j = key_log_cols - 1; j >= 0; j--){
            if(key_log[i][j] == ' '){
                found_space = true;
            }

            if(found_space){
                if(i == 0 && j == 0){
                    key_log[i][j] = ' ';
                } else {
                    key_log[i][j] = key_log[i][j-1];
                }
            }
        }
    }
};

// STICKY_SYM SETUP-----------------------------------------------------------------------------------------------------------------------------------------------

#define sticky_sym_table_rows 9
#define sticky_sym_table_cols 4

char sticky_sym[sticky_sym_table_cols] = {'~', 't', 'i', 'l'};

const char sticky_sym_table[sticky_sym_table_rows][sticky_sym_table_rows] = {
    {'!','e','x','c'},
    {'@','a','t','s'},
    {'#','p','o','u'},
    {'$','d','o','l'},
    {'%','p','e','r'},
    {'^','c','a','r'},
    {'&','a','m','p'},
    {'*','a','s','t'},
    {'~','t','i','l'},
};

const char sticky_sym_table_shifted[sticky_sym_table_rows][sticky_sym_table_rows] = {
    {'!','E','X','C'},
    {'@','A','T','S'},
    {'#','P','O','U'},
    {'$','D','O','L'},
    {'%','P','E','R'},
    {'^','C','A','R'},
    {'&','A','M','P'},
    {'*','A','S','T'},
    {'~','T','I','L'},
};

void send_sticky_sym_array(void){
    SEND_STRING("\n<sticky_sym: {");

    for(int i = 0; i < sticky_sym_table_cols; i++){
        send_char('\'');
        send_char(sticky_sym[i]);
        send_char('\'');

        if(i != sticky_sym_table_cols - 1){
            send_char(',');
        }
    }

    SEND_STRING("}>\n");
}

bool update_sticky_sym(void){
    for(int i = 0; i < sticky_sym_table_rows; i++){
        if(
            (
                (key_log[key_log_rows-1][key_log_cols-3] == sticky_sym_table[i][1] || key_log[key_log_rows-1][key_log_cols-3] == sticky_sym_table_shifted[i][1]) &&
                (key_log[key_log_rows-1][key_log_cols-2] == sticky_sym_table[i][2] || key_log[key_log_rows-1][key_log_cols-2] == sticky_sym_table_shifted[i][2]) &&
                (key_log[key_log_rows-1][key_log_cols-1] == sticky_sym_table[i][3] || key_log[key_log_rows-1][key_log_cols-1] == sticky_sym_table_shifted[i][3])
            ) && !(
                (sticky_sym_table[i][1] == sticky_sym[1] || sticky_sym_table_shifted[i][1] == sticky_sym[1]) &&
                (sticky_sym_table[i][2] == sticky_sym[2] || sticky_sym_table_shifted[i][2] == sticky_sym[2]) &&
                (sticky_sym_table[i][3] == sticky_sym[3] || sticky_sym_table_shifted[i][3] == sticky_sym[3])
            )
        ) {
            for(int j = 0; j < sticky_sym_table_cols; j++){
                sticky_sym[j] = sticky_sym_table[i][j];
            }

            for(int j = 0; j < sticky_sym_table_cols - 1; j++){
                tap_code(KC_BSPC);
            }

            return true;
        }
    }

    return false;
};

void sticky_sym_fn(void){
    update_sticky_sym();
    if(sticky_sym[0] != ' '){
        send_char(sticky_sym[0]);

        for(int i = 0; i < key_log_rows; i++){
            for(int j = 0; j < key_log_cols; j++){
                if(i == key_log_rows - 1 && j == key_log_cols - 1){
                    key_log[i][j] = sticky_sym[0];
                } else {
                    key_log[i][j] = key_log[i][j+1];
                }
            }
        }
    }
};

// USER SPACE-----------------------------------------------------------------------------------------------------------------------------------------------------

bool process_record_user(uint16_t keycode, keyrecord_t *record){
    const uint8_t mods = get_mods();
    const uint8_t oneshot_mods = get_oneshot_mods();
    bool other_key_pressed = false;
    static uint16_t press_timer;

    if(keycode != BASE_SPACE && keycode != NAV_NUM_SPACE){
        if(record->event.pressed){
            other_key_pressed = true;
        }
    }

    switch (keycode) {
        case BASE_SPACE:
        case NAV_NUM_SPACE:
            if (record->event.pressed) {
                other_key_pressed = false;
                press_timer = timer_read();
                log_key(KC_SPC,mods,oneshot_mods);
            } else {
                if(timer_elapsed(press_timer) > 200 || other_key_pressed){
                    remove_space();
                }

            }

            break;
        case SELECT_LINE:
            if (record->event.pressed ){
                tap_code(KC_HOME);
                tap_code16(LSFT(KC_END));
            }

            return false;
        // case NEXT_SENTENCE:
        //     if (record->event.pressed) {
        //         SEND_STRING(". ");
        //         add_oneshot_mods(MOD_BIT(KC_LSFT));
        //     }

        //     return false;
        // case ARROW:
        //     if (record->event.pressed) {
        //         if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {
        //             del_oneshot_mods(MOD_MASK_SHIFT);
        //             unregister_mods(MOD_MASK_SHIFT);
        //             SEND_STRING("=>");
        //             register_mods(mods);
        //         } else {
        //             SEND_STRING("->");
        //         }
        //     }

        //     return false;
        case STICKY_SYM:
            if (record->event.pressed) {
                press_timer = timer_read();
                layer_on(APP_NAV);
            } else {
                if(timer_elapsed(press_timer) < 200){
                    sticky_sym_fn();
                }

                layer_off(APP_NAV);
            }

            return false;

        #ifdef OLED_ENABLE
            case PREV_VIEW:
                if(record->event.pressed){
                    clear_oled();
                    view_selection = view_selection > 0? view_selection - 1 : 2;
                }

                break;
            case NEXT_VIEW:
                if(record->event.pressed){
                   clear_oled();
                   view_selection = view_selection < 2? view_selection + 1 : 0;
                }

                break;
        #endif

        default:
            if (record->event.pressed) {
                log_key(keycode,mods,oneshot_mods);
            }
    }

    return true;
};




