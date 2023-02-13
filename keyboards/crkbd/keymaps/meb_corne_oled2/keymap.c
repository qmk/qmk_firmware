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

#include QMK_KEYBOARD_H

enum layers {
    BASE,
    NAV_NUM,
    NUM_SYM_FN,
    APP_NAV,
    MATH_SYMBOLS,
};

enum custom_keycodes {
    SELECT_LINE =  SAFE_RANGE,
    NEXT_SENTENCE,
    ARROW,
};

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

void td_grv_boot_fn(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
                tap_code16(KC_GRV);
            break;
        case 2:
                tap_code16(KC_GRV);
            break;
        case 3:
                tap_code16(QK_RBT);}
}

enum tap_dances {
    TD_MUSIC = 0,
    TD_GRV_BOOT,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_MUSIC] = ACTION_TAP_DANCE_FN(td_music_fn),
    [TD_GRV_BOOT] = ACTION_TAP_DANCE_FN(td_grv_boot_fn),
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
#define GRV_BOOT TD(TD_GRV_BOOT)
#define APPNAV_MO MO(APP_NAV)

// KEYMAP AND LAYERS----------------------------------------------------------------------------------------------------------------------------------------------

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_split_3x6_3( // Base QWERTY layer
        KC_ESC    , KC_Q      , KC_W      , KC_E      , KC_R      , KC_T         , KC_Y         , KC_U      , KC_I      , KC_O         , KC_P        , KC_BSPC      ,
        KC_TAB    , KC_A      , KC_S      , KC_D      , KC_F      , KC_G         , KC_H         , KC_J      , KC_K      , KC_L         , KC_QUOT     , KC_ENT       ,
        KC_LSFT   , KC_Z      , KC_X      , KC_C      , KC_V      , KC_B         , KC_N         , KC_M      , KC_COMM   , KC_DOT       , KC_SLSH     , KC_RSFT      ,
                                            KC_LCTL   , ALT_DEL   , BASE_SPACE   , BASE_SPACE   , KC_RGUI   , APPNAV_MO
    ),
    [NAV_NUM] = LAYOUT_split_3x6_3( // Left-side navigation, right-side numpad layer
        GRV_BOOT  , KC_HOME   , KC_UP     , KC_END    , KC_PLUS   , KC_LPRN      , KC_RPRN      , KC_7      , KC_8      , KC_9         , KC_DEL      , KC_BSPC      ,
        KC_TAB    , KC_LEFT   , KC_DOWN   , KC_RIGHT  , KC_EQL    , KC_LCBR      , KC_RCBR      , KC_4      , KC_5      , KC_6         , KC_SCLN     , KC_ENT       ,
        KC_LSFT   , KC_PIPE   , KC_UNDS   , KC_COLN   , KC_MINS   , KC_LBRC      , KC_RBRC      , KC_1      , KC_2      , KC_3         , KC_BSLS     , KC_RSFT      ,
                                            KC_TRNS   , KC_TRNS   , NAV_NUM_SPACE, NAV_NUM_SPACE, KC_0      , KC_TRNS
    ),
    [NUM_SYM_FN] = LAYOUT_split_3x6_3( // Top-row numbers, middle-row symbols, bottom row function keys layer
        KC_1      , KC_2      , KC_3      , KC_4      , KC_5      , KC_6         , KC_7         , KC_8      , KC_9      , KC_0         , KC_MINS     , KC_EQL       ,
        KC_EXLM   , KC_AT     , KC_HASH   , KC_DLR    , KC_PERC   , KC_CIRC      , KC_AMPR      , KC_ASTR   , KC_LPRN   , KC_RPRN      , KC_UNDS     , KC_PLUS      ,
        KC_F1     , KC_F2     , KC_F3     , KC_F4     , KC_F5     , KC_F6        , KC_F7        , KC_F8     , KC_F9     , KC_F10       , KC_F11      , KC_F12       ,
                                            KC_CAPS   , KC_MPLY   , KC_TRNS      , KC_TRNS      , KC_MPRV   , KC_MNXT
    ),
    [APP_NAV] = LAYOUT_split_3x6_3( // Transparent left-side, application navigation right-side
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS      , TAB_LEFT     , TAB_RIGHT, KC_HOME    , KC_UP        , KC_END      , ALT_F4       ,
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS      , BACK         , FORWARD  , KC_LEFT    , KC_DOWN      , KC_RIGHT    , SELECT_LINE  ,
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS      , ZOOM_OUT     , ZOOM_IN  , ARROW      , NEXT_SENTENCE, DESKTOP_LEFT, DESKTOP_RIGHT,
                                            KC_TRNS   , KC_TRNS   , KC_TRNS      , KC_TRNS      , MUSIC    , KC_TRNS
    ),
    [MATH_SYMBOLS] = LAYOUT_split_3x6_3( // Transparent left-side, application navigation right-side
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS      , TAB_LEFT     , TAB_RIGHT, KC_HOME    , KC_UP        , KC_END      , ALT_F4       ,
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS      , BACK         , FORWARD  , KC_LEFT    , KC_DOWN      , KC_RIGHT    , SELECT_LINE  ,
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS      , ZOOM_OUT     , ZOOM_IN  , ARROW      , NEXT_SENTENCE, DESKTOP_LEFT, DESKTOP_RIGHT,
                                            KC_TRNS   , KC_TRNS   , KC_TRNS      , KC_TRNS      , MUSIC    , KC_TRNS
    ),
};

// OLED SETUP-----------------------------------------------------------------------------------------------------------------------------------------------------

#ifdef OLED_ENABLE

    bool init_rotate = true;

    // RENDER STATUS FUNCTION FOR MASTER

    void render_status(void) {

        // ROW INDEX 0 - CURRENT LAYER

        oled_set_cursor(0, 0);
        switch (get_highest_layer(layer_state)) {
            case BASE:
                oled_write("Base", false);
                break;
            case NAV_NUM:
                oled_write("NNum", false);
                break;
            case NUM_SYM_FN:
                oled_write("NSFn", false);
                break;
            case APP_NAV:
                oled_write("ANav", false);
                break;
            case MATH_SYMBOLS:
                oled_write("MSym", false);
        }

        // ROW INDEX 2 - CAPS LOCK STATUS

        oled_set_cursor(0,2);
        oled_write("CS:", false);
        oled_set_cursor(3,2);
        led_t led_state = host_keyboard_led_state();
        oled_write_P(led_state.caps_lock ? PSTR("+") : PSTR("-"), false);
    }

    // RENDER STATIC FUNCTION FOR SLAVE

    #define oled_sym_table_rows 16
    #define oled_sym_table_cols 5
    const char oled_sym_table[oled_sym_table_rows][oled_sym_table_cols] = {
        {'S','y','m','b','s'},
        {'-','-','-','-','-'},
        {'!',' ','E','X','C'},
        {'@',' ','A','T','S'},
        {'#',' ','P','O','U'},
        {'$',' ','D','O','L'},
        {'%',' ','P','E','R'},
        {'^',' ','C','A','R'},
        {'&',' ','A','M','P'},
        {'*',' ','A','S','T'},
        {'~',' ','T','I','L'},
        {' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' '},
    };

    void render_oled_sym_table(void){
        int oled_row = 0;
        int oled_col = 0;

        for(int i = 0; i < oled_sym_table_rows; i++){
            oled_col = 0;

            for(int j = 0; j < oled_sym_table_cols; j++){
                oled_set_cursor(oled_col,oled_row);
                oled_write((char[2]) { (char) oled_sym_table[i][j], '\0' },false);
                oled_col++;
            }

            oled_row++;
        }
    }

    // void render_static(void){
    //     oled_set_cursor(0,0);
    //     oled_write("Key C", false);

    //     oled_set_cursor(0,2);
    //     oled_write("EXC !", false);

    //     oled_set_cursor(0,3);
    //     oled_write("ATS @", false);

    //     oled_set_cursor(0,4);
    //     oled_write("POU #", false);

    //     oled_set_cursor(0,5);
    //     oled_write("DOL $", false);

    //     oled_set_cursor(0,6);
    //     oled_write("PER %", false);

    //     oled_set_cursor(0,7);
    //     oled_write("CAR ^", false);

    //     oled_set_cursor(0,8);
    //     oled_write("AMP &", false);

    //     oled_set_cursor(0,9);
    //     oled_write("AST *", false);

    //     oled_set_cursor(0,10);
    //     oled_write("TIL ~", false);
    // }

    // DRAW TO OLEDs
    bool oled_task_user(void) {
        if(init_rotate){
            oled_init(135);
            init_rotate = false;
        }

        // if(is_keyboard_master()){
        //     render_status();
        // }else{
        //     render_static();
        // }
        render_oled_sym_table();

        return false;
    }

#endif

// POST INITIALIZATION--------------------------------------------------------------------------------------------------------------------------------------------

// void keyboard_post_init_user(void) {

// }

// USER SPACE-----------------------------------------------------------------------------------------------------------------------------------------------------

bool process_record_user(uint16_t keycode, keyrecord_t *record){
    const uint8_t mods = get_mods();
    const uint8_t oneshot_mods = get_oneshot_mods();

    switch (keycode) {
        case SELECT_LINE:
            if (record->event.pressed ){
                tap_code(KC_HOME);
                tap_code16(LSFT(KC_END));
            }

            return false;
        case NEXT_SENTENCE:
            if (record->event.pressed) {
                SEND_STRING(". ");
                add_oneshot_mods(MOD_BIT(KC_LSFT));
            }

            return false;
        case ARROW:
            if (record->event.pressed) {
                if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {
                    del_oneshot_mods(MOD_MASK_SHIFT);
                    unregister_mods(MOD_MASK_SHIFT);
                    SEND_STRING("=>");
                    register_mods(mods);
                } else {
                    SEND_STRING("->");
                }
            }

            return false;
    }

    return true;
}



